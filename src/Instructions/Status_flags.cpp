#include "CPU.h"

////////////////////////////////////// Status Flag Changes
void CPU::CLC (u32& _cycles, Mem &_mem)
{
   C = 0; 
   _cycles -= 2;
}

void CPU::CLD (u32& _cycles, Mem &_mem)
{
   D = 0; 
   _cycles -= 2;
}

void CPU::CLI (u32& _cycles, Mem &_mem)
{
   I = 0; 
   _cycles -= 2;
}

void CPU::CLV (u32& _cycles, Mem &_mem)
{
   V = 0; 
   _cycles -= 2;
}

void CPU::SEC (u32& _cycles, Mem &_mem)
{
   C = 1; 
   _cycles -= 2;
}

void CPU::SED (u32& _cycles, Mem &_mem)
{
   D = 1; 
   _cycles -= 2;
}

void CPU::SEI (u32& _cycles, Mem &_mem)
{
   I = 1; 
   _cycles -= 2;
}

