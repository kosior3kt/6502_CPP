#include "CPU.h"

////////////////////////////////////// Logical
///AND
void CPU::AND_IM (u32& _cycles, Mem &_mem)
{
   Byte val  = FetchByte(_cycles, _mem);  ///the fetched byte
   A        &= val;
   Byte flag = 0b11111111 & (N_f | Z_f); /// does this work(?)
   SetCustomFlagsWithRegister(Register::A, flag);
}

void CPU::AND_ZP (u32& _cycles, Mem &_mem)
{
   Byte zeroPageAddress = FetchByte(_cycles, _mem);
   A                   &= ReadByte(_cycles, zeroPageAddress, _mem);
   Byte flag            = 0b11111111 & (N_f | Z_f); /// does this work(?)
   SetCustomFlagsWithRegister(Register::A, flag);
}

void CPU::AND_ZPX(u32& _cycles, Mem &_mem)
{
   Byte zeroPageAddress = FetchByte(_cycles, _mem);
   zeroPageAddress += X;
   _cycles--;
   if(zeroPageAddress > _mem.MAX_MEM)
   {
      std::cout << "instrukcja LDA ZPX przekroczyla obszar pamieci";
      return;
   }
   A        &= ReadByte(_cycles, zeroPageAddress, _mem);
   Byte flag = 0b11111111 & (N_f | Z_f); /// does this work(?)
   SetCustomFlagsWithRegister(Register::A, flag);
}

void CPU::AND_ABS(u32& _cycles, Mem &_mem)
{
   Word address = FetchByte(_cycles, _mem) | FetchByte(_cycles, _mem) << 8;
   auto temp = ReadByte(_cycles, address, _mem);
   A           &=    temp;
   Byte flag    = 0b11111111 & (N_f | Z_f); /// does this work(?)
   SetCustomFlagsWithRegister(Register::A, flag);
}

void CPU::AND_ABSX(u32& _cycles, Mem &_mem)
{
   Word address = FetchByte(_cycles, _mem) | FetchByte(_cycles, _mem) << 8;
   address += X;
   auto temp = ReadByte(_cycles, address, _mem);
   A           &=    temp;
   Byte flag    = 0b11111111 & (N_f | Z_f); /// does this work(?)
   SetCustomFlagsWithRegister(Register::A, flag);
}

void CPU::AND_ABSY(u32& _cycles, Mem &_mem)
{  
   Word address = FetchByte(_cycles, _mem) | FetchByte(_cycles, _mem) << 8;
   address += Y;
   auto temp = ReadByte(_cycles, address, _mem);
   A           &=    temp;
   Byte flag    = 0b11111111 & (N_f | Z_f); /// does this work(?)
   SetCustomFlagsWithRegister(Register::A, flag);
}

void CPU::AND_INDX(u32& _cycles, Mem &_mem)
{
   Byte adress = FetchByte(_cycles, _mem) + X;
   Byte eaLow  = ReadByte(_cycles, adress, _mem);
   Byte eaHigh = ReadByte(_cycles, ++adress, _mem);
   Word ea     = eaLow + (eaHigh << 8);
   --_cycles; /// have to add this here
   A          &= ReadByte(_cycles, ea, _mem);
   Byte flag   = 0b11111111 & (N_f | Z_f); /// does this work(?)
   SetCustomFlagsWithRegister(Register::A, flag);
}

void CPU::AND_INDY(u32& _cycles, Mem &_mem)
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
   A        &= ReadByte(_cycles, ea, _mem);
   Byte flag = 0b11111111 & (N_f | Z_f); 
   SetCustomFlagsWithRegister(Register::A, flag);
}

///EOR
void CPU::EOR_IM (u32& _cycles, Mem &_mem)
{

}

void CPU::EOR_ZP (u32& _cycles, Mem &_mem)
{

}

void CPU::EOR_ZPX(u32& _cycles, Mem &_mem)
{

}

void CPU::EOR_ABS(u32& _cycles, Mem &_mem)
{

}

void CPU::EOR_ABSX(u32& _cycles, Mem &_mem)
{

}

void CPU::EOR_ABSY(u32& _cycles, Mem &_mem)
{

}

void CPU::EOR_INDX(u32& _cycles, Mem &_mem)
{

}

void CPU::EOR_INDY(u32& _cycles, Mem &_mem)
{

}


///ORA 
void CPU::ORA_IM (u32& _cycles, Mem &_mem)
{

}

void CPU::ORA_ZP (u32& _cycles, Mem &_mem)
{

}

void CPU::ORA_ZPX(u32& _cycles, Mem &_mem)
{

}

void CPU::ORA_ABS(u32& _cycles, Mem &_mem)
{

}

void CPU::ORA_ABSX(u32& _cycles, Mem &_mem)
{

}

void CPU::ORA_ABSY(u32& _cycles, Mem &_mem)
{

}

void CPU::ORA_INDX(u32& _cycles, Mem &_mem)
{

}

void CPU::ORA_INDY(u32& _cycles, Mem &_mem)
{

}


/// BIT
void CPU::BIT_ZP (u32& _cycles, Mem &_mem)
{

}

void CPU::BIT_ZBS(u32& _cycles, Mem &_mem)
{

}

