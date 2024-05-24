#include "CPU.h"

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
