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
#include "STM8.h"
#include "GPTimer.h"


STM8GPTimer::STM8GPTimer(STM8* stm, u32 iobase, u8 num) : STM8Device(stm, iobase), Num(num)
{
    MapIORange(0x00, 0x16);
}

STM8GPTimer::~STM8GPTimer()
{
}

void STM8GPTimer::Reset()
{
    //
}


u8 STM8GPTimer::IORead(u32 addr)
{
    addr -= IOBase;

    printf("TIM%d: unknown read %06X\n", Num, IOBase+addr);
    return 0;
}

void STM8GPTimer::IOWrite(u32 addr, u8 val)
{
    addr -= IOBase;

    printf("TIM%d: unknown write %06X %02X\n", Num, IOBase+addr, val);
}
