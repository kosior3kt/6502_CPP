#include "CPU.h"



void CPU::CLC(u32 &_cycles, Mem &_mem, const Byte& _opCode)
{
   C = 0; 
   safeCycleDecrement(_cycles);
   safeCycleDecrement(_cycles);
}

void CPU::CLD(u32 &_cycles, Mem &_mem, const Byte& _opCode)
{
   D = 0; 
   safeCycleDecrement(_cycles);
   safeCycleDecrement(_cycles);
}

void CPU::CLI(u32 &_cycles, Mem &_mem, const Byte& _opCode)
{
   I = 0; 
   safeCycleDecrement(_cycles);
   safeCycleDecrement(_cycles);
}

void CPU::CLV(u32 &_cycles, Mem &_mem, const Byte& _opCode)
{
   V = 0; 
   safeCycleDecrement(_cycles);
   safeCycleDecrement(_cycles);
}

void CPU::SEC(u32 &_cycles, Mem &_mem, const Byte& _opCode)
{
   C = 1; 
   safeCycleDecrement(_cycles);
   safeCycleDecrement(_cycles);
}

void CPU::SED(u32 &_cycles, Mem &_mem, const Byte& _opCode)
{
   D = 1; 
   safeCycleDecrement(_cycles);
   safeCycleDecrement(_cycles);
}

void CPU::SEI(u32 &_cycles, Mem &_mem, const Byte& _opCode)
{
   I = 1; 
   safeCycleDecrement(_cycles);
   safeCycleDecrement(_cycles);
}

