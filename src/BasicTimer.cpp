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
#include "BasicTimer.h"


STM8BasicTimer::STM8BasicTimer(STM8* stm, u32 iobase, u8 num) : STM8Device(stm, iobase), Num(num)
{
    MapIORange(0x00, 0x09);

    IntNum = 25;
}

STM8BasicTimer::~STM8BasicTimer()
{
}

void STM8BasicTimer::Reset()
{
    Cnt[0] = 0;
    Cnt[1] = 0;
    Status = 0;
    IntEnable = 0;

    Counter = 0;
    ReloadVal = 0xFF;

    PrescalerReg = 0;
    Prescaler = 2;

    PreCount = 0;
}


void STM8BasicTimer::Run(int cycles)
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

        if (Counter == ReloadVal)
            UpdateEvent();
        else
            Counter++;
    }
}

void STM8BasicTimer::UpdateEvent()
{
    printf("TIM%d UPDATE  %02X %02X\n", Num, STM->MemRead(0x1A3), STM->MemRead(0x1A4));
    Status |= (1<<0);
    PreCount = 0;

    if (Cnt[0] & (1<<3)) // one-shot
        Cnt[0] &= ~(1<<0);

    Counter = 0;

    if (IntEnable & (1<<0))
        TriggerIRQ();
}

void STM8BasicTimer::TriggerIRQ()
{
    STM->TriggerIRQ(IntNum);
}


u8 STM8BasicTimer::IORead(u32 addr)
{
    addr -= IOBase;
    switch (addr)
    {
    case 0x00: return Cnt[0];
    case 0x01: return Cnt[1];
    case 0x04: return IntEnable;
    case 0x05: return Status;
    case 0x07: return Counter;
    case 0x08: return PrescalerReg;
    case 0x09: return ReloadVal;
    }

    printf("TIM%d: unknown read %06X  %06X\n", Num, IOBase+addr, STM->GetPC());
    return 0;
}

void STM8BasicTimer::IOWrite(u32 addr, u8 val)
{
    addr -= IOBase;
    switch (addr)
    {
    case 0x00:
        Cnt[0] = val & 0x8F;
        printf("%06X TIM%d CNT=%02X\n", STM->GetPC(), Num, val);
        if (val & 0xFE) printf("TIM%d: UNSUPPORTED CNT1 %02X\n", Num, val);
        return;
    case 0x01:
        Cnt[1] = val & 0x70;
        if (val) printf("TIM%d: UNSUPPORTED CNT2 %02X\n", Num, val);
        return;

    case 0x04:
        IntEnable = val & 0xC1;
        return;

    case 0x05:
        Status &= val;
        return;

    case 0x06:
        if (val & (1<<0))
        {
            if ((Cnt[0] & 0x06) == 0x00) // URS and UDIS = 0
                UpdateEvent();
        }
        if (val & 0xFE) printf("TIM%d: EVENT GEN %02X\n", Num, val);
        return;

    case 0x07:
        Counter = val;
        return;

    case 0x08:
        PrescalerReg = val & 0x0F;
        Prescaler = 1 << PrescalerReg;
        return;

    case 0x09:
        ReloadVal = val;
        return;
    }

    printf("TIM%d: unknown write %06X %02X\n", Num, IOBase+addr, val);
}
