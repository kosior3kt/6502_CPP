#ifndef __MEMORY__
#define __MEMORY__

#include "../inc/defines.h"
#include <cassert>
#include <iostream>

struct Mem
{
      static constexpr u32 MAX_MEM = 1024 * 64;

      Byte Data[MAX_MEM];

      void Initialise();

      Byte operator[](const u32& _addr) const;

      Byte &operator[](const u32& _addr);

      void writeByte(u32& _cycles, const u32& _addr, const u32& _val);

      void writeWord(u32& _cycles, const u32& _addr, const Word& _val);

      void debug_set(const u32& _addr, const u32& _val);
};

#endif
