#include "CPU.h"

#ifndef ALTERNATIVE

s32 CPU::execute(u32 _cycles, Mem &_mem)
{
    while(_cycles > 0)
   {
      Byte inst         = FetchByte(_cycles, _mem);
      bool found = false;
      for(auto x : instructionMap)
      {
         if(x.first.find(inst) == x.first.end()) continue;
         x.second(_cycles, _mem, inst);
         found = true;
         break;
      }
      if(!found)[[unlikely]]
      {
         printf("Not handled %d\n", inst);
         break;
      }
   }
   return _cycles;
}

#else

///dont touch this

#endif

void CPU::showCycles( Mem &_mem)
{

   u32 cycles  = 100;
   for(auto instruction : instructionMap)
   {
      u32 _cycles = cycles;
      for(auto addressingMode:  instruction.first)
      {
         instruction.second(_cycles, _mem, addressingMode);
         std::cout<<std::ios::hex<<addressingMode<< std::ios::dec <<" :"<< (100 - _cycles) <<std::endl;
      }
   }
}
