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
    MapIORange(0x00, 0x2A);
}

STM8DMA::~STM8DMA()
{
}

void STM8DMA::Reset()
{
    Cnt = 0xFC;
    IntStatus = 0;

    for (int i = 0; i < 4; i++)
    {
        ChanCnt[i] = 0;
        ChanStatus[i] = 0;
        ChanLength[i] = 0;
        ChanPAddr[i] = (i == 3) ? 0x4000 : 0x5200;
        ChanMAddr[i] = 0;
    }
}


u8 STM8DMA::IORead(u32 addr)
{
    addr -= IOBase;
    switch (addr)
    {
    case 0x00: return Cnt;
    case 0x01: return IntStatus;

    case 0x05: return ChanCnt[0];
    case 0x06: return ChanStatus[0];
    case 0x07: return ChanLength[0];
    case 0x08: return (ChanPAddr[0] >> 8) & 0xFF;
    case 0x09: return ChanPAddr[0] & 0xFF;
    case 0x0B: return (ChanMAddr[0] >> 8) & 0xFF;
    case 0x0C: return ChanMAddr[0] & 0xFF;

    case 0x0F: return ChanCnt[1];
    case 0x10: return ChanStatus[1];
    case 0x11: return ChanLength[1];
    case 0x12: return (ChanPAddr[1] >> 8) & 0xFF;
    case 0x13: return ChanPAddr[1] & 0xFF;
    case 0x15: return (ChanMAddr[1] >> 8) & 0xFF;
    case 0x16: return ChanMAddr[1] & 0xFF;

    case 0x19: return ChanCnt[2];
    case 0x1A: return ChanStatus[2];
    case 0x1B: return ChanLength[2];
    case 0x1C: return (ChanPAddr[2] >> 8) & 0xFF;
    case 0x1D: return ChanPAddr[2] & 0xFF;
    case 0x1F: return (ChanMAddr[2] >> 8) & 0xFF;
    case 0x20: return ChanMAddr[2] & 0xFF;

    case 0x23: return ChanCnt[3];
    case 0x24: return ChanStatus[3];
    case 0x25: return ChanLength[3];
    case 0x26: return (ChanPAddr[3] >> 8) & 0xFF;
    case 0x27: return ChanPAddr[3] & 0xFF;
    case 0x28: return (ChanMAddr[3] >> 16) & 0x01;
    case 0x29: return (ChanMAddr[3] >> 8) & 0xFF;
    case 0x2A: return ChanMAddr[3] & 0xFF;
    }

    printf("DMA: unknown read %04X\n", addr+IOBase);
    return 0;
}

void STM8DMA::IOWrite(u32 addr, u8 val)
{
    addr -= IOBase;
    switch (addr)
    {
    case 0x00: SetCnt(val); return;
    case 0x01: return;

    case 0x05: SetChanCnt(0, val); return;
    case 0x06: SetChanStatus(0, val); return;
    case 0x07:
        if (ChanIsRunning(0)) return;
        ChanLength[0] = val;
        return;
    case 0x08:
        if (ChanIsRunning(0)) return;
        ChanPAddr[0] = (ChanPAddr[0] & 0x00FF) | 0x5200 | ((val & 0x01) << 8);
        return;
    case 0x09:
        if (ChanIsRunning(0)) return;
        ChanPAddr[0] = (ChanPAddr[0] & 0xFF00) | val;
        return;
    case 0x0B:
        if (ChanIsRunning(0)) return;
        ChanMAddr[0] = (ChanMAddr[0] & 0x00FF) | ((val & 0x0F) << 8);
        return;
    case 0x0C:
        if (ChanIsRunning(0)) return;
        ChanMAddr[0] = (ChanMAddr[0] & 0xFF00) | val;
        return;

    case 0x0F: SetChanCnt(1, val); return;
    case 0x10: SetChanStatus(1, val); return;
    case 0x11:
        if (ChanIsRunning(1)) return;
        ChanLength[1] = val;
        return;
    case 0x12:
        if (ChanIsRunning(1)) return;
        ChanPAddr[1] = (ChanPAddr[1] & 0x00FF) | 0x5200 | ((val & 0x01) << 8);
        return;
    case 0x13:
        if (ChanIsRunning(1)) return;
        ChanPAddr[1] = (ChanPAddr[1] & 0xFF00) | val;
        return;
    case 0x15:
        if (ChanIsRunning(1)) return;
        ChanMAddr[1] = (ChanMAddr[1] & 0x00FF) | ((val & 0x0F) << 8);
        return;
    case 0x16:
        if (ChanIsRunning(1)) return;
        ChanMAddr[1] = (ChanMAddr[1] & 0xFF00) | val;
        return;

    case 0x19: SetChanCnt(2, val); return;
    case 0x1A: SetChanStatus(2, val); return;
    case 0x1B:
        if (ChanIsRunning(2)) return;
        ChanLength[2] = val;
        return;
    case 0x1C:
        if (ChanIsRunning(2)) return;
        ChanPAddr[2] = (ChanPAddr[2] & 0x00FF) | 0x5200 | ((val & 0x01) << 8);
        return;
    case 0x1D:
        if (ChanIsRunning(2)) return;
        ChanPAddr[2] = (ChanPAddr[2] & 0xFF00) | val;
        return;
    case 0x1F:
        if (ChanIsRunning(2)) return;
        ChanMAddr[2] = (ChanMAddr[2] & 0x00FF) | ((val & 0x0F) << 8);
        return;
    case 0x20:
        if (ChanIsRunning(2)) return;
        ChanMAddr[2] = (ChanMAddr[2] & 0xFF00) | val;
        return;

    case 0x23: SetChanCnt(3, val); return;
    case 0x24: SetChanStatus(3, val); return;
    case 0x25:
        if (ChanIsRunning(3)) return;
        ChanLength[3] = val;
        return;
    case 0x26:
        if (ChanIsRunning(3)) return;
        if (ChanCnt[3] & (1<<6)) // MEM bit
            ChanPAddr[3] = (ChanPAddr[3] & 0x00FF) | ((val & 0x1F) << 8);
        else
            ChanPAddr[3] = (ChanPAddr[3] & 0x00FF) | 0x4000 | ((val & 0x1F) << 8);
        return;
    case 0x27:
        if (ChanIsRunning(3)) return;
        ChanPAddr[3] = (ChanPAddr[3] & 0xFF00) | val;
        return;
    case 0x28:
        // TODO: only for mid/high density devices
        if (ChanIsRunning(3)) return;
        ChanMAddr[3] = (ChanMAddr[3] & 0x0FFFF) | ((val & 0x01) << 16);
        return;
    case 0x29:
        if (ChanIsRunning(3)) return;
        ChanMAddr[3] = (ChanMAddr[3] & 0x100FF) | (val << 8);
        return;
    case 0x2A:
        if (ChanIsRunning(3)) return;
        ChanMAddr[3] = (ChanMAddr[3] & 0x1FF00) | val;
        return;
    }

    printf("DMA: unknown write %04X %02X\n", addr+IOBase, val);
}


void STM8DMA::SetCnt(u8 val)
{
    u8 oldcnt = Cnt;

    printf("GCNT=%02X (old=%02X)\n", val, Cnt);
    if (((Cnt & 0x03) == 0x03) && (val & (1<<0))) // GEN and GB set
        Cnt = (Cnt & 0xFE) | (val & 0x01);
    else
        Cnt = (Cnt & 0x02) | (val & 0xFD);

    if ((!(oldcnt & (1<<0))) && (Cnt & (1<<0)))
    {
        KickDMA(0);
        KickDMA(1);
        KickDMA(2);
        KickDMA(3);
    }
}


void STM8DMA::SetChanCnt(int chan, u8 val)
{
    if (ChanIsRunning(chan) && (val & (1<<0)))
        return;

    u8 oldcnt = ChanCnt[chan];

    if (chan == 3)
    {
        ChanCnt[chan] = val & 0x7F;

        if (val & (1<<6))
            ChanPAddr[chan] = (ChanPAddr[chan] & 0x1FFF);
        else
            ChanPAddr[chan] = (ChanPAddr[chan] & 0x1FFF) | 0x4000;
    }
    else
    {
        ChanCnt[chan] = val & 0x3F;
    }

    if ((!(oldcnt & (1<<0))) && (ChanCnt[chan] & (1<<0)))
        KickDMA(chan);
}

void STM8DMA::SetChanStatus(int chan, u8 val)
{
    if (!ChanIsRunning(chan))
        ChanStatus[chan] = (ChanStatus[chan] & 0xC6) | (val & 0x38);

    if (!(val & (1<<1))) ChanStatus[chan] &= ~(1<<1);
    if (!(val & (1<<2))) ChanStatus[chan] &= ~(1<<2);
}


void STM8DMA::KickDMA(int chan)
{
    if (!(Cnt & (1<<0))) return;
    if (!(ChanCnt[chan] & (1<<0))) return;

    printf("KICK DMA%d / GCNT=%02X IRQ=%02X / CNT=%02X STA=%02X P=%06X M=%06X LEN=%02X\n",
           chan, Cnt, IntStatus, ChanCnt[chan], ChanStatus[chan], ChanPAddr[chan], ChanMAddr[chan], ChanLength[chan]);

    ChanReloadLength[chan] = ChanLength[chan];
    ChanCurPAddr[chan] = ChanPAddr[chan];
    ChanCurMAddr[chan] = ChanMAddr[chan];

    if (Cnt & (1<<6))
    {
        RunMemoryDMA(chan);
    }
    else
    {
        // TODO
    }
}

void STM8DMA::RunMemoryDMA(int chan)
{
    if (chan != 3)
    {
        printf("DMA: ????\n");
        return;
    }

    // TODO: not make this instant, eventually

    int srcinc = 1;
    int dstinc = (ChanCnt[chan] & (1<<5)) ? 1 : -1;

    if (ChanStatus[chan] & (1<<3))
    {
        // 16-bit transfer

        while (ChanLength[chan] != 0)
        {
            u8 msb = STM->MemRead(ChanCurMAddr[chan]);
            ChanCurMAddr[chan] += srcinc;
            ChanCurMAddr[chan] &= 0x1FFFF;

            u8 lsb = STM->MemRead(ChanCurMAddr[chan]);
            ChanCurMAddr[chan] += srcinc;
            ChanCurMAddr[chan] &= 0x1FFFF;

            STM->MemWrite(ChanCurPAddr[chan], msb);
            ChanCurPAddr[chan] += dstinc;
            ChanCurPAddr[chan] &= 0x1FFF;

            STM->MemWrite(ChanCurPAddr[chan], lsb);
            ChanCurPAddr[chan] += dstinc;
            ChanCurPAddr[chan] &= 0x1FFF;

            ChanLength[chan] -= 2;

            if (ChanLength[chan] == 1)
            {
                printf("DMA: bad length %02X for 16-bit transfer\n", ChanReloadLength[chan]);
                break;
            }
        }
    }
    else
    {
        // 8-bit transfer

        while (ChanLength[chan] != 0)
        {
            u8 val = STM->MemRead(ChanCurMAddr[chan]);
            ChanCurMAddr[chan] += srcinc;
            ChanCurMAddr[chan] &= 0x1FFFF;

            STM->MemWrite(ChanCurPAddr[chan], val);
            ChanCurPAddr[chan] += dstinc;
            ChanCurPAddr[chan] &= 0x1FFF;

            ChanLength[chan]--;
        }
    }

    ChanStatus[chan] |= (1<<2); // half transaction flag
    ChanStatus[chan] |= (1<<1); // end of transaction flag

    // TODO: raise interrupt
}
