#ifndef __CPU__
#define __CPU__

#include "memory.h"

#include <functional>
#include <map>
#include <list>
#include <set>

struct CPU
{
      /// want to have everything exposed for now. No need for encapsulation BS yet
      Word PC; /// program counter
      Byte SP; /// stack pointer - it has to be a Byte because it is fixed size 256 between $0100 and $01FF

      Byte A, X, Y; /// registers - less is more

      ///IDK I dont feel like changing it now
      // struct flags
      // {
         Byte C : 1; // status flag
         Byte Z : 1; // status flag
         Byte I : 1; // status flag
         Byte D : 1; // status flag
         Byte B : 1; // status flag
         Byte V : 1; // status flag
         Byte N : 1; // status flag
      // }current_flags{};

      enum class Register : uint8_t
      {
         A,
         X,
         Y
      };

      enum class adressingMode : uint8_t
      {
         ZP,
         ZPX,
         ZPY,
         REL,
         ABS,
         ABSX,
         ABSY,
         IND,
         INDX,
         INDY, 
      };

      Word getAddr(u32& _cycles, const Mem& _mem, const adressingMode& _am);

      ///access to all flags at the same time
      uint8_t getCurrentFlags() const;
      void setCurrentFlags(const uint8_t& _flags);

      ///////////////////////////////////////////////// place for all the function for instruction codes and definitions 
#include "instructionCodes.h"
#include "instructionDefinitions.h"

   private:
      /////////////////////////////////////////////////logic and memory
      Byte FetchByte(u32 &_cycles, const Mem &_mem);
      Word FetchWord(u32 &_cycles, const Mem &_mem);

      Byte ReadByte(u32 &_cycles, const Byte &_addr, const Mem &_mem);
      Byte ReadByte(u32 &_cycles, const Word &_addr, const Mem &_mem);
      Word ReadWord(u32 &_cycles, const Byte &_addr, const Mem &_mem);
      Word ReadWord(u32 &_cycles, const Word &_addr, const Mem &_mem);

      void WriteByte(u32 &_cycles, const Byte &_addr, Mem &_mem, const Byte &_val);
      void WriteByte(u32 &_cycles, const Word &_addr, Mem &_mem, const Byte &_val);
      void WriteWord(u32 &_cycles, const Word &_addr, Mem &_mem, const Word&_val);
      void WriteWord(u32 &_cycles, const Byte&_addr, Mem &_mem, const Word&_val);


      /////////////////////////////////////////////////even I - the creator fear this thing...
      void ApplyToMemory(u32 &_cycles, const Word &_addr, Mem &_mem, std::function<Byte(const Byte &)>);
      void ApplyToMemory(u32 &_cycles, const Byte &_addr, Mem &_mem, std::function<Byte(const Byte &)>);

      /////////////////////////////////////////////////stack
      Byte popByteFromStack(u32& _cycles, Mem& _mem);
      Word popWordFromStack(u32& _cycles, Mem& _mem);

      void pushWordToStack(u32& _cycles, Mem& _mem, const Word& _val);
      void pushByteToStack(u32& _cycles, Mem& _mem, const Byte& _val);

      Byte ReadByteFromStack(u32& _cycles, Mem& _mem);
      Word ReadWordFromStack(u32& _cycles, Mem& _mem);

      void OverwriteByteOnStack(u32& _cycles, Mem& _mem, const Word& _val);
      void OverwriteWordOnStack(u32& _cycles, Mem& _mem, const Word& _val);
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
      std::function<void(u32 &, Mem &)> bindMemberFunction_legacy(Func func)
      {
         return std::bind(
             func, this, std::placeholders::_1, std::placeholders::_2
         );
      }

      /// wow - it actually works (im as surprised as you are)
      template <typename Func>
      std::function<void(u32 &, Mem &, const Byte&)> bindMemberFunction(Func func)
      {
         return std::bind(
             func, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3
         );
      }

      std::map<Byte, std::function<void(u32 &, Mem &)>> instructionMap_legacy;
      std::map<std::set<Byte>, std::function<void(u32 &, Mem &, const Byte&)>> instructionMap;

   public:
      explicit CPU()
      {

         ///////test
         std::set<Byte> opcodes_LDA = {
            INS_LDA_IM  ,
            INS_LDA_ZP  ,
            INS_LDA_ABS ,
            INS_LDA_ZPX ,
            INS_LDA_ABSY,
            INS_LDA_ABSX,
            INS_LDA_INDX,
            INS_LDA_INDY
         };

         std::set<Byte> opcodes_LDX = {
            INS_LDX_IM  ,
            INS_LDX_ZP  ,
            INS_LDX_ZPY ,
            INS_LDX_ABS ,
            INS_LDX_ABSY
         };

         std::set<Byte> opcodes_LDY = {
            INS_LDY_IM  ,
            INS_LDY_ZP  ,
            INS_LDY_ZPX ,
            INS_LDY_ABS ,
            INS_LDY_ABSX
         };


std::set<Byte> opcodes_STA = {
            INS_STA_ZP  ,
            INS_STA_ZPX ,
            INS_STA_ABS ,
            INS_STA_ABSX,
            INS_STA_ABSY,
            INS_STA_INDX,
            INS_STA_INDY
         };


std::set<Byte> opcodes_STX = {
            INS_STX_ZP ,
            INS_STX_ZPY,
            INS_STX_ABS
         };
                       
                       
std::set<Byte> opcodes_STY = {
            INS_STY_ZP ,
            INS_STY_ZPX,
            INS_STY_ABS
         };



std::set<Byte> opcodes_INC = {
            INS_INC_ZP  ,
            INS_INC_ZPX ,
            INS_INC_ABS ,
            INS_INC_ABSX
};
                        
std::set<Byte> opcodes_INX = {
            INS_INX
};

std::set<Byte> opcodes_INY = {
            INS_INY     
};
                        
std::set<Byte> opcodes_DEC = {
            INS_DEC_ZP  ,
            INS_DEC_ZPX ,
            INS_DEC_ABS ,
            INS_DEC_ABSX 
};

std::set<Byte> opcodes_DEY = {
            INS_DEY
};

std::set<Byte> opcodes_DEX = {
            INS_DEX
};

std::set<Byte> opcodes_JSR = {
            INS_JSR    
};

std::set<Byte> opcodes_RTS = {
            INS_RTS    
};

std::set<Byte> opcodes_JMP = {
            INS_JMP_ABS,
            INS_JMP_IND
};

std::set<Byte> opcodes_TSX = {
            INS_TSX
};
std::set<Byte> opcodes_TXS = {
            INS_TXS
};
std::set<Byte> opcodes_PHA = {
            INS_PHA
};
std::set<Byte> opcodes_PHP = {
            INS_PHP
};
std::set<Byte> opcodes_PLA = {
            INS_PLA
};
std::set<Byte> opcodes_PLP = {
            INS_PLP
};
                   
std::set<Byte> opcodes_TAX = {
            INS_TAX
};
std::set<Byte> opcodes_TAY = {
            INS_TAY
};
std::set<Byte> opcodes_TXA = {
            INS_TXA
};

std::set<Byte> opcodes_TYA = {
            INS_TYA
};

std::set<Byte> opcodes_AND = {
            INS_AND_IM  ,
            INS_AND_ZP  ,
            INS_AND_ZPX ,
            INS_AND_ABS ,
            INS_AND_ABSX,
            INS_AND_ABSY,
            INS_AND_INDX,
            INS_AND_INDY
};
                        
                        
std::set<Byte> opcodes_EOR = {
            INS_EOR_IM  ,
            INS_EOR_ZP  ,
            INS_EOR_ZPX ,
            INS_EOR_ABS ,
            INS_EOR_ABSX,
            INS_EOR_ABSY,
            INS_EOR_INDX,
            INS_EOR_INDY
};
                        
                        
std::set<Byte> opcodes_ORA = {
            INS_ORA_IM  ,
            INS_ORA_ZP  ,
            INS_ORA_ZPX ,
            INS_ORA_ABS ,
            INS_ORA_ABSX,
            INS_ORA_ABSY,
            INS_ORA_INDX,
            INS_ORA_INDY
};

std::set<Byte> opcodes_BIT = {
            INS_BIT_ZP ,
            INS_BIT_ABS
};

std::set<Byte> opcodes_BCC = {
            INS_BCC
};
std::set<Byte> opcodes_BCS = {
            INS_BCS
};
std::set<Byte> opcodes_BEQ = {
            INS_BEQ
};
std::set<Byte> opcodes_BMI = {
            INS_BMI
};
std::set<Byte> opcodes_BNE = {
            INS_BNE
};
std::set<Byte> opcodes_BPL = {
            INS_BPL
};
std::set<Byte> opcodes_BVC = {
            INS_BVC
};
std::set<Byte> opcodes_BVS = {
            INS_BVS
};

std::set<Byte> opcodes_ASL = {
            INS_ASL_ACC   ,
            INS_ASL_ZP    ,
            INS_ASL_ZPX   ,
            INS_ASL_ABS   ,
            INS_ASL_ABSX  
};              
                          
std::set<Byte> opcodes_LSR = {
            INS_LSR_ACC   ,
            INS_LSR_ZP    ,
            INS_LSR_ZPX   ,
            INS_LSR_ABS   ,
            INS_LSR_ABSX  
};
                          
                          
std::set<Byte> opcodes_ROL = {
            INS_ROL_ACC   ,
            INS_ROL_ZP    ,
            INS_ROL_ZPX   ,
            INS_ROL_ABS   ,
            INS_ROL_ABSX  
};
                          
std::set<Byte> opcodes_ROR = {
            INS_ROR_ACC   ,
            INS_ROR_ZP    ,
            INS_ROR_ZPX   ,
            INS_ROR_ABS   ,
            INS_ROR_ABSX  
}; 
                          
std::set<Byte> opcodes_ADC = {
            INS_ADC_IM    ,
            INS_ADC_ZP    ,
            INS_ADC_ZPX   ,
            INS_ADC_ABS   ,
            INS_ADC_ABSX  ,
            INS_ADC_ABSY  ,
            INS_ADC_INDX  ,
            INS_ADC_INDY  
}; 
                          
std::set<Byte> opcodes_SBC = {
            INS_SBC_IM    ,
            INS_SBC_ZP    ,
            INS_SBC_ZPX   ,
            INS_SBC_ABS   ,
            INS_SBC_ABSX  ,
            INS_SBC_ABSY  ,
            INS_SBC_INDX  ,
            INS_SBC_INDY  
}; 
                          
std::set<Byte> opcodes_CMP = {
            INS_CMP_IM    ,
            INS_CMP_ZP    ,
            INS_CMP_ZPX   ,
            INS_CMP_ABS   ,
            INS_CMP_ABSX  ,
            INS_CMP_ABSY  ,
            INS_CMP_INDX  ,
            INS_CMP_INDY  
}; 
                          
std::set<Byte> opcodes_CPX = {
            INS_CPX_IM    ,
            INS_CPX_ZP    ,
            INS_CPX_ABS   
}; 
                          
std::set<Byte> opcodes_CPY = {
            INS_CPY_IM    ,
            INS_CPY_ZP    ,
            INS_CPY_ABS   
}; 

std::set<Byte> opcodes_CLC  = {
            INS_CLC       
};

std::set<Byte> opcodes_CLD  = {
            INS_CLD       
};

std::set<Byte> opcodes_CLI  = {
            INS_CLI       
};

std::set<Byte> opcodes_CLV  = {
            INS_CLV       
};

std::set<Byte> opcodes_SEC = {
            INS_SEC                
};

std::set<Byte> opcodes_SED = {
            INS_SED                
};

std::set<Byte> opcodes_SEI = {
            INS_SEI                
};
                                   
std::set<Byte> opcodes_BRK = {
            INS_BRK                
};

std::set<Byte> opcodes_NOP = {
            INS_NOP       
};

std::set<Byte> opcodes_RTI = {
            INS_RTI                
};

///TODO: now the same thing for the rest of functions =3

//instructionMap_test[bindMemberFunction(&CPU::LDA_TEST)] = opcodes_LDA;
instructionMap[opcodes_LDA] = bindMemberFunction(&CPU::LDA_TEST);
instructionMap[opcodes_LDX] = bindMemberFunction(&CPU::LDX_TEST);
instructionMap[opcodes_LDY] = bindMemberFunction(&CPU::LDY_TEST);

instructionMap[opcodes_STA] = bindMemberFunction(&CPU::STA_TEST);
instructionMap[opcodes_STX] = bindMemberFunction(&CPU::STX_TEST);
instructionMap[opcodes_STY] = bindMemberFunction(&CPU::STY_TEST);

instructionMap[opcodes_INC] = bindMemberFunction(&CPU::INC_TEST);
instructionMap[opcodes_INX] = bindMemberFunction(&CPU::INX_TEST);
instructionMap[opcodes_INY] = bindMemberFunction(&CPU::INY_TEST);

instructionMap[opcodes_DEC] = bindMemberFunction(&CPU::DEC_TEST);
instructionMap[opcodes_DEX] = bindMemberFunction(&CPU::DEX_TEST);
instructionMap[opcodes_DEY] = bindMemberFunction(&CPU::DEY_TEST);

instructionMap[opcodes_JSR] = bindMemberFunction(&CPU::JSR_TEST);
instructionMap[opcodes_RTS] = bindMemberFunction(&CPU::RTS_TEST);
instructionMap[opcodes_JMP] = bindMemberFunction(&CPU::JMP_TEST);

instructionMap[opcodes_TSX] = bindMemberFunction(&CPU::TSX_TEST);
instructionMap[opcodes_TXS] = bindMemberFunction(&CPU::TXS_TEST);
instructionMap[opcodes_PHA] = bindMemberFunction(&CPU::PHA_TEST);
instructionMap[opcodes_PHP] = bindMemberFunction(&CPU::PHP_TEST);
instructionMap[opcodes_PLA] = bindMemberFunction(&CPU::PLA_TEST);
instructionMap[opcodes_PLP] = bindMemberFunction(&CPU::PLP_TEST);

instructionMap[opcodes_TAX] = bindMemberFunction(&CPU::TAX_TEST);
instructionMap[opcodes_TXA] = bindMemberFunction(&CPU::TXA_TEST);
instructionMap[opcodes_TAY] = bindMemberFunction(&CPU::TAY_TEST);
instructionMap[opcodes_TYA] = bindMemberFunction(&CPU::TYA_TEST);

instructionMap[opcodes_AND] = bindMemberFunction(&CPU::AND_TEST);
instructionMap[opcodes_EOR] = bindMemberFunction(&CPU::EOR_TEST);
instructionMap[opcodes_ORA] = bindMemberFunction(&CPU::ORA_TEST);
instructionMap[opcodes_BIT] = bindMemberFunction(&CPU::BIT_TEST);

instructionMap[opcodes_BCC] = bindMemberFunction(&CPU::BCC_TEST);
instructionMap[opcodes_BCS] = bindMemberFunction(&CPU::BCS_TEST);
instructionMap[opcodes_BEQ] = bindMemberFunction(&CPU::BEQ_TEST);
instructionMap[opcodes_BMI] = bindMemberFunction(&CPU::BMI_TEST);
instructionMap[opcodes_BNE] = bindMemberFunction(&CPU::BNE_TEST);
instructionMap[opcodes_BPL] = bindMemberFunction(&CPU::BPL_TEST);
instructionMap[opcodes_BVC] = bindMemberFunction(&CPU::BVC_TEST);
instructionMap[opcodes_BVS] = bindMemberFunction(&CPU::BVS_TEST);

instructionMap[opcodes_ASL] = bindMemberFunction(&CPU::ASL_TEST);
instructionMap[opcodes_LSR] = bindMemberFunction(&CPU::LSR_TEST);
instructionMap[opcodes_ROR] = bindMemberFunction(&CPU::ROR_TEST);
instructionMap[opcodes_ROL] = bindMemberFunction(&CPU::ROL_TEST);

instructionMap[opcodes_ADC] = bindMemberFunction(&CPU::ADC_TEST);
instructionMap[opcodes_SBC] = bindMemberFunction(&CPU::SBC_TEST);
instructionMap[opcodes_CMP] = bindMemberFunction(&CPU::CMP_TEST);
instructionMap[opcodes_CPX] = bindMemberFunction(&CPU::CPX_TEST);
instructionMap[opcodes_CPY] = bindMemberFunction(&CPU::CPY_TEST);

instructionMap[opcodes_CLC] = bindMemberFunction(&CPU::CLC_TEST);
instructionMap[opcodes_CLD] = bindMemberFunction(&CPU::CLD_TEST);
instructionMap[opcodes_CLI] = bindMemberFunction(&CPU::CLI_TEST);
instructionMap[opcodes_CLV] = bindMemberFunction(&CPU::CLV_TEST);
instructionMap[opcodes_SEC] = bindMemberFunction(&CPU::SEC_TEST);
instructionMap[opcodes_SED] = bindMemberFunction(&CPU::SED_TEST);
instructionMap[opcodes_SEI] = bindMemberFunction(&CPU::SEI_TEST);

instructionMap[opcodes_BRK] = bindMemberFunction(&CPU::BRK_TEST);
instructionMap[opcodes_NOP] = bindMemberFunction(&CPU::NOP_TEST);
instructionMap[opcodes_RTI] = bindMemberFunction(&CPU::RTI_TEST);
                                                                                                            
///////Do I even want to do this here - this should be more of a static thing? - Lets say it's fine for now




////////////////////////////////////// Load/Store
         //// LDA
         instructionMap_legacy[INS_LDA_IM]   = bindMemberFunction_legacy(&CPU::LDA_IM);
         instructionMap_legacy[INS_LDA_ZP]   = bindMemberFunction_legacy(&CPU::LDA_ZP);
         instructionMap_legacy[INS_LDA_ZPX]  = bindMemberFunction_legacy(&CPU::LDA_ZPX);
         instructionMap_legacy[INS_LDA_ABS]  = bindMemberFunction_legacy(&CPU::LDA_ABS);
         instructionMap_legacy[INS_LDA_ABSX] = bindMemberFunction_legacy(&CPU::LDA_ABSX);
         instructionMap_legacy[INS_LDA_ABSY] = bindMemberFunction_legacy(&CPU::LDA_ABSY);
         instructionMap_legacy[INS_LDA_INDX] = bindMemberFunction_legacy(&CPU::LDA_INDX);
         instructionMap_legacy[INS_LDA_INDY] = bindMemberFunction_legacy(&CPU::LDA_INDY);

         //// LDX
         instructionMap_legacy[INS_LDX_IM]   = bindMemberFunction_legacy(&CPU::LDX_IM);
         instructionMap_legacy[INS_LDX_ZP]   = bindMemberFunction_legacy(&CPU::LDX_ZP);
         instructionMap_legacy[INS_LDX_ZPY]  = bindMemberFunction_legacy(&CPU::LDX_ZPY);
         instructionMap_legacy[INS_LDX_ABS]  = bindMemberFunction_legacy(&CPU::LDX_ABS);
         instructionMap_legacy[INS_LDX_ABSY] = bindMemberFunction_legacy(&CPU::LDX_ABSY);

         //// LDY
         instructionMap_legacy[INS_LDY_IM]   = bindMemberFunction_legacy(&CPU::LDY_IM);
         instructionMap_legacy[INS_LDY_ZP]   = bindMemberFunction_legacy(&CPU::LDY_ZP);
         instructionMap_legacy[INS_LDY_ZPX]  = bindMemberFunction_legacy(&CPU::LDY_ZPX);
         instructionMap_legacy[INS_LDY_ABS]  = bindMemberFunction_legacy(&CPU::LDY_ABS);
         instructionMap_legacy[INS_LDY_ABSX] = bindMemberFunction_legacy(&CPU::LDY_ABSX);
         
         ///STA
         instructionMap_legacy[INS_STA_ZP]   = bindMemberFunction_legacy(&CPU::STA_ZP);
         instructionMap_legacy[INS_STA_ZPX]  = bindMemberFunction_legacy(&CPU::STA_ZPX);
         instructionMap_legacy[INS_STA_ABS]  = bindMemberFunction_legacy(&CPU::STA_ABS);
         instructionMap_legacy[INS_STA_ABSX] = bindMemberFunction_legacy(&CPU::STA_ABSX);
         instructionMap_legacy[INS_STA_ABSY] = bindMemberFunction_legacy(&CPU::STA_ABSY);
         instructionMap_legacy[INS_STA_INDX] = bindMemberFunction_legacy(&CPU::STA_INDX);
         instructionMap_legacy[INS_STA_INDY] = bindMemberFunction_legacy(&CPU::STA_INDY);

         /// STX
         instructionMap_legacy[INS_STX_ZP]   = bindMemberFunction_legacy(&CPU::STX_ZP);
         instructionMap_legacy[INS_STX_ZPY]  = bindMemberFunction_legacy(&CPU::STX_ZPY);
         instructionMap_legacy[INS_STX_ABS]  = bindMemberFunction_legacy(&CPU::STX_ABS);

         /// STY
         instructionMap_legacy[INS_STY_ZP]   = bindMemberFunction_legacy(&CPU::STY_ZP);
         instructionMap_legacy[INS_STY_ZPX]  = bindMemberFunction_legacy(&CPU::STY_ZPX);
         instructionMap_legacy[INS_STY_ABS]  = bindMemberFunction_legacy(&CPU::STY_ABS);

////////////////////////////////////// Increment/Decrement

         /// INC
         instructionMap_legacy[INS_INX]      = bindMemberFunction_legacy(&CPU::INX);
         instructionMap_legacy[INS_INY]      = bindMemberFunction_legacy(&CPU::INY);

         /// INX and INY
         instructionMap_legacy[INS_INC_ZP]   = bindMemberFunction_legacy(&CPU::INC_ZP);
         instructionMap_legacy[INS_INC_ZPX]  = bindMemberFunction_legacy(&CPU::INC_ZPX);
         instructionMap_legacy[INS_INC_ABS]  = bindMemberFunction_legacy(&CPU::INC_ABS);
         instructionMap_legacy[INS_INC_ABSX] = bindMemberFunction_legacy(&CPU::INC_ZPX);

         /// DEC
         instructionMap_legacy[INS_DEX]      = bindMemberFunction_legacy(&CPU::DEX);
         instructionMap_legacy[INS_DEY]      = bindMemberFunction_legacy(&CPU::DEY);

         /// DEY and DEX
         instructionMap_legacy[INS_DEC_ZP]   = bindMemberFunction_legacy(&CPU::DEC_ZP);
         instructionMap_legacy[INS_DEC_ZPX]  = bindMemberFunction_legacy(&CPU::DEC_ZPX);
         instructionMap_legacy[INS_DEC_ABS]  = bindMemberFunction_legacy(&CPU::DEC_ABS);
         instructionMap_legacy[INS_DEC_ABSX] = bindMemberFunction_legacy(&CPU::DEC_ABSX);

////////////////////////////////////// Jumps/Calls

         /// JSR
         instructionMap_legacy[INS_JSR]      = bindMemberFunction_legacy(&CPU::JSR);

         /// RTS
         instructionMap_legacy[INS_RTS]      = bindMemberFunction_legacy(&CPU::RTS);

         /// JMP
         instructionMap_legacy[INS_JMP_ABS]  = bindMemberFunction_legacy(&CPU::JMP_ABS);
         instructionMap_legacy[INS_JMP_IND]  = bindMemberFunction_legacy(&CPU::JMP_IND);
////////////////////////////////////// Stack Operations
         instructionMap_legacy[INS_TSX] = bindMemberFunction_legacy(&CPU::TSX);
         instructionMap_legacy[INS_TXS] = bindMemberFunction_legacy(&CPU::TXS);
         instructionMap_legacy[INS_PHA] = bindMemberFunction_legacy(&CPU::PHA);
         instructionMap_legacy[INS_PHP] = bindMemberFunction_legacy(&CPU::PHP);
         instructionMap_legacy[INS_PLA] = bindMemberFunction_legacy(&CPU::PLA);
         instructionMap_legacy[INS_PLP] = bindMemberFunction_legacy(&CPU::PLP);

////////////////////////////////////// Register Transfers
         instructionMap_legacy[INS_TAX] = bindMemberFunction_legacy(&CPU::TAX);
         instructionMap_legacy[INS_TAY] = bindMemberFunction_legacy(&CPU::TAY);
         instructionMap_legacy[INS_TXA] = bindMemberFunction_legacy(&CPU::TXA);
         instructionMap_legacy[INS_TYA] = bindMemberFunction_legacy(&CPU::TYA);

////////////////////////////////////// Logical
         /// AND
         instructionMap_legacy[INS_AND_IM  ] = bindMemberFunction_legacy(&CPU::AND_IM  );
         instructionMap_legacy[INS_AND_ZP  ] = bindMemberFunction_legacy(&CPU::AND_ZP  );
         instructionMap_legacy[INS_AND_ZPX ] = bindMemberFunction_legacy(&CPU::AND_ZPX );
         instructionMap_legacy[INS_AND_ABS ] = bindMemberFunction_legacy(&CPU::AND_ABS );
         instructionMap_legacy[INS_AND_ABSX] = bindMemberFunction_legacy(&CPU::AND_ABSX);
         instructionMap_legacy[INS_AND_ABSY] = bindMemberFunction_legacy(&CPU::AND_ABSY);
         instructionMap_legacy[INS_AND_INDX] = bindMemberFunction_legacy(&CPU::AND_INDX);
         instructionMap_legacy[INS_AND_INDY] = bindMemberFunction_legacy(&CPU::AND_INDY);

         /// EOR
         instructionMap_legacy[INS_EOR_IM  ] = bindMemberFunction_legacy(&CPU::EOR_IM  );
         instructionMap_legacy[INS_EOR_ZP  ] = bindMemberFunction_legacy(&CPU::EOR_ZP  );
         instructionMap_legacy[INS_EOR_ZPX ] = bindMemberFunction_legacy(&CPU::EOR_ZPX );
         instructionMap_legacy[INS_EOR_ABS ] = bindMemberFunction_legacy(&CPU::EOR_ABS );
         instructionMap_legacy[INS_EOR_ABSX] = bindMemberFunction_legacy(&CPU::EOR_ABSX);
         instructionMap_legacy[INS_EOR_ABSY] = bindMemberFunction_legacy(&CPU::EOR_ABSY);
         instructionMap_legacy[INS_EOR_INDX] = bindMemberFunction_legacy(&CPU::EOR_INDX);
         instructionMap_legacy[INS_EOR_INDY] = bindMemberFunction_legacy(&CPU::EOR_INDY);

         ///ORA 
         instructionMap_legacy[INS_ORA_IM  ] = bindMemberFunction_legacy(&CPU::ORA_IM  );
         instructionMap_legacy[INS_ORA_ZP  ] = bindMemberFunction_legacy(&CPU::ORA_ZP  );
         instructionMap_legacy[INS_ORA_ZPX ] = bindMemberFunction_legacy(&CPU::ORA_ZPX );
         instructionMap_legacy[INS_ORA_ABS ] = bindMemberFunction_legacy(&CPU::ORA_ABS );
         instructionMap_legacy[INS_ORA_ABSX] = bindMemberFunction_legacy(&CPU::ORA_ABSX);
         instructionMap_legacy[INS_ORA_ABSY] = bindMemberFunction_legacy(&CPU::ORA_ABSY);
         instructionMap_legacy[INS_ORA_INDX] = bindMemberFunction_legacy(&CPU::ORA_INDX);
         instructionMap_legacy[INS_ORA_INDY] = bindMemberFunction_legacy(&CPU::ORA_INDY);

         /// BIT
         instructionMap_legacy[INS_BIT_ZP ] = bindMemberFunction_legacy(&CPU::BIT_ZP );
         instructionMap_legacy[INS_BIT_ABS] = bindMemberFunction_legacy(&CPU::BIT_ABS);


////////////////////////////////////// Branches
         instructionMap_legacy[INS_BCC ] = bindMemberFunction_legacy(&CPU::BCC );
         instructionMap_legacy[INS_BCS ] = bindMemberFunction_legacy(&CPU::BCS );
         instructionMap_legacy[INS_BEQ ] = bindMemberFunction_legacy(&CPU::BEQ );
         instructionMap_legacy[INS_BMI ] = bindMemberFunction_legacy(&CPU::BMI );
         instructionMap_legacy[INS_BNE ] = bindMemberFunction_legacy(&CPU::BNE );
         instructionMap_legacy[INS_BPL ] = bindMemberFunction_legacy(&CPU::BPL );
         instructionMap_legacy[INS_BVC ] = bindMemberFunction_legacy(&CPU::BVC );
         instructionMap_legacy[INS_BVS ] = bindMemberFunction_legacy(&CPU::BVS );


////////////////////////////////////// Shifts
         ///ASL
         instructionMap_legacy[INS_ASL_ACC  ] = bindMemberFunction_legacy(&CPU::ASL_ACC  );
         instructionMap_legacy[INS_ASL_ZP   ] = bindMemberFunction_legacy(&CPU::ASL_ZP   );
         instructionMap_legacy[INS_ASL_ZPX  ] = bindMemberFunction_legacy(&CPU::ASL_ZPX  );
         instructionMap_legacy[INS_ASL_ABS  ] = bindMemberFunction_legacy(&CPU::ASL_ABS  );
         instructionMap_legacy[INS_ASL_ABSX ] = bindMemberFunction_legacy(&CPU::ASL_ABSX );

         ///LSR
         instructionMap_legacy[INS_LSR_ACC  ] = bindMemberFunction_legacy(&CPU::LSR_ACC  );
         instructionMap_legacy[INS_LSR_ZP   ] = bindMemberFunction_legacy(&CPU::LSR_ZP   );
         instructionMap_legacy[INS_LSR_ZPX  ] = bindMemberFunction_legacy(&CPU::LSR_ZPX  );
         instructionMap_legacy[INS_LSR_ABS  ] = bindMemberFunction_legacy(&CPU::LSR_ABS  );
         instructionMap_legacy[INS_LSR_ABSX ] = bindMemberFunction_legacy(&CPU::LSR_ABSX );

         ///ROL
         instructionMap_legacy[INS_ROL_ACC ] = bindMemberFunction_legacy(&CPU::ROL_ACC );
         instructionMap_legacy[INS_ROL_ZP  ] = bindMemberFunction_legacy(&CPU::ROL_ZP  );
         instructionMap_legacy[INS_ROL_ZPX ] = bindMemberFunction_legacy(&CPU::ROL_ZPX );
         instructionMap_legacy[INS_ROL_ABS ] = bindMemberFunction_legacy(&CPU::ROL_ABS );
         instructionMap_legacy[INS_ROL_ABSX] = bindMemberFunction_legacy(&CPU::ROL_ABSX);

         ///ROR
         instructionMap_legacy[INS_ROR_ACC ] = bindMemberFunction_legacy(&CPU::ROR_ACC );
         instructionMap_legacy[INS_ROR_ZP  ] = bindMemberFunction_legacy(&CPU::ROR_ZP  );
         instructionMap_legacy[INS_ROR_ZPX ] = bindMemberFunction_legacy(&CPU::ROR_ZPX );
         instructionMap_legacy[INS_ROR_ABS ] = bindMemberFunction_legacy(&CPU::ROR_ABS );
         instructionMap_legacy[INS_ROR_ABSX] = bindMemberFunction_legacy(&CPU::ROR_ABSX);

////////////////////////////////////// Arithmetic
         ///ADC
         instructionMap_legacy[INS_ADC_IM  ] = bindMemberFunction_legacy(&CPU::ADC_IM  );
         instructionMap_legacy[INS_ADC_ZP  ] = bindMemberFunction_legacy(&CPU::ADC_ZP  );
         instructionMap_legacy[INS_ADC_ZPX ] = bindMemberFunction_legacy(&CPU::ADC_ZPX );
         instructionMap_legacy[INS_ADC_ABS ] = bindMemberFunction_legacy(&CPU::ADC_ABS );
         instructionMap_legacy[INS_ADC_ABSX] = bindMemberFunction_legacy(&CPU::ADC_ABSX);
         instructionMap_legacy[INS_ADC_ABSY] = bindMemberFunction_legacy(&CPU::ADC_ABSY);
         instructionMap_legacy[INS_ADC_INDX] = bindMemberFunction_legacy(&CPU::ADC_INDX);
         instructionMap_legacy[INS_ADC_INDY] = bindMemberFunction_legacy(&CPU::ADC_INDY);

         /// SBC
         instructionMap_legacy[INS_SBC_IM  ] = bindMemberFunction_legacy(&CPU::SBC_IM  );
         instructionMap_legacy[INS_SBC_ZP  ] = bindMemberFunction_legacy(&CPU::SBC_ZP  );
         instructionMap_legacy[INS_SBC_ZPX ] = bindMemberFunction_legacy(&CPU::SBC_ZPX );
         instructionMap_legacy[INS_SBC_ABS ] = bindMemberFunction_legacy(&CPU::SBC_ABS );
         instructionMap_legacy[INS_SBC_ABSX] = bindMemberFunction_legacy(&CPU::SBC_ABSX);
         instructionMap_legacy[INS_SBC_ABSY] = bindMemberFunction_legacy(&CPU::SBC_ABSY);
         instructionMap_legacy[INS_SBC_INDX] = bindMemberFunction_legacy(&CPU::SBC_INDX);
         instructionMap_legacy[INS_SBC_INDY] = bindMemberFunction_legacy(&CPU::SBC_INDY);

         /// CMP
         instructionMap_legacy[INS_CMP_IM  ] = bindMemberFunction_legacy(&CPU::CMP_IM  );
         instructionMap_legacy[INS_CMP_ZP  ] = bindMemberFunction_legacy(&CPU::CMP_ZP  );
         instructionMap_legacy[INS_CMP_ZPX ] = bindMemberFunction_legacy(&CPU::CMP_ZPX );
         instructionMap_legacy[INS_CMP_ABS ] = bindMemberFunction_legacy(&CPU::CMP_ABS );
         instructionMap_legacy[INS_CMP_ABSX] = bindMemberFunction_legacy(&CPU::CMP_ABSX);
         instructionMap_legacy[INS_CMP_ABSY] = bindMemberFunction_legacy(&CPU::CMP_ABSY);
         instructionMap_legacy[INS_CMP_INDX] = bindMemberFunction_legacy(&CPU::CMP_INDX);
         instructionMap_legacy[INS_CMP_INDY] = bindMemberFunction_legacy(&CPU::CMP_INDY);

         ///CPX
         instructionMap_legacy[INS_CPX_IM  ] = bindMemberFunction_legacy(&CPU::CPX_IM  );
         instructionMap_legacy[INS_CPX_ZP  ] = bindMemberFunction_legacy(&CPU::CPX_ZP  );
         instructionMap_legacy[INS_CPX_ABS ] = bindMemberFunction_legacy(&CPU::CPX_ABS );

         ///CPY
         instructionMap_legacy[INS_CPY_IM  ] = bindMemberFunction_legacy(&CPU::CPY_IM  );
         instructionMap_legacy[INS_CPY_ZP  ] = bindMemberFunction_legacy(&CPU::CPY_ZP  );
         instructionMap_legacy[INS_CPY_ABS ] = bindMemberFunction_legacy(&CPU::CPY_ABS );


////////////////////////////////////// Status Flag Changes
         instructionMap_legacy[INS_CLC     ] = bindMemberFunction_legacy(&CPU::CLC     );
         instructionMap_legacy[INS_CLD     ] = bindMemberFunction_legacy(&CPU::CLD     );
         instructionMap_legacy[INS_CLI     ] = bindMemberFunction_legacy(&CPU::CLI     );
         instructionMap_legacy[INS_CLV     ] = bindMemberFunction_legacy(&CPU::CLV     );
         instructionMap_legacy[INS_SEC     ] = bindMemberFunction_legacy(&CPU::SEC     );
         instructionMap_legacy[INS_SED     ] = bindMemberFunction_legacy(&CPU::SED     );
         instructionMap_legacy[INS_SEI     ] = bindMemberFunction_legacy(&CPU::SEI     );


////////////////////////////////////// System Functions
         instructionMap_legacy[INS_BRK     ] = bindMemberFunction_legacy(&CPU::BRK     );
         instructionMap_legacy[INS_NOP     ] = bindMemberFunction_legacy(&CPU::NOP     );
         instructionMap_legacy[INS_RTI     ] = bindMemberFunction_legacy(&CPU::RTI     );


         /// NULL ///figure out later how to make it not hang my program =3
         // instructionMap[INS_NULL] = bindMemberFunction(&CPU::NULL_INS);
      }
};

#endif
