#include "CPU.h"



void CPU::CLC_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode)
{

}

void CPU::CLD_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode)
{

}

void CPU::CLI_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode)
{

}

void CPU::CLV_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode)
{

}

void CPU::SEC_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode)
{

}

void CPU::SED_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode)
{

}

void CPU::SEI_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode)
{

}


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

