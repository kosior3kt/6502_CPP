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
#include "instructionDefinitions_test.h"


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
      s32 execute_test(u32 _cycles, Mem &_mem);

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

      /// wow - it actually works (im as surprised as you are)
      template <typename Func>
      std::function<void(u32 &, Mem &, const Byte&)> bindMemberFunction2(Func func)
      {
         return std::bind(
             func, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3
         );
      }

      std::map<Byte, std::function<void(u32 &, Mem &)>> instructionMap;
      std::map<std::set<Byte>, std::function<void(u32 &, Mem &, const Byte&)>> instructionMap_test;

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
            INS_DEX
};

std::set<Byte> opcodes_DEX = {
            INS_DEY
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
instructionMap_test[opcodes_LDA] = bindMemberFunction2(&CPU::LDA_TEST);
instructionMap_test[opcodes_LDX] = bindMemberFunction2(&CPU::LDX_TEST);
instructionMap_test[opcodes_LDY] = bindMemberFunction2(&CPU::LDY_TEST);

instructionMap_test[opcodes_STA] = bindMemberFunction2(&CPU::STA_TEST);
instructionMap_test[opcodes_STX] = bindMemberFunction2(&CPU::STX_TEST);
instructionMap_test[opcodes_STY] = bindMemberFunction2(&CPU::STY_TEST);

instructionMap_test[opcodes_INC] = bindMemberFunction2(&CPU::INC_TEST);
instructionMap_test[opcodes_INX] = bindMemberFunction2(&CPU::INX_TEST);
instructionMap_test[opcodes_INY] = bindMemberFunction2(&CPU::INY_TEST);

instructionMap_test[opcodes_DEC] = bindMemberFunction2(&CPU::DEC_TEST);
instructionMap_test[opcodes_DEX] = bindMemberFunction2(&CPU::DEX_TEST);
instructionMap_test[opcodes_DEY] = bindMemberFunction2(&CPU::DEY_TEST);

instructionMap_test[opcodes_JSR] = bindMemberFunction2(&CPU::JSR_TEST);
instructionMap_test[opcodes_RTS] = bindMemberFunction2(&CPU::RTS_TEST);
instructionMap_test[opcodes_JMP] = bindMemberFunction2(&CPU::JMP_TEST);

instructionMap_test[opcodes_TSX] = bindMemberFunction2(&CPU::TSX_TEST);
instructionMap_test[opcodes_TXS] = bindMemberFunction2(&CPU::TXS_TEST);
instructionMap_test[opcodes_PHA] = bindMemberFunction2(&CPU::PHA_TEST);
instructionMap_test[opcodes_PHP] = bindMemberFunction2(&CPU::PHP_TEST);
instructionMap_test[opcodes_PLA] = bindMemberFunction2(&CPU::PLA_TEST);
instructionMap_test[opcodes_PLP] = bindMemberFunction2(&CPU::PLP_TEST);

instructionMap_test[opcodes_TAX] = bindMemberFunction2(&CPU::TAX_TEST);
instructionMap_test[opcodes_TAY] = bindMemberFunction2(&CPU::TAY_TEST);
instructionMap_test[opcodes_TXA] = bindMemberFunction2(&CPU::TXA_TEST);
instructionMap_test[opcodes_TYA] = bindMemberFunction2(&CPU::TYA_TEST);

instructionMap_test[opcodes_AND] = bindMemberFunction2(&CPU::AND_TEST);
instructionMap_test[opcodes_EOR] = bindMemberFunction2(&CPU::EOR_TEST);
instructionMap_test[opcodes_ORA] = bindMemberFunction2(&CPU::ORA_TEST);
instructionMap_test[opcodes_BIT] = bindMemberFunction2(&CPU::BIT_TEST);

instructionMap_test[opcodes_BCC] = bindMemberFunction2(&CPU::BCC_TEST);
instructionMap_test[opcodes_BCS] = bindMemberFunction2(&CPU::BCS_TEST);
instructionMap_test[opcodes_BEQ] = bindMemberFunction2(&CPU::BEQ_TEST);
instructionMap_test[opcodes_BMI] = bindMemberFunction2(&CPU::BMI_TEST);
instructionMap_test[opcodes_BNE] = bindMemberFunction2(&CPU::BNE_TEST);
instructionMap_test[opcodes_BPL] = bindMemberFunction2(&CPU::BPL_TEST);
instructionMap_test[opcodes_BVC] = bindMemberFunction2(&CPU::BVC_TEST);
instructionMap_test[opcodes_BVS] = bindMemberFunction2(&CPU::BVS_TEST);

instructionMap_test[opcodes_ASL] = bindMemberFunction2(&CPU::ASL_TEST);
instructionMap_test[opcodes_LSR] = bindMemberFunction2(&CPU::LSR_TEST);
instructionMap_test[opcodes_ROL] = bindMemberFunction2(&CPU::ROR_TEST);
instructionMap_test[opcodes_ROR] = bindMemberFunction2(&CPU::ROL_TEST);

instructionMap_test[opcodes_ADC] = bindMemberFunction2(&CPU::ADC_TEST);
instructionMap_test[opcodes_SBC] = bindMemberFunction2(&CPU::SBC_TEST);
instructionMap_test[opcodes_CMP] = bindMemberFunction2(&CPU::CMP_TEST);
instructionMap_test[opcodes_CPX] = bindMemberFunction2(&CPU::CPX_TEST);
instructionMap_test[opcodes_CPY] = bindMemberFunction2(&CPU::CPY_TEST);

instructionMap_test[opcodes_CLC] = bindMemberFunction2(&CPU::CLC_TEST);
instructionMap_test[opcodes_CLD] = bindMemberFunction2(&CPU::CLD_TEST);
instructionMap_test[opcodes_CLI] = bindMemberFunction2(&CPU::CLI_TEST);
instructionMap_test[opcodes_CLV] = bindMemberFunction2(&CPU::CLV_TEST);
instructionMap_test[opcodes_SEC] = bindMemberFunction2(&CPU::SEC_TEST);
instructionMap_test[opcodes_SED] = bindMemberFunction2(&CPU::SED_TEST);
instructionMap_test[opcodes_SEI] = bindMemberFunction2(&CPU::SEI_TEST);

instructionMap_test[opcodes_BRK] = bindMemberFunction2(&CPU::BRK_TEST);
instructionMap_test[opcodes_NOP] = bindMemberFunction2(&CPU::NOP_TEST);
instructionMap_test[opcodes_RTI] = bindMemberFunction2(&CPU::RTI_TEST);
                                                                                                            
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
         instructionMap[INS_BIT_ABS] = bindMemberFunction(&CPU::BIT_ABS);


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
