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
   --_cycles;
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
   --_cycles;
   Byte flag = (N_f | Z_f); 
   SetCustomFlagsWithRegister(Register::X, flag);
}

void CPU::INY_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode)
{
   ++Y; //this as well should be wrapping
   --_cycles;
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
   --_cycles;
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
   --_cycles;
   HEX_PRINT("here");
   Byte flag = (N_f | Z_f); 
   SetCustomFlagsWithRegister(Register::X, flag);
}

void CPU::DEY_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode)
{
   --Y;
   --_cycles;
   HEX_PRINT("here");
   Byte flag = (N_f | Z_f);
   SetCustomFlagsWithRegister(Register::Y, flag);
}


//////////////////////////////////// INC

void CPU::INC_ZP(u32 &_cycles, Mem &_mem)
{
   Word address = getAddr(_cycles, _mem, adressingMode::ZP);
   --_cycles;
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

void CPU::INC_ZPX(u32 &_cycles, Mem &_mem)
{
   Word address = getAddr(_cycles, _mem, adressingMode::ZPX);
   --_cycles;

   ApplyToMemory(
       _cycles, address, _mem,
       [this](const Byte &_val
       ) -> Byte { 
         Byte flag = (N_f | Z_f); 
         SetCustomFlagsWithValue(_val, flag);
          return (_val + 1);
       }
   );
   --_cycles;
}

void CPU::INC_ABS(u32 &_cycles, Mem &_mem)
{
   Word address = getAddr(_cycles, _mem, adressingMode::ABS);
   _cycles--;
   ApplyToMemory(
       _cycles, address, _mem,
       [this](const Byte &_val
       ) -> Byte { /// need to caputer this, so that it can manipulate NZ flags
         Byte flag = (N_f | Z_f); 
         SetCustomFlagsWithValue(_val, flag);
          return (_val + 1);
       }
   );
}

void CPU::INC_ABSX(u32 &_cycles, Mem &_mem)
{
   Word address = getAddr(_cycles, _mem, adressingMode::ABSX);
   --_cycles;

   ApplyToMemory(
       _cycles, address, _mem,
       [this](const Byte &_val
       ) -> Byte { /// need to caputer this, so that it can manipulate NZ flags
         Byte flag = (N_f | Z_f); 
         SetCustomFlagsWithValue(_val, flag);
          return (_val + 1);
       }
   );
}

//////////////////////////////////// INX

void CPU::INX(u32 &_cycles, Mem &_mem)
{
   ++X;  ///this should be wrapping
   --_cycles;
   Byte flag = (N_f | Z_f); 
   SetCustomFlagsWithRegister(Register::X, flag);
}

//////////////////////////////////// INY

void CPU::INY(u32 &_cycles, Mem &_mem)
{
   ++Y; //this as well should be wrapping
   --_cycles;
   Byte flag = (N_f | Z_f); 
   SetCustomFlagsWithRegister(Register::Y, flag);
}

//////////////////////////////////// DEC

void CPU::DEC_ZP(u32 &_cycles, Mem &_mem)
{
   Word address = getAddr(_cycles, _mem, adressingMode::ZP);
   --_cycles;
   ApplyToMemory(
       _cycles, address, _mem,
       [this](const Byte &_val
       ) -> Byte { /// need to caputer this, so that it can manipulate NZ flags
         Byte flag = (N_f | Z_f); 
         SetCustomFlagsWithValue(_val, flag);
          return (_val - 1);
       }
   );
}

void CPU::DEC_ZPX(u32 &_cycles, Mem &_mem)
{
   Word address = getAddr(_cycles, _mem, adressingMode::ZPX);
   --_cycles;

   ApplyToMemory(
       _cycles, address, _mem,
       [this](const Byte &_val
       ) -> Byte { /// need to caputer this, so that it can manipulate NZ flags
         Byte flag = (N_f | Z_f); 
         SetCustomFlagsWithValue(_val, flag);
          return (_val - 1);
       }
   );
   --_cycles;
}

void CPU::DEC_ABS(u32 &_cycles, Mem &_mem)
{
   Word address = getAddr(_cycles, _mem, adressingMode::ABS);
   _cycles--;
   ApplyToMemory(
       _cycles, address, _mem,
       [this](const Byte &_val
       ) -> Byte { /// need to caputer this, so that it can manipulate NZ flags
         Byte flag = (N_f | Z_f); 
         SetCustomFlagsWithValue(_val, flag);
          return (_val - 1);
       }
   );
}

void CPU::DEC_ABSX(u32 &_cycles, Mem &_mem)
{
   Word address = getAddr(_cycles, _mem, adressingMode::ABSX);
   --_cycles;

   ApplyToMemory(
       _cycles, address, _mem,
       [this](const Byte &_val
       ) -> Byte { /// need to caputer this, so that it can manipulate NZ flags
         Byte flag = (N_f | Z_f); 
         SetCustomFlagsWithValue(_val, flag);
          return (_val - 1);
       }
   );
}

//////////////////////////////////// DEX
void CPU::DEX(u32 &_cycles, Mem &_mem)
{
   --X;
   --_cycles;
   Byte flag = (N_f | Z_f); 
   SetCustomFlagsWithRegister(Register::X, flag);
}

//////////////////////////////////// DEY

void CPU::DEY(u32 &_cycles, Mem &_mem)
{
   --Y;
   --_cycles;
   Byte flag = (N_f | Z_f);
   SetCustomFlagsWithRegister(Register::Y, flag);
}

