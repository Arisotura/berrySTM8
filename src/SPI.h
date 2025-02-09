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

#ifndef SPI_H
#define SPI_H

#include "types.h"

class STM8SPI : public STM8Device
{
public:
    STM8SPI(STM8* stm, u32 iobase, u8 num);
    ~STM8SPI() override;
    void Reset() override;

    u8 IORead(u32 addr) override;
    void IOWrite(u32 addr, u8 val) override;

private:
    u8 Num;

    u8 Cnt[2];
    u8 IntCnt;
    u8 Status;
    u8 RXData, TXData;
    u8 CRCPoly;
    u8 RXCRC;
    u8 TXCRC;

    u8 CurRXData;
    u8 CurTXData;

    void SendData(u8 val);
    u8 ReceiveData();
};

#endif // SPI_H
