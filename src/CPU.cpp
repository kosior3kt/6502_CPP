#include "CPU.h"

s32 CPU::execute(u32 _cycles, Mem &_mem)
{
   while(_cycles)
   {
      Byte inst = FetchByte(_cycles, _mem);
      switch(inst) /// TODO: abstaract this later into a std::map<INS,
                   /// 'function pointer'>, so that it isnt such a massive boi
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

      default:
      {
         /// TODO: decide later if we want to panic or sth in such case
         printf("Not handled %d\n", inst);
         return _cycles;
         break;
      }
      }
   }
   return _cycles;
}
