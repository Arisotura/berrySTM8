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
#include "Accel.h"


namespace Accel
{

u8 RegAddr;
bool GotAddr;

u8 ReadVal;

u8 Cnt[6];
u8 Unk17;


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

    Cnt[0] = 0x07;
    Cnt[1] = 0;
    Cnt[2] = 0;
    Cnt[3] = 0;
    Cnt[4] = 0;
    Cnt[5] = 0;
    Unk17 = 0;
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
        printf("Accel: read %02X\n", RegAddr&0x3F);

        switch (RegAddr & 0x3F)
        {
        case 0x0F:      // WHO_AM_I
            ReadVal = 0x33;
            break;

        case 0x17:
            ReadVal = Unk17;
            break;

        case 0x20:
            ReadVal = Cnt[0];
            break;
        case 0x21:
            ReadVal = Cnt[1];
            break;
        case 0x22:
            ReadVal = Cnt[2];
            break;
        case 0x23:
            ReadVal = Cnt[3];
            break;
        case 0x24:
            ReadVal = Cnt[4];
            break;
        case 0x25:
            ReadVal = Cnt[5];
            break;

        case 0x27: // status reg
            ReadVal = 0;//0x0F;
            break;

        default:
            ReadVal = 0;
            break;
        }
    }
    else
    {
        // write
        printf("Accel: write %02X %02X\n", RegAddr&0x3F, val);

        switch (RegAddr & 0x3F)
        {
        case 0x17:
            Unk17 = val;
            break;

        case 0x20:
            Cnt[0] = val;
            break;
        case 0x21:
            Cnt[1] = val;
            break;
        case 0x22:
            Cnt[2] = val;
            break;
        case 0x23:
            Cnt[3] = val;
            break;
        case 0x24:
            Cnt[4] = val;
            break;
        case 0x25:
            Cnt[5] = val;
            break;
        }
    }

    if (RegAddr & (1<<6))
        RegAddr = (RegAddr & 0xC0) | ((RegAddr + 1) & 0x3F);
}

}
