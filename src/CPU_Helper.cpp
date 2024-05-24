#include "CPU.h"

void CPU::Reset(Mem &_mem)
{
   PC = 0xFFFC;
   SP = 0x0100;
   C = Z = I = D = B = V = N = 0;
   A = X = Y = 0;
   _mem.Initialise();
}

Byte CPU::FetchByte(u32 &_cycles, const Mem &_mem)
{
   Byte data = _mem[PC];
   ++PC;
   --_cycles;
   return data;
}

Word CPU::FetchWord(u32 &_cycles, const Mem &_mem)
{
   // 6502 is little endian - so the first is the least significant byte
   Word data = _mem[PC];
   data |= (_mem[PC] << 8);
   PC += 2;
   _cycles -= 2;
   /// good old endiannes ifdef here (if you care ofc...)
   return data;
}

Byte CPU::ReadByte(u32 &_cycles, const Byte &_addr, const Mem &_mem)
{
   Byte data = _mem[_addr];
   --_cycles;
   return data;
}

Byte CPU::ReadByte(u32 &_cycles, const Word &_addr, const Mem &_mem)
{
   Byte data = _mem[_addr];
   --_cycles;
   return data;
}

Byte CPU::ReadWord(u32 &_cycles, const Byte &_addr, const Mem &_mem)
{
   assert(_addr + 0x0001 < Mem::MAX_MEM);
   Word ea;
   Byte eaLow = ReadByte(_cycles, _addr, _mem);
   Byte eaHigh = ReadByte(_cycles, _addr, _mem);
   ea = eaLow + (eaHigh << 8);
   return ea;
}

Byte CPU::ReadWord(u32 &_cycles, const Word &_addr, const Mem &_mem)
{
   assert(_addr + 0x0001 < Mem::MAX_MEM);
   Word ea;
   Byte eaLow = ReadByte(_cycles, _addr, _mem);
   Byte eaHigh = ReadByte(_cycles, _addr, _mem);
   ea = eaLow + (eaHigh << 8);
   return ea;
}

void CPU::LDASetStatus()
{
   Z = (A == 0);
   N = (A & 0b10000000) > 0; /// is this correct?
}

void CPU::LDXSetStatus()
{
   Z = (X == 0);
   N = (X & 0b10000000) > 0; /// is this correct?
}

void CPU::LDYSetStatus()
{
   Z = (Y == 0);
   N = (Y & 0b10000000) > 0; /// is this correct?
}
