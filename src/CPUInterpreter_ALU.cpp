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


#define DeclTemplateW(func) \
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
    template int STM8::func<STM8::Op_ShortIndirect, false>(); \
    template int STM8::func<STM8::Op_ShortIndirect, true>(); \
    template int STM8::func<STM8::Op_LongIndirect, false>(); \
    template int STM8::func<STM8::Op_ShortIndirectInd, false>(); \
    template int STM8::func<STM8::Op_ShortIndirectInd, true>(); \
    template int STM8::func<STM8::Op_LongIndirectInd, false>();


inline bool CarryAdd8(u8 a, u8 b)
{
    return (0xFF-a) < b;
}

inline bool CarrySub8(u8 a, u8 b)
{
    return a >= b;
}

inline bool OverflowAdd8(u8 a, u8 b)
{
    u8 res = a + b;
    return (!((a ^ b) & 0x80)) && ((a ^ res) & 0x80);
}

inline bool OverflowSub8(u8 a, u8 b)
{
    u8 res = a - b;
    return ((a ^ b) & 0x80) && ((a ^ res) & 0x80);
}

inline bool OverflowAdc8(u8 a, u8 b, u8 carry)
{
    s32 fullResult = (s32)(s8)a + (s8)b + carry;
    u8 res = a + b + carry;
    return (s8)res != fullResult;
}

inline bool OverflowSbc8(u8 a, u8 b, u8 carry)
{
    s32 fullResult = (s32)(s8)a - (s8)b - carry;
    u8 res = a - b - carry;
    return (s8)res != fullResult;
}

inline bool CarryAdd16(u16 a, u16 b)
{
    return (0xFFFF-a) < b;
}

inline bool CarrySub16(u16 a, u16 b)
{
    return a >= b;
}

inline bool OverflowAdd16(u16 a, u16 b)
{
    u16 res = a + b;
    return (!((a ^ b) & 0x8000)) && ((a ^ res) & 0x8000);
}

inline bool OverflowSub16(u16 a, u16 b)
{
    u16 res = a - b;
    return ((a ^ b) & 0x8000) && ((a ^ res) & 0x8000);
}


template<bool indY>
int STM8::OP_ADDW_Imm()
{
    u16 a = indY ? Y : X;
    u16 b = (CPUFetch() << 8);
    b |= CPUFetch();

    u16 val = a + b;
    if (indY) Y = val;
    else      X = val;
    SetNZVCH((val & 0x8000), (!val), OverflowAdd16(a, b), CarryAdd16(a, b), CarryAdd8(a&0xFF, b&0xFF));

    return 2;
}

template int STM8::OP_ADDW_Imm<false>();
template int STM8::OP_ADDW_Imm<true>();


template<STM8::OperandType op, bool indY>
int STM8::OP_ADDW_Ind()
{
    u32 addr = CPUFetchOpAddr<op, indY>();

    u16 a, b;

    if (OpIsInd(op))
        a = indY ? X : Y;
    else
        a = indY ? Y : X;

    b = (MemRead(addr) << 8);
    b |= MemRead(addr+1);

    u16 val = a + b;
    if (indY) Y = val;
    else      X = val;
    SetNZVCH((val & 0x8000), (!val), OverflowAdd16(a, b), CarryAdd16(a, b), CarryAdd8(a&0xFF, b&0xFF));

    return OpIsIndirect(op) ? 5 : 2;
}

template int STM8::OP_ADDW_Ind<STM8::Op_LongDirect, false>();
template int STM8::OP_ADDW_Ind<STM8::Op_LongDirect, true>();
template int STM8::OP_ADDW_Ind<STM8::Op_ShortDirectSP, false>();
template int STM8::OP_ADDW_Ind<STM8::Op_ShortDirectSP, true>();


int STM8::OP_ADDW_SP()
{
    u16 b = CPUFetch();
    SP += b;
    return 2;
}


int STM8::OP_BCP_Imm()
{
    u8 val = CPUFetch();

    val = A & val;
    SetNZ((val & 0x80), (!val));

    return 1;
}


int STM8::OP_CP_Imm()
{
    u8 a = A;
    u8 b = CPUFetch();

    u8 val = a - b;
    SetNZVC((val & 0x80), (!val), OverflowSub8(a, b), CarrySub8(a, b));

    return 1;
}


template<bool indY>
int STM8::OP_CPW_Imm()
{
    u16 a = indY ? Y : X;
    u16 b = (CPUFetch() << 8);
    b |= CPUFetch();

    u16 val = a - b;
    SetNZVC((val & 0x8000), (!val), OverflowSub16(a, b), CarrySub16(a, b));

    return 2;
}

template int STM8::OP_CPW_Imm<false>();
template int STM8::OP_CPW_Imm<true>();


template<STM8::OperandType op, bool indY>
int STM8::OP_CPW_Ind()
{
    u32 addr = CPUFetchOpAddr<op, indY>();

    u16 a, b;

    if (OpIsInd(op))
        a = indY ? X : Y;
    else
        a = indY ? Y : X;

    b = (MemRead(addr) << 8);
    b |= MemRead(addr+1);

    u16 val = a - b;
    SetNZVC((val & 0x8000), (!val), OverflowSub16(a, b), CarrySub16(a, b));

    return OpIsIndirect(op) ? 5 : 2;
}

DeclTemplateW(OP_CPW_Ind)


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
