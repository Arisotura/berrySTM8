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


template<bool toY>
void STM8::OP_LDW_Imm()
{
    // TODO: return 2 cycles
    // TODO: flags!!

    u16 val = (CPUFetch() << 8);
    val |= CPUFetch();

    if (toY) Y = val;
    else     X = val;
    SetNZ((val & 0x8000), (!val));
}

template void STM8::OP_LDW_Imm<false>();
template void STM8::OP_LDW_Imm<true>();


template<STM8::OperandType op, bool toY>
void STM8::OP_LDW_ToInd()
{
    u32 addr = CPUFetchOpAddr<op, toY>();
    u16 val = (MemRead(addr) << 8);
    val |= MemRead(addr+1);

    if (toY) Y = val;
    else     X = val;
    SetNZ((val & 0x8000), (!val));

    // TODO: cycle count
}

template void STM8::OP_LDW_ToInd<STM8::Op_LongDirect, false>();
template void STM8::OP_LDW_ToInd<STM8::Op_LongDirect, true>();


void STM8::OP_LDW_SP_X()
{
    SP = X;
}
