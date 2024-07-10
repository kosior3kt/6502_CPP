#include "CPU.h"

//////////////////////////////////// LDA
void CPU::LDA_IM(u32 &_cycles, Mem &_mem)
{
   Byte val  = FetchByte(_cycles, _mem);
   A         = val;
   Byte flag = (N_f | Z_f);
   SetCustomFlagsWithRegister(Register::A, flag);
}

void CPU::LDA_ZP(u32 &_cycles, Mem &_mem)
{
   Word address = getAddr(_cycles, _mem, adressingMode::ZP);
   A            = ReadByte(_cycles, address, _mem);
   Byte flag    = (N_f | Z_f);
   SetCustomFlagsWithRegister(Register::A, flag);
}

void CPU::LDA_ZPX(u32 &_cycles, Mem &_mem)
{
   Word address = getAddr(_cycles, _mem, adressingMode::ZPX);
   A            = ReadByte(_cycles, address, _mem);
   Byte flag    = (N_f | Z_f);
   SetCustomFlagsWithRegister(Register::A, flag);
}

void CPU::LDA_ABS(u32 &_cycles, Mem &_mem)
{
   Word address = getAddr(_cycles, _mem, adressingMode::ABS);
   A            = ReadByte(_cycles, address, _mem);
   Byte flag    = (N_f | Z_f);
   SetCustomFlagsWithRegister(Register::A, flag);
}

void CPU::LDA_ABSX(u32 &_cycles, Mem &_mem)
{
   Word address = getAddr(_cycles, _mem, adressingMode::ABSX);
   A         = ReadByte(_cycles, address, _mem);
   Byte flag = (N_f | Z_f); 
   SetCustomFlagsWithRegister(Register::A, flag);
}

void CPU::LDA_ABSY(u32 &_cycles, Mem &_mem)
{
   Word address = getAddr(_cycles, _mem, adressingMode::ABSY);
   A         = ReadByte(_cycles, address, _mem);
   Byte flag = (N_f | Z_f); 
   SetCustomFlagsWithRegister(Register::A, flag);
}

void CPU::LDA_INDX(u32 &_cycles, Mem &_mem)
{
   Word ea     = getAddr(_cycles, _mem, adressingMode::INDX);
   --_cycles;
   A         = ReadByte(_cycles, ea, _mem);
   Byte flag = (N_f | Z_f); 
   SetCustomFlagsWithRegister(Register::A, flag);
}

void CPU::LDA_INDY(u32 &_cycles, Mem &_mem)
{
   Word ea   = getAddr(_cycles, _mem, adressingMode::INDY);
   A         = ReadByte(_cycles, ea, _mem);
   Byte flag = (N_f | Z_f); 
   SetCustomFlagsWithRegister(Register::A, flag);
}


/////////////////////////////////////// LDX
void CPU::LDX_IM(u32 &_cycles, Mem &_mem)
{
   Byte val  = FetchByte(_cycles, _mem);
   X         = val;
   Byte flag = (N_f | Z_f); 
   SetCustomFlagsWithRegister(Register::X, flag);
}

void CPU::LDX_ZP(u32 &_cycles, Mem &_mem)
{

   Word address = getAddr(_cycles, _mem, adressingMode::ZP);
   X                    = ReadByte(_cycles, address, _mem);
   Byte flag            = (N_f | Z_f); 
   SetCustomFlagsWithRegister(Register::X, flag);
}

void CPU::LDX_ZPY(u32 &_cycles, Mem &_mem)
{

   Word address = getAddr(_cycles, _mem, adressingMode::ZPY);
   X         = ReadByte(_cycles, address, _mem);
   Byte flag = (N_f | Z_f); 
   SetCustomFlagsWithRegister(Register::X, flag);
}

void CPU::LDX_ABS(u32 &_cycles, Mem &_mem)
{
   Word address = getAddr(_cycles, _mem, adressingMode::ABS);
   X            = ReadByte(_cycles, address, _mem);
   Byte flag    = (N_f | Z_f); 
   SetCustomFlagsWithRegister(Register::X, flag);
}

void CPU::LDX_ABSY(u32 &_cycles, Mem &_mem)
{
   Word address = getAddr(_cycles, _mem, adressingMode::ABSY);
   X         = ReadByte(_cycles, address, _mem);
   Byte flag = (N_f | Z_f); 
   SetCustomFlagsWithRegister(Register::X, flag);
}

//////////////////////////////////// LDY

void CPU::LDY_IM(u32 &_cycles, Mem &_mem)
{
   Byte val  = FetchByte(_cycles, _mem);
   Y         = val;
   Byte flag = (N_f | Z_f); 
   SetCustomFlagsWithRegister(Register::Y, flag);
}

void CPU::LDY_ZP(u32 &_cycles, Mem &_mem)
{
   Word address = getAddr(_cycles, _mem, adressingMode::ZP);
   Y                    = ReadByte(_cycles, address, _mem);
   Byte flag            = (N_f | Z_f); 
   SetCustomFlagsWithRegister(Register::Y, flag);
}

void CPU::LDY_ZPX(u32 &_cycles, Mem &_mem)
{
   Word address = getAddr(_cycles, _mem, adressingMode::ZPX);
   Y         = ReadByte(_cycles, address, _mem);
   Byte flag = (N_f | Z_f); 
   SetCustomFlagsWithRegister(Register::Y, flag);
}

void CPU::LDY_ABS(u32 &_cycles, Mem &_mem)
{
   Word address = getAddr(_cycles, _mem, adressingMode::ABS);
   Y            = ReadByte(_cycles, address, _mem);
   Byte flag    = (N_f | Z_f); 
   SetCustomFlagsWithRegister(Register::Y, flag);
}

void CPU::LDY_ABSX(u32 &_cycles, Mem &_mem)
{
   Word address = getAddr(_cycles, _mem, adressingMode::ABSX);
   Y         = ReadByte(_cycles, address, _mem);
   Byte flag = (N_f | Z_f); 
   SetCustomFlagsWithRegister(Register::Y, flag);
}


//////////////////////////////////// STA

void CPU::STA_ABS(u32 &_cycles, Mem &_mem) 
{
   Word address = getAddr(_cycles, _mem, adressingMode::ABS);
   WriteByte(_cycles, address, _mem, CPU::A);
}

void CPU::STA_ABSX(u32 &_cycles, Mem &_mem) 
{
   Word address = getAddr(_cycles, _mem, adressingMode::ABSX);
   _cycles--;
   WriteByte(_cycles, address, _mem, CPU::A);
}

void CPU::STA_ABSY(u32 &_cycles, Mem &_mem) 
{
   Word address = getAddr(_cycles, _mem, adressingMode::ABSY);
   _cycles--;
   WriteByte(_cycles, address, _mem, CPU::A);
}

void CPU::STA_ZP(u32 &_cycles, Mem &_mem) 
{
   Word address = getAddr(_cycles, _mem, adressingMode::ZP);
   WriteByte(_cycles, address, _mem, CPU::A);
   ///no flags to set (in theory)
}

void CPU::STA_ZPX(u32 &_cycles, Mem &_mem) 
{
   Word address = getAddr(_cycles, _mem, adressingMode::ZPX);
   WriteByte(_cycles, address, _mem, CPU::A);
}

void CPU::STA_INDX(u32 &_cycles, Mem &_mem) 
{
   Word address = getAddr(_cycles, _mem, adressingMode::INDX);
   WriteByte(_cycles, address, _mem, CPU::A);
}

void CPU::STA_INDY(u32 &_cycles, Mem &_mem) 
{
   Word address = getAddr(_cycles, _mem, adressingMode::INDY);
   WriteByte(_cycles, address, _mem, CPU::A);
}

///STX
void CPU::STX_ZP(u32 &_cycles, Mem &_mem) 
{
   Word address = getAddr(_cycles, _mem, adressingMode::ZP);
   WriteByte(_cycles, address, _mem, CPU::X);
   ///no flags to set (in theory)
}

void CPU::STX_ZPY(u32 &_cycles, Mem &_mem)
{
   Word address = getAddr(_cycles, _mem, adressingMode::ZPY);
   WriteByte(_cycles, address, _mem, CPU::X);
}

void CPU::STX_ABS(u32 &_cycles, Mem &_mem) 
{
   Word address = getAddr(_cycles, _mem, adressingMode::ABS);
   WriteByte(_cycles, address, _mem, CPU::X);
}

///STY
void CPU::STY_ZP(u32 &_cycles, Mem &_mem) 
{   
   Word address = getAddr(_cycles, _mem, adressingMode::ZP);
   WriteByte(_cycles, address, _mem, CPU::Y);
}

void CPU::STY_ZPX(u32 &_cycles, Mem &_mem) 
{
   Word address = getAddr(_cycles, _mem, adressingMode::ZPX);
   WriteByte(_cycles, address, _mem, CPU::Y);
}

void CPU::STY_ABS(u32 &_cycles, Mem &_mem) 
{
   Word address = getAddr(_cycles, _mem, adressingMode::ABS);
   WriteByte(_cycles, address, _mem, CPU::Y);
}

