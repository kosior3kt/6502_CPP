#include "CPU.h"

s32 CPU::execute(u32 _cycles, Mem &_mem)
{
   while(_cycles > 0)
   {
      Byte inst         = FetchByte(_cycles, _mem);
      auto functionIter = CPU::instructionMap.find(inst);

      if(functionIter != instructionMap.end()) [[likely]]
      {
         functionIter->second(_cycles, _mem);
      }
      else [[unlikely]]
      {
         printf("Not handled %d\n", inst);
         break;
      }
   }
   return _cycles;
}

s32 CPU::execute_test(u32 _cycles, Mem &_mem)
{
    while(_cycles > 0)
   {
      Byte inst         = FetchByte(_cycles, _mem);
      bool found = false;
      for(auto x : instructionMap_test)
      {
         if(x.first.find(inst) == x.first.end()) continue;
         x.second(_cycles, _mem, inst);
         found = true;
      }
      if(!found)[[unlikely]]
      {
         printf("Not handled %d\n", inst);
         break;
      }
   }
   return _cycles;
}

s32 CPU::execute_alternative(
    u32 _cycles, Mem &_mem
) /// from now on I will use mainly CPU::execute and not support this one. Feel
  /// free to port rest of command here tho
{

   while(_cycles)
   {
      Byte inst = FetchByte(_cycles, _mem);
      switch(inst)
      {
      case INS_LDA_IM:
      {
         LDA_IM(_cycles, _mem);
         break;
      }

      case INS_LDA_ZP:
      {
         LDA_ZP(_cycles, _mem);
         break;
      }

      case INS_LDA_ZPX:
      {
         LDA_ZPX(_cycles, _mem);
         break;
      }

      case INS_LDA_ABS:
      {
         LDA_ABS(_cycles, _mem);
         break;
      }

      case INS_LDA_ABSX:
      {
         LDA_ABSX(_cycles, _mem);
         break;
      }

      case INS_LDA_ABSY:
      {
         LDA_ABSY(_cycles, _mem);
         break;
      }

      case INS_JSR:
      {
         JSR(_cycles, _mem);
         break;
      }

      case INS_LDA_INDX:
      {
         LDA_INDX(_cycles, _mem);
         break;
      }

      case INS_LDA_INDY:
      {
         LDA_INDY(_cycles, _mem);
         break;
      }

      case INS_LDX_IM:
      {
         LDX_IM(_cycles, _mem);
         break;
      }

      case INS_LDX_ZP:
      {
         LDX_ZP(_cycles, _mem);
         break;
      }

      case INS_LDX_ZPY:
      {
         LDX_ZPY(_cycles, _mem);
         break;
      }

      case INS_LDX_ABS:
      {
         LDX_ABS(_cycles, _mem);
         break;
      }

      case INS_LDX_ABSY:
      {
         LDX_ABSY(_cycles, _mem);
         break;
      }

      case INS_LDY_IM:
      {
         LDY_IM(_cycles, _mem);
         break;
      }

      case INS_LDY_ZP:
      {
         LDY_ZP(_cycles, _mem);
         break;
      }

      case INS_LDY_ZPX:
      {
         LDY_ZPX(_cycles, _mem);
         break;
      }

      case INS_LDY_ABS:
      {
         LDY_ABS(_cycles, _mem);
         break;
      }

      case INS_LDY_ABSX:
      {
         LDY_ABSX(_cycles, _mem);
         break;
      }

      case INS_INX:
      {
         INX(_cycles, _mem);
         break;
      }

      case INS_INY:
      {
         INY(_cycles, _mem);
         break;
      }

      case INS_DEX:
      {
         DEX(_cycles, _mem);
         break;
      }

      case INS_DEY:
      {
         DEY(_cycles, _mem);
         break;
      }

      case INS_NULL:
      {
         return _cycles;
      }

      default:
      {
         printf("Not handled %d\n", inst);
         return _cycles;
         break;
      }
      }
   }
   return _cycles;
}
