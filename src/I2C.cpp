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
#include "I2C.h"


STM8I2C::STM8I2C(STM8* stm, u32 iobase) : STM8Device(stm, iobase)
{
    MapIORange(0x00, 0x0E);
}

STM8I2C::~STM8I2C()
{
    //
}

void STM8I2C::Reset()
{
    //
}


u8 STM8I2C::IORead(u32 addr)
{
    addr -= IOBase;
    switch (addr)
    {
    }

    printf("I2C: unknown read %04X\n", addr+IOBase);
    return 0;
}

void STM8I2C::IOWrite(u32 addr, u8 val)
{
    addr -= IOBase;
    switch (addr)
    {
    }

    printf("I2C: unknown write %04X %02X\n", addr+IOBase, val);
}


//
