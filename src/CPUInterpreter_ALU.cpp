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


#define DeclTemplate(func) \
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


int STM8::OP_AND_Imm()
{
    u8 val = CPUFetch();
    val &= A;

    A = val;
    SetNZ((val & 0x80), (!val));
    return 1;
}

template<STM8::OperandType op, bool indY>
int STM8::OP_AND_Mem()
{
    u32 addr = CPUFetchOpAddr<op, indY>();
    u8 val = MemRead(addr);
    val &= A;

    A = val;
    SetNZ((val & 0x80), (!val));
    return OpIsIndirect(op) ? 4 : 1;
}

DeclTemplate(OP_AND_Mem)


int STM8::OP_BCP_Imm()
{
    u8 val = CPUFetch();

    val = A & val;
    SetNZ((val & 0x80), (!val));

    return 1;
}


template<int bit>
int STM8::OP_BRES()
{
    u32 addr = CPUFetchOpAddr<Op_LongDirect>();
    u8 val = MemRead(addr);
    val &= ~(1<<bit);
    MemWrite(addr, val);

    return 1;
}

template int STM8::OP_BRES<0>();
template int STM8::OP_BRES<1>();
template int STM8::OP_BRES<2>();
template int STM8::OP_BRES<3>();
template int STM8::OP_BRES<4>();
template int STM8::OP_BRES<5>();
template int STM8::OP_BRES<6>();
template int STM8::OP_BRES<7>();


template<int bit>
int STM8::OP_BSET()
{
    u32 addr = CPUFetchOpAddr<Op_LongDirect>();
    u8 val = MemRead(addr);
    val |= (1<<bit);
    MemWrite(addr, val);

    return 1;
}

template int STM8::OP_BSET<0>();
template int STM8::OP_BSET<1>();
template int STM8::OP_BSET<2>();
template int STM8::OP_BSET<3>();
template int STM8::OP_BSET<4>();
template int STM8::OP_BSET<5>();
template int STM8::OP_BSET<6>();
template int STM8::OP_BSET<7>();


int STM8::OP_CLR_A()
{
    A = 0;
    SetNZ(false, true);

    return 1;
}

template<STM8::OperandType op, bool indY>
int STM8::OP_CLR_Mem()
{
    u32 addr = CPUFetchOpAddr<op, indY>();

    MemWrite(addr, 0);
    SetNZ(false, true);

    return OpIsIndirect(op) ? 4 : 1;
}

DeclTemplate(OP_CLR_Mem);


template<bool indY>
int STM8::OP_CLRW()
{
    if (indY) Y = 0;
    else      X = 0;
    SetNZ(false, true);

    return 1;
}

template int STM8::OP_CLRW<false>();
template int STM8::OP_CLRW<true>();


int STM8::OP_CP_Imm()
{
    u8 a = A;
    u8 b = CPUFetch();

    u8 val = a - b;
    SetNZVC((val & 0x80), (!val), OverflowSub8(a, b), CarrySub8(a, b));

    return 1;
}

template<STM8::OperandType op, bool indY>
int STM8::OP_CP_Mem()
{
    u32 addr = CPUFetchOpAddr<op, indY>();
    u8 a = A;
    u8 b = MemRead(addr);

    u8 val = a - b;
    SetNZVC((val & 0x80), (!val), OverflowSub8(a, b), CarrySub8(a, b));

    return OpIsIndirect(op) ? 4 : 1;
}

DeclTemplate(OP_CP_Mem);


int STM8::OP_CPL_A()
{
    A = ~A;
    SetNZC((A & 0x80), (!A), true);

    return 1;
}

template<STM8::OperandType op, bool indY>
int STM8::OP_CPL_Mem()
{
    u32 addr = CPUFetchOpAddr<op, indY>();
    u8 val = MemRead(addr);

    val = ~val;
    MemWrite(addr, val);
    SetNZC((val & 0x80), (!val), true);

    return OpIsIndirect(op) ? 4 : 1;
}

DeclTemplate(OP_CPL_Mem);


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
int STM8::OP_CPW_Mem()
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

DeclTemplateW(OP_CPW_Mem)


int STM8::OP_DEC_Imm()
{
    u8 val = A;

    A--;
    SetNZV((A & 0x80), (!A), OverflowSub8(val, 1));
    return 1;
}

template<STM8::OperandType op, bool indY>
int STM8::OP_DEC_Mem()
{
    u32 addr = CPUFetchOpAddr<op, indY>();
    u8 val = MemRead(addr);

    u8 nval = val - 1;
    MemWrite(addr, nval);
    SetNZV((nval & 0x80), (!nval), OverflowSub8(val, 1));
    return OpIsIndirect(op) ? 4 : 1;
}

DeclTemplate(OP_DEC_Mem)


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


int STM8::OP_OR_Imm()
{
    u8 val = CPUFetch();
    val |= A;

    A = val;
    SetNZ((val & 0x80), (!val));
    return 1;
}

template<STM8::OperandType op, bool indY>
int STM8::OP_OR_Mem()
{
    u32 addr = CPUFetchOpAddr<op, indY>();
    u8 val = MemRead(addr);
    val |= A;

    A = val;
    SetNZ((val & 0x80), (!val));
    return OpIsIndirect(op) ? 4 : 1;
}

DeclTemplate(OP_OR_Mem)


template<bool indY>
int STM8::OP_RRWA()
{
    u16 ind = indY ? Y : X;

    u8 tmp = A;
    A = ind & 0xFF;
    ind = (ind >> 8) | tmp;

    if (indY) Y = ind;
    else      X = ind;
    SetNZ((ind & 0x8000), (!ind));

    return 1;
}

template int STM8::OP_RRWA<false>();
template int STM8::OP_RRWA<true>();


int STM8::OP_SUB_SP()
{
    u16 b = CPUFetch();
    SP -= b;
    return 1;
}


int STM8::OP_TNZ_A()
{
    u8 val = A;

    SetNZ((val & 0x80), (!val));
    return 1;
}

template<STM8::OperandType op, bool indY>
int STM8::OP_TNZ_Mem()
{
    u32 addr = CPUFetchOpAddr<op, indY>();
    u8 val = MemRead(addr);

    SetNZ((val & 0x80), (!val));
    return OpIsIndirect(op) ? 4 : 1;
}

DeclTemplate(OP_TNZ_Mem)
