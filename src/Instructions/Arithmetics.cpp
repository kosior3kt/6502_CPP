#include "CPU.h"



void CPU::ADC_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode)
{

}

void CPU::SBC_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode)
{

}

void CPU::CMP_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode)
{

}

void CPU::CPX_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode)
{

}

void CPU::CPY_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode)
{

}



////////////////////////////////////// Arithmetic
///ADC
void CPU::ADC_IM (u32& _cycles, Mem &_mem){}
void CPU::ADC_ZP (u32& _cycles, Mem &_mem){}
void CPU::ADC_ZPX(u32& _cycles, Mem &_mem){}
void CPU::ADC_ABS(u32& _cycles, Mem &_mem){}
void CPU::ADC_ABSX(u32& _cycles, Mem &_mem){}
void CPU::ADC_ABSY(u32& _cycles, Mem &_mem){}
void CPU::ADC_INDX(u32& _cycles, Mem &_mem){}
void CPU::ADC_INDY(u32& _cycles, Mem &_mem){}

/// SBC
void CPU::SBC_IM (u32& _cycles, Mem &_mem){}
void CPU::SBC_ZP (u32& _cycles, Mem &_mem){}
void CPU::SBC_ZPX(u32& _cycles, Mem &_mem){}
void CPU::SBC_ABS(u32& _cycles, Mem &_mem){}
void CPU::SBC_ABSX(u32& _cycles, Mem &_mem){}
void CPU::SBC_ABSY(u32& _cycles, Mem &_mem){}
void CPU::SBC_INDX(u32& _cycles, Mem &_mem){}
void CPU::SBC_INDY(u32& _cycles, Mem &_mem){}

/// CMP
void CPU::CMP_IM (u32& _cycles, Mem &_mem){}
void CPU::CMP_ZP (u32& _cycles, Mem &_mem){}
void CPU::CMP_ZPX(u32& _cycles, Mem &_mem){}
void CPU::CMP_ABS(u32& _cycles, Mem &_mem){}
void CPU::CMP_ABSX(u32& _cycles, Mem &_mem){}
void CPU::CMP_ABSY(u32& _cycles, Mem &_mem){}
void CPU::CMP_INDX(u32& _cycles, Mem &_mem){}
void CPU::CMP_INDY(u32& _cycles, Mem &_mem){}

///CPX
void CPU::CPX_IM (u32& _cycles, Mem &_mem){}
void CPU::CPX_ZP (u32& _cycles, Mem &_mem){}
void CPU::CPX_ABS(u32& _cycles, Mem &_mem){}

///CPY
void CPU::CPY_IM (u32& _cycles, Mem &_mem){}
void CPU::CPY_ZP (u32& _cycles, Mem &_mem){}
void CPU::CPY_ABS(u32& _cycles, Mem &_mem){}

