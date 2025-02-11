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
#include "DMA.h"


const char* SPI_CS[2] = {"PB4", "PD7"};


STM8SPI::STM8SPI(STM8* stm, u32 iobase, u8 num) : STM8Device(stm, iobase), Num(num)
{
    MapIORange(0x00, 0x07);

    switch (num)
    {
    case 0: IntNum = 26; break;
    case 1: IntNum = 29; break;
    }
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

    SlaveSel = false;
    CurRXData = 0;
    CurTXData = 0;
}


bool STM8SPI::IsMaster()
{
    return (Cnt[0] & (1<<2));
}

void STM8SPI::UpdateMasterMode()
{
    if (!(Cnt[0] & (1<<2))) return;

    bool nss;
    if (Cnt[1] & (1<<1))
    {
        // software NSS
        nss = (Cnt[1] & (1<<0));
    }
    else
    {
        // hardware NSS
        nss = SlaveSel;
    }

    if (!nss)
    {
        // master mode fault, fall back to slave mode
        printf("SPI%d: master mode fault\n", Num);
        Cnt[0] &= ~(1<<6); // SPE
        Cnt[0] &= ~(1<<2); // MSTR
        Status |= (1<<5);  // MODF
        if (IntCnt & (1<<5)) // ERRIE
            TriggerIRQ();
    }
}


void STM8SPI::TriggerIRQ()
{
    STM->TriggerIRQ(IntNum);
}


void STM8SPI::SlaveSelect()
{
    SlaveSel = true;
    STM->SetInput(SPI_CS[Num], 0);
    UpdateMasterMode();
}

void STM8SPI::SlaveSend(u8 val)
{
    // TODO simulate transmission delay?
    // TODO buffer full case?
    // TODO: TX here is inaccurate (should be at the start of a byte, RX at the end)
    printf("SlaveSend(%02X): %02X\n", val, Status);
    if (!(Status & (1<<1)))
    {
        CurTXData = TXData;
        Status |= (1<<1);
        CheckTXDMA();
        if (IntCnt & (1<<7))
            TriggerIRQ();
    }

    RXData = val;

    Status |= (1<<0);
    CheckRXDMA();
    if (IntCnt & (1<<6))
        TriggerIRQ();
}

u8 STM8SPI::SlaveReceive()
{
    return CurTXData;
}

void STM8SPI::SlaveRelease()
{
    SlaveSel = false;
    STM->SetInput(SPI_CS[Num], 1);
}


void STM8SPI::CheckRXDMA()
{
    STM->DMA->CheckPeripheralDMA(Num ? 0 : 1);
}

void STM8SPI::CheckTXDMA()
{
    STM->DMA->CheckPeripheralDMA(Num ? 3 : 2);
}

int STM8SPI::RXDMALength()
{
    if (!(IntCnt & (1<<0))) return 0;
    if (!(Status & (1<<0))) return 0;
    return 1;
}

int STM8SPI::TXDMALength()
{
    printf("CheckTXDMA %02X %02X\n", IntCnt, Status);
    if (!(IntCnt & (1<<1))) return 0;
    if (!(Status & (1<<1))) return 0;
    return 1;
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
        SetCnt0(val);
        return;
    case 0x01:
        SetCnt1(val);
        return;
    case 0x02:
        SetIntCnt(val);
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


void STM8SPI::SetCnt0(u8 val)
{
    Cnt[0] = val;
    //UpdateMasterMode();
}

void STM8SPI::SetCnt1(u8 val)
{
    Cnt[1] = val;
    UpdateMasterMode();
}

void STM8SPI::SetIntCnt(u8 val)
{
    IntCnt = val & 0xF3;

    if (IntCnt & (1<<0)) CheckRXDMA();
    if (IntCnt & (1<<1)) CheckTXDMA();
}

void STM8SPI::SendData(u8 val)
{
    if (IsMaster())
    {
        // TODO
    }
    else
    {
        // CHECKME: this is probably wrong
        // UIC firmware does 'clr $5204' after a SPI transfer
        // supposedly this should clear the RX buffer if there's anything left in it?
        /*if (!SlaveSel)
        {
            Status &= ~(1<<0);
            Status |= (1<<1);
            return;
        }*/
        Status &= ~(1<<0);

        printf("TX BUFFER = %02X\n", val);
        TXData = val;
        Status &= ~(1<<1);
    }
}

u8 STM8SPI::ReceiveData()
{
    if (IsMaster())
    {
        // TODO
        return 0;
    }
    else
    {
        Status &= ~(1<<0);
        return RXData;
    }
}
