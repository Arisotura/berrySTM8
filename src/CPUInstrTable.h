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

int OP_Prefix72();
int OP_Prefix90();
int OP_Prefix91();
int OP_Prefix92();

int OP_BCP_Imm();

template<bool indY> int OP_CPW_Imm();
template<STM8::OperandType op, bool indY> int OP_CPW_Ind();

template<bool indY> int OP_INCW();

template<ConditionCode cond> int OP_JRcc();
int OP_INT();

int OP_LD_Imm();
template<OperandType op, bool indY> int OP_LD_A();
template<OperandType op, bool indY> int OP_LD_Mem();
int OP_LD_XL_A();
int OP_LD_A_XL();
int OP_LD_YL_A();
int OP_LD_A_YL();
int OP_LD_XH_A();
int OP_LD_A_XH();
int OP_LD_YH_A();
int OP_LD_A_YH();

template<bool indY> int OP_LDW_Imm();
template<OperandType op, bool indY> int OP_LDW_Ind();
template<OperandType op, bool indY> int OP_LDW_Mem();
int OP_LDW_Y_X();
int OP_LDW_X_Y();
int OP_LDW_X_SP();
int OP_LDW_SP_X();
int OP_LDW_Y_SP();
int OP_LDW_SP_Y();

typedef int (STM8::*InstrFunc)();

InstrFunc InstrTable[256] =
{
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, // 00
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_CPW_Ind<Op_ShortDirectSP,false>, // 10
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_LDW_Ind<Op_ShortDirectSP,true>, &STM8::OP_LDW_Mem<Op_ShortDirectSP,true>,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_LDW_Ind<Op_ShortDirectSP,false>, &STM8::OP_LDW_Mem<Op_ShortDirectSP,false>,
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
    &STM8::OP_INCW<false>, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, // 60
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_LD_Mem<Op_ShortDirectSP,false>,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_Prefix72, &STM8::OP_UNK, // 70
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_LD_A<Op_ShortDirectSP,false>,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_INT, &STM8::OP_UNK, // 80
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_Prefix90, &STM8::OP_Prefix91, &STM8::OP_Prefix92, &STM8::OP_LDW_X_Y, // 90
    &STM8::OP_LDW_SP_X, &STM8::OP_LD_XH_A, &STM8::OP_LDW_X_SP, &STM8::OP_LD_XL_A,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_LD_A_XH, &STM8::OP_LD_A_XL,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_CPW_Imm<false>, // A0
    &STM8::OP_UNK, &STM8::OP_BCP_Imm, &STM8::OP_LD_Imm, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_LDW_Imm<false>, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_CPW_Ind<Op_ShortDirect,false>, // B0
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_LD_A<Op_ShortDirect,false>, &STM8::OP_LD_Mem<Op_ShortDirect,false>,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_LDW_Ind<Op_ShortDirect,false>, &STM8::OP_LDW_Mem<Op_ShortDirect,false>,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_CPW_Ind<Op_LongDirect,false>, // C0
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_LD_A<Op_LongDirect,false>, &STM8::OP_LD_Mem<Op_LongDirect,false>,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_LDW_Ind<Op_LongDirect,false>, &STM8::OP_LDW_Mem<Op_LongDirect,false>,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_CPW_Ind<Op_LongDirectInd,false>, // D0
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_LD_A<Op_LongDirectInd,false>, &STM8::OP_LD_Mem<Op_LongDirectInd,false>,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_LDW_Ind<Op_LongDirectInd,false>, &STM8::OP_LDW_Mem<Op_LongDirectInd,false>,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_CPW_Ind<Op_ShortDirectInd,false>, // E0
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_LD_A<Op_ShortDirectInd,false>, &STM8::OP_LD_Mem<Op_ShortDirectInd,false>,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_LDW_Ind<Op_ShortDirectInd,false>, &STM8::OP_LDW_Mem<Op_ShortDirectInd,false>,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_CPW_Ind<Op_Ind,false>, // F0
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_LD_A<Op_Ind,false>, &STM8::OP_LD_Mem<Op_Ind,false>,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_LDW_Ind<Op_Ind,false>, &STM8::OP_LDW_Mem<Op_Ind,false>
};

InstrFunc InstrTable72[256] =
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
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
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
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, // B0
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_CPW_Ind<Op_LongIndirect,false>, // C0
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_LD_A<Op_LongIndirect,false>, &STM8::OP_LD_Mem<Op_LongIndirect,false>,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_LDW_Ind<Op_LongIndirect,false>, &STM8::OP_LDW_Mem<Op_LongIndirect,false>,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_CPW_Ind<Op_LongIndirectInd,false>, // D0
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_LD_A<Op_LongIndirectInd,false>, &STM8::OP_LD_Mem<Op_LongIndirectInd,false>,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_LDW_Ind<Op_LongIndirectInd,false>, &STM8::OP_LDW_Mem<Op_LongIndirectInd,false>,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, // E0
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, // F0
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK
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
    &STM8::OP_INCW<true>, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
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
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_LDW_Y_X, // 90
    &STM8::OP_LDW_SP_Y, &STM8::OP_LD_YH_A, &STM8::OP_LDW_Y_SP, &STM8::OP_LD_YL_A,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_LD_A_YH, &STM8::OP_LD_A_YL,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_CPW_Imm<true>, // A0
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_LDW_Imm<true>, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_CPW_Ind<Op_ShortDirect,true>, // B0
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_LDW_Ind<Op_ShortDirect,true>, &STM8::OP_LDW_Mem<Op_ShortDirect,true>,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_CPW_Ind<Op_LongDirect,true>, // C0
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_LDW_Ind<Op_LongDirect,true>, &STM8::OP_LDW_Mem<Op_LongDirect,true>,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_CPW_Ind<Op_LongDirectInd,true>, // D0
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_LD_A<Op_LongDirectInd,true>, &STM8::OP_LD_Mem<Op_LongDirectInd,true>,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_LDW_Ind<Op_LongDirectInd,true>, &STM8::OP_LDW_Mem<Op_LongDirectInd,true>,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_CPW_Ind<Op_ShortDirectInd,true>, // E0
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_LD_A<Op_ShortDirectInd,true>, &STM8::OP_LD_Mem<Op_ShortDirectInd,true>,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_LDW_Ind<Op_ShortDirectInd,true>, &STM8::OP_LDW_Mem<Op_ShortDirectInd,true>,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_CPW_Ind<Op_Ind,true>, // F0
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_LD_A<Op_Ind,true>, &STM8::OP_LD_Mem<Op_Ind,true>,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_LDW_Ind<Op_Ind,true>, &STM8::OP_LDW_Mem<Op_Ind,true>
};

InstrFunc InstrTable91[256] =
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
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
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
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, // B0
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_CPW_Ind<Op_ShortIndirect,true>, // C0
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_LDW_Ind<Op_ShortIndirect,true>, &STM8::OP_LDW_Mem<Op_ShortIndirect,true>,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_CPW_Ind<Op_ShortIndirectInd,true>, // D0
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_LD_A<Op_ShortIndirectInd,true>, &STM8::OP_LD_Mem<Op_ShortIndirectInd,true>,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_LDW_Ind<Op_ShortIndirectInd,true>, &STM8::OP_LDW_Mem<Op_ShortIndirectInd,true>,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, // E0
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, // F0
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK
};

InstrFunc InstrTable92[256] =
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
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
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
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, // B0
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_CPW_Ind<Op_ShortIndirect,false>, // C0
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_LD_A<Op_ShortIndirect,false>, &STM8::OP_LD_Mem<Op_ShortIndirect,false>,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_LDW_Ind<Op_ShortIndirect,false>, &STM8::OP_LDW_Mem<Op_ShortIndirect,false>,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_CPW_Ind<Op_ShortIndirectInd,false>, // D0
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_LD_A<Op_ShortIndirectInd,false>, &STM8::OP_LD_Mem<Op_ShortIndirectInd,false>,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_LDW_Ind<Op_ShortIndirectInd,false>, &STM8::OP_LDW_Mem<Op_ShortIndirectInd,false>,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, // E0
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, // F0
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK
};
