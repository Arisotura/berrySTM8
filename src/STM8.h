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

#ifndef STM8_H
#define STM8_H

#include "types.h"

class STM8
{
public:
    STM8();
    ~STM8();
    void Reset();

    // 0=EEPROM 1=FLASH
    bool LoadImage(int type, const char* filename);

    void CPUReset();
    u8 CPUFetch();
    u32 CPUExecute(u32 cycles);

    u8 MemRead(u32 addr);
    void MemWrite(u32 addr, u8 val);

private:
    // TODO: some kind of model ID?

    // ---- CPU ---------------------------------

    u8 A;
    u16 X, Y;
    u16 SP;
    u32 PC;
    u8 CC;

    // ---- memory ------------------------------

    u8* RAM;
    u32 RAMSize;
    u32 RAMMask;

    u8* EEPROM;
    u32 EEPROMStart;
    u32 EEPROMEnd;
    u32 EEPROMSize;
    u32 EEPROMMask;

    u8* FLASH;
    const u32 FLASHStart = 0x8000;
    u32 FLASHEnd;
    u32 FLASHSize;
    u32 FLASHMask;
};

#endif // STM8_H
