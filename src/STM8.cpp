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
}

STM8::~STM8()
{
    //
}

void STM8::Reset()
{
    CPUReset();

    memset(RAM, 0, RAMSize);
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


u8 STM8::CPUFetch()
{
    u8 ret = MemRead(PC);
    PC++; PC &= 0xFFFFFF;
    return ret;
}

u32 STM8::CPUExecute(u32 cycles)
{
    u32 count = 0;
    while (count < cycles)
    {
        u8 op = CPUFetch();
        // TODO!
        printf("STM8: OP %02X\n", op);

        exit(-1);
    }

    return count;
}


u8 STM8::MemRead(u32 addr)
{
    if (addr < RAMSize)
    {
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

    printf("STM8: unknown read %06X\n", addr);
    return 0;
}

void STM8::MemWrite(u32 addr, u8 val)
{
    if (addr < RAMSize)
    {
        RAM[addr] = val;
        return;
    }

    printf("STM8: unknown write %06X %02X\n", addr, val);
}
