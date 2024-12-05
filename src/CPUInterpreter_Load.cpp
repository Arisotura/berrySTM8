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


#define DeclTemplateLD(func) \
    template int STM8::func<STM8::Op_ShortDirect, false>(); \
    template int STM8::func<STM8::Op_LongDirect, false>(); \
    template int STM8::func<STM8::Op_Ind, false>(); \
    template int STM8::func<STM8::Op_Ind, true>(); \
    template int STM8::func<STM8::Op_ShortDirectInd, false>(); \
    template int STM8::func<STM8::Op_ShortDirectInd, true>(); \
    template int STM8::func<STM8::Op_LongDirectInd, false>(); \
    template int STM8::func<STM8::Op_LongDirectInd, true>(); \
    template int STM8::func<STM8::Op_ShortDirectSP, false>(); \
    template int STM8::func<STM8::Op_ShortIndirect, false>(); \
    template int STM8::func<STM8::Op_LongIndirect, false>(); \
    template int STM8::func<STM8::Op_ShortIndirectInd, false>(); \
    template int STM8::func<STM8::Op_ShortIndirectInd, true>(); \
    template int STM8::func<STM8::Op_LongIndirectInd, false>();

#define DeclTemplateLDW(func) \
    template int STM8::func<STM8::Op_ShortDirect, false>(); \
    template int STM8::func<STM8::Op_ShortDirect, true>(); \
    template int STM8::func<STM8::Op_LongDirect, false>(); \
    template int STM8::func<STM8::Op_LongDirect, true>(); \
    template int STM8::func<STM8::Op_Ind, false>(); \
    template int STM8::func<STM8::Op_Ind, true>(); \
    template int STM8::func<STM8::Op_ShortDirectInd, false>(); \
    template int STM8::func<STM8::Op_ShortDirectInd, true>(); \
    template int STM8::func<STM8::Op_LongDirectInd, false>(); \
    template int STM8::func<STM8::Op_LongDirectInd, true>(); \
    template int STM8::func<STM8::Op_ShortDirectSP, false>(); \
    template int STM8::func<STM8::Op_ShortDirectSP, true>(); \
    template int STM8::func<STM8::Op_ShortIndirect, false>(); \
    template int STM8::func<STM8::Op_ShortIndirect, true>(); \
    template int STM8::func<STM8::Op_LongIndirect, false>(); \
    template int STM8::func<STM8::Op_ShortIndirectInd, false>(); \
    template int STM8::func<STM8::Op_ShortIndirectInd, true>(); \
    template int STM8::func<STM8::Op_LongIndirectInd, false>();


int STM8::OP_LD_Imm()
{
    u8 val = CPUFetch();

    A = val;
    SetNZ((val & 0x80), (!val));

    return 1;
}

template<STM8::OperandType op, bool indY>
int STM8::OP_LD_A()
{
    u32 addr = CPUFetchOpAddr<op, indY>();
    u8 val = MemRead(addr);

    A = val;
    SetNZ((val & 0x80), (!val));

    return (op < Op_ShortIndirect) ? 1 : 4;
}

DeclTemplateLD(OP_LD_A)


template<STM8::OperandType op, bool indY>
int STM8::OP_LD_Mem()
{
    u32 addr = CPUFetchOpAddr<op, indY>();
    u8 val = A;

    MemWrite(addr, val);
    SetNZ((val & 0x80), (!val));

    return (op < Op_ShortIndirect) ? 1 : 4;
}

DeclTemplateLDW(OP_LD_Mem);


int STM8::OP_LD_XL_A()
{
    X = (X & 0xFF00) | A;
    return 1;
}

int STM8::OP_LD_A_XL()
{
    A = X & 0xFF;
    return 1;
}

int STM8::OP_LD_YL_A()
{
    Y = (Y & 0xFF00) | A;
    return 1;
}

int STM8::OP_LD_A_YL()
{
    A = Y & 0xFF;
    return 1;
}

int STM8::OP_LD_XH_A()
{
    X = (X & 0x00FF) | (A << 8);
    return 1;
}

int STM8::OP_LD_A_XH()
{
    A = X >> 8;
    return 1;
}

int STM8::OP_LD_YH_A()
{
    Y = (Y & 0x00FF) | (A << 8);
    return 1;
}

int STM8::OP_LD_A_YH()
{
    A = Y >> 8;
    return 1;
}


template<bool indY>
int STM8::OP_LDW_Imm()
{
    u16 val = (CPUFetch() << 8);
    val |= CPUFetch();

    if (indY) Y = val;
    else      X = val;
    SetNZ((val & 0x8000), (!val));

    return 2;
}

template int STM8::OP_LDW_Imm<false>();
template int STM8::OP_LDW_Imm<true>();


template<STM8::OperandType op, bool indY>
int STM8::OP_LDW_Ind()
{
    u32 addr = CPUFetchOpAddr<op, indY>();
    u16 val = (MemRead(addr) << 8);
    val |= MemRead(addr+1);

    if (indY) Y = val;
    else      X = val;
    SetNZ((val & 0x8000), (!val));

    return (op < Op_ShortIndirect) ? 2 : 5;
}

DeclTemplateLDW(OP_LDW_Ind);


template<STM8::OperandType op, bool indY>
int STM8::OP_LDW_Mem()
{
    u32 addr = CPUFetchOpAddr<op, indY>();
    u16 val;
    if ((op >= Op_Ind && op <= Op_ExtendedDirectInd) ||
        (op >= Op_ShortIndirectInd))
        val = indY ? X : Y;
    else
        val = indY ? Y : X;

    MemWrite(addr, val >> 8);
    MemWrite(addr+1, val & 0xFF);
    SetNZ((val & 0x8000), (!val));

    return (op < Op_ShortIndirect) ? 2 : 5;
}

DeclTemplateLDW(OP_LDW_Mem);


int STM8::OP_LDW_Y_X()
{
    Y = X;
    return 1;
}

int STM8::OP_LDW_X_Y()
{
    X = Y;
    return 1;
}

int STM8::OP_LDW_X_SP()
{
    X = SP;
    return 1;
}

int STM8::OP_LDW_SP_X()
{
    SP = X;
    return 1;
}

int STM8::OP_LDW_Y_SP()
{
    Y = SP;
    return 1;
}

int STM8::OP_LDW_SP_Y()
{
    SP = Y;
    return 1;
}
