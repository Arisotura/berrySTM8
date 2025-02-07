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

    switch (Num)
    {
    case 2: IntNum = 19; break;
    case 3: IntNum = 21; break;
    case 5: IntNum = 27; break;
    }
}

STM8GPTimer::~STM8GPTimer()
{
}

void STM8GPTimer::Reset()
{
    Cnt[0] = 0;
    Cnt[1] = 0;
    Status[0] = 0;
    Status[1] = 0;
    IntEnable = 0;

    Counter = 0;
    ReloadVal = 0xFFFF;

    PrescalerReg = 0;
    Prescaler = 2;

    PreCount = 0;
}


void STM8GPTimer::Run(int cycles)
{
    if (!(Cnt[0] & (1<<0)))
    {
        // not running
        return;
    }

    PreCount += cycles;
    while (PreCount >= Prescaler)
    {
        PreCount -= Prescaler;

        if (Cnt[0] & (1<<4))
        {
            // count down

            if (Counter == 0)
                UpdateEvent();
            else
                Counter--;
        }
        else
        {
            // count up

            if (Counter == ReloadVal)
                UpdateEvent();
            else
                Counter++;
        }
    }
}

void STM8GPTimer::UpdateEvent()
{
    //printf("TIM%d UPDATE\n", Num);
    Status[0] |= (1<<0);
    PreCount = 0;

    if (Cnt[0] & (1<<4))
        Counter = ReloadVal;
    else
        Counter = 0;

    if (IntEnable & (1<<0))
        TriggerIRQ();
}

void STM8GPTimer::TriggerIRQ()
{
    STM->TriggerIRQ(IntNum);
}


u8 STM8GPTimer::IORead(u32 addr)
{
    addr -= IOBase;
    switch (addr)
    {
    case 0x00: return Cnt[0];
    case 0x01: return Cnt[1];
    case 0x05: return IntEnable;
    case 0x06: return Status[0];
    case 0x07: return Status[1];
    case 0x0C: return Counter >> 8;
    case 0x0D: return Counter & 0xFF;
    case 0x0E: return PrescalerReg;
    case 0x0F: return ReloadVal >> 8;
    case 0x10: return ReloadVal & 0xFF;
    }

    printf("TIM%d: unknown read %06X  %06X\n", Num, IOBase+addr, STM->GetPC());
    return 0;
}

void STM8GPTimer::IOWrite(u32 addr, u8 val)
{
    addr -= IOBase;
    switch (addr)
    {
    case 0x00:
        Cnt[0] = val;
        printf("%06X TIM%d CNT=%02X\n", STM->GetPC(), Num, val);
        if (val & 0xFE) printf("TIM%d: UNSUPPORTED CNT1 %02X\n", Num, val);
        return;
    case 0x01:
        Cnt[1] = val & 0xF8;
        if (val) printf("TIM%d: UNSUPPORTED CNT2 %02X\n", Num, val);
        return;

    case 0x05:
        IntEnable = val & 0xC7;
        return;

    case 0x06:
        Status[0] &= val;
        return;
    case 0x07:
        Status[1] &= val;
        return;

    case 0x08:
        if (val & (1<<0))
        {
            if ((Cnt[0] & 0x06) == 0x00) // URS and UDIS = 0
                UpdateEvent();
        }
        if (val & 0xFE) printf("TIM%d: EVENT GEN %02X\n", Num, val);
        return;

    case 0x0C:
        Counter = (Counter & 0x00FF) | (val << 8);
        return;
    case 0x0D:
        Counter = (Counter & 0xFF00) | val;
        return;

    case 0x0E:
        PrescalerReg = val & 0x07;
        Prescaler = 1 << PrescalerReg;
        return;

    case 0x0F:
        ReloadVal = (ReloadVal & 0x00FF) | (val << 8);
        return;
    case 0x10:
        ReloadVal = (ReloadVal & 0xFF00) | val;
        return;
    }

    printf("TIM%d: unknown write %06X %02X\n", Num, IOBase+addr, val);
}
