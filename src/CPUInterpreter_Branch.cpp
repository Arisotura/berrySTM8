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


template<int bit>
int STM8::OP_BTJF()
{
    u32 addr = CPUFetchOpAddr<Op_LongDirect>();
    s8 offset = (s8)CPUFetch();

    u8 val = MemRead(addr);
    if (!(val & (1<<bit)))
    {
        CC |= Flag_C;
        CPUJumpTo(PC + offset);
        return 3;
    }

    CC &= ~Flag_C;
    return 2;
}

template int STM8::OP_BTJF<0>();
template int STM8::OP_BTJF<1>();
template int STM8::OP_BTJF<2>();
template int STM8::OP_BTJF<3>();
template int STM8::OP_BTJF<4>();
template int STM8::OP_BTJF<5>();
template int STM8::OP_BTJF<6>();
template int STM8::OP_BTJF<7>();


template<int bit>
int STM8::OP_BTJT()
{
    u32 addr = CPUFetchOpAddr<Op_LongDirect>();
    s8 offset = (s8)CPUFetch();

    u8 val = MemRead(addr);
    if (val & (1<<bit))
    {
        CC |= Flag_C;
        CPUJumpTo(PC + offset);
        return 3;
    }

    CC &= ~Flag_C;
    return 2;
}

template int STM8::OP_BTJT<0>();
template int STM8::OP_BTJT<1>();
template int STM8::OP_BTJT<2>();
template int STM8::OP_BTJT<3>();
template int STM8::OP_BTJT<4>();
template int STM8::OP_BTJT<5>();
template int STM8::OP_BTJT<6>();
template int STM8::OP_BTJT<7>();


// call stack debug
u32 call_pc[200];
u32 call_sp[200];
int call_level = 0;


template<STM8::OperandType op, bool indY>
int STM8::OP_CALL()
{
    u32 dst = CPUFetchOpAddr<op, indY>();

    call_pc[call_level] = PC;
    call_sp[call_level] = SP;
    call_level++;

    MemWrite(SP--, PC & 0xFF);
    MemWrite(SP--, (PC >> 8) & 0xFF);

    CPUJumpTo((PC & 0xFF0000) | dst);
    return OpIsIndirect(op) ? 6 : 4;
}

template int STM8::OP_CALL<STM8::Op_LongDirect,false>();
template int STM8::OP_CALL<STM8::Op_Ind,false>();
template int STM8::OP_CALL<STM8::Op_Ind,true>();
template int STM8::OP_CALL<STM8::Op_ShortDirectInd,false>();
template int STM8::OP_CALL<STM8::Op_ShortDirectInd,true>();
template int STM8::OP_CALL<STM8::Op_LongDirectInd,false>();
template int STM8::OP_CALL<STM8::Op_LongDirectInd,true>();
template int STM8::OP_CALL<STM8::Op_ShortIndirect,false>();
template int STM8::OP_CALL<STM8::Op_LongIndirect,false>();
template int STM8::OP_CALL<STM8::Op_ShortIndirectInd,false>();
template int STM8::OP_CALL<STM8::Op_ShortIndirectInd,true>();
template int STM8::OP_CALL<STM8::Op_LongIndirectInd,false>();



template<STM8::OperandType op>
int STM8::OP_CALLF()
{
    u32 dst = CPUFetchOpAddr<op>();

    MemWrite(SP--, PC & 0xFF);
    MemWrite(SP--, (PC >> 8) & 0xFF);
    MemWrite(SP--, (PC >> 16) & 0xFF);

    CPUJumpTo(dst);
    return OpIsIndirect(op) ? 8 : 5;
}

template int STM8::OP_CALLF<STM8::Op_ExtendedDirect>();
template int STM8::OP_CALLF<STM8::Op_ExtendedIndirect>();


int STM8::OP_CALLR()
{
    s8 offset = (s8)CPUFetch();

    call_pc[call_level] = PC;
    call_sp[call_level] = SP;
    call_level++;

    MemWrite(SP--, PC & 0xFF);
    MemWrite(SP--, (PC >> 8) & 0xFF);

    CPUJumpTo(PC + offset);
    return 4;
}


int STM8::OP_INT()
{
    u32 dst = (CPUFetch() << 16);
    dst |= (CPUFetch() << 8);
    dst |= CPUFetch();

    CPUJumpTo(dst);
    return 2;
}


int STM8::OP_IRET()
{
    CC = MemRead(++SP);
    A = MemRead(++SP);
    X = (MemRead(++SP) << 8);
    X |= MemRead(++SP);
    Y = (MemRead(++SP) << 8);
    Y |= MemRead(++SP);
    u32 pc = (MemRead(++SP) << 16);
    pc |= (MemRead(++SP) << 8);
    pc |= MemRead(++SP);

    CPUJumpTo(pc);
    UpdateIRQ();
    return 11;
}


template<STM8::OperandType op, bool indY>
int STM8::OP_JP()
{
    u32 dst = CPUFetchOpAddr<op, indY>();

    CPUJumpTo((PC & 0xFF0000) | dst);
    if (OpIsIndirect(op))
        return 5;
    else if ((op == Op_ShortDirectInd || op == Op_LongDirectInd) && indY)
        return 2; // ???
    else
        return 1;
}

template int STM8::OP_JP<STM8::Op_LongDirect,false>();
template int STM8::OP_JP<STM8::Op_Ind,false>();
template int STM8::OP_JP<STM8::Op_Ind,true>();
template int STM8::OP_JP<STM8::Op_ShortDirectInd,false>();
template int STM8::OP_JP<STM8::Op_ShortDirectInd,true>();
template int STM8::OP_JP<STM8::Op_LongDirectInd,false>();
template int STM8::OP_JP<STM8::Op_LongDirectInd,true>();
template int STM8::OP_JP<STM8::Op_ShortIndirect,false>();
template int STM8::OP_JP<STM8::Op_LongIndirect,false>();
template int STM8::OP_JP<STM8::Op_ShortIndirectInd,false>();
template int STM8::OP_JP<STM8::Op_ShortIndirectInd,true>();
template int STM8::OP_JP<STM8::Op_LongIndirectInd,false>();


template<STM8::OperandType op>
int STM8::OP_JPF()
{
    u32 dst = CPUFetchOpAddr<op>();

    CPUJumpTo(dst);
    return OpIsIndirect(op) ? 6 : 2;
}

template int STM8::OP_JPF<STM8::Op_ExtendedDirect>();
template int STM8::OP_JPF<STM8::Op_ExtendedIndirect>();


template<STM8::ConditionCode cond>
int STM8::OP_JRcc()
{
    s8 offset = (s8)CPUFetch();

    bool jump;
    switch (cond)
    {
    case Cond_T: jump = true; break;
    case Cond_F: jump = false; break;
    case Cond_EQ: jump =  (CC & Flag_Z); break;
    case Cond_NE: jump = !(CC & Flag_Z); break;
    case Cond_H:  jump =  (CC & Flag_H); break;
    case Cond_NH: jump = !(CC & Flag_H); break;
    case Cond_MI: jump =  (CC & Flag_N); break;
    case Cond_PL: jump = !(CC & Flag_N); break;
    case Cond_V:  jump =  (CC & Flag_V); break;
    case Cond_NV: jump = !(CC & Flag_V); break;
    case Cond_SGE: jump = !((!!(CC & Flag_N)) ^ (!!(CC & Flag_V))); break;
    case Cond_SGT: jump = !((!!(CC & Flag_Z)) | ((!!(CC & Flag_N)) ^ (!!(CC & Flag_V)))); break;
    case Cond_SLE: jump =  ((!!(CC & Flag_Z)) | ((!!(CC & Flag_N)) ^ (!!(CC & Flag_V)))); break;
    case Cond_SLT: jump =  ((!!(CC & Flag_N)) ^ (!!(CC & Flag_V))); break;
    case Cond_UGE: jump = !(CC & Flag_C); break;
    case Cond_UGT: jump = (!(CC & Flag_C)) && (!(CC & Flag_Z)); break;
    case Cond_ULE: jump = (CC & Flag_C) || (CC & Flag_Z); break;
    case Cond_ULT: jump =  (CC & Flag_C); break;
    default: return 0; // ???
    }

    if (!jump) return 1;

    CPUJumpTo(PC + offset);
    return 2;
}

template int STM8::OP_JRcc<STM8::Cond_T>();
template int STM8::OP_JRcc<STM8::Cond_F>();
template int STM8::OP_JRcc<STM8::Cond_EQ>();
template int STM8::OP_JRcc<STM8::Cond_NE>();
template int STM8::OP_JRcc<STM8::Cond_H>();
template int STM8::OP_JRcc<STM8::Cond_NH>();
template int STM8::OP_JRcc<STM8::Cond_MI>();
template int STM8::OP_JRcc<STM8::Cond_PL>();
template int STM8::OP_JRcc<STM8::Cond_V>();
template int STM8::OP_JRcc<STM8::Cond_NV>();
template int STM8::OP_JRcc<STM8::Cond_SGE>();
template int STM8::OP_JRcc<STM8::Cond_SGT>();
template int STM8::OP_JRcc<STM8::Cond_SLE>();
template int STM8::OP_JRcc<STM8::Cond_SLT>();
template int STM8::OP_JRcc<STM8::Cond_UGE>();
template int STM8::OP_JRcc<STM8::Cond_UGT>();
template int STM8::OP_JRcc<STM8::Cond_ULE>();
template int STM8::OP_JRcc<STM8::Cond_ULT>();


int STM8::OP_RET()
{
    u16 pc = (MemRead(++SP) << 8);
    pc |= MemRead(++SP);

    CPUJumpTo((PC & 0xFF0000) | pc);

    if (call_level == 0)
    {
        printf("!! CALL STACK FUCKED: RET BUT LEVEL IS 0\n");
    }
    else
    {
        call_level--;
        printf("RET: PC=%06X/%06X SP=%06X/%06X\n", PC, call_pc[call_level], SP, call_sp[call_level]);
        if (PC != call_pc[call_level]) printf("!!! CALL STACK FUCKED: BAD PC\n");
        if (SP != call_sp[call_level]) printf("!!! CALL STACK FUCKED: BAD SP\n");
    }

    return 4;
}


int STM8::OP_RETF()
{
    u16 pc = (MemRead(++SP) << 16);
    pc |= (MemRead(++SP) << 8);
    pc |= MemRead(++SP);

    CPUJumpTo(pc);
    return 5;
}
