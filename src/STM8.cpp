/*
    Copyright 2024 Arisotura

    This file is part of berrySTM8.

    berrySTM8 is free software: you can redistribute it and/or modify it under
    the terms of the GNU General Public License as published by the Free
    Software Foundation, either version 3 of the License, or (at your option)
    any later version.

    berrySTM8 is distributed in the hope that it will be useful, but WITHOUT ANY
    WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
    FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with berrySTM8. If not, see http://www.gnu.org/licenses/.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "STM8.h"
#include "DMA.h"
#include "I2C.h"
#include "GPTimer.h"


STM8::STM8()
{
    // TODO: make these customizable based on some model ID or w/e
    RAMSize = 0x1000;
    EEPROMSize = 0x800;
    FLASHSize = 0x10000;

    EEPROMStart = 0x1000;
    EEPROMEnd = EEPROMStart + EEPROMSize;

    FLASHEnd = 0x8000 + FLASHSize;

    RAMMask = RAMSize - 1;
    EEPROMMask = EEPROMSize - 1;
    FLASHMask = FLASHSize - 1;

    RAM = new u8[RAMSize];
    EEPROM = new u8[EEPROMSize];
    FLASH = new u8[FLASHSize];

    memset(RAM, 0, RAMSize);
    memset(EEPROM, 0, EEPROMSize);
    memset(FLASH, 0, FLASHSize);

    memset(IORegisters, 0, sizeof(IORegisters));

    DMA = new STM8DMA(this, 0x5070);
    I2C = new STM8I2C(this, 0x5210);

    TIM2 = new STM8GPTimer(this, 0x5250, 2);
    TIM3 = new STM8GPTimer(this, 0x5280, 3);
    TIM5 = new STM8GPTimer(this, 0x5300, 5);
}

STM8::~STM8()
{
    delete TIM2;
    delete TIM3;
    delete TIM5;

    delete I2C;
    delete DMA;
}

void STM8::Reset()
{
    CPUReset();

    for (int i = 0; i < 30; i++)
        IntPrio[i] = 3;
    IntMask = 0;

    memset(RAM, 0, RAMSize);

    FLASH_PUKR = 0;
    FLASH_DUKR = 0;
    FLASH_IAPSR = 0x40;

    ClkEnable[0] = 0x00;
    ClkEnable[1] = 0x80;
    ClkEnable[2] = 0x00;

    DMA->Reset();
    I2C->Reset();

    TIM2->Reset();
    TIM3->Reset();
    TIM5->Reset();
}


bool STM8::LoadImage(int type, const char* filename)
{
    FILE* f = fopen(filename, "rb");
    if (!f) return false;

    u8* dst; u32 len;
    switch (type)
    {
    case 0: dst = EEPROM; len = EEPROMSize; break;
    case 1: dst = FLASH;  len = FLASHSize;  break;
    default:
        fclose(f);
        return false;
    }

    fread(dst, len, 1, f);
    fclose(f);
    return true;
}


void STM8::CPUReset()
{
    A = 0;
    X = 0;
    Y = 0;
    SP = 0;
    PC = 0x8000;
    CC = 0x28;

    NextIRQ = -1;
}


void STM8::CPUJumpTo(u32 addr)
{
    //printf("branch %06X -> %06X\n", PC, addr);
    if (addr==0xBEFB) printf("fart %08X\n", PC);
    if (addr==0xBC2C) printf("i2cwrite %08X\n", PC);
    if (addr==0xBFAF) printf("BFAF! A=%02X X=%04X Y=%04X  @ %06X\n", A, X, Y, PC);
    PC = addr & 0xFFFFFF;
}

void STM8::CPUTriggerIRQ(int irq)
{
    printf("SERVICE IRQ %d %04X\n", irq, 0x8008+(irq<<2));

    MemWrite(SP--, PC & 0xFF);
    MemWrite(SP--, (PC >> 8) & 0xFF);
    MemWrite(SP--, PC >> 16);
    MemWrite(SP--, Y & 0xFF);
    MemWrite(SP--, Y >> 8);
    MemWrite(SP--, X & 0xFF);
    MemWrite(SP--, X >> 8);
    MemWrite(SP--, A);
    MemWrite(SP--, CC);

    u8 prio = IntPrio[irq];
    CC &= ~(Flag_I0|Flag_I1);
    CC |= ((prio & 0x1) << 3) | ((prio & 0x2) << 4);

    CPUJumpTo(0x8008 + (irq<<2));
    // TODO: the exception should probably take some cycles to be processed
}

u8 STM8::CPUFetch()
{
    u8 ret = MemRead(PC);
    PC++; PC &= 0xFFFFFF;
    return ret;
}

template<STM8::OperandType op, bool indY>
u32 STM8::CPUFetchOpAddr()
{
    u32 addr, ptr;
    u16 index = indY ? Y : X;

    switch (op)
    {
    case STM8::Op_ShortDirect:
        addr = CPUFetch();
        break;

    case STM8::Op_LongDirect:
        addr = (CPUFetch() << 8);
        addr |= CPUFetch();
        break;

    case STM8::Op_ExtendedDirect:
        addr = CPUFetch() << 16;
        addr |= (CPUFetch() << 8);
        addr |= CPUFetch();
        break;

    case STM8::Op_Ind:
        addr = index;
        break;

    case STM8::Op_ShortDirectInd:
        addr = CPUFetch();
        addr += index;
        break;

    case STM8::Op_LongDirectInd:
        addr = (CPUFetch() << 8);
        addr |= CPUFetch();
        addr += index;
        break;

    case STM8::Op_ExtendedDirectInd:
        addr = CPUFetch() << 16;
        addr |= (CPUFetch() << 8);
        addr |= CPUFetch();
        addr += index;
        break;

    case STM8::Op_ShortDirectSP:
        addr = CPUFetch();
        addr += SP;
        break;

    case STM8::Op_ShortIndirect:
        ptr = CPUFetch();
        addr = (MemRead(ptr) << 8) | MemRead(ptr+1);
        break;

    case STM8::Op_LongIndirect:
        ptr = (CPUFetch() << 8);
        ptr |= CPUFetch();
        addr = (MemRead(ptr) << 8) | MemRead(ptr+1);
        break;

    case STM8::Op_ExtendedIndirect:
        ptr = (CPUFetch() << 8);
        ptr |= CPUFetch();
        addr = (MemRead(ptr) << 16) | (MemRead(ptr+1) << 8) | MemRead(ptr+2);
        break;

    case STM8::Op_ShortIndirectInd:
        ptr = CPUFetch();
        addr = (MemRead(ptr) << 8) | MemRead(ptr+1);
        addr += index;
        break;

    case STM8::Op_LongIndirectInd:
        ptr = (CPUFetch() << 8);
        ptr |= CPUFetch();
        addr = (MemRead(ptr) << 8) | MemRead(ptr+1);
        addr += index;
        break;

    case STM8::Op_ExtendedIndirectInd:
        ptr = (CPUFetch() << 8);
        ptr |= CPUFetch();
        addr = (MemRead(ptr) << 16) | (MemRead(ptr+1) << 8) | MemRead(ptr+2);
        addr += index;
        break;
    }

    return addr;
}

#define DeclTemplate(op) \
    template u32 STM8::CPUFetchOpAddr<STM8::op, false>(); \
    template u32 STM8::CPUFetchOpAddr<STM8::op, true>();

DeclTemplate(Op_ShortDirect)
DeclTemplate(Op_LongDirect)
DeclTemplate(Op_ExtendedDirect)
DeclTemplate(Op_Ind)
DeclTemplate(Op_ShortDirectInd)
DeclTemplate(Op_ShortDirectSP)
DeclTemplate(Op_LongDirectInd)
DeclTemplate(Op_ExtendedDirectInd)
DeclTemplate(Op_ShortIndirect)
DeclTemplate(Op_LongIndirect)
DeclTemplate(Op_ExtendedIndirect)
DeclTemplate(Op_ShortIndirectInd)
DeclTemplate(Op_LongIndirectInd)
DeclTemplate(Op_ExtendedIndirectInd)

#undef DeclTemplate


int STM8::CPUExecute(int cycles)
{
    int count = 0;
    while (count < cycles)
    {
        u8 op = CPUFetch();
        _lastop = op; // debug
        int cy = (this->*InstrTable[op])();

        printf("PC=%06X A=%02X X=%04X Y=%04X SP=%04X CC=%02X\n", PC, A, X,Y, SP, CC);

        // this will do the job for most cases
        // instructions are supposed to have decode cycles and execute cycles, but
        // the documentation isn't complete
        count += cy;//(cy - 1);

        RunDevices(cy);

        if (NextIRQ != -1)
        {
            CPUTriggerIRQ(NextIRQ);
            NextIRQ = -1;
        }
    }

    return count;
}


void STM8::RunDevices(int cycles)
{
    if (ClkEnable[0] & (1<<0)) TIM2->Run(cycles);
    if (ClkEnable[0] & (1<<1)) TIM3->Run(cycles);
    if (ClkEnable[2] & (1<<1)) TIM5->Run(cycles);
}


void STM8::TriggerIRQ(int irq)
{
    IntMask |= (1<<irq);
    UpdateIRQ();
}

void STM8::UpdateIRQ()
{
    u8 priolevels[4] = {2, 1, 0, 3};
    u8 curprio = ((CC >> 3) & 0x1) | ((CC >> 4) & 0x2);
    u8 curlev = priolevels[curprio];

    for (int j = 3; j > 0; j--)
    {
        for (int i = 0; i < 30; i++)
        {
            if (!(IntMask & (1<<i)))
                continue;

            u8 irqprio = IntPrio[i];
            u8 irqlev = priolevels[irqprio];
            if (irqlev != j)
                continue;
            if (irqlev <= curlev) // checkme
                continue;

            NextIRQ = i;
            IntMask &= ~(1<<i); // checkme
            printf("triggering IRQ %d\n", i);
            return;
        }
    }
}


void STM8::MapIORange(STM8Device* dev, u32 start, u32 end)
{
    start &= 0xFFF;
    end &= 0xFFF;

    for (u32 addr = start; addr <= end; addr++)
        IORegisters[addr] = dev;
}


u8 STM8::MemRead(u32 addr)
{
    if (addr < RAMSize)
    {
        //printf("STM8: RAM read %04X %02X\n", addr, RAM[addr]);
        return RAM[addr];
    }
    else if ((addr >= EEPROMStart) && (addr < EEPROMEnd))
    {
        return EEPROM[addr - EEPROMStart];
    }
    else if ((addr >= FLASHStart) && (addr < FLASHEnd))
    {
        return FLASH[addr - FLASHStart];
    }
    else if ((addr >= 0x5000) && (addr < 0x5800))
    {
        return IORead(addr);
    }

    switch (addr)
    {
    case 0x4808: return 2; // hack (option byte)

    case 0x7F70: return IntPrio[0] | (IntPrio[1] << 2) | (IntPrio[2] << 4) | (IntPrio[3] << 6);
    case 0x7F71: return IntPrio[4] | (IntPrio[5] << 2) | (IntPrio[6] << 4) | (IntPrio[7] << 6);
    case 0x7F72: return IntPrio[8] | (IntPrio[9] << 2) | (IntPrio[10] << 4) | (IntPrio[11] << 6);
    case 0x7F73: return IntPrio[12] | (IntPrio[13] << 2) | (IntPrio[14] << 4) | (IntPrio[15] << 6);
    case 0x7F74: return IntPrio[16] | (IntPrio[17] << 2) | (IntPrio[18] << 4) | (IntPrio[19] << 6);
    case 0x7F75: return IntPrio[20] | (IntPrio[21] << 2) | (IntPrio[22] << 4) | (IntPrio[23] << 6);
    case 0x7F76: return IntPrio[24] | (IntPrio[25] << 2) | (IntPrio[26] << 4) | (IntPrio[27] << 6);
    case 0x7F77: return IntPrio[28] | (IntPrio[29] << 2) | 0xF0;
    }

    printf("STM8: unknown read %06X\n", addr);
    return 0;
}

void STM8::MemWrite(u32 addr, u8 val)
{
    if (addr < RAMSize)
    {
        //printf("STM8: RAM write %04X %02X\n", addr, val);
        RAM[addr] = val;
        return;
    }
    else if ((addr >= EEPROMStart) && (addr < EEPROMEnd))
    {
        if (!(FLASH_IAPSR & (1<<3))) return;

        printf("STM8: EEPROM write %04X %02X\n", addr, val);
        EEPROM[addr - EEPROMStart] = val;
        FLASH_IAPSR |= (1<<2);
        return;
    }
    else if ((addr >= FLASHStart) && (addr < FLASHEnd))
    {
        if (!(FLASH_IAPSR & (1<<1))) return;

        printf("STM8: FLASH write %04X %02X\n", addr, val);
        FLASH[addr - FLASHStart] = val;
        FLASH_IAPSR |= (1<<2);
        return;
    }
    else if ((addr >= 0x5000) && (addr < 0x5800))
    {
        IOWrite(addr, val);
        return;
    }

    switch (addr)
    {
    case 0x7F70:
        if ((val & 0x03) != 0x02) IntPrio[0] = val & 0x3;
        if ((val & 0x0C) != 0x08) IntPrio[1] = (val >> 2) & 0x3;
        if ((val & 0x30) != 0x20) IntPrio[2] = (val >> 4) & 0x3;
        if ((val & 0xC0) != 0x80) IntPrio[3] = val >> 6;
        return;
    case 0x7F71:
        if ((val & 0x03) != 0x02) IntPrio[4] = val & 0x3;
        if ((val & 0x0C) != 0x08) IntPrio[5] = (val >> 2) & 0x3;
        if ((val & 0x30) != 0x20) IntPrio[6] = (val >> 4) & 0x3;
        if ((val & 0xC0) != 0x80) IntPrio[7] = val >> 6;
        return;
    case 0x7F72:
        if ((val & 0x03) != 0x02) IntPrio[8] = val & 0x3;
        if ((val & 0x0C) != 0x08) IntPrio[9] = (val >> 2) & 0x3;
        if ((val & 0x30) != 0x20) IntPrio[10] = (val >> 4) & 0x3;
        if ((val & 0xC0) != 0x80) IntPrio[11] = val >> 6;
        return;
    case 0x7F73:
        if ((val & 0x03) != 0x02) IntPrio[12] = val & 0x3;
        if ((val & 0x0C) != 0x08) IntPrio[13] = (val >> 2) & 0x3;
        if ((val & 0x30) != 0x20) IntPrio[14] = (val >> 4) & 0x3;
        if ((val & 0xC0) != 0x80) IntPrio[15] = val >> 6;
        return;
    case 0x7F74:
        if ((val & 0x03) != 0x02) IntPrio[16] = val & 0x3;
        if ((val & 0x0C) != 0x08) IntPrio[17] = (val >> 2) & 0x3;
        if ((val & 0x30) != 0x20) IntPrio[18] = (val >> 4) & 0x3;
        if ((val & 0xC0) != 0x80) IntPrio[19] = val >> 6;
        return;
    case 0x7F75:
        if ((val & 0x03) != 0x02) IntPrio[20] = val & 0x3;
        if ((val & 0x0C) != 0x08) IntPrio[21] = (val >> 2) & 0x3;
        if ((val & 0x30) != 0x20) IntPrio[22] = (val >> 4) & 0x3;
        if ((val & 0xC0) != 0x80) IntPrio[23] = val >> 6;
        return;
    case 0x7F76:
        if ((val & 0x03) != 0x02) IntPrio[24] = val & 0x3;
        if ((val & 0x0C) != 0x08) IntPrio[25] = (val >> 2) & 0x3;
        if ((val & 0x30) != 0x20) IntPrio[26] = (val >> 4) & 0x3;
        if ((val & 0xC0) != 0x80) IntPrio[27] = val >> 6;
        return;
    case 0x7F77:
        if ((val & 0x03) != 0x02) IntPrio[28] = val & 0x3;
        if ((val & 0x0C) != 0x08) IntPrio[29] = (val >> 2) & 0x3;
        return;
    }

    printf("STM8: unknown write %06X %02X\n", addr, val);
}


u8 STM8::IORead(u32 addr)
{
    auto dev = IORegisters[addr & 0x7FF];
    if (dev)
        return dev->IORead(addr);

    // TODO remove these hacks
    switch (addr)
    {
    case 0x5054: return FLASH_IAPSR;
    case 0x50C3: return ClkEnable[0];
    case 0x50C4: return ClkEnable[1];
    case 0x50D0: return ClkEnable[2];
    case 0x514C: return 4;
    case 0x53C3: return 3; // HACK
    }

    printf("STM8: unknown IO read %06X\n", addr);
    return 0;
}

void STM8::IOWrite(u32 addr, u8 val)
{
    auto dev = IORegisters[addr & 0x7FF];
    if (dev)
        return dev->IOWrite(addr, val);

    // TODO: move these to their own devices
    // or atleast don't hardcode the addresses
    switch (addr)
    {
    case 0x5052:
        if ((FLASH_PUKR == 0x56) && (val == 0xAE))
        {
            FLASH_IAPSR |= (1<<1);
            FLASH_PUKR = 0;
        }
        else if (val == 0x56)
        {
            FLASH_PUKR = 0x56;
        }
        else
        {
            FLASH_PUKR = 0;
        }
        return;

    case 0x5053:
        if ((FLASH_PUKR == 0xAE) && (val == 0x56))
        {
            FLASH_IAPSR |= (1<<3);
            FLASH_PUKR = 0;
        }
        else if (val == 0xAE)
        {
            FLASH_PUKR = 0xAE;
        }
        else
        {
            FLASH_PUKR = 0;
        }
        return;

    case 0x50C3: ClkEnable[0] = val; return;
    case 0x50C4: ClkEnable[1] = val; return;
    case 0x50D0: ClkEnable[2] = val; return;
    }

    printf("STM8: unknown IO write %06X %02X\n", addr, val);
}
