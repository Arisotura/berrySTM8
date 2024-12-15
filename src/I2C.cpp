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
#include "I2C.h"


STM8I2C::STM8I2C(STM8* stm, u32 iobase) : STM8Device(stm, iobase)
{
    MapIORange(0x00, 0x0E);
}

STM8I2C::~STM8I2C()
{
}

void STM8I2C::Reset()
{
    Cnt[0] = 0;
    Cnt[1] = 0;
    Freq = 0;
    OwnAddr[0] = 0;
    OwnAddr[1] = 0;
    OwnAddr[2] = 0;
    Data = 0;
    Status[0] = 0;
    Status[1] = 0;
    Status[2] = 0;
    IntCnt = 0;
    ClockCnt = 0x000B;
    TRISE = 0x02;
    PEC = 0;
}


u8 STM8I2C::IORead(u32 addr)
{
    addr -= IOBase;
    switch (addr)
    {
    case 0x00: return Cnt[0];
    case 0x01: return Cnt[1];
    case 0x02: return Freq;
    case 0x03: return OwnAddr[0];
    case 0x04: return OwnAddr[1];
    case 0x05: return OwnAddr[2];
    case 0x06: return Data; // TODO handle underrun/etc
    case 0x07: return Status[0];
    case 0x08: return Status[1];
    case 0x09: return Status[2];
    case 0x0A: return IntCnt;
    case 0x0B: return ClockCnt & 0xFF;
    case 0x0C: return ClockCnt >> 8;
    case 0x0D: return TRISE;
    case 0x0E: return PEC;
    }

    printf("I2C: unknown read %04X\n", addr+IOBase);
    return 0;
}

void STM8I2C::IOWrite(u32 addr, u8 val)
{
    addr -= IOBase;
    switch (addr)
    {
    case 0x00: SetCnt0(val); return;
    case 0x01: SetCnt1(val); return;
    }

    printf("I2C: unknown write %04X %02X\n", addr+IOBase, val);
}


void STM8I2C::SetCnt0(u8 val)
{
    printf("I2C: CNT0=%02X\n", val);

    Cnt[0] = val & 0xFB;
    // TODO most of the effects (PE bit etc)
}

void STM8I2C::SetCnt1(u8 val)
{
    printf("I2C: CNT1=%02X\n", val);

    Cnt[1] = val & 0xBF;

    if (Cnt[1] & (1<<0))
    {
        printf("I2C: START\n");
        Status[0] |= (1<<0); // signal start condition
    }
}
