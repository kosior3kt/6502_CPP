#ifndef __CPU__
#define __CPU__

#include "memory.h"

#include <functional>
#include <map>

/// maybe later I will use it, when I discover that it is faster or sth
#define SUBST(VAR)                                                            \
   std::bind(&CPU::VAR, this, std::placeholders::_1, std::placeholders::_2)

// TODO:
/*
// - add stack operations (push pop)
// - fill function for settings flags
// - change instructions into enum if possible
// - remove instances of SetNZWithValue and replace it with general flag
setting function
// - abstract addressing modes
// - implement rest of the operations:
//    + AND
//    + ANC
//    + ASL
//    + BCC
//    + BCS
//    + BEQ
//    + BIT
//    + BMI
//    + BNE
//    + BPL
//    + BRK
//    + BVC
//    + CLC
//    + CLD
//    + CLI
//    + CLV
//    + CMP
//    + CPX
//    + CPY
//    + EOR
//    + JMP
//    + LSR
//    + NOP
//    + ORA
//    + PHA
//    + PHP
//    + PLA
//    + PLP
//    + ROL
//    + ROR
//    + RTI
//    + RTS
//    + SBC
//    + SEC
//    + SED
//    + SEI
//    + STA
//    + STX
//    + STY
//    + TAX
//    + TAY
//    + TSX
//    + TXA
//    + TXS
//    + TXY
*/

struct CPU
{
      /// want to have everything exposed for now. No need for encapsulation BS
      /// yet
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

      /// here we store all the instruction codes together with addressing
      /// mdoes (did what I had to do...)
#include "instructionCodes.h"

      /* ///unused for now, maybe I will change it later
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

      ///logic
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

      [[deprecated("Use execute() instead")]] s32
      execute_alternative(u32 _cycles, Mem &_mem);

      ///flags managment
      [[deprecated("Use SetCustomFlags...() instead")]] 
      void SetNZWithRegister(const Register &_reg);
      [[deprecated("Use SetCustomFlags...() instead")]] 
      void SetNZWithValue(const Byte &_val);

      void SetCustomFlagsWithValue(const Byte &_val, Byte &_flags);
      void SetCustomFlagsWithRegister(const Register &_reg, Byte &_flags);

   private:
      /// place for all the function for instructis
#include "instructionDefinitions.h"
   
   private: ///yeah, Im dubling private purposely for transaperncy
      /// wow - it actually works (im as surprised as you are)
      template <typename Func>
      std::function<void(u32 &, Mem &)> bindMemberFunction(Func func)
      {
         return std::bind(
             func, this, std::placeholders::_1, std::placeholders::_2
         );
      }

      std::map<Byte, std::function<void(u32 &, Mem &)> > instructionMap;

   public:
      explicit CPU()
      {
         ///////Do I even want to do this here - this should be more of a
         /// static thing?

         //// LDA
         instructionMap[INS_LDA_IM]   = bindMemberFunction(&CPU::LDA_IM);
         instructionMap[INS_LDA_ZP]   = bindMemberFunction(&CPU::LDA_ZP);
         instructionMap[INS_LDA_ZPX]  = bindMemberFunction(&CPU::LDA_ZPX);
         instructionMap[INS_LDA_ABS]  = bindMemberFunction(&CPU::LDA_ABS);
         instructionMap[INS_LDA_ABSX] = bindMemberFunction(&CPU::LDA_ABSX);
         instructionMap[INS_LDA_ABSY] = bindMemberFunction(&CPU::LDA_ABSY);
         instructionMap[INS_LDA_INDX] = bindMemberFunction(&CPU::LDA_INDX);
         instructionMap[INS_LDA_INDY] = bindMemberFunction(&CPU::LDA_INDY);

         //// LDX
         instructionMap[INS_LDX_IM]   = bindMemberFunction(&CPU::LDX_IM);
         instructionMap[INS_LDX_ZP]   = bindMemberFunction(&CPU::LDX_ZP);
         instructionMap[INS_LDX_ZPY]  = bindMemberFunction(&CPU::LDX_ZPY);
         instructionMap[INS_LDX_ABS]  = bindMemberFunction(&CPU::LDX_ABS);
         instructionMap[INS_LDX_ABSY] = bindMemberFunction(&CPU::LDX_ABSY);

         //// LDY
         instructionMap[INS_LDY_IM]   = bindMemberFunction(&CPU::LDY_IM);
         instructionMap[INS_LDY_ZP]   = bindMemberFunction(&CPU::LDY_ZP);
         instructionMap[INS_LDY_ZPX]  = bindMemberFunction(&CPU::LDY_ZPX);
         instructionMap[INS_LDY_ABS]  = bindMemberFunction(&CPU::LDY_ABS);
         instructionMap[INS_LDY_ABSX] = bindMemberFunction(&CPU::LDY_ABSX);

         /// JSR
         instructionMap[INS_JSR] = bindMemberFunction(&CPU::JSR);

         /// INC
         instructionMap[INS_INX] = bindMemberFunction(&CPU::INX);
         instructionMap[INS_INY] = bindMemberFunction(&CPU::INY);

         instructionMap[INS_INC_ZP]   = bindMemberFunction(&CPU::INC_ZP);
         instructionMap[INS_INC_ZPX]  = bindMemberFunction(&CPU::INC_ZPX);
         instructionMap[INS_INC_ABS]  = bindMemberFunction(&CPU::INC_ABS);
         instructionMap[INS_INC_ABSX] = bindMemberFunction(&CPU::INC_ZPX);

         /// DEC
         instructionMap[INS_DEX] = bindMemberFunction(&CPU::DEX);
         instructionMap[INS_DEY] = bindMemberFunction(&CPU::DEY);

         instructionMap[INS_DEC_ZP]   = bindMemberFunction(&CPU::DEC_ZP);
         instructionMap[INS_DEC_ZPX]  = bindMemberFunction(&CPU::DEC_ZPX);
         instructionMap[INS_DEC_ABS]  = bindMemberFunction(&CPU::DEC_ABS);
         instructionMap[INS_DEC_ABSX] = bindMemberFunction(&CPU::DEC_ABSX);

         /// NULL ///figure out later how to make it not hang my program =3
         // instructionMap[INS_NULL] = bindMemberFunction(&CPU::NULL_INS);
      }
};

#endif
