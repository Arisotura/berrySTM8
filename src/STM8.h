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

#ifndef STM8_H
#define STM8_H

#include "types.h"

class STM8
{
public:
    STM8();
    ~STM8();
    void Reset();

    // 0=EEPROM 1=FLASH
    bool LoadImage(int type, const char* filename);

    void SetInput(char* pin, u8 val);
    u8 GetOutput(char* pin);

    void CPUReset();
    void CPUJumpTo(u32 addr);
    void CPUTriggerIRQ(int irq);
    u8 CPUFetch();
    int CPUExecute(int cycles);

    void RunDevices(int cycles);

    void TriggerIRQ(int irq);

    u8 MemRead(u32 addr);
    void MemWrite(u32 addr, u8 val);

    u32 GetPC() { return PC; }

private:
    // TODO: some kind of model ID?

    // ---- CPU ---------------------------------

    enum
    {
        Flag_C  = (1<<0),
        Flag_Z  = (1<<1),
        Flag_N  = (1<<2),
        Flag_I0 = (1<<3),
        Flag_H  = (1<<4),
        Flag_I1 = (1<<5),
        Flag_V  = (1<<7)
    };

    enum ConditionCode
    {
        Cond_T = 0,     // true
        Cond_F,         // false
        Cond_EQ,        // Z=1
        Cond_NE,        // Z=0
        Cond_H,         // H=1
        Cond_NH,        // H=0
        Cond_M,         // I=1
        Cond_NM,        // I=0
        Cond_MI,        // N=1
        Cond_PL,        // N=0
        Cond_V,         // V=1
        Cond_NV,        // V=0
        Cond_SGE,       // (N^V)=0
        Cond_SGT,       // (Z|(N^V))=0
        Cond_SLE,       // (Z|(N^V))=1
        Cond_SLT,       // (N^V)=1
        Cond_UGE,       // C=0
        Cond_UGT,       // C=0 & Z=0
        Cond_ULE,       // C=1 | Z=1
        Cond_ULT        // C=1
    };

    u8 A;
    u16 X, Y;
    u16 SP;
    u32 PC;
    u8 CC;

    u16 _lastop;

    s8 NextIRQ;

    void SetNZ(bool n, bool z)
    {
        CC &= ~(Flag_N | Flag_Z);
        if (n) CC |= Flag_N;
        if (z) CC |= Flag_Z;
    }

    void SetNZV(bool n, bool z, bool v)
    {
        CC &= ~(Flag_N | Flag_Z | Flag_V);
        if (n) CC |= Flag_N;
        if (z) CC |= Flag_Z;
        if (v) CC |= Flag_V;
    }

    void SetNZC(bool n, bool z, bool c)
    {
        CC &= ~(Flag_N | Flag_Z | Flag_C);
        if (n) CC |= Flag_N;
        if (z) CC |= Flag_Z;
        if (c) CC |= Flag_C;
    }

    void SetNZVC(bool n, bool z, bool v, bool c)
    {
        CC &= ~(Flag_N | Flag_Z | Flag_V | Flag_C);
        if (n) CC |= Flag_N;
        if (z) CC |= Flag_Z;
        if (v) CC |= Flag_V;
        if (c) CC |= Flag_C;
    }

    void SetNZVCH(bool n, bool z, bool v, bool c, bool h)
    {
        CC &= ~(Flag_N | Flag_Z | Flag_V | Flag_C | Flag_H);
        if (n) CC |= Flag_N;
        if (z) CC |= Flag_Z;
        if (v) CC |= Flag_V;
        if (c) CC |= Flag_C;
        if (h) CC |= Flag_H;
    }

    template<typename T>
    void SetFlagsAdd(T a, T m, T r, u8 mask)
    {
        CC &= ~(Flag_N | Flag_Z | mask);

        T carry = ((a & m) | (m & (~r)) | (a & (~r)));
        T topbit = 1 << ((8 * sizeof(T)) - 1);
        T halfbit = 1 << ((4 * sizeof(T)) - 1);

        if (r & topbit)
            CC |= Flag_N;
        if (!r)
            CC |= Flag_Z;
        if ((mask & Flag_C) && (carry & topbit))
            CC |= Flag_C;
        if ((mask & Flag_H) && (carry & halfbit))
            CC |= Flag_H;
        if ((mask & Flag_V) && ((carry ^ (carry << 1)) & topbit))
            CC |= Flag_V;
    }

    template<typename T>
    void SetFlagsSub(T a, T m, T r, u8 mask)
    {
        CC &= ~(Flag_N | Flag_Z | mask);

        T carry = (((~a) & m) | ((~a) & r) | (a & m & r));
        T topbit = 1 << ((8 * sizeof(T)) - 1);
        T halfbit = 1 << ((4 * sizeof(T)) - 1);

        if (r & topbit)
            CC |= Flag_N;
        if (!r)
            CC |= Flag_Z;
        if ((mask & Flag_C) && (carry & topbit))
            CC |= Flag_C;
        if ((mask & Flag_H) && (carry & halfbit))
            CC |= Flag_H;
        if ((mask & Flag_V) && ((carry ^ (carry << 1)) & topbit))
            CC |= Flag_V;
    }

    void SetI(bool i0, bool i1)
    {
        CC &= ~(Flag_I0 | Flag_I1);
        if (i0) CC |= Flag_I0;
        if (i1) CC |= Flag_I1;
    }

    enum OperandType
    {
        Op_ShortDirect = 0,
        Op_LongDirect,
        Op_ExtendedDirect,
        Op_Ind,
        Op_ShortDirectInd,
        Op_LongDirectInd,
        Op_ExtendedDirectInd,
        Op_ShortDirectSP,
        Op_ShortIndirect,
        Op_LongIndirect,
        Op_ExtendedIndirect,
        Op_ShortIndirectInd,
        Op_LongIndirectInd,
        Op_ExtendedIndirectInd
    };

    bool OpIsInd(OperandType op)
    {
        return ((op >= Op_Ind && op <= Op_ExtendedDirectInd) ||
                (op >= Op_ShortIndirectInd));
    }

    bool OpIsIndirect(OperandType op)
    {
        return op >= Op_ShortIndirect;
    }

    template<OperandType op, bool indY = false>
    u32 CPUFetchOpAddr();

#include "CPUInstrTable.h"

    // ---- IRQ ---------------------------------

    u8 IntPrio[30];
    u32 IntMask;

    void UpdateIRQ();

    // ---- memory ------------------------------

    u8* RAM;
    u32 RAMSize;
    u32 RAMMask;

    u8* EEPROM;
    u32 EEPROMStart;
    u32 EEPROMEnd;
    u32 EEPROMSize;
    u32 EEPROMMask;

    u8* FLASH;
    const u32 FLASHStart = 0x8000;
    u32 FLASHEnd;
    u32 FLASHSize;
    u32 FLASHMask;

    u8 IORead(u32 addr);
    void IOWrite(u32 addr, u8 val);

    // ---- I/O devices -------------------------

    void MapIORange(STM8Device* dev, u32 start, u32 end);
    friend class STM8Device;

    STM8GPIO* GPIO[9];

    STM8DMA* DMA;
    STM8I2C* I2C;

    STM8GPTimer* TIM2;
    STM8GPTimer* TIM3;
    STM8BasicTimer* TIM4;
    STM8GPTimer* TIM5;

    STM8Device* IORegisters[0x800];

    // ---- clock -------------------------------

    u8 ClkEnable[3];

    // ---- FLASH registers ---------------------

    u8 FLASH_PUKR;
    u8 FLASH_DUKR;
    u8 FLASH_IAPSR;
};


class STM8Device
{
public:
    STM8Device(STM8* stm, u32 iobase) : STM(stm), IOBase(iobase) {}
    virtual ~STM8Device() {}
    virtual void Reset() = 0;

    virtual u8 IORead(u32 addr) = 0;
    virtual void IOWrite(u32 addr, u8 val) = 0;

protected:
    STM8* STM;
    u32 IOBase;

    void MapIORange(u32 first, u32 last) { STM->MapIORange(this, IOBase+first, IOBase+last); }
};

#endif // STM8_H
