#ifndef __MEMORY__
#define __MEMORY__

#include "defines.h"
#include <cassert>
#include <iostream>
#include <fstream>
#include <inttypes.h>

struct Mem
{
      static constexpr u32 MAX_MEM = 1024 * 64;

      Byte Data[MAX_MEM];

      void initialise();

      Byte operator[](const u32& _addr) const;

      Byte &operator[](const u32& _addr);

      void debug_set(const u32& _addr, const u32& _val);

      Byte debug_get(const u32& _addr);

      void debug_dumpMemory(const std::string& _fileName);

      ///prolly need a way to change binary data into a memory for the program. Need serializer and deserializer then...
      void loadFromFile(std::string_view _path);
};

#endif
