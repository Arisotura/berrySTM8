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

#ifndef I2C_H
#define I2C_H

class STM8I2C : public STM8Device
{
public:
    STM8I2C(STM8* stm, u32 base);
    ~STM8I2C();
    void Reset();

    u8 IORead(u32 addr);
    void IOWrite(u32 addr, u8 val) override;

private:
    u8 Cnt[2];
    u8 Freq;
    u8 OwnAddr[3];
    u8 Data;
    u8 Status[3];
    u8 IntCnt;
    u16 ClockCnt;
    u8 TRISE;
    u8 PEC;

    void SetCnt0(u8 val);
    void SetCnt1(u8 val);

    void TriggerIRQ();
};

#endif // I2C_H
