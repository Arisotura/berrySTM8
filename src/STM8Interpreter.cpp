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


/*u8 STM8::FetchOp8_Imm()
{
    return CPUFetch();
}

u8 STM8::FetchOp8_Dir8()
{
    u32 addr = CPUFetch();

    return MemRead(addr);
}

u8 STM8::FetchOp8_Dir16()
{
    u32 addr = (CPUFetch() << 8);
    addr |= CPUFetch();

    return MemRead(addr);
}

u8 STM8::FetchOp8_Dir24()
{
    u32 addr = (CPUFetch() << 16);
    addr |= (CPUFetch() << 8);
    addr |= CPUFetch();

    return MemRead(addr);
}

u8 STM8::FetchOp8_IndX()
{
    u32 addr = X;

    return MemRead(addr);
}

u8 STM8::FetchOp8_IndX_Dir8()
{
    u32 addr = CPUFetch();
    addr += X;

    return MemRead(addr);
}*/




void STM8::OP_UNK()
{
    printf("unknown opcode %04X @ %08X\n", _lastop, PC-1);
    exit(-1);
}


void STM8::OP_Prefix90()
{
    u8 op = CPUFetch();
    _lastop = 0x9000 | op; // debug
    (this->*InstrTable90[op])();
}
