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
}

STM8::~STM8()
{
    delete DMA;
}

void STM8::Reset()
{
    CPUReset();

    memset(RAM, 0, RAMSize);

    FLASH_PUKR = 0;
    FLASH_DUKR = 0;
    FLASH_IAPSR = 0x40;

    DMA->Reset();
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
    CC = 0;
}


void STM8::CPUJumpTo(u32 addr)
{
    //printf("branch %06X -> %06X\n", PC, addr);
    PC = addr & 0xFFFFFF;
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

        //printf("PC=%06X A=%02X X=%04X Y=%04X SP=%04X CC=%02X\n", PC, A, X,Y, SP, CC);

        // this will do the job for most cases
        // instructions are supposed to have decode cycles and execute cycles, but
        // the documentation isn't complete
        count += cy;//(cy - 1);
    }

    return count;
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
        printf("STM8: RAM read %04X %02X\n", addr, RAM[addr]);
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

    if (addr == 0x4808) return 2; // hack

    printf("STM8: unknown read %06X\n", addr);
    return 0;
}

void STM8::MemWrite(u32 addr, u8 val)
{
    if (addr < RAMSize)
    {
        printf("STM8: RAM write %04X %02X\n", addr, val);
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
    }

    printf("STM8: unknown IO write %06X %02X\n", addr, val);
}
