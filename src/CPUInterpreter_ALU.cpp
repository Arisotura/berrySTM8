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


int STM8::OP_ADC_Imm()
{
    u8 a = A;
    u8 b = CPUFetch();

    u8 val = a + b;
    if (CC & Flag_C) val++;
    A = val;
    SetFlagsAdd(a, b, val, Flag_V|Flag_C|Flag_H);

    return 1;
}

template<STM8::OperandType op, bool indY>
int STM8::OP_ADC_Mem()
{
    u32 addr = CPUFetchOpAddr<op, indY>();

    u8 a = A;
    u8 b = MemRead(addr);

    u8 val = a + b;
    if (CC & Flag_C) val++;
    A = val;
    SetFlagsAdd(a, b, val, Flag_V|Flag_C|Flag_H);

    return OpIsIndirect(op) ? 4 : 1;
}

DeclTemplate(OP_ADC_Mem)


int STM8::OP_ADD_Imm()
{
    u8 a = A;
    u8 b = CPUFetch();

    u8 val = a + b;
    A = val;
    SetFlagsAdd(a, b, val, Flag_V|Flag_C|Flag_H);

    return 1;
}

template<STM8::OperandType op, bool indY>
int STM8::OP_ADD_Mem()
{
    u32 addr = CPUFetchOpAddr<op, indY>();

    u8 a = A;
    u8 b = MemRead(addr);

    u8 val = a + b;
    A = val;
    SetFlagsAdd(a, b, val, Flag_V|Flag_C|Flag_H);

    return OpIsIndirect(op) ? 4 : 1;
}

DeclTemplate(OP_ADD_Mem)


template<bool indY>
int STM8::OP_ADDW_Imm()
{
    u16 a = indY ? Y : X;
    u16 b = (CPUFetch() << 8);
    b |= CPUFetch();

    u16 val = a + b;
    if (indY) Y = val;
    else      X = val;
    SetFlagsAdd(a, b, val, Flag_V|Flag_C|Flag_H);

    return 2;
}

template int STM8::OP_ADDW_Imm<false>();
template int STM8::OP_ADDW_Imm<true>();

template<STM8::OperandType op, bool indY>
int STM8::OP_ADDW_Mem()
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
    SetFlagsAdd(a, b, val, Flag_V|Flag_C|Flag_H);

    return OpIsIndirect(op) ? 5 : 2;
}

template int STM8::OP_ADDW_Mem<STM8::Op_LongDirect, false>();
template int STM8::OP_ADDW_Mem<STM8::Op_LongDirect, true>();
template int STM8::OP_ADDW_Mem<STM8::Op_ShortDirectSP, false>();
template int STM8::OP_ADDW_Mem<STM8::Op_ShortDirectSP, true>();

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

template<STM8::OperandType op, bool indY>
int STM8::OP_BCP_Mem()
{
    u32 addr = CPUFetchOpAddr<op, indY>();
    u8 val = MemRead(addr);

    val = A & val;
    SetNZ((val & 0x80), (!val));
    return OpIsIndirect(op) ? 4 : 1;
}

DeclTemplate(OP_BCP_Mem)


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
    SetFlagsSub(a, b, val, Flag_V|Flag_C);

    return 1;
}

template<STM8::OperandType op, bool indY>
int STM8::OP_CP_Mem()
{
    u32 addr = CPUFetchOpAddr<op, indY>();
    u8 a = A;
    u8 b = MemRead(addr);

    u8 val = a - b;
    SetFlagsSub(a, b, val, Flag_V|Flag_C);

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
int STM8::OP_CPLW()
{
    u16 ind = indY ? Y : X;

    u16 val = ~ind;
    if (indY) Y = ind;
    else      X = ind;
    SetNZC((val & 0x8000), (!val), true);

    return 2;
}

template int STM8::OP_CPLW<false>();
template int STM8::OP_CPLW<true>();


template<bool indY>
int STM8::OP_CPW_Imm()
{
    u16 a = indY ? Y : X;
    u16 b = (CPUFetch() << 8);
    b |= CPUFetch();

    u16 val = a - b;
    SetFlagsSub(a, b, val, Flag_V|Flag_C);

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
    SetFlagsSub(a, b, val, Flag_V|Flag_C);

    return OpIsIndirect(op) ? 5 : 2;
}

DeclTemplateW(OP_CPW_Mem)


int STM8::OP_DEC_A()
{
    u8 val = A;

    A--;
    SetFlagsSub(val, (u8)1, A, Flag_V);
    return 1;
}

template<STM8::OperandType op, bool indY>
int STM8::OP_DEC_Mem()
{
    u32 addr = CPUFetchOpAddr<op, indY>();
    u8 val = MemRead(addr);

    u8 nval = val - 1;
    MemWrite(addr, nval);
    SetFlagsSub(val, (u8)1, nval, Flag_V);
    return OpIsIndirect(op) ? 4 : 1;
}

DeclTemplate(OP_DEC_Mem)


template<bool indY>
int STM8::OP_DECW()
{
    u16 oldval = indY ? Y : X;
    u16 val = oldval - 1;

    if (indY) Y = val;
    else      X = val;
    SetFlagsSub(oldval, (u16)1, val, Flag_V);

    return 1;
}

template int STM8::OP_DECW<false>();
template int STM8::OP_DECW<true>();


int STM8::OP_EXG_XL()
{
    u8 tmp = A;
    A = X & 0xFF;
    X = (X & 0xFF00) | tmp;
    return 1;
}

int STM8::OP_EXG_YL()
{
    u8 tmp = A;
    A = Y & 0xFF;
    Y = (Y & 0xFF00) | tmp;
    return 1;
}

int STM8::OP_EXG_Mem()
{
    u32 addr = CPUFetchOpAddr<Op_LongDirect>();
    u8 tmp = A;
    A = MemRead(addr);
    MemWrite(addr, tmp);
    return 3;
}


int STM8::OP_EXGW()
{
    u16 tmp = X;
    X = Y;
    Y = tmp;
    return 1;
}


int STM8::OP_INC_A()
{
    u8 val = A;

    A++;
    SetFlagsAdd(val, (u8)1, A, Flag_V);
    return 1;
}

template<STM8::OperandType op, bool indY>
int STM8::OP_INC_Mem()
{
    u32 addr = CPUFetchOpAddr<op, indY>();
    u8 val = MemRead(addr);

    u8 nval = val + 1;
    MemWrite(addr, nval);
    SetFlagsAdd(val, (u8)1, nval, Flag_V);
    return OpIsIndirect(op) ? 4 : 1;
}

DeclTemplate(OP_INC_Mem)


template<bool indY>
int STM8::OP_INCW()
{
    u16 oldval = indY ? Y : X;
    u16 val = oldval + 1;

    if (indY) Y = val;
    else      X = val;
    SetFlagsAdd(oldval, (u16)1, val, Flag_V);

    return 1;
}

template int STM8::OP_INCW<false>();
template int STM8::OP_INCW<true>();


template<bool indY>
int STM8::OP_MUL()
{
    u16 ind = indY ? Y : X;
    u16 val = (ind & 0xFF) * A;

    if (indY) Y = val;
    else      X = val;
    CC &= ~(Flag_C | Flag_H);
    return 4;
}

template int STM8::OP_MUL<false>();
template int STM8::OP_MUL<true>();


int STM8::OP_NEG_A()
{
    A = -A;
    SetNZVC((A & 0x80), (!A), (A == 0x80), (!!A));

    return 1;
}

template<STM8::OperandType op, bool indY>
int STM8::OP_NEG_Mem()
{
    u32 addr = CPUFetchOpAddr<op, indY>();
    u8 val = MemRead(addr);

    val = -val;
    MemWrite(addr, val);
    SetNZVC((val & 0x80), (!val), (val == 0x80), (!!val));

    return OpIsIndirect(op) ? 4 : 1;
}

DeclTemplate(OP_NEG_Mem);


template<bool indY>
int STM8::OP_NEGW()
{
    u16 ind = indY ? Y : X;

    ind = -ind;
    if (indY) Y = ind;
    else      X = ind;
    SetNZVC((ind & 0x8000), (!ind), (ind == 0x8000), (!!ind));

    return 2;
}

template int STM8::OP_NEGW<false>();
template int STM8::OP_NEGW<true>();


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


int STM8::OP_RLC_A()
{
    u8 val = A;

    A <<= 1;
    if (CC & Flag_C) A |= 0x01;
    SetNZC((A & 0x80), (!A), (val & 0x80));
    return 1;
}

template<STM8::OperandType op, bool indY>
int STM8::OP_RLC_Mem()
{
    u32 addr = CPUFetchOpAddr<op, indY>();
    u8 val = MemRead(addr);

    u8 nval = val << 1;
    if (CC & Flag_C) nval |= 0x01;
    MemWrite(addr, nval);
    SetNZC((nval & 0x80), (!nval), (val & 0x80));
    return OpIsIndirect(op) ? 4 : 1;
}

DeclTemplate(OP_RLC_Mem)


template<bool indY>
int STM8::OP_RLCW()
{
    if (indY)
    {
        u16 val = Y;

        Y <<= 1;
        if (CC & Flag_C) Y |= 0x0001;
        SetNZC((Y & 0x8000), (!Y), (val & 0x8000));
    }
    else
    {
        u16 val = X;

        X <<= 1;
        if (CC & Flag_C) X |= 0x0001;
        SetNZC((X & 0x8000), (!X), (val & 0x8000));
    }
    return 2;
}

template int STM8::OP_RLCW<false>();
template int STM8::OP_RLCW<true>();


template<bool indY>
int STM8::OP_RLWA()
{
    u16 ind = indY ? Y : X;

    u8 tmp = A;
    A = ind >> 8;
    ind = (ind << 8) | tmp;

    if (indY) Y = ind;
    else      X = ind;
    SetNZ((ind & 0x8000), (!ind));

    return 1;
}

template int STM8::OP_RLWA<false>();
template int STM8::OP_RLWA<true>();


int STM8::OP_RRC_A()
{
    u8 val = A;

    A >>= 1;
    if (CC & Flag_C) A |= 0x80;
    SetNZC((A & 0x80), (!A), (val & 0x01));
    return 1;
}

template<STM8::OperandType op, bool indY>
int STM8::OP_RRC_Mem()
{
    u32 addr = CPUFetchOpAddr<op, indY>();
    u8 val = MemRead(addr);

    u8 nval = val >> 1;
    if (CC & Flag_C) nval |= 0x80;
    MemWrite(addr, nval);
    SetNZC((nval & 0x80), (!nval), (val & 0x01));
    return OpIsIndirect(op) ? 4 : 1;
}

DeclTemplate(OP_RRC_Mem)


template<bool indY>
int STM8::OP_RRCW()
{
    if (indY)
    {
        u16 val = Y;

        Y >>= 1;
        if (CC & Flag_C) Y |= 0x8000;
        SetNZC((Y & 0x8000), (!Y), (val & 0x0001));
    }
    else
    {
        u16 val = X;

        X >>= 1;
        if (CC & Flag_C) X |= 0x8000;
        SetNZC((X & 0x8000), (!X), (val & 0x0001));
    }
    return 2;
}

template int STM8::OP_RRCW<false>();
template int STM8::OP_RRCW<true>();


template<bool indY>
int STM8::OP_RRWA()
{
    u16 ind = indY ? Y : X;

    u8 tmp = A;
    A = ind & 0xFF;
    ind = (ind >> 8) | (tmp << 8);

    if (indY) Y = ind;
    else      X = ind;
    SetNZ((ind & 0x8000), (!ind));

    return 1;
}

template int STM8::OP_RRWA<false>();
template int STM8::OP_RRWA<true>();


int STM8::OP_SBC_Imm()
{
    u8 a = A;
    u8 b = CPUFetch();

    // TODO: does SBC set the H flag or not?
    // ADC does set it
    u8 val = a - b;
    if (CC & Flag_C) val--;
    A = val;
    SetFlagsSub(a, b, val, Flag_V|Flag_C);

    return 1;
}

template<STM8::OperandType op, bool indY>
int STM8::OP_SBC_Mem()
{
    u32 addr = CPUFetchOpAddr<op, indY>();

    u8 a = A;
    u8 b = MemRead(addr);

    u8 val = a - b;
    if (CC & Flag_C) val--;
    A = val;
    SetFlagsSub(a, b, val, Flag_V|Flag_C);

    return OpIsIndirect(op) ? 4 : 1;
}

DeclTemplate(OP_SBC_Mem)


int STM8::OP_SLL_A()
{
    u8 val = A;

    A <<= 1;
    SetNZC((A & 0x80), (!A), (val & 0x80));
    return 1;
}

template<STM8::OperandType op, bool indY>
int STM8::OP_SLL_Mem()
{
    u32 addr = CPUFetchOpAddr<op, indY>();
    u8 val = MemRead(addr);

    u8 nval = val << 1;
    MemWrite(addr, nval);
    SetNZC((nval & 0x80), (!nval), (val & 0x80));
    return OpIsIndirect(op) ? 4 : 1;
}

DeclTemplate(OP_SLL_Mem)


template<bool indY>
int STM8::OP_SLLW()
{
    if (indY)
    {
        u16 val = Y;

        Y <<= 1;
        SetNZC((Y & 0x8000), (!Y), (val & 0x8000));
    }
    else
    {
        u16 val = X;

        X <<= 1;
        SetNZC((X & 0x8000), (!X), (val & 0x8000));
    }
    return 2;
}

template int STM8::OP_SLLW<false>();
template int STM8::OP_SLLW<true>();


int STM8::OP_SRA_A()
{
    u8 val = A;

    A = (((s8)A) >> 1);
    SetNZC((A & 0x80), (!A), (val & 0x01));
    return 1;
}

template<STM8::OperandType op, bool indY>
int STM8::OP_SRA_Mem()
{
    u32 addr = CPUFetchOpAddr<op, indY>();
    u8 val = MemRead(addr);

    u8 nval = (((s8)val) >> 1);
    MemWrite(addr, nval);
    SetNZC((nval & 0x80), (!nval), (val & 0x01));
    return OpIsIndirect(op) ? 4 : 1;
}

DeclTemplate(OP_SRA_Mem)


template<bool indY>
int STM8::OP_SRAW()
{
    if (indY)
    {
        u16 val = Y;

        Y = (((s16)Y) >> 1);
        SetNZC((Y & 0x8000), (!Y), (val & 0x0001));
    }
    else
    {
        u16 val = X;

        X = (((s16)X) >> 1);
        SetNZC((X & 0x8000), (!X), (val & 0x0001));
    }
    return 2;
}

template int STM8::OP_SRAW<false>();
template int STM8::OP_SRAW<true>();


int STM8::OP_SRL_A()
{
    u8 val = A;

    A >>= 1;
    SetNZC((A & 0x80), (!A), (val & 0x01));
    return 1;
}

template<STM8::OperandType op, bool indY>
int STM8::OP_SRL_Mem()
{
    u32 addr = CPUFetchOpAddr<op, indY>();
    u8 val = MemRead(addr);

    u8 nval = val >> 1;
    MemWrite(addr, nval);
    SetNZC((nval & 0x80), (!nval), (val & 0x01));
    return OpIsIndirect(op) ? 4 : 1;
}

DeclTemplate(OP_SRL_Mem)


template<bool indY>
int STM8::OP_SRLW()
{
    if (indY)
    {
        u16 val = Y;

        Y >>= 1;
        SetNZC((Y & 0x8000), (!Y), (val & 0x0001));
    }
    else
    {
        u16 val = X;

        X >>= 1;
        SetNZC((X & 0x8000), (!X), (val & 0x0001));
    }
    return 2;
}

template int STM8::OP_SRLW<false>();
template int STM8::OP_SRLW<true>();


int STM8::OP_SUB_Imm()
{
    u8 a = A;
    u8 b = CPUFetch();

    // TODO: does SUB set the H flag or not?
    // both ADD and ADDW do, and SUBW does
    u8 val = a - b;
    A = val;
    SetFlagsSub(a, b, val, Flag_V|Flag_C);

    return 1;
}

template<STM8::OperandType op, bool indY>
int STM8::OP_SUB_Mem()
{
    u32 addr = CPUFetchOpAddr<op, indY>();

    u8 a = A;
    u8 b = MemRead(addr);

    u8 val = a - b;
    A = val;
    SetFlagsSub(a, b, val, Flag_V|Flag_C);

    return OpIsIndirect(op) ? 4 : 1;
}

DeclTemplate(OP_SUB_Mem)

int STM8::OP_SUB_SP()
{
    u16 b = CPUFetch();
    SP -= b;
    return 1;
}


template<bool indY>
int STM8::OP_SUBW_Imm()
{
    u16 a = indY ? Y : X;
    u16 b = (CPUFetch() << 8);
    b |= CPUFetch();

    u16 val = a - b;
    if (indY) Y = val;
    else      X = val;
    SetFlagsSub(a, b, val, Flag_V|Flag_C|Flag_H);

    return 2;
}

template int STM8::OP_SUBW_Imm<false>();
template int STM8::OP_SUBW_Imm<true>();

template<STM8::OperandType op, bool indY>
int STM8::OP_SUBW_Mem()
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
    if (indY) Y = val;
    else      X = val;
    SetFlagsSub(a, b, val, Flag_V|Flag_C|Flag_H);

    return OpIsIndirect(op) ? 5 : 2;
}

template int STM8::OP_SUBW_Mem<STM8::Op_LongDirect, false>();
template int STM8::OP_SUBW_Mem<STM8::Op_LongDirect, true>();
template int STM8::OP_SUBW_Mem<STM8::Op_ShortDirectSP, false>();
template int STM8::OP_SUBW_Mem<STM8::Op_ShortDirectSP, true>();


int STM8::OP_SWAP_A()
{
    A = (A >> 4) | (A << 4);
    SetNZ((A & 0x80), (!A));
    return 1;
}

template<STM8::OperandType op, bool indY>
int STM8::OP_SWAP_Mem()
{
    u32 addr = CPUFetchOpAddr<op, indY>();
    u8 val = MemRead(addr);

    val = (val >> 4) | (val << 4);
    MemWrite(addr, val);
    SetNZ((val & 0x80), (!val));
    return OpIsIndirect(op) ? 4 : 1;
}

DeclTemplate(OP_SWAP_Mem)


template<bool indY>
int STM8::OP_SWAPW()
{
    u16 ind = indY ? Y : X;

    ind = (ind >> 8) | (ind << 8);
    if (indY) Y = ind;
    else      X = ind;
    SetNZ((ind & 0x8000), (!ind));
    return 1;
}

template int STM8::OP_SWAPW<false>();
template int STM8::OP_SWAPW<true>();


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


template<bool indY>
int STM8::OP_TNZW()
{
    u16 ind = indY ? Y : X;

    SetNZ((ind & 0x8000), (!ind));
    return 2;
}

template int STM8::OP_TNZW<false>();
template int STM8::OP_TNZW<true>();


int STM8::OP_XOR_Imm()
{
    u8 val = CPUFetch();
    val ^= A;

    A = val;
    SetNZ((val & 0x80), (!val));
    return 1;
}

template<STM8::OperandType op, bool indY>
int STM8::OP_XOR_Mem()
{
    u32 addr = CPUFetchOpAddr<op, indY>();
    u8 val = MemRead(addr);
    val ^= A;

    A = val;
    SetNZ((val & 0x80), (!val));
    return OpIsIndirect(op) ? 4 : 1;
}

DeclTemplate(OP_XOR_Mem)
