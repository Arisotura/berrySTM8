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
#include "GPIO.h"


STM8GPIO::STM8GPIO(STM8* stm, u32 iobase, u8 num) : STM8Device(stm, iobase), Num(num)
{
    MapIORange(0x00, 0x04);

    Port = 'A' + num;
}

STM8GPIO::~STM8GPIO()
{
    //
}

void STM8GPIO::Reset()
{
    Output = 0;
    Input = 0;
    Dir = 0;
    Cnt1 = (Num == 0) ? 0x01 : 0x00;
    Cnt2 = 0;
}


bool STM8GPIO::SetInput(u8 num, u8 val)
{
    u8 mask = (1<<num);
    u8 oldval = (Input & mask) ? 1 : 0;
    if (val) Input |= mask;
    else     Input &= ~mask;

    Update();

    if ((!(Dir & mask)) && (Cnt2 & mask))
    {
        // check for interrupt
        STM->NotifyExtIRQ(Num, num, oldval, val);
    }

    return false;
}

u8 STM8GPIO::GetOutput(u8 num)
{
    u8 mask = (1<<num);
    if (Output & mask) return 1;
    return 0;
}


void STM8GPIO::Update()
{
    // TODO do something!

    /*for (int i = 0; i < 8; i++)
    {
        u8 mask = (1<<i);

        if (Dir & mask)
        {
            // output
            printf("P%c%d: output, val=%d, %s, slope %s\n",
                   Port, i,
                   (Output & mask) ? 1 : 0,
                   (Cnt1 & mask) ? "push-pull" : "open drain",
                   (Cnt2 & mask) ? "fast" : "slow");
        }
        else
        {
            // input
            printf("P%c%d: input, %s, interrupt %s\n",
                   Port, i,
                   (Cnt1 & mask) ? "pull-up" : "floating",
                   (Cnt2 & mask) ? "enabled" : "disabled");
        }
    }*/
}


u8 STM8GPIO::IORead(u32 addr)
{
    addr -= IOBase;
    switch (addr)
    {
    case 0x00: return Output;
    case 0x01: return Input;
    case 0x02: return Dir;
    case 0x03: return Cnt1;
    case 0x04: return Cnt2;
    }

    printf("GPIO%d: unknown read %06X  %06X\n", Num, IOBase+addr, STM->GetPC());
    return 0;
}

void STM8GPIO::IOWrite(u32 addr, u8 val)
{
    addr -= IOBase;
    switch (addr)
    {
    case 0x00:
        Output = val;
        Update();
        return;
    case 0x01:
        return;
    case 0x02:
        Dir = val;
        Update();
        return;
    case 0x03:
        Cnt1 = val;
        Update();
        return;
    case 0x04:
        Cnt2 = val;
        Update();
        return;
    }

    printf("GPIO%d: unknown write %06X %02X\n", Num, IOBase+addr, val);
}
