#include "CPU.h"

void CPU::BCC(u32 &_cycles, Mem &_mem, const Byte& _opCode)
{
   int8_t relAddr = fetchByte(_cycles, _mem); ///this hing needs to be singed...
   if(C != 0) return;
   PC += relAddr;
}

void CPU::BCS(u32 &_cycles, Mem &_mem, const Byte& _opCode)
{
   int8_t relAddr = fetchByte(_cycles, _mem); ///this hing needs to be singed...
   if(C != 1) return;
   PC += relAddr;
}

void CPU::BEQ(u32 &_cycles, Mem &_mem, const Byte& _opCode)
{
   int8_t relAddr = fetchByte(_cycles, _mem); ///this hing needs to be singed...
   if(Z != 1) return;
   PC += relAddr;
}

void CPU::BMI(u32 &_cycles, Mem &_mem, const Byte& _opCode)
{
   int8_t relAddr = fetchByte(_cycles, _mem); ///this hing needs to be singed...
   if(N != 1) return;
   PC += relAddr;
}

void CPU::BNE(u32 &_cycles, Mem &_mem, const Byte& _opCode)
{
   int8_t relAddr = fetchByte(_cycles, _mem); ///this hing needs to be singed...
   if(Z != 0) return;
   PC += relAddr;
}

void CPU::BPL(u32 &_cycles, Mem &_mem, const Byte& _opCode)
{
   int8_t relAddr = fetchByte(_cycles, _mem); ///this hing needs to be singed...
   if(N != 0) return;
   PC += relAddr;
}

void CPU::BVC(u32 &_cycles, Mem &_mem, const Byte& _opCode)
{
   int8_t relAddr = fetchByte(_cycles, _mem); ///this hing needs to be singed...
   if(V != 0) return;
   PC += relAddr;
}

void CPU::BVS(u32 &_cycles, Mem &_mem, const Byte& _opCode)
{
   int8_t relAddr = fetchByte(_cycles, _mem); ///this hing needs to be singed...
   if(V != 1) return;
   PC += relAddr;
}
