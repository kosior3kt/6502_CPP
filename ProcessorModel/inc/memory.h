#ifndef __MEMORY__
#define __MEMORY__

#include "defines.h"
#include <cassert>
#include <iostream>
#include <fstream>
#include <inttypes.h>

struct Mem
{

      Byte Data[MAX_MEM];

      void initialise();

      Byte operator[](const u32& _addr) const;

      Byte &operator[](const u32& _addr);

      void set(const u32& _addr, const u32& _val);

      void debug_set(const u32& _addr, const u32& _val);

      Byte at(const u32& _addr) const;

      ///prolly need a way to change binary data into a memory for the program. Need serializer and deserializer then...
      void loadFromFile(std::string_view _path);

      void saveInFile(std::string_view _path);

      ///shouldn't need to use this
      Byte debug_get(const u32& _addr);

      void debug_dumpMemory(const std::string& _fileName);
};

#endif
