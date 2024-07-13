#include "CPU.h"

//////////////////////////////////// test
void CPU::LDA_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode)
{
   bool immediete = false;
   Word address{};

   switch(_opCode){
      case CPU::INS_LDA_IM :{
         Byte val  = FetchByte(_cycles, _mem);
         A         = val;
         immediete = true;
         break;
      }
      case CPU::INS_LDA_ZP :{
         address = getAddr(_cycles, _mem, adressingMode::ZP);
         break;
      }
      case CPU::INS_LDA_ZPX :{
         address = getAddr(_cycles, _mem, adressingMode::ZPX);
         break;
      }
      case CPU::INS_LDA_ABS :{
         address = getAddr(_cycles, _mem, adressingMode::ABS);
         break;
      }
      case CPU::INS_LDA_ABSX :{
         address = getAddr(_cycles, _mem, adressingMode::ABSX);
         break;
      }
      case CPU::INS_LDA_ABSY :{
         address = getAddr(_cycles, _mem, adressingMode::ABSY);
         break;
      }
      case CPU::INS_LDA_INDX :{
         address = getAddr(_cycles, _mem, adressingMode::INDX);
         --_cycles;
         break;
      }
      case CPU::INS_LDA_INDY :{
         address = getAddr(_cycles, _mem, adressingMode::INDY);
         break;
      }
   }

   if(!immediete)
   {
      A  = ReadByte(_cycles, address, _mem);
   }
   Byte flag = (N_f | Z_f);
   SetCustomFlagsWithRegister(Register::A, flag);
}


void CPU::LDX_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode)
{
   bool immediete = false;
   Word address{};

   switch(_opCode){
      case CPU::INS_LDX_IM :{
         Byte val  = FetchByte(_cycles, _mem);
         X         = val;
         immediete = true;
         break;
      }
      case CPU::INS_LDX_ZP :{
         address = getAddr(_cycles, _mem, adressingMode::ZP);
         break;
      }
      case CPU::INS_LDX_ZPY :{
         address = getAddr(_cycles, _mem, adressingMode::ZPY);
         break;
      }
      case CPU::INS_LDX_ABS :{
         address = getAddr(_cycles, _mem, adressingMode::ABS);
         break;
      }
      case CPU::INS_LDX_ABSY :{
         address = getAddr(_cycles, _mem, adressingMode::ABSY);
         break;
      }
   }

   if(!immediete)
   {
      X  = ReadByte(_cycles, address, _mem);
   }
   Byte flag = (N_f | Z_f);
   SetCustomFlagsWithRegister(Register::X, flag);
}

void CPU::LDY_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode)
{
   bool immediete = false;
   Word address{};

   switch(_opCode){
      case CPU::INS_LDY_IM :{
         Byte val  = FetchByte(_cycles, _mem);
         Y         = val;
         immediete = true;
         break;
      }
      case CPU::INS_LDY_ZP :{
         address = getAddr(_cycles, _mem, adressingMode::ZP);
         break;
      }
      case CPU::INS_LDY_ZPX :{
         address = getAddr(_cycles, _mem, adressingMode::ZPX);
         break;
      }
      case CPU::INS_LDY_ABS :{
         address = getAddr(_cycles, _mem, adressingMode::ABS);
         break;
      }
      case CPU::INS_LDY_ABSX :{
         address = getAddr(_cycles, _mem, adressingMode::ABSX);
         break;
      }
   }

   if(!immediete)
   {
      Y  = ReadByte(_cycles, address, _mem);
   }
   Byte flag = (N_f | Z_f);
   SetCustomFlagsWithRegister(Register::Y, flag);
}


void CPU::STA_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode)
{
   Word address{};

   switch(_opCode){
      case CPU::INS_STA_ZP :{
         address = getAddr(_cycles, _mem, adressingMode::ZP);
         break;
      }
      case CPU::INS_STA_ZPX :{
         address = getAddr(_cycles, _mem, adressingMode::ZPX);
         break;
      }
      case CPU::INS_STA_ABS :{
         address = getAddr(_cycles, _mem, adressingMode::ABS);
         break;
      }
      case CPU::INS_STA_ABSX :{
         address = getAddr(_cycles, _mem, adressingMode::ABSX);
         break;
      }
      case CPU::INS_STA_ABSY :{
         address = getAddr(_cycles, _mem, adressingMode::ABSY);
         break;
      }
      case CPU::INS_STA_INDX :{
         address = getAddr(_cycles, _mem, adressingMode::INDX);
         --_cycles;
         break;
      }
      case CPU::INS_STA_INDY :{
         address = getAddr(_cycles, _mem, adressingMode::INDY);
         break;
      }
   }

   WriteByte(_cycles, address, _mem, CPU::A);
}

void CPU::STX_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode)
{
   Word address{};

   switch(_opCode){
      case CPU::INS_STX_ZP :{
         address = getAddr(_cycles, _mem, adressingMode::ZP);
         break;
      }
      case CPU::INS_STX_ZPY :{
         address = getAddr(_cycles, _mem, adressingMode::ZPY);
         break;
      }
      case CPU::INS_STX_ABS :{
         address = getAddr(_cycles, _mem, adressingMode::ABS);
         break;
      }
   }

   WriteByte(_cycles, address, _mem, CPU::X);

}

void CPU::STY_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode)
{
   Word address{};

   switch(_opCode){
      case CPU::INS_STY_ZP :{
         address = getAddr(_cycles, _mem, adressingMode::ZP);
         break;
      }
      case CPU::INS_STY_ZPX :{
         address = getAddr(_cycles, _mem, adressingMode::ZPX);
         break;
      }
      case CPU::INS_STY_ABS :{
         address = getAddr(_cycles, _mem, adressingMode::ABS);
         break;
      }
   }

   WriteByte(_cycles, address, _mem, CPU::Y);
}


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

