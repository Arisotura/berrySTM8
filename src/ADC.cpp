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
#include "ADC.h"


const char* ADC_Chan[] =
{
    "PA6", // 0
    "PA5", // 1
    "PA4", // 2
    "PC7", // 3
    "PC4", // 4
    "PC3", // 5
    "PC2", // 6
    "PD7", // 7
    "PD6", // 8
    "PD5", // 9
    "PD4", // 10
    "PB7", // 11
    "PB6", // 12
    "PB5", // 13
    "PB4", // 14
    "PB3", // 15
    "PB2", // 16
    "PB1", // 17
    "PB0", // 18
    "PD3", // 19
    "PD2", // 20
    "PD1", // 21
    "PD0", // 22
    "PE5", // 23
    "PF0", // 24
    "PF1", // 25
    "PF2", // 26
    "PF3", // 27
};


STM8ADC::STM8ADC(STM8* stm, u32 iobase) : STM8Device(stm, iobase)
{
    //
}

STM8ADC::~STM8ADC()
{
    //
}

void STM8ADC::Reset()
{
    //
}


u8 STM8ADC::IORead(u32 addr)
{
    addr -= IOBase;
    switch (addr)
    {
    }

    printf("ADC: unknown read %04X\n", addr+IOBase);
    return 0;
}

void STM8ADC::IOWrite(u32 addr, u8 val)
{
    addr -= IOBase;
    switch (addr)
    {
    }

    printf("ADC: unknown write %04X %02X\n", addr+IOBase, val);
}
