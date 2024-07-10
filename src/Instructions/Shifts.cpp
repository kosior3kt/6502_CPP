#include "CPU.h"

#define ALMOST_OVERFLOW 0b10000000
////////////////////////////////////// Shifts
///ASL
void CPU::ASL_ACC(u32& _cycles, Mem &_mem)
{
   if(A >= ALMOST_OVERFLOW)
   {
      C = 1;
   }
   A = A << 1;
   --_cycles -= 2;
   A &= 0b11111110;  //make sure the last bit is beingi filled with 0
   Byte flag = 0b11111111 & (N_f | Z_f); /// does this work(?)
   SetCustomFlagsWithRegister(Register::A, flag);
}

void CPU::ASL_ZP (u32& _cycles, Mem &_mem)
{
   Byte zeroPageAddress = FetchByte(_cycles, _mem);
   ApplyToMemory(_cycles, zeroPageAddress, _mem, [&](const Byte& _byte) -> Byte{
             if(_byte >= ALMOST_OVERFLOW) {
               C = 1;
             }
             return _byte << 1;
         });
   Byte flag = 0b11111111 & (N_f | Z_f);
   SetCustomFlagsWithRegister(Register::A, flag);
}

void CPU::ASL_ZPX(u32& _cycles, Mem &_mem)
{
   Byte zeroPageAddress = FetchByte(_cycles, _mem) + X;
   ApplyToMemory(_cycles, zeroPageAddress, _mem, [&](const Byte& _byte) -> Byte{
             if(_byte >= ALMOST_OVERFLOW) {
               C = 1;
             }
             return _byte << 1;
         });
   _cycles -= 2;
   Byte flag = 0b11111111 & (N_f | Z_f);
   SetCustomFlagsWithRegister(Register::A, flag);
}

void CPU::ASL_ABS(u32& _cycles, Mem &_mem)
{

}

void CPU::ASL_ABSX(u32& _cycles, Mem &_mem)
{

}


///LSR
void CPU::LSR_ACC(u32& _cycles, Mem &_mem)
{

}

void CPU::LSR_ZP (u32& _cycles, Mem &_mem)
{

}

void CPU::LSR_ZPX(u32& _cycles, Mem &_mem)
{

}

void CPU::LSR_ABS(u32& _cycles, Mem &_mem)
{

}

void CPU::LSR_ABSX(u32& _cycles, Mem &_mem)
{

}


///ROL
void CPU::ROL_ACC(u32& _cycles, Mem &_mem)
{

}

void CPU::ROL_ZP (u32& _cycles, Mem &_mem)
{

}

void CPU::ROL_ZPX(u32& _cycles, Mem &_mem)
{

}

void CPU::ROL_ABS(u32& _cycles, Mem &_mem)
{

}

void CPU::ROL_ABSX(u32& _cycles, Mem &_mem)
{

}


///ROR
void CPU::ROR_ACC(u32& _cycles, Mem &_mem)
{

}

void CPU::ROR_ZP (u32& _cycles, Mem &_mem)
{

}

void CPU::ROR_ZPX(u32& _cycles, Mem &_mem)
{

}

void CPU::ROR_ABS(u32& _cycles, Mem &_mem)
{

}

void CPU::ROR_ABSX(u32& _cycles, Mem &_mem)
{

}


