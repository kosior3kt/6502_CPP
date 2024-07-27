#include "CPU.h"

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



void CPU::TSX(u32 &_cycles, Mem &_mem, const Byte& _opCode)
{
   X = SP;
  safeCycleDecrement(_cycles);   ///TODO: measure later how many cycles this thing should even use
}

void CPU::TXS(u32 &_cycles, Mem &_mem, const Byte& _opCode)
{
  SP = X;
  safeCycleDecrement(_cycles);
}

void CPU::PHA(u32 &_cycles, Mem &_mem, const Byte& _opCode)
{
   pushByteToStack(_cycles, _mem, A);
  safeCycleDecrement(_cycles);
}

void CPU::PHP(u32 &_cycles, Mem &_mem, const Byte& _opCode)
{
   auto flags = getCurrentFlags();
   std::bitset<8> flags_bit(flags);
   HEX_PRINT("those are flags that I've pushed: ", (flags_bit));
   pushByteToStack(_cycles, _mem, flags);
   safeCycleDecrement(_cycles);
}

void CPU::PLA(u32 &_cycles, Mem &_mem, const Byte& _opCode)
{
   Byte value = popByteFromStack(_cycles, _mem);
   safeCycleDecrement(_cycles);
   A = value;
}

void CPU::PLP(u32 &_cycles, Mem &_mem, const Byte& _opCode)
{
   HEX_PRINT("\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!PLP CALLED!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");

   auto flags = popByteFromStack(_cycles, _mem);
   std::bitset<8> flags_bit(flags);
   HEX_PRINT("those are flags that I've read: ", (flags_bit));
   setCurrentFlags(flags);
   safeCycleDecrement(_cycles);
}

