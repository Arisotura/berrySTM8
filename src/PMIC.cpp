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
#include "PMIC.h"


namespace PMIC
{

u8 RegAddr;
bool GotAddr;

u8 Reg07;


bool Init()
{
    return true;
}

void DeInit()
{
}

void Reset()
{
    RegAddr = 0;
    GotAddr = false;

    Reg07 = 0;
}


void Start()
{
    GotAddr = false;
}

void Stop()
{
}

u8 Read()
{
    printf("PMIC: READ %02X\n", RegAddr);

    u8 ret = 0;
    switch (RegAddr)
    {
    case 0x01:
        // charger status
        // bit6 = AC, bit7 = USB
        ret = 0x40;
        break;

    case 0x07:
        ret = Reg07;
        break;

    case 0x09:
        // battery level LSB
        ret = 0xFF;
        break;
    case 0x0A:
        // battery level MSB
        ret = 0x03;
        break;
    }

    // CHECKME: how many bits does it have?
    RegAddr++;
    return ret;
}

void Write(u8 val)
{
    if (!GotAddr)
    {
        RegAddr = val;
        GotAddr = true;

        return;
    }

    printf("PMIC: WRITE %02X %02X\n", RegAddr, val);

    switch (RegAddr)
    {
    case 0x07:
        // general control reg?
        Reg07 = val;
        Reg07 |= 0x20; // power ready bit? UIC waits for this
        break;
    }

    // CHECKME: how many bits does it have?
    RegAddr++;
}

}
