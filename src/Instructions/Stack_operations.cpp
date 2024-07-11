#include "CPU.h"



void CPU::TSX_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode)
{

}

void CPU::TXS_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode)
{

}

void CPU::PHA_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode)
{

}

void CPU::PHP_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode)
{

}

void CPU::PLA_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode)
{

}

void CPU::PLP_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode)
{

}


////////////////////////////////////// helper functions
uint8_t CPU::getCurrentFlags() const
{
   return   (C << 0) |
            (Z << 1) |
            (I << 2) |
            (D << 3) |
            (B << 4) |
            (V << 6) |
            (N << 7);
}

void CPU::setCurrentFlags(const uint8_t& _flags)
{
   C = (_flags >> 0) & 1;
   Z = (_flags >> 1) & 1;
   I = (_flags >> 2) & 1;
   D = (_flags >> 3) & 1;
   B = (_flags >> 4) & 1;
   V = (_flags >> 6) & 1;
   N = (_flags >> 7) & 1;
}

////////////////////////////////////// Stack Operations
void CPU::TSX(u32& _cycles, Mem &_mem)
{
   X = SP;
  --_cycles;   ///TODO: measure later how many cycles this thing should even use
}

void CPU::TXS(u32& _cycles, Mem &_mem)
{
  SP = X;
  --_cycles;
}

void CPU::PHA(u32& _cycles, Mem &_mem)
{
   pushByteToStack(_cycles, _mem, A);
  --_cycles;
}

void CPU::PHP(u32& _cycles, Mem &_mem)
{
   auto flags = getCurrentFlags();
   pushByteToStack(_cycles, _mem, flags);
  --_cycles;
}

void CPU::PLA(u32& _cycles, Mem &_mem)
{
   Byte value = popByteFromStack(_cycles, _mem);
   --_cycles;
   A = value;
}

void CPU::PLP(u32& _cycles, Mem &_mem)
{
   auto flags = popByteFromStack(_cycles, _mem);
   setCurrentFlags(flags);
   --_cycles;
}
