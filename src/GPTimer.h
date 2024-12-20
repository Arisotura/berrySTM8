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

#ifndef GPTIMER_H
#define GPTIMER_H

#include "types.h"

class STM8GPTimer : public STM8Device
{
public:
    STM8GPTimer(STM8* stm, u32 iobase, u8 num);
    ~STM8GPTimer() override;
    void Reset() override;

    void Run(int cycles);

    void UpdateEvent();

    u8 IORead(u32 addr) override;
    void IOWrite(u32 addr, u8 val) override;

private:
    u8 Num;

    u8 Cnt[2];
    u8 Status[2];

    u16 Counter;
    u16 ReloadVal;

    u8 PrescalerReg;
    u8 Prescaler;

    u8 PreCount;
};

#endif // GPTIMER_H
