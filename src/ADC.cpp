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
#include "ADC.h"


const char* ADC_Chan[] =
{
    "PA6", // 0
    "PA5", // 1
    "PA4", // 2
    "PC7", // 3
    "PC4", // 4
    "PC3", // 5
    "PC2", // 6
    "PD7", // 7
    "PD6", // 8
    "PD5", // 9
    "PD4", // 10
    "PB7", // 11
    "PB6", // 12
    "PB5", // 13
    "PB4", // 14
    "PB3", // 15
    "PB2", // 16
    "PB1", // 17
    "PB0", // 18
    "PD3", // 19
    "PD2", // 20
    "PD1", // 21
    "PD0", // 22
    "PE5", // 23
    "PF0", // 24
    "PF1", // 25
    "PF2", // 26
    "PF3", // 27
};


STM8ADC::STM8ADC(STM8* stm, u32 iobase) : STM8Device(stm, iobase)
{
    MapIORange(0x00, 0x11);
}

STM8ADC::~STM8ADC()
{
    //
}

void STM8ADC::Reset()
{
    Cnt[0] = 0;
    Cnt[1] = 0;
    Cnt[2] = 0x1F;
    Status = 0;
    Data = 0;
    HighThreshold = 0xFFF;
    LowThreshold = 0;
    ChanSequence = 0;
    TriggerDisable = 0;
}


u8 STM8ADC::IORead(u32 addr)
{
    addr -= IOBase;
    switch (addr)
    {
    case 0x00: return Cnt[0];
    case 0x01: return Cnt[1];
    case 0x02: return Cnt[2];
    case 0x03: return Status;
    case 0x04: return Data >> 8;
    case 0x05: return Data & 0xFF;
    case 0x06: return HighThreshold >> 8;
    case 0x07: return HighThreshold & 0xFF;
    case 0x08: return LowThreshold >> 8;
    case 0x09: return LowThreshold & 0xFF;
    case 0x0A: return ChanSequence >> 24;
    case 0x0B: return (ChanSequence >> 16) & 0xFF;
    case 0x0C: return (ChanSequence >> 8) & 0xFF;
    case 0x0D: return ChanSequence & 0xFF;
    case 0x0E: return TriggerDisable >> 24;
    case 0x0F: return (TriggerDisable >> 16) & 0xFF;
    case 0x10: return (TriggerDisable >> 8) & 0xFF;
    case 0x11: return TriggerDisable & 0xFF;
    }

    printf("ADC: unknown read %04X\n", addr+IOBase);
    return 0;
}

void STM8ADC::IOWrite(u32 addr, u8 val)
{
    addr -= IOBase;
    switch (addr)
    {
    case 0x00:
        SetCnt0(val);
        return;
    case 0x01:
        SetCnt1(val);
        return;
    case 0x02:
        SetCnt2(val);
        return;
    case 0x03:
        Status &= val;
        return;

    case 0x06:
        HighThreshold = (HighThreshold & 0x00FF) | ((val & 0x0F) << 8);
        return;
    case 0x07:
        HighThreshold = (HighThreshold & 0x0F00) | val;
        return;

    case 0x08:
        LowThreshold = (LowThreshold & 0x00FF) | ((val & 0x0F) << 8);
        return;
    case 0x09:
        LowThreshold = (LowThreshold & 0x0F00) | val;
        return;

    case 0x0A:
        ChanSequence = (ChanSequence & 0x00FFFFFF) | ((val & 0xBF) << 24);
        return;
    case 0x0B:
        ChanSequence = (ChanSequence & 0xFF00FFFF) | (val << 16);
        return;
    case 0x0C:
        ChanSequence = (ChanSequence & 0xFFFF00FF) | (val << 8);
        return;
    case 0x0D:
        ChanSequence = (ChanSequence & 0xFFFFFF00) | val;
        return;

    case 0x0E:
        TriggerDisable = (TriggerDisable & 0x00FFFFFF) | ((val & 0x3F) << 24);
        return;
    case 0x0F:
        TriggerDisable = (TriggerDisable & 0xFF00FFFF) | (val << 16);
        return;
    case 0x10:
        TriggerDisable = (TriggerDisable & 0xFFFF00FF) | (val << 8);
        return;
    case 0x11:
        TriggerDisable = (TriggerDisable & 0xFFFFFF00) | val;
        return;
    }

    printf("ADC: unknown write %04X %02X\n", addr+IOBase, val);
}


void STM8ADC::SetCnt0(u8 val)
{
    Cnt[0] = val;

    if (val & (1<<1))
    {
        // perform conversion

        if (val & (1<<2))
        {
            printf("ADC: !! CONTINUOUS MODE TODO\n");
            return;
        }

        if (!(ChanSequence & (1<<31)))
        {
            printf("ADC: !! DMA MODE TODO\n");
            return;
        }

        if (ChanSequence & (1<<29))
        {
            printf("ADC: !! TS CHANNEL TODO\n");
            return;
        }
        if (ChanSequence & (1<<28))
        {
            printf("ADC: !! VREF CHANNEL TODO\n");
            return;
        }

        int chan;
        for (chan = 27; chan >= 0; chan--)
        {
            if (ChanSequence & (1<<chan))
                break;
        }

        if (!(ChanSequence & (1<<chan)))
        {
            printf("ADC: no channel selected??\n");
            return;
        }

        printf("ADC: reading from channel %d (%s)\n", chan, ADC_Chan[chan]);

        u16 adcval = 0; // TODO: actually read inputs

        switch ((Cnt[0] >> 5) & 3)
        {
        case 0: break;                 // 12-bit
        case 1: adcval >>= 2; break;   // 10-bit
        case 2: adcval >>= 4; break;   // 8-bit
        case 3: adcval >>= 6; break;   // 6-bit
        }

        Data = adcval;

        Cnt[0] &= ~(1<<1);
        Status |= (1<<0);
        if (Cnt[0] & (1<<3))
            TriggerIRQ();
    }
}

void STM8ADC::SetCnt1(u8 val)
{
    Cnt[1] = val;
}

void STM8ADC::SetCnt2(u8 val)
{
    Cnt[2] = val;
}

void STM8ADC::TriggerIRQ()
{
    STM->TriggerIRQ(18);
}
