#include "memory.h"

void Mem::Initialise()
{
   for(u32 i = 0; i < MAX_MEM; ++i)
   {
      Data[i] = 0;
   }
}

Byte Mem::operator[](const u32 &_addr) const
{
   assert(_addr < MAX_MEM);
   return Data[_addr];
}

Byte& Mem::operator[](const u32 &_addr)
{
   assert(_addr < MAX_MEM);
   return Data[_addr];
}

void Mem::writeByte(u32 &_cycles, const u32 &_addr, const u32 &_val)
{
   assert(_addr < MAX_MEM);
   Data[_addr] = _val;
   --_cycles;
}

void Mem::writeWord(u32 &_cycles, const u32 &_addr, const Word &_val)
{
   assert(_addr < MAX_MEM);
   Data[_addr]     = _val & 0xFF;
   Data[_addr + 1] = (_val >> 8);
   _cycles -= 2;
}

void Mem::debug_set(const u32 &_addr, const u32 &_val)
{
   assert(_addr < MAX_MEM);
   Data[_addr] = _val;
}
