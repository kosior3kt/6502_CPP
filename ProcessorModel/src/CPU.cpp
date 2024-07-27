#include "CPU.h"


s32 CPU::execute(u32 _cycles, Mem &_mem)
{
   bool end {false};
    while(!end)
   {
      Byte inst         = fetchByte(_cycles, _mem);
      bool found = false;
      for(auto x : instructionMap)
      {
         if(x.first.find(inst) == x.first.end()) continue;
         x.second(_cycles, _mem, inst);
         found = true;
         break;
      }
#ifdef ENDLESS_MODE
      ///preparing for future - I have no idea what I want to do with this now...
#else
      end = (_cycles == 0) ? true : false;
#endif

      if(!found)[[unlikely]]
      {
         printf("Not handled %d\n", inst);
         break;   ///<----- doesn't this slow code instead of helping it?
      }
   }
   return _cycles;
}

///this thing doesn't even work I think xD
[[deprecated("this doesn't even work...")]]
void CPU::showCycles( Mem &_mem)
{
   u32 cycles  = 100;
   for(auto instruction: instructionMap)
   {
      u32 _cycles = cycles;
      for(auto addressingMode: instruction.first)
      {
         instruction.second(_cycles, _mem, addressingMode);
         std::cout<<std::ios::hex<<addressingMode<< std::ios::dec <<" :"<< (100 - _cycles) <<std::endl;
      }
   }
}


void CPU::showCPUState(const Mem& _mem, const bool _showPCMem, const bool _showSPMem, const unsigned _num)
{
   std::cout<<"================|| ASSIGNED NUMBER: "<<(int)_num<<" ||================\n";  ///dont want this to be displayed in hex

   HEX_PRINT_TO_BE_WRAPPED("  REGISTERS:\n",
         "    A: ", (int)A, "\n",
         "    X: ", (int)X, "\n",
         "    Y: ", (int)Y, "\n"
         );
   HEX_PRINT_TO_BE_WRAPPED("  FLAGS:\n",
         "    C: ", (int)C, "\n",
         "    Z: ", (int)Z, "\n",
         "    I: ", (int)I, "\n",
         "    D: ", (int)D, "\n",
         "    B: ", (int)B, "\n",
         "    V: ", (int)V, "\n",
         "    N: ", (int)N, "\n"
         );
   HEX_PRINT_TO_BE_WRAPPED("  PC and SP:\n",
         "   PC: ", (int)PC, "\n",
         "   SP: ", (int)SP, "\n"
         );

   u32 temp ;
   if(_showPCMem)
   {
      temp = PC;
      HEX_PRINT_TO_BE_WRAPPED("  MEMORY AROUND PC:");
      for(int i = 0; i < 5; ++i) temp += (-!!temp);   ///this will decrese it by 5 if possible else to zero - it will not wrap
      for(int i = 0; i < 10; ++i)
      {
         HEX_PRINT_TO_BE_WRAPPED
            (
               "   ", temp, " => ", (int)_mem.at(temp)
            );
         if(temp >= 1024*64 - 1) break; ///so it doesnt cross the system mem
         ++temp;
      }
   }

   if(_showSPMem)
   {
      temp = SP;
      HEX_PRINT_TO_BE_WRAPPED("  MEMORY AROUND SP:");
      for(int i = 0; i < 5; ++i)
      {
         if(SP >= 0xFF) break;
         SP++;
      }
      for(int i = 10; i > 0; --i)
      {
         HEX_PRINT_TO_BE_WRAPPED
            (
               "   ", temp, " => ", (int)_mem.at(temp)
            );
         if(temp >= 1024*64 - 1) break; ///so it doesnt cross the system mem
         --temp;
      }
   }
}
