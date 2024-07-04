#include "CPU.h"


//////////////////////////////////// INC

void CPU::INC_ZP(u32 &_cycles, Mem &_mem)
{
   Byte zeroPageAddress = FetchByte(_cycles, _mem);
   --_cycles;
   ApplyToMemory(
       _cycles, zeroPageAddress, _mem,
       [this](const Byte &_val
       ) -> Byte { /// need to capture "this", so that it can manipulate NZ flags
         Byte flag = 0b11111111 & (N_f | Z_f); /// does this work(?)
         SetCustomFlagsWithValue(_val, flag);
          return (_val + 1);
       }
   );
}

void CPU::INC_ZPX(u32 &_cycles, Mem &_mem)
{
   Byte zeroPageAddress = FetchByte(_cycles, _mem);
   zeroPageAddress += X;
   assert(
       zeroPageAddress <= 0xFF && zeroPageAddress >= 0x00
   ); /////Dont know if this wrapps or crosses page
   --_cycles;

   ApplyToMemory(
       _cycles, zeroPageAddress, _mem,
       [this](const Byte &_val
       ) -> Byte { /// need to caputer this, so that it can manipulate NZ flags
         Byte flag = 0b11111111 & (N_f | Z_f); /// does this work(?)
         SetCustomFlagsWithValue(_val, flag);
          return (_val + 1);
       }
   );
   --_cycles;
}

void CPU::INC_ABS(u32 &_cycles, Mem &_mem)
{
   Word address = FetchByte(_cycles, _mem) | FetchByte(_cycles, _mem) << 8;
   _cycles--;
   ApplyToMemory(
       _cycles, address, _mem,
       [this](const Byte &_val
       ) -> Byte { /// need to caputer this, so that it can manipulate NZ flags
         Byte flag = 0b11111111 & (N_f | Z_f); /// does this work(?)
         SetCustomFlagsWithValue(_val, flag);
          return (_val + 1);
       }
   );
}

void CPU::INC_ABSX(u32 &_cycles, Mem &_mem)
{
   Byte eaLow   = FetchByte(_cycles, _mem);
   Byte eaHigh  = FetchByte(_cycles, _mem);
   Word address = eaLow + (eaHigh << 8); /// Little endian daddyy
   address += X;
   --_cycles;

   assert(address < 0xFFFF && address > 0);
   ApplyToMemory(
       _cycles, address, _mem,
       [this](const Byte &_val
       ) -> Byte { /// need to caputer this, so that it can manipulate NZ flags
         Byte flag = 0b11111111 & (N_f | Z_f); /// does this work(?)
         SetCustomFlagsWithValue(_val, flag);
          return (_val + 1);
       }
   );
}

//////////////////////////////////// INX

void CPU::INX(u32 &_cycles, Mem &_mem)
{
   if(X == 0xFF)
      X = 0;
   else
      ++X;
   --_cycles;
   Byte flag = 0b11111111 & (N_f | Z_f); /// does this work(?)
   SetCustomFlagsWithRegister(Register::X, flag);
}

//////////////////////////////////// INY

void CPU::INY(u32 &_cycles, Mem &_mem)
{
   if(Y == 0xFF)
      Y = 0;
   else
      ++Y;
   --_cycles;
   Byte flag = 0b11111111 & (N_f | Z_f); /// does this work(?)
   SetCustomFlagsWithRegister(Register::Y, flag);
}

//////////////////////////////////// DEC

void CPU::DEC_ZP(u32 &_cycles, Mem &_mem)
{
   Byte zeroPageAddress = FetchByte(_cycles, _mem);
   --_cycles;
   ApplyToMemory(
       _cycles, zeroPageAddress, _mem,
       [this](const Byte &_val
       ) -> Byte { /// need to caputer this, so that it can manipulate NZ flags
         Byte flag = 0b11111111 & (N_f | Z_f); /// does this work(?)
         SetCustomFlagsWithValue(_val, flag);
          return (_val - 1);
       }
   );
}

void CPU::DEC_ZPX(u32 &_cycles, Mem &_mem)
{
   Byte zeroPageAddress = FetchByte(_cycles, _mem);
   zeroPageAddress += X;
   assert(
       zeroPageAddress <= 0xFF && zeroPageAddress >= 0x00
   ); /////Dont know if this wrapps or crosses page
   --_cycles;

   ApplyToMemory(
       _cycles, zeroPageAddress, _mem,
       [this](const Byte &_val
       ) -> Byte { /// need to caputer this, so that it can manipulate NZ flags
         Byte flag = 0b11111111 & (N_f | Z_f); /// does this work(?)
         SetCustomFlagsWithValue(_val, flag);
          return (_val - 1);
       }
   );
   --_cycles;
}

void CPU::DEC_ABS(u32 &_cycles, Mem &_mem)
{
   Word address = FetchByte(_cycles, _mem) | FetchByte(_cycles, _mem) << 8;
   _cycles--;
   ApplyToMemory(
       _cycles, address, _mem,
       [this](const Byte &_val
       ) -> Byte { /// need to caputer this, so that it can manipulate NZ flags
         Byte flag = 0b11111111 & (N_f | Z_f); /// does this work(?)
         SetCustomFlagsWithValue(_val, flag);
          return (_val - 1);
       }
   );
}

void CPU::DEC_ABSX(u32 &_cycles, Mem &_mem)
{
   Byte eaLow   = FetchByte(_cycles, _mem);
   Byte eaHigh  = FetchByte(_cycles, _mem);
   Word address = eaLow + (eaHigh << 8); /// Little endian daddyy
   address += X;
   --_cycles;

   assert(address < 0xFFFF && address > 0);
   ApplyToMemory(
       _cycles, address, _mem,
       [this](const Byte &_val
       ) -> Byte { /// need to caputer this, so that it can manipulate NZ flags
         Byte flag = 0b11111111 & (N_f | Z_f); /// does this work(?)
         SetCustomFlagsWithValue(_val, flag);
          return (_val - 1);
       }
   );
}

//////////////////////////////////// DEX
void CPU::DEX(u32 &_cycles, Mem &_mem)
{
   if(X == 0)
      X = 0xFF;
   else
      --X;
   --_cycles;
   Byte flag = 0b11111111 & (N_f | Z_f); /// does this work(?)
   SetCustomFlagsWithRegister(Register::X, flag);
}

//////////////////////////////////// DEY

void CPU::DEY(u32 &_cycles, Mem &_mem)
{
   if(Y == 0)
      Y = 0xFF;
   else
      --Y;
   --_cycles;
   Byte flag = 0b11111111 & (N_f | Z_f); /// does this work(?)
   SetCustomFlagsWithRegister(Register::Y, flag);
}

