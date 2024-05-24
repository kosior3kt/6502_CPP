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

      enum class Register : uint8_t
      {
         A,
         X,
         Y
      };

      /// Empty instruction
      static constexpr Byte INS_NULL = 0x00;

      /// LDA instructions
      static constexpr Byte INS_LDA_IM   = 0xA9;
      static constexpr Byte INS_LDA_ZP   = 0xA5;
      static constexpr Byte INS_LDA_ABS  = 0xAD;
      static constexpr Byte INS_LDA_ZPX  = 0xB5;
      static constexpr Byte INS_LDA_ABSY = 0xB9;
      static constexpr Byte INS_LDA_ABSX = 0xBD;
      static constexpr Byte INS_LDA_INDX = 0xA1;
      static constexpr Byte INS_LDA_INDY = 0xB1;

      /// JSR instruction
      static constexpr Byte INS_JSR = 0x20;

      /// LDX instructions
      static constexpr Byte INS_LDX_IM   = 0xA2;
      static constexpr Byte INS_LDX_ZP   = 0xA6;
      static constexpr Byte INS_LDX_ZPY  = 0xB6;
      static constexpr Byte INS_LDX_ABS  = 0xAE;
      static constexpr Byte INS_LDX_ABSY = 0xBE;

      /// LDY instructions
      static constexpr Byte INS_LDY_IM   = 0xA0;
      static constexpr Byte INS_LDY_ZP   = 0xA4;
      static constexpr Byte INS_LDY_ZPX  = 0xB4;
      static constexpr Byte INS_LDY_ABS  = 0xAC;
      static constexpr Byte INS_LDY_ABSX = 0xBC;

      struct canBeExceeded
      {
            bool can;
            uint8_t value;
            canBeExceeded(bool _b, uint8_t _v) :
                can(_b),
                value(_v){};
      };

      std::map<Byte, canBeExceeded> numberOfCyclesByInstruction_{
         {   INS_LDA_IM, canBeExceeded(false, 2) },
         {   INS_LDA_ZP, canBeExceeded(false, 3) },
         {  INS_LDA_ABS, canBeExceeded(false, 4) },
         { INS_LDA_ABSX,  canBeExceeded(true, 4) },
         { INS_LDA_ABSY,  canBeExceeded(true, 4) },
         { INS_LDA_INDX, canBeExceeded(false, 6) },
         { INS_LDA_INDY,  canBeExceeded(true, 5) },
         {  INS_LDA_ZPX, canBeExceeded(false, 4) },
         {      INS_JSR, canBeExceeded(false, 6) },
      };

      void Reset(Mem &_mem);

      Byte FetchByte(u32 &_cycles, const Mem &_mem);

      Word FetchWord(u32 &_cycles, const Mem &_mem);

      Byte ReadByte(u32 &_cycles, const Byte &_addr, const Mem &_mem);

      Byte ReadByte(u32 &_cycles, const Word &_addr, const Mem &_mem);

      Byte ReadWord(u32 &_cycles, const Byte &_addr, const Mem &_mem);

      Byte ReadWord(u32 &_cycles, const Word &_addr, const Mem &_mem);

      void LDASetStatus();

      void LDXSetStatus();

      void LDYSetStatus();

      s32 execute(u32 _cycles, Mem &_mem);

   private:
      /// place for all the function for instructis

      /// LDA - instruction LDA loads value from given memory location into the
      /// A register. It has 8 different adression modes - they are below
      void LDA_IM(u32 &_cycles, Mem &_mem);
      void LDA_ZP(u32 &_cycles, Mem &_mem);
      void LDA_ZPX(u32 &_cycles, Mem &_mem);
      void LDA_ABS(u32 &_cycles, Mem &_mem);
      void LDA_ABSY(u32 &_cycles, Mem &_mem);
      void LDA_ABSX(u32 &_cycles, Mem &_mem);
      void LDA_INDX(u32 &_cycles, Mem &_mem);
      void LDA_INDY(u32 &_cycles, Mem &_mem);

      /// JSR - this instruction jumps to the subrutine  (and preasumably
      /// returns)
      void JSR(u32 &_cycles, Mem &_mem);

      /// LDX  - instruction LDX loads value from given memory location into
      /// the X register. It has 5 different adressing modes
      void LDX_IM(u32 &_cycles, Mem &_mem);
      void LDX_ZP(u32 &_cycles, Mem &_mem);
      void LDX_ZPY(u32 &_cycles, Mem &_mem);
      void LDX_ABS(u32 &_cycles, Mem &_mem);
      void LDX_ABSY(u32 &_cycles, Mem &_mem);

      /// LDY - instruction LDX loads value from given memory location into the
      /// Y register. It has 5 different adressing modes
      void LDY_IM(u32 &_cycles, Mem &_mem);
      void LDY_ZP(u32 &_cycles, Mem &_mem);
      void LDY_ZPX(u32 &_cycles, Mem &_mem);
      void LDY_ABS(u32 &_cycles, Mem &_mem);
      void LDY_ABSX(u32 &_cycles, Mem &_mem);

      /// INC - instruction INC increments value in the given memory locatino

      /// INX - this instruction increments value stored in the X register

      /// INY - this instruction increments value stored in the Y register
};

#endif
