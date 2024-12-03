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

int OP_UNK();

int OP_Prefix90();

template<ConditionCode cond> int OP_JRcc();
int OP_INT();

int OP_LD_Imm();
template<OperandType op, bool indY> int OP_LD_A();

template<bool indY> int OP_LDW_Imm();
template<OperandType op, bool indY> int OP_LDW_Ind();
int OP_LDW_SP_X();

typedef int (STM8::*InstrFunc)();

InstrFunc InstrTable[256] =
{
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, // 00
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, // 10
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_LDW_Ind<Op_ShortDirectSP,true>, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_LDW_Ind<Op_ShortDirectSP,false>, &STM8::OP_UNK,
    &STM8::OP_JRcc<Cond_T>, &STM8::OP_JRcc<Cond_F>, &STM8::OP_JRcc<Cond_UGT>, &STM8::OP_JRcc<Cond_ULE>, // 20
    &STM8::OP_JRcc<Cond_UGE>, &STM8::OP_JRcc<Cond_ULT>, &STM8::OP_JRcc<Cond_NE>, &STM8::OP_JRcc<Cond_EQ>,
    &STM8::OP_JRcc<Cond_NV>, &STM8::OP_JRcc<Cond_V>, &STM8::OP_JRcc<Cond_PL>, &STM8::OP_JRcc<Cond_MI>,
    &STM8::OP_JRcc<Cond_SGT>, &STM8::OP_JRcc<Cond_SLE>, &STM8::OP_JRcc<Cond_SGE>, &STM8::OP_JRcc<Cond_SLT>,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, // 30
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, // 40
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, // 50
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, // 60
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, // 70
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_LD_A<Op_ShortDirectSP,false>,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_INT, &STM8::OP_UNK, // 80
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_Prefix90, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, // 90
    &STM8::OP_LDW_SP_X, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, // A0
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_LD_Imm, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_LDW_Imm<false>, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, // B0
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_LD_A<Op_ShortDirect,false>, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_LDW_Ind<Op_ShortDirect,false>, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, // C0
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_LD_A<Op_LongDirect,false>, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_LDW_Ind<Op_LongDirect,false>, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, // D0
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_LD_A<Op_LongDirectInd,false>, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_LDW_Ind<Op_LongDirectInd,false>, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, // E0
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_LD_A<Op_ShortDirectInd,false>, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_LDW_Ind<Op_ShortDirectInd,false>, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, // F0
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_LD_A<Op_Ind,false>, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_LDW_Ind<Op_Ind,false>, &STM8::OP_UNK
};

InstrFunc InstrTable90[256] =
{
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, // 00
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, // 10
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, // 20
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_JRcc<Cond_NH>, &STM8::OP_JRcc<Cond_H>, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, // 30
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, // 40
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, // 50
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, // 60
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, // 70
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, // 80
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, // 90
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, // A0
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_LDW_Imm<true>, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, // B0
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_LDW_Ind<Op_ShortDirect,true>, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, // C0
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_LDW_Ind<Op_LongDirect,true>, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, // D0
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_LD_A<Op_LongDirectInd,true>, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_LDW_Ind<Op_LongDirectInd,true>, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, // E0
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_LD_A<Op_ShortDirectInd,true>, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_LDW_Ind<Op_ShortDirectInd,true>, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, // F0
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_LD_A<Op_Ind,true>, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_LDW_Ind<Op_Ind,true>, &STM8::OP_UNK
};
