#ifndef __CPU__
#define __CPU__

#include "memory.h"

#include <map>

struct CPU
{

      Word PC; /// program counter
      Word SP; /// stack pointer

      Byte A, X, Y; /// registers

      Byte C : 1; // status flag
      Byte Z : 1; // status flag
      Byte I : 1; // status flag
      Byte D : 1; // status flag
      Byte B : 1; // status flag
      Byte V : 1; // status flag
      Byte N : 1; // status flag

      /// not used for now
      enum class INS : Byte
      {
         LDA_IM      = 0xA9,
         INS_LDA_ZP  = 0xA5,
         INS_LDA_ZPX = 0xB5,
         INS_JSR     = 0x20,
      };

      static constexpr Byte INS_LDA_IM   = 0xA9;
      static constexpr Byte INS_LDA_ZP   = 0xA5;
      static constexpr Byte INS_LDA_ABS  = 0xAD;
      static constexpr Byte INS_LDA_ZPX  = 0xB5;
      static constexpr Byte INS_LDA_ABSY = 0xB9;
      static constexpr Byte INS_LDA_ABSX = 0xBD;
      static constexpr Byte INS_JSR      = 0x20;

      std::map<Byte, uint8_t> numberOfCyclesByInstruction_{
         {  INS_LDA_IM, 2 },
         {  INS_LDA_ZP, 3 },
         { INS_LDA_ABS, 4 },
         { INS_LDA_ABS, 4 },
         { INS_LDA_ZPX, 4 },
         {     INS_JSR, 6 },
      };

      void Reset(Mem &_mem);

      Byte FetchByte(u32 &_cycles, const Mem &_mem);

      Word FetchWord(u32 &_cycles, const Mem &_mem);

      Byte ReadByte(u32 &_cycles, const Byte &_addr, const Mem &_mem);

      Byte ReadByte(u32 &_cycles, const Word &_addr, const Mem &_mem);

      void LDASetStatus();

      s32 execute(u32 _cycles, Mem &_mem);
};

#endif
