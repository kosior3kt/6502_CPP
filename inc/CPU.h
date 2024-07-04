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
         ///////Do I even want to do this here - this should be more of a static thing? - Lets say it's fine for now

////////////////////////////////////// Load/Store
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

////////////////////////////////////// Increment/Decrement

         /// INC
         instructionMap[INS_INX]      = bindMemberFunction(&CPU::INX);
         instructionMap[INS_INY]      = bindMemberFunction(&CPU::INY);

         /// INX and INY
         instructionMap[INS_INC_ZP]   = bindMemberFunction(&CPU::INC_ZP);
         instructionMap[INS_INC_ZPX]  = bindMemberFunction(&CPU::INC_ZPX);
         instructionMap[INS_INC_ABS]  = bindMemberFunction(&CPU::INC_ABS);
         instructionMap[INS_INC_ABSX] = bindMemberFunction(&CPU::INC_ZPX);

         /// DEC
         instructionMap[INS_DEX]      = bindMemberFunction(&CPU::DEX);
         instructionMap[INS_DEY]      = bindMemberFunction(&CPU::DEY);

         /// DEY and DEX
         instructionMap[INS_DEC_ZP]   = bindMemberFunction(&CPU::DEC_ZP);
         instructionMap[INS_DEC_ZPX]  = bindMemberFunction(&CPU::DEC_ZPX);
         instructionMap[INS_DEC_ABS]  = bindMemberFunction(&CPU::DEC_ABS);
         instructionMap[INS_DEC_ABSX] = bindMemberFunction(&CPU::DEC_ABSX);

////////////////////////////////////// Jumps/Calls

         /// JSR
         instructionMap[INS_JSR]      = bindMemberFunction(&CPU::JSR);

         /// RTS
         instructionMap[INS_RTS]      = bindMemberFunction(&CPU::RTS);

         /// JMP
         instructionMap[INS_JMP_ABS]  = bindMemberFunction(&CPU::JMP_ABS);
         instructionMap[INS_JMP_IND]  = bindMemberFunction(&CPU::JMP_IND);
////////////////////////////////////// Stack Operations
         instructionMap[INS_TSX] = bindMemberFunction(&CPU::TSX);
         instructionMap[INS_TXS] = bindMemberFunction(&CPU::TXS);
         instructionMap[INS_PHA] = bindMemberFunction(&CPU::PHA);
         instructionMap[INS_PHP] = bindMemberFunction(&CPU::PHP);
         instructionMap[INS_PLA] = bindMemberFunction(&CPU::PLA);
         instructionMap[INS_PLP] = bindMemberFunction(&CPU::PLP);

////////////////////////////////////// Register Transfers
         instructionMap[INS_TAX] = bindMemberFunction(&CPU::TAX);
         instructionMap[INS_TAY] = bindMemberFunction(&CPU::TAY);
         instructionMap[INS_TXA] = bindMemberFunction(&CPU::TXA);
         instructionMap[INS_TYA] = bindMemberFunction(&CPU::TYA);

////////////////////////////////////// Logical
         /// AND
         instructionMap[INS_AND_IM  ] = bindMemberFunction(&CPU::AND_IM  );
         instructionMap[INS_AND_ZP  ] = bindMemberFunction(&CPU::AND_ZP  );
         instructionMap[INS_AND_ZPX ] = bindMemberFunction(&CPU::AND_ZPX );
         instructionMap[INS_AND_ABS ] = bindMemberFunction(&CPU::AND_ABS );
         instructionMap[INS_AND_ABSX] = bindMemberFunction(&CPU::AND_ABSX);
         instructionMap[INS_AND_ABSY] = bindMemberFunction(&CPU::AND_ABSY);
         instructionMap[INS_AND_INDX] = bindMemberFunction(&CPU::AND_INDX);
         instructionMap[INS_AND_INDY] = bindMemberFunction(&CPU::AND_INDY);

         /// EOR
         instructionMap[INS_EOR_IM  ] = bindMemberFunction(&CPU::EOR_IM  );
         instructionMap[INS_EOR_ZP  ] = bindMemberFunction(&CPU::EOR_ZP  );
         instructionMap[INS_EOR_ZPX ] = bindMemberFunction(&CPU::EOR_ZPX );
         instructionMap[INS_EOR_ABS ] = bindMemberFunction(&CPU::EOR_ABS );
         instructionMap[INS_EOR_ABSX] = bindMemberFunction(&CPU::EOR_ABSX);
         instructionMap[INS_EOR_ABSY] = bindMemberFunction(&CPU::EOR_ABSY);
         instructionMap[INS_EOR_INDX] = bindMemberFunction(&CPU::EOR_INDX);
         instructionMap[INS_EOR_INDY] = bindMemberFunction(&CPU::EOR_INDY);

         ///ORA 
         instructionMap[INS_ORA_IM  ] = bindMemberFunction(&CPU::ORA_IM  );
         instructionMap[INS_ORA_ZP  ] = bindMemberFunction(&CPU::ORA_ZP  );
         instructionMap[INS_ORA_ZPX ] = bindMemberFunction(&CPU::ORA_ZPX );
         instructionMap[INS_ORA_ABS ] = bindMemberFunction(&CPU::ORA_ABS );
         instructionMap[INS_ORA_ABSX] = bindMemberFunction(&CPU::ORA_ABSX);
         instructionMap[INS_ORA_ABSY] = bindMemberFunction(&CPU::ORA_ABSY);
         instructionMap[INS_ORA_INDX] = bindMemberFunction(&CPU::ORA_INDX);
         instructionMap[INS_ORA_INDY] = bindMemberFunction(&CPU::ORA_INDY);

         /// BIT
         instructionMap[INS_BIT_ZP ] = bindMemberFunction(&CPU::BIT_ZP );
         instructionMap[INS_BIT_ZBS] = bindMemberFunction(&CPU::BIT_ZBS);


////////////////////////////////////// Branches
         instructionMap[INS_BCC ] = bindMemberFunction(&CPU::BCC );
         instructionMap[INS_BCS ] = bindMemberFunction(&CPU::BCS );
         instructionMap[INS_BEQ ] = bindMemberFunction(&CPU::BEQ );
         instructionMap[INS_BMI ] = bindMemberFunction(&CPU::BMI );
         instructionMap[INS_BNE ] = bindMemberFunction(&CPU::BNE );
         instructionMap[INS_BPL ] = bindMemberFunction(&CPU::BPL );
         instructionMap[INS_BVC ] = bindMemberFunction(&CPU::BVC );
         instructionMap[INS_BVS ] = bindMemberFunction(&CPU::BVS );


////////////////////////////////////// Shifts
         ///ASL
         instructionMap[INS_ASL_ACC  ] = bindMemberFunction(&CPU::ASL_ACC  );
         instructionMap[INS_ASL_ZP   ] = bindMemberFunction(&CPU::ASL_ZP   );
         instructionMap[INS_ASL_ZPX  ] = bindMemberFunction(&CPU::ASL_ZPX  );
         instructionMap[INS_ASL_ABS  ] = bindMemberFunction(&CPU::ASL_ABS  );
         instructionMap[INS_ASL_ABSX ] = bindMemberFunction(&CPU::ASL_ABSX );

         ///LSR
         instructionMap[INS_LSR_ACC  ] = bindMemberFunction(&CPU::LSR_ACC  );
         instructionMap[INS_LSR_ZP   ] = bindMemberFunction(&CPU::LSR_ZP   );
         instructionMap[INS_LSR_ZPX  ] = bindMemberFunction(&CPU::LSR_ZPX  );
         instructionMap[INS_LSR_ABS  ] = bindMemberFunction(&CPU::LSR_ABS  );
         instructionMap[INS_LSR_ABSX ] = bindMemberFunction(&CPU::LSR_ABSX );

         ///ROL
         instructionMap[INS_ROL_ACC ] = bindMemberFunction(&CPU::ROL_ACC );
         instructionMap[INS_ROL_ZP  ] = bindMemberFunction(&CPU::ROL_ZP  );
         instructionMap[INS_ROL_ZPX ] = bindMemberFunction(&CPU::ROL_ZPX );
         instructionMap[INS_ROL_ABS ] = bindMemberFunction(&CPU::ROL_ABS );
         instructionMap[INS_ROL_ABSX] = bindMemberFunction(&CPU::ROL_ABSX);

         ///ROR
         instructionMap[INS_ROR_ACC ] = bindMemberFunction(&CPU::ROR_ACC );
         instructionMap[INS_ROR_ZP  ] = bindMemberFunction(&CPU::ROR_ZP  );
         instructionMap[INS_ROR_ZPX ] = bindMemberFunction(&CPU::ROR_ZPX );
         instructionMap[INS_ROR_ABS ] = bindMemberFunction(&CPU::ROR_ABS );
         instructionMap[INS_ROR_ABSX] = bindMemberFunction(&CPU::ROR_ABSX);

////////////////////////////////////// Arithmetic
         ///ADC
         instructionMap[INS_ADC_IM  ] = bindMemberFunction(&CPU::ADC_IM  );
         instructionMap[INS_ADC_ZP  ] = bindMemberFunction(&CPU::ADC_ZP  );
         instructionMap[INS_ADC_ZPX ] = bindMemberFunction(&CPU::ADC_ZPX );
         instructionMap[INS_ADC_ABS ] = bindMemberFunction(&CPU::ADC_ABS );
         instructionMap[INS_ADC_ABSX] = bindMemberFunction(&CPU::ADC_ABSX);
         instructionMap[INS_ADC_ABSY] = bindMemberFunction(&CPU::ADC_ABSY);
         instructionMap[INS_ADC_INDX] = bindMemberFunction(&CPU::ADC_INDX);
         instructionMap[INS_ADC_INDY] = bindMemberFunction(&CPU::ADC_INDY);

         /// SBC
         instructionMap[INS_SBC_IM  ] = bindMemberFunction(&CPU::SBC_IM  );
         instructionMap[INS_SBC_ZP  ] = bindMemberFunction(&CPU::SBC_ZP  );
         instructionMap[INS_SBC_ZPX ] = bindMemberFunction(&CPU::SBC_ZPX );
         instructionMap[INS_SBC_ABS ] = bindMemberFunction(&CPU::SBC_ABS );
         instructionMap[INS_SBC_ABSX] = bindMemberFunction(&CPU::SBC_ABSX);
         instructionMap[INS_SBC_ABSY] = bindMemberFunction(&CPU::SBC_ABSY);
         instructionMap[INS_SBC_INDX] = bindMemberFunction(&CPU::SBC_INDX);
         instructionMap[INS_SBC_INDY] = bindMemberFunction(&CPU::SBC_INDY);

         /// CMP
         instructionMap[INS_CMP_IM  ] = bindMemberFunction(&CPU::CMP_IM  );
         instructionMap[INS_CMP_ZP  ] = bindMemberFunction(&CPU::CMP_ZP  );
         instructionMap[INS_CMP_ZPX ] = bindMemberFunction(&CPU::CMP_ZPX );
         instructionMap[INS_CMP_ABS ] = bindMemberFunction(&CPU::CMP_ABS );
         instructionMap[INS_CMP_ABSX] = bindMemberFunction(&CPU::CMP_ABSX);
         instructionMap[INS_CMP_ABSY] = bindMemberFunction(&CPU::CMP_ABSY);
         instructionMap[INS_CMP_INDX] = bindMemberFunction(&CPU::CMP_INDX);
         instructionMap[INS_CMP_INDY] = bindMemberFunction(&CPU::CMP_INDY);

         ///CPX
         instructionMap[INS_CPX_IM  ] = bindMemberFunction(&CPU::CPX_IM  );
         instructionMap[INS_CPX_ZP  ] = bindMemberFunction(&CPU::CPX_ZP  );
         instructionMap[INS_CPX_ABS ] = bindMemberFunction(&CPU::CPX_ABS );

         ///CPY
         instructionMap[INS_CPY_IM  ] = bindMemberFunction(&CPU::CPY_IM  );
         instructionMap[INS_CPY_ZP  ] = bindMemberFunction(&CPU::CPY_ZP  );
         instructionMap[INS_CPY_ABS ] = bindMemberFunction(&CPU::CPY_ABS );


////////////////////////////////////// Status Flag Changes
         instructionMap[INS_CLC     ] = bindMemberFunction(&CPU::CLC     );
         instructionMap[INS_CLD     ] = bindMemberFunction(&CPU::CLD     );
         instructionMap[INS_CLI     ] = bindMemberFunction(&CPU::CLI     );
         instructionMap[INS_CLV     ] = bindMemberFunction(&CPU::CLV     );
         instructionMap[INS_SEC     ] = bindMemberFunction(&CPU::SEC     );
         instructionMap[INS_SED     ] = bindMemberFunction(&CPU::SED     );
         instructionMap[INS_SEI     ] = bindMemberFunction(&CPU::SEI     );


////////////////////////////////////// System Functions
         instructionMap[INS_BRK     ] = bindMemberFunction(&CPU::BRK     );
         instructionMap[INS_NOP     ] = bindMemberFunction(&CPU::NOP     );
         instructionMap[INS_RTI     ] = bindMemberFunction(&CPU::RTI     );


         /// NULL ///figure out later how to make it not hang my program =3
         // instructionMap[INS_NULL] = bindMemberFunction(&CPU::NULL_INS);

      }
};

#endif
