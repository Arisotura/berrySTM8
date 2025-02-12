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
#include "Compass.h"


namespace Compass
{

u8 RegAddr;
bool GotAddr;

u8 ReadVal;


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
    printf("Compass: WRITE %02X\n", val);
    if (!GotAddr)
    {
        RegAddr = val;
        GotAddr = true;

        return;
    }

    //printf("Compass: WRITE %02X %02X\n", RegAddr, val);

    switch (RegAddr)
    {
    }

    // CHECKME: how many bits does it have?
    RegAddr++;
}

}
