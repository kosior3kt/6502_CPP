#include "CPU.h"


void CPU::TYA_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode)
{
   A = Y;
   Y = 0;
   Byte flag = (Z_f | N_f);
   SetCustomFlagsWithRegister(Register::A, flag);
}

void CPU::TAY_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode)
{
   Y = A;
   A = 0;
   Byte flag = (Z_f | N_f);
   SetCustomFlagsWithRegister(Register::Y, flag);
}

void CPU::TXA_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode)
{
   A = X;
   X = 0;
   Byte flag = (Z_f | N_f);
   SetCustomFlagsWithRegister(Register::A, flag);
}

void CPU::TAX_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode)
{
   X = A;
   A = 0;
   Byte flag = (Z_f | N_f);
   SetCustomFlagsWithRegister(Register::X, flag);
}


////////////////////////////////////// Register Transfers
void CPU::TAX(u32& _cycles, Mem &_mem)
{
   X = A;
   A = 0;
   Byte flag = (Z_f | N_f);
   SetCustomFlagsWithRegister(Register::X, flag);
}

void CPU::TAY(u32& _cycles, Mem &_mem)
{
   Y = A;
   A = 0;
   Byte flag = (Z_f | N_f);
   SetCustomFlagsWithRegister(Register::Y, flag);
}

void CPU::TXA(u32& _cycles, Mem &_mem)
{
   A = X;
   X = 0;
   Byte flag = (Z_f | N_f);
   SetCustomFlagsWithRegister(Register::A, flag);
}

void CPU::TYA(u32& _cycles, Mem &_mem)
{
   A = Y;
   Y = 0;
   Byte flag = (Z_f | N_f);
   SetCustomFlagsWithRegister(Register::A, flag);
}
