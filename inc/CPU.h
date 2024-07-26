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
      /////////////////////////////////////////////////safe decrement
      void safeCycleDecrement(u32& _cycles);

      /////////////////////////////////////////////////logic and memory
      Byte fetchByte(u32 &_cycles, const Mem &_mem);
      Word fetchWord(u32 &_cycles, const Mem &_mem);

      Byte readByte(u32 &_cycles, const Byte &_addr, const Mem &_mem);
      Byte readByte(u32 &_cycles, const Word &_addr, const Mem &_mem);
      Word readWord(u32 &_cycles, const Byte &_addr, const Mem &_mem);
      Word readWord(u32 &_cycles, const Word &_addr, const Mem &_mem);

      void writeByte(u32 &_cycles, const Byte &_addr, Mem &_mem, const Byte &_val);
      void writeByte(u32 &_cycles, const Word &_addr, Mem &_mem, const Byte &_val);
      void writeWord(u32 &_cycles, const Word &_addr, Mem &_mem, const Word&_val);
      void writeWord(u32 &_cycles, const Byte&_addr, Mem &_mem, const Word&_val);


      /////////////////////////////////////////////////even I - the creator fear this thing...
      void applyToMemory(u32 &_cycles, const Word &_addr, Mem &_mem, std::function<Byte(const Byte &)>);
      void applyToMemory(u32 &_cycles, const Byte &_addr, Mem &_mem, std::function<Byte(const Byte &)>);

      /////////////////////////////////////////////////stack
      Byte popByteFromStack(u32& _cycles, Mem& _mem);
      Word popWordFromStack(u32& _cycles, Mem& _mem);

      void pushWordToStack(u32& _cycles, Mem& _mem, const Word& _val);
      void pushByteToStack(u32& _cycles, Mem& _mem, const Byte& _val);

      Byte readByteFromStack(u32& _cycles, Mem& _mem);
      Word readWordFromStack(u32& _cycles, Mem& _mem);

      void overwriteByteOnStack(u32& _cycles, Mem& _mem, const Word& _val);
      void overwriteWordOnStack(u32& _cycles, Mem& _mem, const Word& _val);
   public:

      void Reset(Mem &_mem, const Word& _PC_start = 0xFFFC);

      /////////////////////////////////////////////////execution 
      s32 execute(u32 _cycles, Mem &_mem);
      void showCycles( Mem &_mem);

      [[deprecated("Use execute() instead")]] 
      s32 execute_alternative(u32 _cycles, Mem &_mem);

      /////////////////////////////////////////////////flags managment
      [[deprecated("Use SetCustomFlags...() instead")]] 
      void setNZWithRegister(const Register &_reg);

      [[deprecated("Use SetCustomFlags...() instead")]]
      void setNZWithValue(const Byte &_val);

      void setCustomFlagsWithValue(const Byte &_val, Byte &_flags);
      void setCustomFlagsWithRegister(const Register &_reg, Byte &_flags);

   
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

         std::set<Byte> opcodes_NOTHING = {
                     INS_NOTHING
         };

         ///TODO: now the same thing for the rest of functions =3

         //instructionMap_test[bindMemberFunction(&CPU::LDA)] = opcodes_LDA;
         instructionMap[opcodes_LDA] = bindMemberFunction(&CPU::LDA);
         instructionMap[opcodes_LDX] = bindMemberFunction(&CPU::LDX);
         instructionMap[opcodes_LDY] = bindMemberFunction(&CPU::LDY);

         instructionMap[opcodes_STA] = bindMemberFunction(&CPU::STA);
         instructionMap[opcodes_STX] = bindMemberFunction(&CPU::STX);
         instructionMap[opcodes_STY] = bindMemberFunction(&CPU::STY);

         instructionMap[opcodes_INC] = bindMemberFunction(&CPU::INC);
         instructionMap[opcodes_INX] = bindMemberFunction(&CPU::INX);
         instructionMap[opcodes_INY] = bindMemberFunction(&CPU::INY);

         instructionMap[opcodes_DEC] = bindMemberFunction(&CPU::DEC);
         instructionMap[opcodes_DEX] = bindMemberFunction(&CPU::DEX);
         instructionMap[opcodes_DEY] = bindMemberFunction(&CPU::DEY);

         instructionMap[opcodes_JSR] = bindMemberFunction(&CPU::JSR);
         instructionMap[opcodes_RTS] = bindMemberFunction(&CPU::RTS);
         instructionMap[opcodes_JMP] = bindMemberFunction(&CPU::JMP);

         instructionMap[opcodes_TSX] = bindMemberFunction(&CPU::TSX);
         instructionMap[opcodes_TXS] = bindMemberFunction(&CPU::TXS);
         instructionMap[opcodes_PHA] = bindMemberFunction(&CPU::PHA);
         instructionMap[opcodes_PHP] = bindMemberFunction(&CPU::PHP);
         instructionMap[opcodes_PLA] = bindMemberFunction(&CPU::PLA);
         instructionMap[opcodes_PLP] = bindMemberFunction(&CPU::PLP);

         instructionMap[opcodes_TAX] = bindMemberFunction(&CPU::TAX);
         instructionMap[opcodes_TXA] = bindMemberFunction(&CPU::TXA);
         instructionMap[opcodes_TAY] = bindMemberFunction(&CPU::TAY);
         instructionMap[opcodes_TYA] = bindMemberFunction(&CPU::TYA);

         instructionMap[opcodes_AND] = bindMemberFunction(&CPU::AND);
         instructionMap[opcodes_EOR] = bindMemberFunction(&CPU::EOR);
         instructionMap[opcodes_ORA] = bindMemberFunction(&CPU::ORA);
         instructionMap[opcodes_BIT] = bindMemberFunction(&CPU::BIT);

         instructionMap[opcodes_BCC] = bindMemberFunction(&CPU::BCC);
         instructionMap[opcodes_BCS] = bindMemberFunction(&CPU::BCS);
         instructionMap[opcodes_BEQ] = bindMemberFunction(&CPU::BEQ);
         instructionMap[opcodes_BMI] = bindMemberFunction(&CPU::BMI);
         instructionMap[opcodes_BNE] = bindMemberFunction(&CPU::BNE);
         instructionMap[opcodes_BPL] = bindMemberFunction(&CPU::BPL);
         instructionMap[opcodes_BVC] = bindMemberFunction(&CPU::BVC);
         instructionMap[opcodes_BVS] = bindMemberFunction(&CPU::BVS);

         instructionMap[opcodes_ASL] = bindMemberFunction(&CPU::ASL);
         instructionMap[opcodes_LSR] = bindMemberFunction(&CPU::LSR);
         instructionMap[opcodes_ROR] = bindMemberFunction(&CPU::ROR);
         instructionMap[opcodes_ROL] = bindMemberFunction(&CPU::ROL);

         instructionMap[opcodes_ADC] = bindMemberFunction(&CPU::ADC);
         instructionMap[opcodes_SBC] = bindMemberFunction(&CPU::SBC);
         instructionMap[opcodes_CMP] = bindMemberFunction(&CPU::CMP);
         instructionMap[opcodes_CPX] = bindMemberFunction(&CPU::CPX);
         instructionMap[opcodes_CPY] = bindMemberFunction(&CPU::CPY);

         instructionMap[opcodes_CLC] = bindMemberFunction(&CPU::CLC);
         instructionMap[opcodes_CLD] = bindMemberFunction(&CPU::CLD);
         instructionMap[opcodes_CLI] = bindMemberFunction(&CPU::CLI);
         instructionMap[opcodes_CLV] = bindMemberFunction(&CPU::CLV);
         instructionMap[opcodes_SEC] = bindMemberFunction(&CPU::SEC);
         instructionMap[opcodes_SED] = bindMemberFunction(&CPU::SED);
         instructionMap[opcodes_SEI] = bindMemberFunction(&CPU::SEI);

         instructionMap[opcodes_BRK] = bindMemberFunction(&CPU::BRK);
         instructionMap[opcodes_NOP] = bindMemberFunction(&CPU::NOP);
         instructionMap[opcodes_RTI] = bindMemberFunction(&CPU::RTI);
                                                                                                                     
         instructionMap[opcodes_NOTHING] = bindMemberFunction(&CPU::NOTHING_);
         ///instructionMap[opcodes_NOTHING] = bindMemberFunction(&CPU::NOTHING_);
         ///////Do I even want to do this here - this should be more of a static thing? - Lets say it's fine for now
      }
};

#endif
