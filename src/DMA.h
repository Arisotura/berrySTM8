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

#ifndef DMA_H
#define DMA_H

class STM8DMA : public STM8Device
{
public:
    STM8DMA(STM8* stm, u32 base);
    ~STM8DMA() override;
    void Reset() override;

    u8 IORead(u32 addr) override;
    void IOWrite(u32 addr, u8 val) override;

private:
    u8 Cnt;
    u8 IntStatus;

    u8 ChanCnt[4];
    u8 ChanStatus[4];
    u8 ChanLength[4];
    u32 ChanPAddr[4];   // peripheral address, or memory 1 address for chan 3
    u32 ChanMAddr[4];   // memory address, or memory 0 address for chan 3

    u8 ChanReloadLength[4];
    u32 ChanCurPAddr[4];
    u32 ChanCurMAddr[4];

    void SetCnt(u8 val);

    bool ChanIsRunning(int chan)
    {
        if (!(Cnt & (1<<0))) return false;
        if (!(ChanCnt[chan] & (1<<0))) return false;
        if (!(ChanStatus[chan] & (1<<7))) return false;
        return true;
    }

    void SetChanCnt(int chan, u8 val);
    void SetChanStatus(int chan, u8 val);

    void KickDMA(int chan);
    void RunMemoryDMA(int chan);
};

#endif // DMA_H
