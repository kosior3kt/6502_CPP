#include "CPU.h"

////////////////////////////////////// Logical
void CPU::AND_IM (u32& _cycles, Mem &_mem){}
void CPU::AND_ZP (u32& _cycles, Mem &_mem){}
void CPU::AND_ZPX(u32& _cycles, Mem &_mem){}
void CPU::AND_ABS(u32& _cycles, Mem &_mem){}
void CPU::AND_ABSX(u32& _cycles, Mem &_mem){}
void CPU::AND_ABSY(u32& _cycles, Mem &_mem){}
void CPU::AND_INDX(u32& _cycles, Mem &_mem){}
void CPU::AND_INDY(u32& _cycles, Mem &_mem){}

void CPU::EOR_IM (u32& _cycles, Mem &_mem){}
void CPU::EOR_ZP (u32& _cycles, Mem &_mem){}
void CPU::EOR_ZPX(u32& _cycles, Mem &_mem){}
void CPU::EOR_ABS(u32& _cycles, Mem &_mem){}
void CPU::EOR_ABSX(u32& _cycles, Mem &_mem){}
void CPU::EOR_ABSY(u32& _cycles, Mem &_mem){}
void CPU::EOR_INDX(u32& _cycles, Mem &_mem){}
void CPU::EOR_INDY(u32& _cycles, Mem &_mem){}

///ORA 
void CPU::ORA_IM (u32& _cycles, Mem &_mem){}
void CPU::ORA_ZP (u32& _cycles, Mem &_mem){}
void CPU::ORA_ZPX(u32& _cycles, Mem &_mem){}
void CPU::ORA_ABS(u32& _cycles, Mem &_mem){}
void CPU::ORA_ABSX(u32& _cycles, Mem &_mem){}
void CPU::ORA_ABSY(u32& _cycles, Mem &_mem){}
void CPU::ORA_INDX(u32& _cycles, Mem &_mem){}
void CPU::ORA_INDY(u32& _cycles, Mem &_mem){}

/// BIT
void CPU::BIT_ZP (u32& _cycles, Mem &_mem){}
void CPU::BIT_ZBS(u32& _cycles, Mem &_mem){}
