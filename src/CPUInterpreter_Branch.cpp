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


int STM8::OP_CALL_Imm()
{
    u32 dst = (CPUFetch() << 8);
    dst |= CPUFetch();

    MemWrite(SP--, PC & 0xFF);
    MemWrite(SP--, (PC >> 8) & 0xFF);

    CPUJumpTo((PC & 0xFF0000) | dst);
    return 4;
}


int STM8::OP_CALLR()
{
    s8 offset = (s8)CPUFetch();

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


int STM8::OP_JPF_Imm()
{
    u32 dst = (CPUFetch() << 16);
    dst |= (CPUFetch() << 8);
    dst |= CPUFetch();

    CPUJumpTo(dst);
    return 2;
}

int STM8::OP_JPF_Mem()
{
    u32 dst = CPUFetchOpAddr<Op_ExtendedIndirect>();

    CPUJumpTo(dst);
    return 6;
}


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
    return 4;
}
