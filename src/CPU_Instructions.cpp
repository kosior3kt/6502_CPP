#include "CPU.h"

//////////////////////////////////// NULL

void CPU::NULL_INS(u32 &_cycles, Mem &_mem)
{
   // printf("\nhere in null ins. Number of cycles is: %d\n", _cycles);
   Byte val = FetchByte(_cycles, _mem);
   return;
}

//////////////////////////////////// LDA
void CPU::LDA_IM(u32 &_cycles, Mem &_mem)
{
   Byte val  = FetchByte(_cycles, _mem);
   A         = val;
   Byte flag = 0b11111111 & (N_f | Z_f); /// does this work(?)
   SetCustomFlagsWithRegister(Register::A, flag);
}

void CPU::LDA_ZP(u32 &_cycles, Mem &_mem)
{
   Byte zeroPageAddress = FetchByte(_cycles, _mem);
   A                    = ReadByte(_cycles, zeroPageAddress, _mem);
   Byte flag            = 0b11111111 & (N_f | Z_f); /// does this work(?)
   SetCustomFlagsWithRegister(Register::A, flag);
}

void CPU::LDA_ZPX(u32 &_cycles, Mem &_mem)
{
   Byte zeroPageAddress = FetchByte(_cycles, _mem);
   zeroPageAddress += X;
   _cycles--;
   if(zeroPageAddress > _mem.MAX_MEM)
   {
      std::cout << "instrukcja LDA ZPX przekroczyla obszar pamieci";
      return;
   }
   A         = ReadByte(_cycles, zeroPageAddress, _mem);
   Byte flag = 0b11111111 & (N_f | Z_f); /// does this work(?)
   SetCustomFlagsWithRegister(Register::A, flag);
}

void CPU::LDA_ABS(u32 &_cycles, Mem &_mem)
{
   Word address = FetchByte(_cycles, _mem) | FetchByte(_cycles, _mem) << 8;
   A            = ReadByte(_cycles, address, _mem);
   Byte flag    = 0b11111111 & (N_f | Z_f); /// does this work(?)
   SetCustomFlagsWithRegister(Register::A, flag);
}

void CPU::LDA_ABSX(u32 &_cycles, Mem &_mem)
{
   Byte eaLow   = FetchByte(_cycles, _mem);
   Byte eaHigh  = FetchByte(_cycles, _mem);
   Word address = eaLow + (eaHigh << 8); /// Little endian daddyy
   address += X;
   // address = address % Mem::MAX_MEM;   ///Does it make sense???
   // (spoiler - it didn't)
   if(eaLow + X > 0xFF)
      --_cycles;
   A         = ReadByte(_cycles, address, _mem);
   Byte flag = 0b11111111 & (N_f | Z_f); /// does this work(?)
   SetCustomFlagsWithRegister(Register::A, flag);
}

void CPU::LDA_ABSY(u32 &_cycles, Mem &_mem)
{
   Byte eaLow   = FetchByte(_cycles, _mem);
   Byte eaHigh  = FetchByte(_cycles, _mem);
   Word address = eaLow + (eaHigh << 8); /// Little endian daddyy
   address += Y;
   // address = address % Mem::MAX_MEM;   ///Does it make sense???
   if(eaLow + Y > 0xFF)
      --_cycles;
   A         = ReadByte(_cycles, address, _mem);
   Byte flag = 0b11111111 & (N_f | Z_f); /// does this work(?)
   SetCustomFlagsWithRegister(Register::A, flag);
}

void CPU::LDA_INDX(u32 &_cycles, Mem &_mem)
{
   Word adress = FetchByte(_cycles, _mem) + X;
   Byte eaLow  = ReadByte(_cycles, adress, _mem);
   Byte eaHigh = ReadByte(_cycles, ++adress, _mem);
   Word ea     = eaLow + (eaHigh << 8);
   --_cycles; /// have to add this here
   A         = ReadByte(_cycles, ea, _mem);
   Byte flag = 0b11111111 & (N_f | Z_f); /// does this work(?)
   SetCustomFlagsWithRegister(Register::A, flag);
}

void CPU::LDA_INDY(u32 &_cycles, Mem &_mem)
{
   Word adress = FetchByte(_cycles, _mem);
   Byte eaLow  = ReadByte(_cycles, adress, _mem);
   Byte eaHigh = ReadByte(
       _cycles, ++adress, _mem
   ); /// TODO: abstract this later on, and find out why this is supposed to be
      /// able to cross page
   if(eaLow + Y > 0xFF)
      --_cycles;
   Word ea   = eaLow + (eaHigh << 8) + Y;
   A         = ReadByte(_cycles, ea, _mem);
   Byte flag = 0b11111111 & (N_f | Z_f); /// does this work(?)
   SetCustomFlagsWithRegister(Register::A, flag);
}

/////////////////////////////////////// JSR
void CPU::JSR(u32 &_cycles, Mem &_mem)
{
   Word subRoutineAddr = FetchWord(_cycles, _mem);
#ifdef DEBUG
   auto temp = SP;
#endif
   _mem.writeWord(
       _cycles, ++SP, PC - 1
   ); /// does this make sense(?) ((I belive so))
   // ++S
   //_mem.writeWord(_cycles, SP , PC - 1);
   PC = subRoutineAddr;
#ifdef DEBUG
   printf("SP before: %d, SP now: %d\n", temp, SP);
   assert(SP == temp + 1);
#endif
   --_cycles;
}

/////////////////////////////////////// LDX
void CPU::LDX_IM(u32 &_cycles, Mem &_mem)
{
   Byte val  = FetchByte(_cycles, _mem);
   X         = val;
   Byte flag = 0b11111111 & (N_f | Z_f); /// does this work(?)
   SetCustomFlagsWithRegister(Register::X, flag);
}

void CPU::LDX_ZP(u32 &_cycles, Mem &_mem)
{
   Byte zeroPageAddress = FetchByte(_cycles, _mem);
   X                    = ReadByte(_cycles, zeroPageAddress, _mem);
   Byte flag            = 0b11111111 & (N_f | Z_f); /// does this work(?)
   SetCustomFlagsWithRegister(Register::X, flag);
}

void CPU::LDX_ZPY(u32 &_cycles, Mem &_mem)
{
   Byte zeroPageAddress = FetchByte(_cycles, _mem);
   zeroPageAddress += Y;
   _cycles--;
   if(zeroPageAddress > _mem.MAX_MEM)
   {
      std::cout << "instrukcja LDA ZPY przekroczyla obszar pamieci";
      return;
   }
   X         = ReadByte(_cycles, zeroPageAddress, _mem);
   Byte flag = 0b11111111 & (N_f | Z_f); /// does this work(?)
   SetCustomFlagsWithRegister(Register::X, flag);
}

void CPU::LDX_ABS(u32 &_cycles, Mem &_mem)
{
   Word address = FetchByte(_cycles, _mem) | FetchByte(_cycles, _mem) << 8;
   X            = ReadByte(_cycles, address, _mem);
   Byte flag    = 0b11111111 & (N_f | Z_f); /// does this work(?)
   SetCustomFlagsWithRegister(Register::X, flag);
}

void CPU::LDX_ABSY(u32 &_cycles, Mem &_mem)
{
   Byte eaLow   = FetchByte(_cycles, _mem);
   Byte eaHigh  = FetchByte(_cycles, _mem);
   Word address = eaLow + (eaHigh << 8); /// Little endian daddyy
   address += Y;
   // address = address % Mem::MAX_MEM;   ///Does it make sense???
   if(eaLow + Y > 0xFF)
      --_cycles;
   X         = ReadByte(_cycles, address, _mem);
   Byte flag = 0b11111111 & (N_f | Z_f); /// does this work(?)
   SetCustomFlagsWithRegister(Register::X, flag);
}

//////////////////////////////////// LDY

void CPU::LDY_IM(u32 &_cycles, Mem &_mem)
{
   Byte val  = FetchByte(_cycles, _mem);
   Y         = val;
   Byte flag = 0b11111111 & (N_f | Z_f); /// does this work(?)
   SetCustomFlagsWithRegister(Register::Y, flag);
}

void CPU::LDY_ZP(u32 &_cycles, Mem &_mem)
{
   Byte zeroPageAddress = FetchByte(_cycles, _mem);
   Y                    = ReadByte(_cycles, zeroPageAddress, _mem);
   Byte flag            = 0b11111111 & (N_f | Z_f); /// does this work(?)
   SetCustomFlagsWithRegister(Register::Y, flag);
}

void CPU::LDY_ZPX(u32 &_cycles, Mem &_mem)
{
   Byte zeroPageAddress = FetchByte(_cycles, _mem);
   zeroPageAddress += X;
   _cycles--;
   if(zeroPageAddress > _mem.MAX_MEM)
   {
      std::cout << "instrukcja LDA ZPY przekroczyla obszar pamieci";
      return;
   }
   Y         = ReadByte(_cycles, zeroPageAddress, _mem);
   Byte flag = 0b11111111 & (N_f | Z_f); /// does this work(?)
   SetCustomFlagsWithRegister(Register::Y, flag);
}

void CPU::LDY_ABS(u32 &_cycles, Mem &_mem)
{
   Word address = FetchByte(_cycles, _mem) | FetchByte(_cycles, _mem) << 8;
   Y            = ReadByte(_cycles, address, _mem);
   Byte flag    = 0b11111111 & (N_f | Z_f); /// does this work(?)
   SetCustomFlagsWithRegister(Register::Y, flag);
}

void CPU::LDY_ABSX(u32 &_cycles, Mem &_mem)
{
   Byte eaLow   = FetchByte(_cycles, _mem);
   Byte eaHigh  = FetchByte(_cycles, _mem);
   Word address = eaLow + (eaHigh << 8); /// Little endian daddyy
   address += X;
   // address = address % Mem::MAX_MEM;   ///Does it make sense???
   if(eaLow + X > 0xFF)
      --_cycles;
   Y         = ReadByte(_cycles, address, _mem);
   Byte flag = 0b11111111 & (N_f | Z_f); /// does this work(?)
   SetCustomFlagsWithRegister(Register::Y, flag);
}

//////////////////////////////////// INC

void CPU::INC_ZP(u32 &_cycles, Mem &_mem)
{
   Byte zeroPageAddress = FetchByte(_cycles, _mem);
   _cycles--;
   ApplyToMemory(
       _cycles, zeroPageAddress, _mem,
       [this](const Byte &_val
       ) -> Byte { /// need to caputer this, so that it can manipulate NZ flags
          CPU::SetNZWithValue(_val + 1);
          return (_val + 1);
       }
   );
}

void CPU::INC_ZPX(u32 &_cycles, Mem &_mem)
{
   Byte zeroPageAddress = FetchByte(_cycles, _mem);
   zeroPageAddress += X;
   assert(
       zeroPageAddress < 0xFF && zeroPageAddress > 0x00
   ); /////Dont know if this wrapps or crosses page
   _cycles--;

   ApplyToMemory(
       _cycles, zeroPageAddress, _mem,
       [this](const Byte &_val
       ) -> Byte { /// need to caputer this, so that it can manipulate NZ flags
          CPU::SetNZWithValue(_val + 1);
          return (_val + 1);
       }
   );
}

void CPU::INC_ABS(u32 &_cycles, Mem &_mem)
{
   Word address = FetchByte(_cycles, _mem) | FetchByte(_cycles, _mem) << 8;
   ApplyToMemory(
       _cycles, address, _mem,
       [this](const Byte &_val
       ) -> Byte { /// need to caputer this, so that it can manipulate NZ flags
          CPU::SetNZWithValue(_val + 1);
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
          CPU::SetNZWithValue(_val + 1);
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
