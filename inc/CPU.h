#ifndef __CPU__
#define __CPU__

#include "memory.h"

#include <functional>
#include <map>

struct CPU
{
      /// want to have everything exposed for now. No need for encapsulation BS yet
      Word PC; /// program counter
      Byte SP; /// stack pointer - it has to be a Byte because it is fixed size 256 between $0100 and $01FF

      Byte A, X, Y; /// registers - less is more

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

      ///////////////////////////////////////////////// place for all the function for instruction codes and definitions 
#include "instructionCodes.h"
#include "instructionDefinitions.h"


   private:
      /////////////////////////////////////////////////logic and memory
      Byte FetchByte(u32 &_cycles, const Mem &_mem);
      Word FetchWord(u32 &_cycles, const Mem &_mem);

      Byte ReadByte(u32 &_cycles, const Byte &_addr, const Mem &_mem);
      Byte ReadByte(u32 &_cycles, const Word &_addr, const Mem &_mem);
      Byte ReadWord(u32 &_cycles, const Byte &_addr, const Mem &_mem);
      Byte ReadWord(u32 &_cycles, const Word &_addr, const Mem &_mem);

      void WriteByte(u32 &_cycles, const Byte &_addr, Mem &_mem, const Byte &_val);
      void WriteByte(u32 &_cycles, const Word &_addr, Mem &_mem, const Byte &_val);
      void WriteWord(u32 &_cycles, const Word &_addr, Mem &_mem, const Word&_val);
      void WriteWord(u32 &_cycles, const Byte&_addr, Mem &_mem, const Word&_val);


      /////////////////////////////////////////////////even I - the creator fear this thing...
      void ApplyToMemory(u32 &_cycles, const Word &_addr, Mem &_mem, std::function<Byte(const Byte &)>);
      void ApplyToMemory(u32 &_cycles, const Byte &_addr, Mem &_mem, std::function<Byte(const Byte &)>);

      /////////////////////////////////////////////////stack
      void pushByteToStack(u32& _cycles, Mem& _mem, const Byte& _val);
      Byte popByteFromStack(u32& _cycles, Mem& _mem);
      void pushWordToStack(u32& _cycles, Mem& _mem, const Word& _val);
      Word popWordFromStack(u32& _cycles, Mem& _mem);
   public:

      void Reset(Mem &_mem, const Word& _PC_start = 0xFFFC);

      /////////////////////////////////////////////////execution 
      s32 execute(u32 _cycles, Mem &_mem);

      [[deprecated("Use execute() instead")]] 
      s32 execute_alternative(u32 _cycles, Mem &_mem);

      /////////////////////////////////////////////////flags managment
      [[deprecated("Use SetCustomFlags...() instead")]] 
      void SetNZWithRegister(const Register &_reg);

      [[deprecated("Use SetCustomFlags...() instead")]]
      void SetNZWithValue(const Byte &_val);

      void SetCustomFlagsWithValue(const Byte &_val, Byte &_flags);
      void SetCustomFlagsWithRegister(const Register &_reg, Byte &_flags);

   
   private:      
      /// wow - it actually works (im as surprised as you are)
      template <typename Func>
      std::function<void(u32 &, Mem &)> bindMemberFunction(Func func)
      {
         return std::bind(
             func, this, std::placeholders::_1, std::placeholders::_2
         );
      }

      std::map<Byte, std::function<void(u32 &, Mem &)>> instructionMap;

   public:
      explicit CPU()
      {
         ///////Do I even want to do this here - this should be more of a static thing?

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
         instructionMap[INS_JSR]      = bindMemberFunction(&CPU::JSR);

         /// INC
         instructionMap[INS_INX]      = bindMemberFunction(&CPU::INX);
         instructionMap[INS_INY]      = bindMemberFunction(&CPU::INY);

         instructionMap[INS_INC_ZP]   = bindMemberFunction(&CPU::INC_ZP);
         instructionMap[INS_INC_ZPX]  = bindMemberFunction(&CPU::INC_ZPX);
         instructionMap[INS_INC_ABS]  = bindMemberFunction(&CPU::INC_ABS);
         instructionMap[INS_INC_ABSX] = bindMemberFunction(&CPU::INC_ZPX);

         /// DEC
         instructionMap[INS_DEX]      = bindMemberFunction(&CPU::DEX);
         instructionMap[INS_DEY]      = bindMemberFunction(&CPU::DEY);

         instructionMap[INS_DEC_ZP]   = bindMemberFunction(&CPU::DEC_ZP);
         instructionMap[INS_DEC_ZPX]  = bindMemberFunction(&CPU::DEC_ZPX);
         instructionMap[INS_DEC_ABS]  = bindMemberFunction(&CPU::DEC_ABS);
         instructionMap[INS_DEC_ABSX] = bindMemberFunction(&CPU::DEC_ABSX);

         ///STA
         instructionMap[INS_STA_ZP]   = bindMemberFunction(&CPU::STA_ZP);
         instructionMap[INS_STA_ZPX]  = bindMemberFunction(&CPU::STA_ZPX);
         instructionMap[INS_STA_ABS]  = bindMemberFunction(&CPU::STA_ABS);
         instructionMap[INS_STA_ABSX] = bindMemberFunction(&CPU::STA_ABSX);
         instructionMap[INS_STA_ABSY] = bindMemberFunction(&CPU::STA_ABSY);
         instructionMap[INS_STA_INDX] = bindMemberFunction(&CPU::STA_INDX);
         instructionMap[INS_STA_INDY] = bindMemberFunction(&CPU::STA_INDY);

         /// STX
         instructionMap[INS_STX_ZP]   = bindMemberFunction(&CPU::STX_ZP);
         instructionMap[INS_STX_ZPY]  = bindMemberFunction(&CPU::STX_ZPY);
         instructionMap[INS_STX_ABS]  = bindMemberFunction(&CPU::STX_ABS);

         /// STY
         instructionMap[INS_STY_ZP]   = bindMemberFunction(&CPU::STY_ZP);
         instructionMap[INS_STY_ZPX]  = bindMemberFunction(&CPU::STY_ZPX);
         instructionMap[INS_STY_ABS]  = bindMemberFunction(&CPU::STY_ABS);

         /// RTS
         instructionMap[INS_RTS]      = bindMemberFunction(&CPU::RTS);

         /// JMP
         instructionMap[INS_JMP_ABS]  = bindMemberFunction(&CPU::JMP_ABS);
         instructionMap[INS_JMP_IND]  = bindMemberFunction(&CPU::JMP_IND);

         /// NULL ///figure out later how to make it not hang my program =3
         // instructionMap[INS_NULL] = bindMemberFunction(&CPU::NULL_INS);

      }
};

#endif
