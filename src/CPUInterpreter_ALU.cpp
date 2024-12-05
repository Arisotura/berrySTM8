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

#include "STM8.h"


inline bool OverflowAdd16(u16 a, u16 b)
{
    u16 res = a + b;
    return (!((a ^ b) & 0x8000)) && ((a ^ res) & 0x8000);
}


int STM8::OP_BCP_Imm()
{
    u8 val = CPUFetch();

    val = A & val;
    SetNZ((val & 0x80), (!val));

    return 1;
}


template<bool indY>
int STM8::OP_INCW()
{
    u16 oldval = indY ? Y : X;
    u16 val = oldval + 1;

    if (indY) Y = val;
    else      X = val;
    SetNZV((val & 0x8000), (!val), OverflowAdd16(oldval, 1));

    return 1;
}

template int STM8::OP_INCW<false>();
template int STM8::OP_INCW<true>();
