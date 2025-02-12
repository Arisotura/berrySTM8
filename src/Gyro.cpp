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
#include "Gyro.h"


namespace Gyro
{

u8 RegAddr;
bool GotAddr;

u8 ReadVal;

u8 Unk00;
u8 Unk16;


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

    ReadVal = 0;

    Unk00 = 0;
    Unk16 = 0;
}


void Select()
{
    GotAddr = false;
}

void Release()
{
}

u8 Read()
{
    return ReadVal;
}

void Write(u8 val)
{
    if (!GotAddr)
    {
        RegAddr = val;
        GotAddr = true;

        return;
    }

    if (RegAddr & (1<<7))
    {
        // read
        printf("Gyro: read %02X\n", RegAddr&0x7F);

        switch (RegAddr & 0x7F)
        {
        case 0x00:
            ReadVal = Unk00;
            break;

        case 0x16:
            ReadVal = Unk16;
            break;

        default:
            ReadVal = 0;
            break;
        }
    }
    else
    {
        // write
        printf("Gyro: write %02X %02X\n", RegAddr&0x7F, val);

        switch (RegAddr & 0x7F)
        {
        case 0x00:
            Unk00 = val;
            break;

        case 0x16:
            Unk16 = val;
            break;
        }
    }

    RegAddr = (RegAddr & 0x80) | ((RegAddr + 1) & 0x7F);
}

}
