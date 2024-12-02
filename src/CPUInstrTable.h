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
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_LDW_Ind<STM8::Op_ShortDirectSP,true>, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_LDW_Ind<STM8::Op_ShortDirectSP,false>, &STM8::OP_UNK,
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
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_LD_A<STM8::Op_ShortDirectSP,false>,
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
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_LD_A<STM8::Op_ShortDirect,false>, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_LDW_Ind<STM8::Op_ShortDirect,false>, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, // C0
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_LD_A<STM8::Op_LongDirect,false>, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_LDW_Ind<STM8::Op_LongDirect,false>, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, // D0
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_LD_A<STM8::Op_LongDirectInd,false>, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_LDW_Ind<STM8::Op_LongDirectInd,false>, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, // E0
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_LD_A<STM8::Op_ShortDirectInd,false>, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_LDW_Ind<STM8::Op_ShortDirectInd,false>, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, // F0
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_LD_A<STM8::Op_Ind,false>, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_LDW_Ind<STM8::Op_Ind,false>, &STM8::OP_UNK
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
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_LDW_Imm<true>, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, // B0
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_LDW_Ind<STM8::Op_ShortDirect,true>, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, // C0
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_LDW_Ind<STM8::Op_LongDirect,true>, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, // D0
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_LD_A<STM8::Op_LongDirectInd,true>, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_LDW_Ind<STM8::Op_LongDirectInd,true>, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, // E0
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_LD_A<STM8::Op_ShortDirectInd,true>, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_LDW_Ind<STM8::Op_ShortDirectInd,true>, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, // F0
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_LD_A<STM8::Op_Ind,true>, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_UNK,
    &STM8::OP_UNK, &STM8::OP_UNK, &STM8::OP_LDW_Ind<STM8::Op_Ind,true>, &STM8::OP_UNK
};
