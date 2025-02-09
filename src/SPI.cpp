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
#include "SPI.h"


STM8SPI::STM8SPI(STM8* stm, u32 iobase, u8 num) : STM8Device(stm, iobase), Num(num)
{
    MapIORange(0x00, 0x07);
}

STM8SPI::~STM8SPI()
{
    //
}

void STM8SPI::Reset()
{
    Cnt[0] = 0;
    Cnt[1] = 0;
    IntCnt = 0;
    Status = 0x02;
    RXData = 0;
    TXData = 0;
    CRCPoly = 0x07;
    RXCRC = 0;
    TXCRC = 0;

    CurRXData = 0;
    CurTXData = 0;
}


u8 STM8SPI::IORead(u32 addr)
{
    addr -= IOBase;
    switch (addr)
    {
    case 0x00: return Cnt[0];
    case 0x01: return Cnt[1];
    case 0x02: return IntCnt;
    case 0x03: return Status;
    case 0x04: return ReceiveData();
    case 0x05: return CRCPoly;
    case 0x06: return RXCRC;
    case 0x07: return TXCRC;
    }

    printf("SPI%d: unknown read %06X  %06X\n", Num, IOBase+addr, STM->GetPC());
    return 0;
}

void STM8SPI::IOWrite(u32 addr, u8 val)
{
    printf("SPI%d: write %06X %02X\n", Num, addr, val);
    addr -= IOBase;
    switch (addr)
    {
    case 0x00:
        Cnt[0] = val;
        return;
    case 0x01:
        Cnt[1] = val;
        return;
    case 0x02:
        IntCnt = val & 0xF3;
        return;
    case 0x03:
        Status &= (val | 0x87); // checkme
        return;
    case 0x04:
        SendData(val);
        return;
    case 0x05:
        CRCPoly = val;
        return;
    }

    printf("SPI%d: unknown write %06X %02X\n", Num, IOBase+addr, val);
}


void STM8SPI::SendData(u8 val)
{
    //
}

u8 STM8SPI::ReceiveData()
{
    //
    return 0;
}
