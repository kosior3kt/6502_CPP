#include "CPU.h"



void CPU::CLC_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode)
{
   C = 0; 
   safeCycleDecrement(_cycles);
   safeCycleDecrement(_cycles);
}

void CPU::CLD_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode)
{
   D = 0; 
   safeCycleDecrement(_cycles);
   safeCycleDecrement(_cycles);
}

void CPU::CLI_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode)
{
   I = 0; 
   safeCycleDecrement(_cycles);
   safeCycleDecrement(_cycles);
}

void CPU::CLV_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode)
{
   V = 0; 
   safeCycleDecrement(_cycles);
   safeCycleDecrement(_cycles);
}

void CPU::SEC_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode)
{
   C = 1; 
   safeCycleDecrement(_cycles);
   safeCycleDecrement(_cycles);
}

void CPU::SED_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode)
{
   D = 1; 
   safeCycleDecrement(_cycles);
   safeCycleDecrement(_cycles);
}

void CPU::SEI_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode)
{
   I = 1; 
   safeCycleDecrement(_cycles);
   safeCycleDecrement(_cycles);
}

