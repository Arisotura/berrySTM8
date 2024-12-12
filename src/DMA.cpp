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
#include "STM8.h"
#include "DMA.h"


STM8DMA::STM8DMA(STM8* stm, u32 iobase) : STM8Device(stm, iobase)
{
    MapIORange(0x00, 0x01);
    MapIORange(0x05, 0x09); MapIORange(0x0B, 0x0C);
    MapIORange(0x0F, 0x13); MapIORange(0x15, 0x16);
    MapIORange(0x19, 0x1D); MapIORange(0x1F, 0x20);
    MapIORange(0x23, 0x2A);
}

STM8DMA::~STM8DMA()
{
    //
}

void STM8DMA::Reset()
{
    //
}


u8 STM8DMA::IORead(u32 addr)
{
    addr -= IOBase;

    //

    printf("DMA unk read %04X\n", addr+IOBase);
    return 0;
}

void STM8DMA::IOWrite(u32 addr, u8 val)
{
    addr -= IOBase;

    //

    printf("DMA unk write %04X %02X\n", addr+IOBase, val);
}
