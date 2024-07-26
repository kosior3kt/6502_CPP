#include "CPU.h"


void CPU::TYA(u32 &_cycles, Mem &_mem, const Byte& _opCode)
{
   A = Y;
   Y = 0;
   Byte flag = (Z_f | N_f);
   setCustomFlagsWithRegister(Register::A, flag);
}

void CPU::TAY(u32 &_cycles, Mem &_mem, const Byte& _opCode)
{
   Y = A;
   A = 0;
   Byte flag = (Z_f | N_f);
   setCustomFlagsWithRegister(Register::Y, flag);
}

void CPU::TXA(u32 &_cycles, Mem &_mem, const Byte& _opCode)
{
   A = X;
   X = 0;
   Byte flag = (Z_f | N_f);
   setCustomFlagsWithRegister(Register::A, flag);
}

void CPU::TAX(u32 &_cycles, Mem &_mem, const Byte& _opCode)
{
   X = A;
   A = 0;
   Byte flag = (Z_f | N_f);
   setCustomFlagsWithRegister(Register::X, flag);
}

