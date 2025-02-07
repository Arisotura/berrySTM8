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
#include "I2C.h"


STM8I2C::STM8I2C(STM8* stm, u32 iobase) : STM8Device(stm, iobase)
{
    MapIORange(0x00, 0x0E);

    memset(Devices, 0, sizeof(Devices));
    NumDevices = 0;
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
    TXData = 0;
    RXData = 0;
    TXEmpty = true;
    RXEmpty = true;
    Status[0] = 0;
    Status[1] = 0;
    Status[2] = 0;
    IntCnt = 0;
    ClockCnt = 0x000B;
    TRISE = 0x02;
    PEC = 0;

    // TODO make customizable with the registers and shit
    CycleLen = 15*3;
    CycleCount = 0;

    //SendingAddr = false;
    State = 0;
    StateDuration = 0;

    CurAddr = 0;
    CurTXData = 0;
    CurRXData = 0;
    AckCurByte = false;
    AckNextByte = false;

    CurDevice = nullptr;
}


void STM8I2C::RegisterDevice(u8 addr, void (*fnstart)(), void (*fnstop)(), u8 (*fnread)(), void (*fnwrite)(u8))
{
    sDevice* dev = &Devices[NumDevices++];
    dev->Addr = addr;
    dev->fnStart = fnstart;
    dev->fnStop = fnstop;
    dev->fnRead = fnread;
    dev->fnWrite = fnwrite;
}


void STM8I2C::Run(int cycles)
{
    CycleCount += cycles;
    while (CycleCount >= CycleLen)
    {
        CycleCount -= CycleLen;

        if (State == 0) continue;
        if (StateDuration <= 0) continue;

        StateDuration--;
        if (StateDuration > 0) continue;

        if (State == 1)
        {
            // sent start bit

            Cnt[1] &= ~(1<<0);
            Status[0] |= (1<<0); // signal start condition
            Status[0] &= ~(1<<7);
            Status[2] &= ~(1<<1);
            if (IntCnt & (1<<1))
                TriggerIRQ();
            printf("I2C: START\n");
        }
        else if (State == 2)
        {
            // sent address byte

            AckCurByte = true;

            // set TRA bit based on address bit0 (direction)
            if (CurAddr & (1<<0))
                Status[2] &= ~(1<<2);
            else
                Status[2] |= (1<<2);

            Status[0] |= (1<<1); // address sent
            //Status[0] |= (1<<2); // request new data byte
            Status[2] &= ~(1<<1);
            if (IntCnt & (1<<1))
                TriggerIRQ();
            printf("I2C: sent address\n");
        }
        else if (State == 3)
        {
            // sent data byte

            if (!TXEmpty)
            {
                // we have another byte to send
                TXEmpty = true;
                Status[0] |= (1<<7); // TX empty
                if ((IntCnt & 0x06) == 0x06)
                    TriggerIRQ();
            }
            else
            {
                // we ran out of data to send, request more
                Status[0] |= (1<<2); // BTF
                Status[2] &= ~(1<<1);
                if (IntCnt & (1<<1))
                    TriggerIRQ();
            }
            printf("I2C: sent data (%02X), TXEmpty=%d\n", CurTXData, TXEmpty);
        }
        else if (State == 4)
        {
            // received data byte

            bool zz = RXEmpty;
            if (RXEmpty)
            {
                // we have room for the last received byte
                RXData = CurRXData;
                RXEmpty = false;
                Status[0] |= (1<<6); // RX not empty
                Status[2] &= ~(1<<1);
                if ((IntCnt & 0x06) == 0x06)
                    TriggerIRQ();
            }
            else
            {
                // the previous byte has not been read
                Status[0] |= (1<<2); // BTF
                Status[2] &= ~(1<<1);
                if (IntCnt & (1<<1))
                    TriggerIRQ();
            }
            printf("I2C: received data (%02X), RXEmpty=%d(%d), IntCnt=%02X\n", RXData, RXEmpty, zz, IntCnt);
        }
        else if (State == 5)
        {
            // sent stop bit

            Cnt[1] &= ~(1<<1);
            Status[2] &= ~(1<<2); // TX/RX bit
            Status[2] &= ~(1<<1);
            Status[2] &= ~(1<<0); // master bit
            printf("I2C: STOP\n");
        }

        UpdateState();
    }
}

void STM8I2C::UpdateState()
{
    if (Status[2] & (1<<1))
        return;

    if (Cnt[1] & (1<<0))
    {
        // start
        State = 1;
        StateDuration = 1;
        Status[2] |= (1<<1); // busy
        Status[2] |= (1<<0); // master bit

        //printf("UpdateState: START\n");
    }
    else if (Cnt[1] & (1<<1))
    {
        // stop
        State = 5;
        StateDuration = 1;
        Status[2] |= (1<<1); // busy

        //printf("UpdateState: STOP\n");

        if (CurDevice)
        {
            CurDevice->fnStop();
            CurDevice = nullptr;
        }
    }
    else if ((State == 1) && (!TXEmpty))
    {
        // sending out address byte
        State = 2;
        StateDuration = 9; // 8 data bits + ack
        Status[0] |= (1<<7); // TX empty
        Status[2] |= (1<<1); // busy

        CurAddr = TXData;
        TXEmpty = true;
        //printf("UpdateState: SEND ADDR\n");

        CurDevice = nullptr;
        for (int i = 0; i < NumDevices; i++)
        {
            if (Devices[i].Addr == (CurAddr >> 1))
            {
                CurDevice = &Devices[i];
                break;
            }
        }

        if (CurDevice)
        {
            CurDevice->fnStart();
        }
        else
            Status[1] |= (1<<2); // NACK
    }
    else if (State == 2)
    {
        if (Status[2] & (1<<2))
            State = 3;
        else
            State = 4;
    }
    else if (State == 5)
    {
        State = 0;
    }

    // when a byte is sent:
    // * set TXE bit
    // * if there's no new byte available: set BTF

    if ((State == 3) && (!TXEmpty))
    {
        // sending out data byte
        State = 3;
        StateDuration = 9;
        Status[0] |= (1<<7); // TX empty
        Status[2] |= (1<<1); // busy

        // TODO: send data to device here
        CurTXData = TXData;
        TXEmpty = true;
        //printf("UpdateState: SEND BYTE\n");

        if (CurDevice)
        {
            CurDevice->fnWrite(CurTXData);
        }
        else
            Status[1] |= (1<<2); // NACK

        TriggerIRQ();
    }
    else if ((State == 4) )//&& RXEmpty)
    {
        bool ack;
        if (Cnt[1] & (1<<3))
        {
            ack = AckCurByte;
            AckCurByte = AckNextByte;
            AckNextByte = (Cnt[1] & (1<<2));
        }
        else
            ack = (Cnt[1] & (1<<2));

        if (ack)
        {
            // receiving data byte
            State = 4;
            StateDuration = 9;
            Status[2] |= (1<<1); // busy

            // TODO: receive data from device here
            //CurRXData = 0x20;
            //printf("UpdateState: RECV BYTE\n");

            if (CurDevice)
            {
                CurRXData = CurDevice->fnRead();
            }
            else
                CurRXData = 0x00; // checkme
        }
        else
        {
            /*State = 5;
            StateDuration = 1; // checkme
            Status[2] |= (1<<1); // busy*/

            //printf("UpdateState: RECV STOP\n");
        }
    }
}


u8 STM8I2C::IORead(u32 addr)
{
    //printf("I2C: READ %06X    %06X\n", addr, STM->GetPC());
    addr -= IOBase;
    switch (addr)
    {
    case 0x00: return Cnt[0];
    case 0x01: return Cnt[1];
    case 0x02: return Freq;
    case 0x03: return OwnAddr[0];
    case 0x04: return OwnAddr[1];
    case 0x05: return OwnAddr[2];
    case 0x06: return ReceiveData();
    case 0x07: return Status[0];
    case 0x08: return Status[1];
    case 0x09: Status[0] &= ~(1<<1); return Status[2];
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
    //printf("I2C: WRITE %06X %02X     %06X\n", addr, val, STM->GetPC());
    addr -= IOBase;
    switch (addr)
    {
    case 0x00: SetCnt0(val); return;
    case 0x01: SetCnt1(val); return;

    case 0x06: SendData(val); return;

    case 0x08: Status[1] &= val; return;

    case 0x0A: IntCnt = val & 0x1F; return;
    }

    printf("I2C: unknown write %04X %02X\n", addr+IOBase, val);
}


void STM8I2C::SetCnt0(u8 val)
{
    //printf("I2C: CNT0=%02X\n", val);

    Cnt[0] = val & 0xFB;
    // TODO most of the effects (PE bit etc)
}

void STM8I2C::SetCnt1(u8 val)
{
    //printf("I2C: CNT1=%02X  %06X\n", val, STM->GetPC());

    Cnt[1] = val & 0xBF;

    if (Cnt[1] & (1<<3))
        AckNextByte = (Cnt[1] & (1<<2));

    UpdateState();
}

void STM8I2C::SendData(u8 val)
{
    //printf("I2C: SEND %02X  %06X\n", val, STM->GetPC());
    Status[0] &= ~0xCD; // clear status bits

    TXData = val;
    TXEmpty = false;
    UpdateState();
}

u8 STM8I2C::ReceiveData()
{
    //printf("I2C: DATA READ\n");

    Status[0] &= ~(1<<6);
    RXEmpty = true;
    u8 ret = RXData;
    UpdateState();
    return ret;
}


void STM8I2C::TriggerIRQ()
{
    STM->TriggerIRQ(29);
}
