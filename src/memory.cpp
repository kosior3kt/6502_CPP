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

Byte &Mem::operator[](const u32 &_addr)
{
   assert(_addr < MAX_MEM);
   return Data[_addr];
}

void Mem::debug_set(const u32 &_addr, const u32 &_val)
{
   assert(_addr < MAX_MEM);
   Data[_addr] = _val;
}

Byte Mem::debug_get(const u32 &_addr)
{
   assert(_addr < MAX_MEM);
   return Data[_addr];
}

void Mem::debug_dumpMemory(const std::string& _fileName){
   std::ofstream _file;
   _file.open(_fileName);
   if(!_file) return;
   for(int i = 0; i < Mem::MAX_MEM; ++i)
   {
      _file << (int)Data[i] << " at the adress: " << i << "\n";   ///this construction flushes at the end of line
   }
   _file.close();
}
