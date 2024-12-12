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
#include <stdlib.h>
#include "STM8.h"


int STM8::OP_UNK()
{
    printf("unknown opcode %04X @ %08X\n", _lastop, PC-1);
    printf("PC=%06X A=%02X X=%04X Y=%04X SP=%04X CC=%02X\n", PC, A, X,Y, SP, CC);
    exit(-1);
    return 1;
}


int STM8::OP_NOP()
{
    return 1;
}


int STM8::OP_RIM()
{
    SetI(false, true);
    return 1;
}


int STM8::OP_SIM()
{
    SetI(true, true);
    return 1;
}


int STM8::OP_RVF()
{
    CC &= ~Flag_V;
    return 1;
}


int STM8::OP_Prefix72()
{
    u8 op = CPUFetch();
    _lastop = 0x7200 | op; // debug
    return (this->*InstrTable72[op])();
}

int STM8::OP_Prefix90()
{
    u8 op = CPUFetch();
    _lastop = 0x9000 | op; // debug
    return (this->*InstrTable90[op])();
}

int STM8::OP_Prefix91()
{
    u8 op = CPUFetch();
    _lastop = 0x9100 | op; // debug
    return (this->*InstrTable91[op])();
}

int STM8::OP_Prefix92()
{
    u8 op = CPUFetch();
    _lastop = 0x9200 | op; // debug
    return (this->*InstrTable92[op])();
}
