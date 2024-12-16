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
int OP_CCF();
int OP_NOP();
int OP_RCF();
int OP_RIM();
int OP_RVF();
int OP_SIM();
int OP_SCF();
int OP_Prefix72();
int OP_Prefix90();
int OP_Prefix91();
int OP_Prefix92();

int OP_ADC_Imm();
template<OperandType op, bool indY> int OP_ADC_Mem();
int OP_ADD_Imm();
template<OperandType op, bool indY> int OP_ADD_Mem();
template<bool indY> int OP_ADDW_Imm();
template<OperandType op, bool indY> int OP_ADDW_Mem();
int OP_ADDW_SP();
int OP_AND_Imm();
template<OperandType op, bool indY> int OP_AND_Mem();
template<int bit> int OP_BRES();
template<int bit> int OP_BSET();
int OP_BCP_Imm();
template<OperandType op, bool indY> int OP_BCP_Mem();
int OP_CLR_A();
template<OperandType op, bool indY> int OP_CLR_Mem();
template<bool indY> int OP_CLRW();
int OP_CP_Imm();
template<OperandType op, bool indY> int OP_CP_Mem();
int OP_CPL_A();
template<OperandType op, bool indY> int OP_CPL_Mem();
template<bool indY> int OP_CPLW();
template<bool indY> int OP_CPW_Imm();
template<OperandType op, bool indY> int OP_CPW_Mem();
int OP_DEC_A();
template<OperandType op, bool indY> int OP_DEC_Mem();
template<bool indY> int OP_DECW();
int OP_INC_A();
template<OperandType op, bool indY> int OP_INC_Mem();
template<bool indY> int OP_INCW();
template<bool indY> int OP_MUL();
int OP_NEG_A();
template<OperandType op, bool indY> int OP_NEG_Mem();
template<bool intY> int OP_NEGW();
int OP_OR_Imm();
template<OperandType op, bool indY> int OP_OR_Mem();
template<bool indY> int OP_RLWA();
int OP_RRC_A();
template<OperandType op, bool indY> int OP_RRC_Mem();
template<bool indY> int OP_RRWA();
int OP_SBC_Imm();
template<OperandType op, bool indY> int OP_SBC_Mem();
int OP_SLL_A();
template<OperandType op, bool indY> int OP_SLL_Mem();
template<bool indY> int OP_SLLW();
int OP_SRL_A();
template<OperandType op, bool indY> int OP_SRL_Mem();
template<bool indY> int OP_SRLW();
int OP_SUB_Imm();
template<OperandType op, bool indY> int OP_SUB_Mem();
int OP_SUB_SP();
template<bool indY> int OP_SUBW_Imm();
template<OperandType op, bool indY> int OP_SUBW_Mem();
template<bool indY> int OP_SWAPW();
int OP_TNZ_A();
template<OperandType op, bool indY> int OP_TNZ_Mem();
template<bool indY> int OP_TNZW();
int OP_XOR_Imm();
template<OperandType op, bool indY> int OP_XOR_Mem();

template<int bit> int OP_BTJF();
template<int bit> int OP_BTJT();
template<OperandType op, bool indY> int OP_CALL();
template<OperandType op> int OP_CALLF();
int OP_CALLR();
int OP_INT();
int OP_IRET();
template<OperandType op, bool indY> int OP_JP();
template<OperandType op> int OP_JPF();
template<ConditionCode cond> int OP_JRcc();
int OP_RET();
int OP_RETF();

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
int OP_MOV_Imm();
template<OperandType op> int OP_MOV_Mem();
int OP_POP_A();
int OP_POP_CC();
int OP_POP_Mem();
template<bool indY> int OP_POPW();
int OP_PUSH_A();
int OP_PUSH_CC();
int OP_PUSH_Imm();
int OP_PUSH_Mem();
template<bool indY> int OP_PUSHW();

typedef int (STM8::*InstrFunc)();

InstrFunc InstrTable[256] =
{
    // 00
    &STM8::OP_NEG_Mem<Op_ShortDirectSP,false>, &STM8::OP_RRWA<false>,                     &STM8::OP_RLWA<false>,                     &STM8::OP_CPL_Mem<Op_ShortDirectSP,false>,
    &STM8::OP_SRL_Mem<Op_ShortDirectSP,false>, &STM8::OP_UNK,                             &STM8::OP_RRC_Mem<Op_ShortDirectSP,false>, &STM8::OP_UNK,
    &STM8::OP_SLL_Mem<Op_ShortDirectSP,false>, &STM8::OP_UNK,                             &STM8::OP_DEC_Mem<Op_ShortDirectSP,false>, &STM8::OP_UNK,
    &STM8::OP_INC_Mem<Op_ShortDirectSP,false>, &STM8::OP_TNZ_Mem<Op_ShortDirectSP,false>, &STM8::OP_UNK,                             &STM8::OP_CLR_Mem<Op_ShortDirectSP,false>,

    // 10
    &STM8::OP_SUB_Mem<Op_ShortDirectSP,false>, &STM8::OP_CP_Mem<Op_ShortDirectSP,false>, &STM8::OP_UNK,                             &STM8::OP_CPW_Mem<Op_ShortDirectSP,false>,
    &STM8::OP_AND_Mem<Op_ShortDirectSP,false>, &STM8::OP_UNK,                            &STM8::OP_LDW_Ind<Op_ShortDirectSP,true>,  &STM8::OP_LDW_Mem<Op_ShortDirectSP,true>,
    &STM8::OP_XOR_Mem<Op_ShortDirectSP,false>, &STM8::OP_UNK,                            &STM8::OP_OR_Mem<Op_ShortDirectSP,false>,  &STM8::OP_ADD_Mem<Op_ShortDirectSP,false>,
    &STM8::OP_ADDW_Imm<false>,                 &STM8::OP_SUBW_Imm<false>,                &STM8::OP_LDW_Ind<Op_ShortDirectSP,false>, &STM8::OP_LDW_Mem<Op_ShortDirectSP,false>,

    // 20
    &STM8::OP_JRcc<Cond_T>,   &STM8::OP_JRcc<Cond_F>,   &STM8::OP_JRcc<Cond_UGT>, &STM8::OP_JRcc<Cond_ULE>,
    &STM8::OP_JRcc<Cond_UGE>, &STM8::OP_JRcc<Cond_ULT>, &STM8::OP_JRcc<Cond_NE>,  &STM8::OP_JRcc<Cond_EQ>,
    &STM8::OP_JRcc<Cond_NV>,  &STM8::OP_JRcc<Cond_V>,   &STM8::OP_JRcc<Cond_PL>,  &STM8::OP_JRcc<Cond_MI>,
    &STM8::OP_JRcc<Cond_SGT>, &STM8::OP_JRcc<Cond_SLE>, &STM8::OP_JRcc<Cond_SGE>, &STM8::OP_JRcc<Cond_SLT>,

    // 30
    &STM8::OP_NEG_Mem<Op_ShortDirect,false>, &STM8::OP_UNK,                           &STM8::OP_POP_Mem,                       &STM8::OP_CPL_Mem<Op_ShortDirect,false>,
    &STM8::OP_SRL_Mem<Op_ShortDirect,false>, &STM8::OP_MOV_Imm,                       &STM8::OP_RRC_Mem<Op_ShortDirect,false>, &STM8::OP_UNK,
    &STM8::OP_SLL_Mem<Op_ShortDirect,false>, &STM8::OP_UNK,                           &STM8::OP_DEC_Mem<Op_ShortDirect,false>, &STM8::OP_PUSH_Mem,
    &STM8::OP_INC_Mem<Op_ShortDirect,false>, &STM8::OP_TNZ_Mem<Op_ShortDirect,false>, &STM8::OP_UNK,                           &STM8::OP_CLR_Mem<Op_ShortDirect,false>,

    // 40
    &STM8::OP_NEG_A, &STM8::OP_UNK,                     &STM8::OP_MUL<false>, &STM8::OP_CPL_A,
    &STM8::OP_SRL_A, &STM8::OP_MOV_Mem<Op_ShortDirect>, &STM8::OP_RRC_A,      &STM8::OP_UNK,
    &STM8::OP_SLL_A, &STM8::OP_UNK,                     &STM8::OP_DEC_A,      &STM8::OP_PUSH_Imm,
    &STM8::OP_INC_A, &STM8::OP_TNZ_A,                   &STM8::OP_UNK,        &STM8::OP_CLR_A,

    // 50
    &STM8::OP_NEGW<false>, &STM8::OP_UNK,                    &STM8::OP_SUB_SP,       &STM8::OP_CPLW<false>,
    &STM8::OP_SRLW<false>, &STM8::OP_MOV_Mem<Op_LongDirect>, &STM8::OP_UNK,          &STM8::OP_UNK,
    &STM8::OP_SLLW<false>, &STM8::OP_UNK,                    &STM8::OP_DECW<false>,  &STM8::OP_ADDW_SP,
    &STM8::OP_INCW<false>, &STM8::OP_TNZW<false>,            &STM8::OP_SWAPW<false>, &STM8::OP_CLRW<false>,

    // 60
    &STM8::OP_NEG_Mem<Op_ShortDirectInd,false>, &STM8::OP_UNK,                              &STM8::OP_UNK,                              &STM8::OP_CPL_Mem<Op_ShortDirectInd,false>,
    &STM8::OP_SRL_Mem<Op_ShortDirectInd,false>, &STM8::OP_UNK,                              &STM8::OP_RRC_Mem<Op_ShortDirectInd,false>, &STM8::OP_UNK,
    &STM8::OP_SLL_Mem<Op_ShortDirectInd,false>, &STM8::OP_UNK,                              &STM8::OP_DEC_Mem<Op_ShortDirectInd,false>, &STM8::OP_LD_Mem<Op_ShortDirectSP,false>,
    &STM8::OP_INC_Mem<Op_ShortDirectInd,false>, &STM8::OP_TNZ_Mem<Op_ShortDirectInd,false>, &STM8::OP_UNK,                              &STM8::OP_CLR_Mem<Op_ShortDirectInd,false>,

    // 70
    &STM8::OP_NEG_Mem<Op_Ind,false>, &STM8::OP_UNK,                   &STM8::OP_Prefix72,              &STM8::OP_CPL_Mem<Op_Ind,false>,
    &STM8::OP_SRL_Mem<Op_Ind,false>, &STM8::OP_UNK,                   &STM8::OP_RRC_Mem<Op_Ind,false>, &STM8::OP_UNK,
    &STM8::OP_SLL_Mem<Op_Ind,false>, &STM8::OP_UNK,                   &STM8::OP_DEC_Mem<Op_Ind,false>, &STM8::OP_LD_A<Op_ShortDirectSP,false>,
    &STM8::OP_INC_Mem<Op_Ind,false>, &STM8::OP_TNZ_Mem<Op_Ind,false>, &STM8::OP_UNK,                   &STM8::OP_CLR_Mem<Op_Ind,false>,

    // 80
    &STM8::OP_IRET,   &STM8::OP_RET,          &STM8::OP_INT,     &STM8::OP_UNK,
    &STM8::OP_POP_A,  &STM8::OP_POPW<false>,  &STM8::OP_POP_CC,  &STM8::OP_RETF,
    &STM8::OP_PUSH_A, &STM8::OP_PUSHW<false>, &STM8::OP_PUSH_CC, &STM8::OP_UNK,
    &STM8::OP_CCF,    &STM8::OP_UNK,          &STM8::OP_UNK,     &STM8::OP_UNK,

    // 90
    &STM8::OP_Prefix90, &STM8::OP_Prefix91, &STM8::OP_Prefix92, &STM8::OP_LDW_X_Y,
    &STM8::OP_LDW_SP_X, &STM8::OP_LD_XH_A,  &STM8::OP_LDW_X_SP, &STM8::OP_LD_XL_A,
    &STM8::OP_RCF,      &STM8::OP_SCF,      &STM8::OP_RIM,      &STM8::OP_SIM,
    &STM8::OP_RVF,      &STM8::OP_NOP,      &STM8::OP_LD_A_XH,  &STM8::OP_LD_A_XL,

    // A0
    &STM8::OP_SUB_Imm,                &STM8::OP_CP_Imm,  &STM8::OP_SBC_Imm,        &STM8::OP_CPW_Imm<false>,
    &STM8::OP_AND_Imm,                &STM8::OP_BCP_Imm, &STM8::OP_LD_Imm,         &STM8::OP_UNK,
    &STM8::OP_XOR_Imm,                &STM8::OP_ADC_Imm, &STM8::OP_OR_Imm,         &STM8::OP_ADD_Imm,
    &STM8::OP_JPF<Op_ExtendedDirect>, &STM8::OP_CALLR,   &STM8::OP_LDW_Imm<false>, &STM8::OP_UNK,

    // B0
    &STM8::OP_SUB_Mem<Op_ShortDirect,false>, &STM8::OP_CP_Mem<Op_ShortDirect,false>,  &STM8::OP_SBC_Mem<Op_ShortDirect,false>, &STM8::OP_CPW_Mem<Op_ShortDirect,false>,
    &STM8::OP_AND_Mem<Op_ShortDirect,false>, &STM8::OP_BCP_Mem<Op_ShortDirect,false>, &STM8::OP_LD_A<Op_ShortDirect,false>,    &STM8::OP_LD_Mem<Op_ShortDirect,false>,
    &STM8::OP_XOR_Mem<Op_ShortDirect,false>, &STM8::OP_ADC_Mem<Op_ShortDirect,false>, &STM8::OP_OR_Mem<Op_ShortDirect,false>,  &STM8::OP_ADD_Mem<Op_ShortDirect,false>,
    &STM8::OP_UNK,                           &STM8::OP_CALLF<Op_ExtendedDirect>,      &STM8::OP_LDW_Ind<Op_ShortDirect,false>, &STM8::OP_LDW_Mem<Op_ShortDirect,false>,

    // C0
    &STM8::OP_SUB_Mem<Op_LongDirect,false>, &STM8::OP_CP_Mem<Op_LongDirect,false>,  &STM8::OP_SBC_Mem<Op_LongDirect,false>, &STM8::OP_CPW_Mem<Op_LongDirect,false>,
    &STM8::OP_AND_Mem<Op_LongDirect,false>, &STM8::OP_BCP_Mem<Op_LongDirect,false>, &STM8::OP_LD_A<Op_LongDirect,false>,    &STM8::OP_LD_Mem<Op_LongDirect,false>,
    &STM8::OP_XOR_Mem<Op_LongDirect,false>, &STM8::OP_ADC_Mem<Op_LongDirect,false>, &STM8::OP_OR_Mem<Op_LongDirect,false>,  &STM8::OP_ADD_Mem<Op_LongDirect,false>,
    &STM8::OP_JP<Op_LongDirect,false>,      &STM8::OP_CALL<Op_LongDirect,false>,    &STM8::OP_LDW_Ind<Op_LongDirect,false>, &STM8::OP_LDW_Mem<Op_LongDirect,false>,

    // D0
    &STM8::OP_SUB_Mem<Op_LongDirectInd,false>, &STM8::OP_CP_Mem<Op_LongDirectInd,false>,   &STM8::OP_SBC_Mem<Op_LongDirectInd,false>, &STM8::OP_CPW_Mem<Op_LongDirectInd,false>,
    &STM8::OP_AND_Mem<Op_LongDirectInd,false>, &STM8::OP_BCP_Mem<Op_LongDirectInd,false>,  &STM8::OP_LD_A<Op_LongDirectInd,false>,    &STM8::OP_LD_Mem<Op_LongDirectInd,false>,
    &STM8::OP_XOR_Mem<Op_LongDirectInd,false>, &STM8::OP_ADC_Mem<Op_LongDirectInd,false>,  &STM8::OP_OR_Mem<Op_LongDirectInd,false>,  &STM8::OP_ADD_Mem<Op_LongDirectInd,false>,
    &STM8::OP_JP<Op_LongDirectInd,false>,      &STM8::OP_CALL<Op_LongDirectInd,false>,     &STM8::OP_LDW_Ind<Op_LongDirectInd,false>, &STM8::OP_LDW_Mem<Op_LongDirectInd,false>,

    // E0
    &STM8::OP_SUB_Mem<Op_ShortDirectInd,false>, &STM8::OP_CP_Mem<Op_ShortDirectInd,false>,   &STM8::OP_SBC_Mem<Op_ShortDirectInd,false>, &STM8::OP_CPW_Mem<Op_ShortDirectInd,false>,
    &STM8::OP_AND_Mem<Op_ShortDirectInd,false>, &STM8::OP_BCP_Mem<Op_ShortDirectInd,false>,  &STM8::OP_LD_A<Op_ShortDirectInd,false>,    &STM8::OP_LD_Mem<Op_ShortDirectInd,false>,
    &STM8::OP_XOR_Mem<Op_ShortDirectInd,false>, &STM8::OP_ADC_Mem<Op_ShortDirectInd,false>,  &STM8::OP_OR_Mem<Op_ShortDirectInd,false>,  &STM8::OP_ADD_Mem<Op_ShortDirectInd,false>,
    &STM8::OP_JP<Op_ShortDirectInd,false>,      &STM8::OP_CALL<Op_ShortDirectInd,false>,     &STM8::OP_LDW_Ind<Op_ShortDirectInd,false>, &STM8::OP_LDW_Mem<Op_ShortDirectInd,false>,

    // F0
    &STM8::OP_SUB_Mem<Op_Ind,false>, &STM8::OP_CP_Mem<Op_Ind,false>,   &STM8::OP_SBC_Mem<Op_Ind,false>, &STM8::OP_CPW_Mem<Op_Ind,false>,
    &STM8::OP_AND_Mem<Op_Ind,false>, &STM8::OP_BCP_Mem<Op_Ind,false>,  &STM8::OP_LD_A<Op_Ind,false>,    &STM8::OP_LD_Mem<Op_Ind,false>,
    &STM8::OP_XOR_Mem<Op_Ind,false>, &STM8::OP_ADC_Mem<Op_Ind,false>,  &STM8::OP_OR_Mem<Op_Ind,false>,  &STM8::OP_ADD_Mem<Op_Ind,false>,
    &STM8::OP_JP<Op_Ind,false>,      &STM8::OP_CALL<Op_Ind,false>,     &STM8::OP_LDW_Ind<Op_Ind,false>, &STM8::OP_LDW_Mem<Op_Ind,false>
};

InstrFunc InstrTable72[256] =
{
    // 00
    &STM8::OP_BTJT<0>, &STM8::OP_BTJF<0>, &STM8::OP_BTJT<1>, &STM8::OP_BTJF<1>,
    &STM8::OP_BTJT<2>, &STM8::OP_BTJF<2>, &STM8::OP_BTJT<3>, &STM8::OP_BTJF<3>,
    &STM8::OP_BTJT<4>, &STM8::OP_BTJF<4>, &STM8::OP_BTJT<5>, &STM8::OP_BTJF<5>,
    &STM8::OP_BTJT<6>, &STM8::OP_BTJF<6>, &STM8::OP_BTJT<7>, &STM8::OP_BTJF<7>,

    // 10
    &STM8::OP_BSET<0>, &STM8::OP_BRES<0>, &STM8::OP_BSET<1>, &STM8::OP_BRES<1>,
    &STM8::OP_BSET<2>, &STM8::OP_BRES<2>, &STM8::OP_BSET<3>, &STM8::OP_BRES<3>,
    &STM8::OP_BSET<4>, &STM8::OP_BRES<4>, &STM8::OP_BSET<5>, &STM8::OP_BRES<5>,
    &STM8::OP_BSET<6>, &STM8::OP_BRES<6>, &STM8::OP_BSET<7>, &STM8::OP_BRES<7>,

    // 20
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,

    // 30
    &STM8::OP_NEG_Mem<Op_LongIndirect,false>, &STM8::OP_UNK,                            &STM8::OP_UNK,                            &STM8::OP_CPL_Mem<Op_LongIndirect,false>,
    &STM8::OP_SRL_Mem<Op_LongIndirect,false>, &STM8::OP_UNK,                            &STM8::OP_RRC_Mem<Op_LongIndirect,false>, &STM8::OP_UNK,
    &STM8::OP_SLL_Mem<Op_LongIndirect,false>, &STM8::OP_UNK,                            &STM8::OP_DEC_Mem<Op_LongIndirect,false>, &STM8::OP_UNK,
    &STM8::OP_INC_Mem<Op_LongIndirect,false>, &STM8::OP_TNZ_Mem<Op_LongIndirect,false>, &STM8::OP_UNK,                            &STM8::OP_CLR_Mem<Op_LongIndirect,false>,

    // 40
    &STM8::OP_NEG_Mem<Op_LongDirectInd,false>, &STM8::OP_UNK,                             &STM8::OP_UNK,                             &STM8::OP_CPL_Mem<Op_LongDirectInd,false>,
    &STM8::OP_SRL_Mem<Op_LongDirectInd,false>, &STM8::OP_UNK,                             &STM8::OP_RRC_Mem<Op_LongDirectInd,false>, &STM8::OP_UNK,
    &STM8::OP_SLL_Mem<Op_LongDirectInd,false>, &STM8::OP_UNK,                             &STM8::OP_DEC_Mem<Op_LongDirectInd,false>, &STM8::OP_UNK,
    &STM8::OP_INC_Mem<Op_LongDirectInd,false>, &STM8::OP_TNZ_Mem<Op_LongDirectInd,false>, &STM8::OP_UNK,                             &STM8::OP_CLR_Mem<Op_LongDirectInd,false>,

    // 50
    &STM8::OP_NEG_Mem<Op_LongDirect,false>, &STM8::OP_UNK,                          &STM8::OP_UNK,                          &STM8::OP_CPL_Mem<Op_LongDirect,false>,
    &STM8::OP_SRL_Mem<Op_LongDirect,false>, &STM8::OP_UNK,                          &STM8::OP_RRC_Mem<Op_LongDirect,false>, &STM8::OP_UNK,
    &STM8::OP_SLL_Mem<Op_LongDirect,false>, &STM8::OP_UNK,                          &STM8::OP_DEC_Mem<Op_LongDirect,false>, &STM8::OP_UNK,
    &STM8::OP_INC_Mem<Op_LongDirect,false>, &STM8::OP_TNZ_Mem<Op_LongDirect,false>, &STM8::OP_UNK,                          &STM8::OP_CLR_Mem<Op_LongDirect,false>,

    // 60
    &STM8::OP_NEG_Mem<Op_LongIndirectInd,false>, &STM8::OP_UNK,                               &STM8::OP_UNK,                               &STM8::OP_CPL_Mem<Op_LongIndirectInd,false>,
    &STM8::OP_SRL_Mem<Op_LongIndirectInd,false>, &STM8::OP_UNK,                               &STM8::OP_RRC_Mem<Op_LongIndirectInd,false>, &STM8::OP_UNK,
    &STM8::OP_SLL_Mem<Op_LongIndirectInd,false>, &STM8::OP_UNK,                               &STM8::OP_DEC_Mem<Op_LongIndirectInd,false>, &STM8::OP_UNK,
    &STM8::OP_INC_Mem<Op_LongIndirectInd,false>, &STM8::OP_TNZ_Mem<Op_LongIndirectInd,false>, &STM8::OP_UNK,                               &STM8::OP_CLR_Mem<Op_LongIndirectInd,false>,

    // 70
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,

    // 80
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,

    // 90
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,

    // A0
    &STM8::OP_UNK, &STM8::OP_UNK,            &STM8::OP_SUBW_Imm<true>, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK,            &STM8::OP_UNK,            &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_ADDW_Imm<true>, &STM8::OP_UNK,            &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK,            &STM8::OP_UNK,            &STM8::OP_UNK,

    // B0
    &STM8::OP_SUBW_Mem<Op_LongDirect,false>, &STM8::OP_UNK,                          &STM8::OP_SUBW_Mem<Op_LongDirect,true>, &STM8::OP_UNK,
    &STM8::OP_UNK,                           &STM8::OP_UNK,                          &STM8::OP_UNK,                          &STM8::OP_UNK,
    &STM8::OP_UNK,                           &STM8::OP_ADDW_Mem<Op_LongDirect,true>, &STM8::OP_UNK,                          &STM8::OP_ADDW_Mem<Op_LongDirect,false>,
    &STM8::OP_UNK,                           &STM8::OP_UNK,                          &STM8::OP_UNK,                          &STM8::OP_UNK,

    // C0
    &STM8::OP_SUB_Mem<Op_LongIndirect,false>, &STM8::OP_CP_Mem<Op_LongIndirect,false>,   &STM8::OP_SBC_Mem<Op_LongIndirect,false>, &STM8::OP_CPW_Mem<Op_LongIndirect,false>,
    &STM8::OP_AND_Mem<Op_LongIndirect,false>, &STM8::OP_BCP_Mem<Op_LongIndirect,false>,  &STM8::OP_LD_A<Op_LongIndirect,false>,    &STM8::OP_LD_Mem<Op_LongIndirect,false>,
    &STM8::OP_XOR_Mem<Op_LongIndirect,false>, &STM8::OP_ADC_Mem<Op_LongIndirect,false>,  &STM8::OP_OR_Mem<Op_LongIndirect,false>,  &STM8::OP_ADD_Mem<Op_LongIndirect,false>,
    &STM8::OP_JP<Op_LongIndirect,false>,      &STM8::OP_CALL<Op_LongIndirect,false>,     &STM8::OP_LDW_Ind<Op_LongIndirect,false>, &STM8::OP_LDW_Mem<Op_LongIndirect,false>,

    // D0
    &STM8::OP_SUB_Mem<Op_LongIndirectInd,false>, &STM8::OP_CP_Mem<Op_LongIndirectInd,false>,   &STM8::OP_SBC_Mem<Op_LongIndirectInd,false>, &STM8::OP_CPW_Mem<Op_LongIndirectInd,false>,
    &STM8::OP_AND_Mem<Op_LongIndirectInd,false>, &STM8::OP_BCP_Mem<Op_LongIndirectInd,false>,  &STM8::OP_LD_A<Op_LongIndirectInd,false>,    &STM8::OP_LD_Mem<Op_LongIndirectInd,false>,
    &STM8::OP_XOR_Mem<Op_LongIndirectInd,false>, &STM8::OP_ADC_Mem<Op_LongIndirectInd,false>,  &STM8::OP_OR_Mem<Op_LongIndirectInd,false>,  &STM8::OP_ADD_Mem<Op_LongIndirectInd,false>,
    &STM8::OP_JP<Op_LongIndirectInd,false>,      &STM8::OP_CALL<Op_LongIndirectInd,false>,     &STM8::OP_LDW_Ind<Op_LongIndirectInd,false>, &STM8::OP_LDW_Mem<Op_LongIndirectInd,false>,

    // E0
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,

    // F0
    &STM8::OP_SUBW_Mem<Op_ShortDirectSP,false>, &STM8::OP_UNK,                             &STM8::OP_SUBW_Mem<Op_ShortDirectSP,true>, &STM8::OP_UNK,
    &STM8::OP_UNK,                              &STM8::OP_UNK,                             &STM8::OP_UNK,                             &STM8::OP_UNK,
    &STM8::OP_UNK,                              &STM8::OP_ADDW_Mem<Op_ShortDirectSP,true>, &STM8::OP_UNK,                             &STM8::OP_ADDW_Mem<Op_ShortDirectSP,false>,
    &STM8::OP_UNK,                              &STM8::OP_UNK,                             &STM8::OP_UNK,                             &STM8::OP_UNK
};

InstrFunc InstrTable90[256] =
{
    // 00
    &STM8::OP_UNK, &STM8::OP_RRWA<true>, &STM8::OP_RLWA<true>, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK,        &STM8::OP_UNK,        &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK,        &STM8::OP_UNK,        &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK,        &STM8::OP_UNK,        &STM8::OP_UNK,

    // 10
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,

    // 20
    &STM8::OP_UNK,           &STM8::OP_UNK,          &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK,           &STM8::OP_UNK,          &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_JRcc<Cond_NH>, &STM8::OP_JRcc<Cond_H>, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK,           &STM8::OP_UNK,          &STM8::OP_UNK, &STM8::OP_UNK,

    // 30
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,

    // 40
    &STM8::OP_NEG_Mem<Op_LongDirectInd,true>, &STM8::OP_UNK,                            &STM8::OP_MUL<true>,                      &STM8::OP_CPL_Mem<Op_LongDirectInd,true>,
    &STM8::OP_SRL_Mem<Op_LongDirectInd,true>, &STM8::OP_UNK,                            &STM8::OP_RRC_Mem<Op_LongDirectInd,true>, &STM8::OP_UNK,
    &STM8::OP_SLL_Mem<Op_LongDirectInd,true>, &STM8::OP_UNK,                            &STM8::OP_DEC_Mem<Op_LongDirectInd,true>, &STM8::OP_UNK,
    &STM8::OP_INC_Mem<Op_LongDirectInd,true>, &STM8::OP_TNZ_Mem<Op_LongDirectInd,true>, &STM8::OP_UNK,                            &STM8::OP_CLR_Mem<Op_LongDirectInd,true>,

    // 50
    &STM8::OP_NEGW<true>, &STM8::OP_UNK,        &STM8::OP_UNK,         &STM8::OP_CPLW<true>,
    &STM8::OP_SRLW<true>, &STM8::OP_UNK,        &STM8::OP_UNK,         &STM8::OP_UNK,
    &STM8::OP_SLLW<true>, &STM8::OP_UNK,        &STM8::OP_DECW<true>,  &STM8::OP_UNK,
    &STM8::OP_INCW<true>, &STM8::OP_TNZW<true>, &STM8::OP_SWAPW<true>, &STM8::OP_CLRW<true>,

    // 60
    &STM8::OP_NEG_Mem<Op_ShortDirectInd,true>, &STM8::OP_UNK,                             &STM8::OP_UNK,                             &STM8::OP_CPL_Mem<Op_ShortDirectInd,true>,
    &STM8::OP_SRL_Mem<Op_ShortDirectInd,true>, &STM8::OP_UNK,                             &STM8::OP_RRC_Mem<Op_ShortDirectInd,true>, &STM8::OP_UNK,
    &STM8::OP_SLL_Mem<Op_ShortDirectInd,true>, &STM8::OP_UNK,                             &STM8::OP_DEC_Mem<Op_ShortDirectInd,true>, &STM8::OP_UNK,
    &STM8::OP_INC_Mem<Op_ShortDirectInd,true>, &STM8::OP_TNZ_Mem<Op_ShortDirectInd,true>, &STM8::OP_UNK,                             &STM8::OP_CLR_Mem<Op_ShortDirectInd,true>,

    // 70
    &STM8::OP_NEG_Mem<Op_Ind,true>, &STM8::OP_UNK,                  &STM8::OP_UNK,                  &STM8::OP_CPL_Mem<Op_Ind,true>,
    &STM8::OP_SRL_Mem<Op_Ind,true>, &STM8::OP_UNK,                  &STM8::OP_RRC_Mem<Op_Ind,true>, &STM8::OP_UNK,
    &STM8::OP_SLL_Mem<Op_Ind,true>, &STM8::OP_UNK,                  &STM8::OP_DEC_Mem<Op_Ind,true>, &STM8::OP_UNK,
    &STM8::OP_INC_Mem<Op_Ind,true>, &STM8::OP_TNZ_Mem<Op_Ind,true>, &STM8::OP_UNK,                  &STM8::OP_CLR_Mem<Op_Ind,true>,

    // 80
    &STM8::OP_UNK, &STM8::OP_UNK,         &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_POPW<true>,  &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_PUSHW<true>, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK,         &STM8::OP_UNK, &STM8::OP_UNK,

    // 90
    &STM8::OP_UNK,      &STM8::OP_UNK,     &STM8::OP_UNK,      &STM8::OP_LDW_Y_X,
    &STM8::OP_LDW_SP_Y, &STM8::OP_LD_YH_A, &STM8::OP_LDW_Y_SP, &STM8::OP_LD_YL_A,
    &STM8::OP_UNK,      &STM8::OP_UNK,     &STM8::OP_UNK,      &STM8::OP_UNK,
    &STM8::OP_UNK,      &STM8::OP_UNK,     &STM8::OP_LD_A_YH,  &STM8::OP_LD_A_YL,

    // A0
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,           &STM8::OP_CPW_Imm<true>,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,           &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,           &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_LDW_Imm<true>, &STM8::OP_UNK,

    // B0
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,                          &STM8::OP_CPW_Mem<Op_ShortDirect,true>,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,                          &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,                          &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_LDW_Ind<Op_ShortDirect,true>, &STM8::OP_LDW_Mem<Op_ShortDirect,true>,

    // C0
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,                         &STM8::OP_CPW_Mem<Op_LongDirect,true>,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,                         &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,                         &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_LDW_Ind<Op_LongDirect,true>, &STM8::OP_LDW_Mem<Op_LongDirect,true>,

    // D0
    &STM8::OP_SUB_Mem<Op_LongDirectInd,true>, &STM8::OP_CP_Mem<Op_LongDirectInd,true>,   &STM8::OP_SBC_Mem<Op_LongDirectInd,true>, &STM8::OP_CPW_Mem<Op_LongDirectInd,true>,
    &STM8::OP_AND_Mem<Op_LongDirectInd,true>, &STM8::OP_BCP_Mem<Op_LongDirectInd,true>,  &STM8::OP_LD_A<Op_LongDirectInd,true>,    &STM8::OP_LD_Mem<Op_LongDirectInd,true>,
    &STM8::OP_XOR_Mem<Op_LongDirectInd,true>, &STM8::OP_ADC_Mem<Op_LongDirectInd,true>,  &STM8::OP_OR_Mem<Op_LongDirectInd,true>,  &STM8::OP_ADD_Mem<Op_LongDirectInd,true>,
    &STM8::OP_JP<Op_LongDirectInd,true>,      &STM8::OP_CALL<Op_LongDirectInd,true>,     &STM8::OP_LDW_Ind<Op_LongDirectInd,true>, &STM8::OP_LDW_Mem<Op_LongDirectInd,true>,

    // E0
    &STM8::OP_SUB_Mem<Op_ShortDirectInd,true>, &STM8::OP_CP_Mem<Op_ShortDirectInd,true>,   &STM8::OP_SBC_Mem<Op_ShortDirectInd,true>, &STM8::OP_CPW_Mem<Op_ShortDirectInd,true>,
    &STM8::OP_AND_Mem<Op_ShortDirectInd,true>, &STM8::OP_BCP_Mem<Op_ShortDirectInd,true>,  &STM8::OP_LD_A<Op_ShortDirectInd,true>,    &STM8::OP_LD_Mem<Op_ShortDirectInd,true>,
    &STM8::OP_XOR_Mem<Op_ShortDirectInd,true>, &STM8::OP_ADC_Mem<Op_ShortDirectInd,true>,  &STM8::OP_OR_Mem<Op_ShortDirectInd,true>,  &STM8::OP_ADD_Mem<Op_ShortDirectInd,true>,
    &STM8::OP_JP<Op_ShortDirectInd,true>,      &STM8::OP_CALL<Op_ShortDirectInd,true>,     &STM8::OP_LDW_Ind<Op_ShortDirectInd,true>, &STM8::OP_LDW_Mem<Op_ShortDirectInd,true>,

    // F0
    &STM8::OP_SUB_Mem<Op_Ind,true>, &STM8::OP_CP_Mem<Op_Ind,true>,   &STM8::OP_SBC_Mem<Op_Ind,true>, &STM8::OP_CPW_Mem<Op_Ind,true>,
    &STM8::OP_AND_Mem<Op_Ind,true>, &STM8::OP_BCP_Mem<Op_Ind,true>,  &STM8::OP_LD_A<Op_Ind,true>,    &STM8::OP_LD_Mem<Op_Ind,true>,
    &STM8::OP_XOR_Mem<Op_Ind,true>, &STM8::OP_ADC_Mem<Op_Ind,true>,  &STM8::OP_OR_Mem<Op_Ind,true>,  &STM8::OP_ADD_Mem<Op_Ind,true>,
    &STM8::OP_JP<Op_Ind,true>,      &STM8::OP_CALL<Op_Ind,true>,     &STM8::OP_LDW_Ind<Op_Ind,true>, &STM8::OP_LDW_Mem<Op_Ind,true>
};

InstrFunc InstrTable91[256] =
{
    // 00
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,

    // 10
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,

    // 20
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,

    // 30
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,

    // 40
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,

    // 50
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,

    // 60
    &STM8::OP_NEG_Mem<Op_ShortDirectInd,true>, &STM8::OP_UNK,                               &STM8::OP_UNK,                               &STM8::OP_CPL_Mem<Op_ShortIndirectInd,true>,
    &STM8::OP_SRL_Mem<Op_ShortDirectInd,true>, &STM8::OP_UNK,                               &STM8::OP_RRC_Mem<Op_ShortIndirectInd,true>, &STM8::OP_UNK,
    &STM8::OP_SLL_Mem<Op_ShortDirectInd,true>, &STM8::OP_UNK,                               &STM8::OP_DEC_Mem<Op_ShortIndirectInd,true>, &STM8::OP_UNK,
    &STM8::OP_INC_Mem<Op_ShortDirectInd,true>, &STM8::OP_TNZ_Mem<Op_ShortIndirectInd,true>, &STM8::OP_UNK,                               &STM8::OP_CLR_Mem<Op_ShortIndirectInd,true>,

    // 70
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,

    // 80
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,

    // 90
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,

    // A0
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,

    // B0
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,

    // C0
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,                            &STM8::OP_CPW_Mem<Op_ShortIndirect,true>,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,                            &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,                            &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_LDW_Ind<Op_ShortIndirect,true>, &STM8::OP_LDW_Mem<Op_ShortIndirect,true>,

    // D0
    &STM8::OP_SUB_Mem<Op_ShortIndirectInd,true>, &STM8::OP_CP_Mem<Op_ShortIndirectInd,true>,   &STM8::OP_SBC_Mem<Op_ShortIndirectInd,true>, &STM8::OP_CPW_Mem<Op_ShortIndirectInd,true>,
    &STM8::OP_AND_Mem<Op_ShortIndirectInd,true>, &STM8::OP_BCP_Mem<Op_ShortIndirectInd,true>,  &STM8::OP_LD_A<Op_ShortIndirectInd,true>,    &STM8::OP_LD_Mem<Op_ShortIndirectInd,true>,
    &STM8::OP_XOR_Mem<Op_ShortIndirectInd,true>, &STM8::OP_ADC_Mem<Op_ShortIndirectInd,true>,  &STM8::OP_OR_Mem<Op_ShortIndirectInd,true>,  &STM8::OP_ADD_Mem<Op_ShortIndirectInd,true>,
    &STM8::OP_JP<Op_ShortIndirectInd,true>,      &STM8::OP_CALL<Op_ShortIndirectInd,true>,     &STM8::OP_LDW_Ind<Op_ShortIndirectInd,true>, &STM8::OP_LDW_Mem<Op_ShortIndirectInd,true>,

    // E0
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,

    // F0
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK
};

InstrFunc InstrTable92[256] =
{
    // 00
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,

    // 10
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,

    // 20
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,

    // 30
    &STM8::OP_NEG_Mem<Op_ShortIndirect,false>, &STM8::OP_UNK,                             &STM8::OP_UNK,                             &STM8::OP_CPL_Mem<Op_ShortIndirect,false>,
    &STM8::OP_SRL_Mem<Op_ShortIndirect,false>, &STM8::OP_UNK,                             &STM8::OP_RRC_Mem<Op_ShortIndirect,false>, &STM8::OP_UNK,
    &STM8::OP_SLL_Mem<Op_ShortIndirect,false>, &STM8::OP_UNK,                             &STM8::OP_DEC_Mem<Op_ShortIndirect,false>, &STM8::OP_UNK,
    &STM8::OP_INC_Mem<Op_ShortIndirect,false>, &STM8::OP_TNZ_Mem<Op_ShortIndirect,false>, &STM8::OP_UNK,                             &STM8::OP_CLR_Mem<Op_ShortIndirect,false>,

    // 40
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,

    // 50
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,

    // 60
    &STM8::OP_NEG_Mem<Op_ShortIndirectInd,false>, &STM8::OP_UNK,                                &STM8::OP_UNK,                                &STM8::OP_CPL_Mem<Op_ShortIndirectInd,false>,
    &STM8::OP_SRL_Mem<Op_ShortIndirectInd,false>, &STM8::OP_UNK,                                &STM8::OP_RRC_Mem<Op_ShortIndirectInd,false>, &STM8::OP_UNK,
    &STM8::OP_SLL_Mem<Op_ShortIndirectInd,false>, &STM8::OP_UNK,                                &STM8::OP_DEC_Mem<Op_ShortIndirectInd,false>, &STM8::OP_UNK,
    &STM8::OP_INC_Mem<Op_ShortIndirectInd,false>, &STM8::OP_TNZ_Mem<Op_ShortIndirectInd,false>, &STM8::OP_UNK,                                &STM8::OP_CLR_Mem<Op_ShortIndirectInd,false>,

    // 70
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,

    // 80
    &STM8::OP_UNK, &STM8::OP_UNK,                        &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK,                        &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK,                        &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_CALLF<Op_ExtendedIndirect>, &STM8::OP_UNK, &STM8::OP_UNK,

    // 90
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,

    // A0
    &STM8::OP_UNK,                      &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK,                      &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK,                      &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_JPF<Op_ExtendedIndirect>, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,

    // B0
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,

    // C0
    &STM8::OP_SUB_Mem<Op_ShortIndirect,false>, &STM8::OP_CP_Mem<Op_ShortIndirect,false>,   &STM8::OP_SBC_Mem<Op_ShortIndirect,false>, &STM8::OP_CPW_Mem<Op_ShortIndirect,false>,
    &STM8::OP_AND_Mem<Op_ShortIndirect,false>, &STM8::OP_BCP_Mem<Op_ShortIndirect,false>,  &STM8::OP_LD_A<Op_ShortIndirect,false>,    &STM8::OP_LD_Mem<Op_ShortIndirect,false>,
    &STM8::OP_XOR_Mem<Op_ShortIndirect,false>, &STM8::OP_ADC_Mem<Op_ShortIndirect,false>,  &STM8::OP_OR_Mem<Op_ShortIndirect,false>,  &STM8::OP_ADD_Mem<Op_ShortIndirect,false>,
    &STM8::OP_JP<Op_ShortIndirect,false>,      &STM8::OP_CALL<Op_ShortIndirect,false>,     &STM8::OP_LDW_Ind<Op_ShortIndirect,false>, &STM8::OP_LDW_Mem<Op_ShortIndirect,false>,

    // D0
    &STM8::OP_SUB_Mem<Op_ShortIndirectInd,false>, &STM8::OP_CP_Mem<Op_ShortIndirectInd,false>,   &STM8::OP_SBC_Mem<Op_ShortIndirectInd,false>, &STM8::OP_CPW_Mem<Op_ShortIndirectInd,false>,
    &STM8::OP_AND_Mem<Op_ShortIndirectInd,false>, &STM8::OP_BCP_Mem<Op_ShortIndirectInd,false>,  &STM8::OP_LD_A<Op_ShortIndirectInd,false>,    &STM8::OP_LD_Mem<Op_ShortIndirectInd,false>,
    &STM8::OP_XOR_Mem<Op_ShortIndirectInd,false>, &STM8::OP_ADC_Mem<Op_ShortIndirectInd,false>,  &STM8::OP_OR_Mem<Op_ShortIndirectInd,false>,  &STM8::OP_ADD_Mem<Op_ShortIndirectInd,false>,
    &STM8::OP_JP<Op_ShortIndirectInd,false>,      &STM8::OP_CALL<Op_ShortIndirectInd,false>,     &STM8::OP_LDW_Ind<Op_ShortIndirectInd,false>, &STM8::OP_LDW_Mem<Op_ShortIndirectInd,false>,

    // E0
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,

    // F0
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK
};
