#include "CPU.h"

/////////////////////README
/*
 *
 * Well the lambdas are ugly, I know that, but otherwise it's non trivial to capture the context and pipe correct flags thing...
 * 
 */


//////////////////////////////////// TEST


void CPU::INC_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode)
{
   Word address{};

   switch(_opCode){
      case CPU::INS_INC_ZP :{
         address = getAddr(_cycles, _mem, adressingMode::ZP);
         break;
      }
      case CPU::INS_INC_ZPX :{
         address = getAddr(_cycles, _mem, adressingMode::ZPX);
         break;
      }
      case CPU::INS_INC_ABS :{
         address = getAddr(_cycles, _mem, adressingMode::ABS);
         break;
      }
      case CPU::INS_INC_ABSX :{
         address = getAddr(_cycles, _mem, adressingMode::ABSX);
         break;
      }
   }
   safeCycleDecrement(_cycles);
   ApplyToMemory(
       _cycles, address, _mem,
       [this](const Byte &_val
       ) -> Byte { /// need to capture "this", so that it can manipulate NZ flags
         Byte flag = (N_f | Z_f); 
         SetCustomFlagsWithValue(_val, flag);
          return (_val + 1);
       }
   );
}

void CPU::INX_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode)
{
   ++X;  ///this should be wrapping
   safeCycleDecrement(_cycles);
   Byte flag = (N_f | Z_f); 
   SetCustomFlagsWithRegister(Register::X, flag);
}

void CPU::INY_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode)
{
   ++Y; //this as well should be wrapping
   safeCycleDecrement(_cycles);
   Byte flag = (N_f | Z_f); 
   SetCustomFlagsWithRegister(Register::Y, flag);
}


void CPU::DEC_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode)
{
   Word address{};

   switch(_opCode){
      case CPU::INS_DEC_ZP :{
         address = getAddr(_cycles, _mem, adressingMode::ZP);
         break;
      }
      case CPU::INS_DEC_ZPX :{
         address = getAddr(_cycles, _mem, adressingMode::ZPX);
         break;
      }
      case CPU::INS_DEC_ABS :{
         address = getAddr(_cycles, _mem, adressingMode::ABS);
         break;
      }
      case CPU::INS_DEC_ABSX :{
         address = getAddr(_cycles, _mem, adressingMode::ABSX);
         break;
      }
   }
   safeCycleDecrement(_cycles);
   ApplyToMemory(
       _cycles, address, _mem,
       [this](const Byte &_val
       ) -> Byte { /// need to capture "this", so that it can manipulate NZ flags
         Byte flag = (N_f | Z_f); 
         SetCustomFlagsWithValue(_val, flag);
          return (_val - 1);
       }
   );
}

void CPU::DEX_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode)
{
   --X;
   safeCycleDecrement(_cycles);
   HEX_PRINT("here");
   Byte flag = (N_f | Z_f); 
   SetCustomFlagsWithRegister(Register::X, flag);
}

void CPU::DEY_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode)
{
   --Y;
   safeCycleDecrement(_cycles);
   HEX_PRINT("here");
   Byte flag = (N_f | Z_f);
   SetCustomFlagsWithRegister(Register::Y, flag);
}

