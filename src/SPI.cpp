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
    //
}


u8 STM8SPI::IORead(u32 addr)
{
    addr -= IOBase;
    switch (addr)
    {
    }

    printf("SPI%d: unknown read %06X  %06X\n", Num, IOBase+addr, STM->GetPC());
    return 0;
}

void STM8SPI::IOWrite(u32 addr, u8 val)
{
    addr -= IOBase;
    switch (addr)
    {
    }

    printf("SPI%d: unknown write %06X %02X\n", Num, IOBase+addr, val);
}
