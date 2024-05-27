#ifndef __CPU__
#define __CPU__

#include "memory.h"

#include <functional>
#include <map>

/// maybe later I will use it, when I discover that it is faster or sth
#define SUBST(VAR)                                                            \
   std::bind(&CPU::VAR, this, std::placeholders::_1, std::placeholders::_2)

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

      /// INC instructions
      static constexpr Byte INS_INC_ZP   = 0xE6;
      static constexpr Byte INS_INC_ZPX  = 0xF6;
      static constexpr Byte INS_INC_ABS  = 0xEE;
      static constexpr Byte INS_INC_ABSX = 0xFE;

      /// INX and INY
      static constexpr Byte INS_INX = 0xE8;
      static constexpr Byte INS_INY = 0xC8;

      /// DEC incstructions
      static constexpr Byte INS_DEC_ZP   = 0xC6;
      static constexpr Byte INS_DEC_ZPX  = 0xD6;
      static constexpr Byte INS_DEC_ABS  = 0xCE;
      static constexpr Byte INS_DEC_ABSX = 0xDE;

      /// DEX and DEY
      static constexpr Byte INS_DEX = 0xCA;
      static constexpr Byte INS_DEY = 0x88;

      /* ///unused for now
      struct canBeExceeded
      {
            bool can;
            uint8_t value;
            canBeExceeded(bool _b, uint8_t _v) :
                can(_b),
                value(_v) {};
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
      */

      void Reset(Mem &_mem);

      Byte FetchByte(u32 &_cycles, const Mem &_mem);

      Word FetchWord(u32 &_cycles, const Mem &_mem);

      Byte ReadByte(u32 &_cycles, const Byte &_addr, const Mem &_mem);

      Byte ReadByte(u32 &_cycles, const Word &_addr, const Mem &_mem);

      void
      WriteByte(u32 &_cycles, const Byte &_addr, Mem &_mem, const Byte &_val);

      void
      WriteByte(u32 &_cycles, const Word &_addr, Mem &_mem, const Byte &_val);

      Byte ReadWord(u32 &_cycles, const Byte &_addr, const Mem &_mem);

      Byte ReadWord(u32 &_cycles, const Word &_addr, const Mem &_mem);

      void
      ApplyToMemory(u32 &_cycles, const Word &_addr, Mem &_mem, std::function<Byte(const Byte &)>);

      void
      ApplyToMemory(u32 &_cycles, const Byte &_addr, Mem &_mem, std::function<Byte(const Byte &)>);

      s32 execute(u32 _cycles, Mem &_mem);

      s32 execute_alternative(u32 _cycles, Mem &_mem);

      void SetNZWithRegister(const Register &_reg);

      void SetNZWithValue(const Byte &_val);

      void SetCustomFlagsWithValue(const Byte &_val, Byte &_flags);

      void SetCustomFlagsWithRegister(const Register &_reg, Byte &_flags);

   private:
      /// place for all the function for instructis

      void NULL_INS(u32 &_cycles, Mem &_mem);

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
      /// void INC(u32& _cycles, Mem& _mem);

      void INC_ZP(u32 &_cycles, Mem &_mem);
      void INC_ZPX(u32 &_cycles, Mem &_mem);
      void INC_ABS(u32 &_cycles, Mem &_mem);
      void INC_ABSX(u32 &_cycles, Mem &_mem);

      /// INX - this instruction increments value stored in the X register
      void INX(u32 &_cycles, Mem &_mem);

      /// INY - this instruction increments value stored in the Y register
      void INY(u32 &_cycles, Mem &_mem);

      /// DEC
      void DEC_ZP(u32 &_cycles, Mem &_mem);
      void DEC_ZPX(u32 &_cycles, Mem &_mem);
      void DEC_ABS(u32 &_cycles, Mem &_mem);
      void DEC_ABSX(u32 &_cycles, Mem &_mem);

      /// DEX
      void DEX(u32 &_cycles, Mem &_mem);

      /// DEY
      void DEY(u32 &_cycles, Mem &_mem);

      /// wow - it actually works (??)
      template <typename Func>
      std::function<void(u32 &, Mem &)> bindMemberFunction(Func func)
      {
         return std::bind(
             func, this, std::placeholders::_1, std::placeholders::_2
         );
      }

      std::map<Byte, std::function<void(u32 &, Mem &)> > test;

   public:
      CPU()
      {
         ///////Do I even want to do this here?

         //// LDA

         test[INS_LDA_IM]   = bindMemberFunction(&CPU::LDA_IM);
         test[INS_LDA_ZP]   = bindMemberFunction(&CPU::LDA_ZP);
         test[INS_LDA_ZPX]  = bindMemberFunction(&CPU::LDA_ZPX);
         test[INS_LDA_ABS]  = bindMemberFunction(&CPU::LDA_ABS);
         test[INS_LDA_ABSX] = bindMemberFunction(&CPU::LDA_ABSX);
         test[INS_LDA_ABSY] = bindMemberFunction(&CPU::LDA_ABSY);
         test[INS_LDA_INDX] = bindMemberFunction(&CPU::LDA_INDX);
         test[INS_LDA_INDY] = bindMemberFunction(&CPU::LDA_INDY);
         //// LDX

         test[INS_LDX_IM]   = bindMemberFunction(&CPU::LDX_IM);
         test[INS_LDX_ZP]   = bindMemberFunction(&CPU::LDX_ZP);
         test[INS_LDX_ZPY]  = bindMemberFunction(&CPU::LDX_ZPY);
         test[INS_LDX_ABS]  = bindMemberFunction(&CPU::LDX_ABS);
         test[INS_LDX_ABSY] = bindMemberFunction(&CPU::LDX_ABSY);
         //// LDY

         test[INS_LDY_IM]   = bindMemberFunction(&CPU::LDY_IM);
         test[INS_LDY_ZP]   = bindMemberFunction(&CPU::LDY_ZP);
         test[INS_LDY_ZPX]  = bindMemberFunction(&CPU::LDY_ZPX);
         test[INS_LDY_ABS]  = bindMemberFunction(&CPU::LDY_ABS);
         test[INS_LDY_ABSX] = bindMemberFunction(&CPU::LDY_ABSX);
         /// JSR

         test[INS_JSR] = bindMemberFunction(&CPU::JSR);
         /// INC

         test[INS_INX] = bindMemberFunction(&CPU::INX);
         test[INS_INY] = bindMemberFunction(&CPU::INY);

         test[INS_INC_ZP]   = bindMemberFunction(&CPU::INC_ZP);
         test[INS_INC_ZPX]  = bindMemberFunction(&CPU::INC_ZPX);
         test[INS_INC_ABS]  = bindMemberFunction(&CPU::INC_ABS);
         test[INS_INC_ABSX] = bindMemberFunction(&CPU::INC_ZPX);
         /// DEC

         test[INS_DEX] = bindMemberFunction(&CPU::DEX);
         test[INS_DEY] = bindMemberFunction(&CPU::DEY);

         test[INS_DEC_ZP]   = bindMemberFunction(&CPU::DEC_ZP);
         test[INS_DEC_ZPX]  = bindMemberFunction(&CPU::DEC_ZPX);
         test[INS_DEC_ABS]  = bindMemberFunction(&CPU::DEC_ABS);
         test[INS_DEC_ABSX] = bindMemberFunction(&CPU::DEC_ABSX);

         // NULL
         // test[INS_NULL] = bindMemberFunction(&CPU::NULL_INS);
      }
};

#endif
