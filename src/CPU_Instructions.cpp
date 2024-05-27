#include "CPU.h"

//////////////////////////////////// NULL 

void CPU::NULL_INS(u32 &_cycles, Mem &_mem)
{
   //printf("\nhere in null ins. Number of cycles is: %d\n", _cycles);
   Byte val = FetchByte(_cycles, _mem);
   return;
}

//////////////////////////////////// LDA
void CPU::LDA_IM(u32 &_cycles, Mem &_mem)
{
   Byte val = FetchByte(_cycles, _mem);
   A        = val;
   LDASetStatus();
}

void CPU::LDA_ZP(u32 &_cycles, Mem &_mem)
{
   Byte zeroPageAddress = FetchByte(_cycles, _mem);
   A                    = ReadByte(_cycles, zeroPageAddress, _mem);
   LDASetStatus();
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
   A = ReadByte(_cycles, zeroPageAddress, _mem);
   LDASetStatus();
}

void CPU::LDA_ABS(u32 &_cycles, Mem &_mem)
{
   Word address = FetchByte(_cycles, _mem) | FetchByte(_cycles, _mem) << 8;
   A            = ReadByte(_cycles, address, _mem);
   LDASetStatus();
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
   A = ReadByte(_cycles, address, _mem);
   LDASetStatus();
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
   A = ReadByte(_cycles, address, _mem);
   LDASetStatus();
}

void CPU::LDA_INDX(u32 &_cycles, Mem &_mem)
{
   Word adress = FetchByte(_cycles, _mem) + X;
   Byte eaLow  = ReadByte(_cycles, adress, _mem);
   Byte eaHigh = ReadByte(_cycles, ++adress, _mem);
   Word ea     = eaLow + (eaHigh << 8);
   --_cycles; /// have to add this here
   A = ReadByte(_cycles, ea, _mem);
   LDASetStatus();
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
   Word ea = eaLow + (eaHigh << 8) + Y;
   A       = ReadByte(_cycles, ea, _mem);
   LDASetStatus();
}

/////////////////////////////////////// MISC
void CPU::JSR(u32 &_cycles, Mem &_mem)
{
   Word subRoutineAddr = FetchWord(_cycles, _mem);
   _mem.writeWord(_cycles, SP + 1, PC - 1);
   //_mem.writeWord(_cycles, SP , PC - 1);
   PC = subRoutineAddr;
   --_cycles;
}

/////////////////////////////////////// LDX
void CPU::LDX_IM(u32 &_cycles, Mem &_mem)
{
   Byte val = FetchByte(_cycles, _mem);
   X        = val;
   LDXSetStatus();
}

void CPU::LDX_ZP(u32 &_cycles, Mem &_mem)
{
   Byte zeroPageAddress = FetchByte(_cycles, _mem);
   X                    = ReadByte(_cycles, zeroPageAddress, _mem);
   LDXSetStatus();
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
   X = ReadByte(_cycles, zeroPageAddress, _mem);
   LDXSetStatus();
}

void CPU::LDX_ABS(u32 &_cycles, Mem &_mem)
{
   Word address = FetchByte(_cycles, _mem) | FetchByte(_cycles, _mem) << 8;
   X            = ReadByte(_cycles, address, _mem);
   LDXSetStatus();
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
   X = ReadByte(_cycles, address, _mem);
   LDXSetStatus();
}

//////////////////////////////////// LDY

void CPU::LDY_IM(u32 &_cycles, Mem &_mem)
{
   Byte val = FetchByte(_cycles, _mem);
   Y        = val;
   LDYSetStatus();
}

void CPU::LDY_ZP(u32 &_cycles, Mem &_mem)
{
   Byte zeroPageAddress = FetchByte(_cycles, _mem);
   Y                    = ReadByte(_cycles, zeroPageAddress, _mem);
   LDYSetStatus();
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
   Y = ReadByte(_cycles, zeroPageAddress, _mem);
   LDYSetStatus();
}

void CPU::LDY_ABS(u32 &_cycles, Mem &_mem)
{
   Word address = FetchByte(_cycles, _mem) | FetchByte(_cycles, _mem) << 8;
   Y            = ReadByte(_cycles, address, _mem);
   LDYSetStatus();
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
   Y = ReadByte(_cycles, address, _mem);
   LDYSetStatus();
}

//////////////////////////////////// INC

//////////////////////////////////// INX

void CPU::INX(u32 &_cycles, Mem &_mem)
{
   if(X == 0xFF)
      X = 0;
   else
      ++X;
   --_cycles;
   LDXSetStatus();
}

//////////////////////////////////// INY

void CPU::INY(u32 &_cycles, Mem &_mem)
{
   if(Y == 0xFF)
      Y = 0;
   else
      ++Y;
   --_cycles;
   LDYSetStatus();
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
   LDXSetStatus();
}

//////////////////////////////////// DEY

void CPU::DEY(u32 &_cycles, Mem &_mem)
{
   if(Y == 0)
      Y = 0xFF;
   else
      --Y;
   --_cycles;
   LDYSetStatus();
}
