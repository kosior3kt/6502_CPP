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
         HEX_PRINT("value of the fetched byte assigned to A: ", (int)val);
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
         safeCycleDecrement(_cycles);
         break;
      }
      case CPU::INS_LDA_INDY :{
         address = getAddr(_cycles, _mem, adressingMode::INDY);
         break;
      }
   }

   if(!immediete)
   {
      HEX_PRINT("here");
      A  = ReadByte(_cycles, address, _mem);
   }

   HEX_PRINT("cycles left: ",          _cycles);
   HEX_PRINT("address of the thing: ", address);

   Byte flag = (N_f | Z_f);
   SetCustomFlagsWithRegister(Register::A, flag);
}


void CPU::LDX_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode)
{
   bool immediete = false;
   Word address{};


   std::cout<<"here "<<std::endl;
   switch(_opCode){
      case CPU::INS_LDX_IM :{
         Byte val  = FetchByte(_cycles, _mem);
         X         = val;
         immediete = true;
         HEX_PRINT("address after addition: ", address);
         break;
      }
      case CPU::INS_LDX_ZP :{
         address = getAddr(_cycles, _mem, adressingMode::ZP);
         HEX_PRINT("address after addition: ", address);
         break;
      }
      case CPU::INS_LDX_ZPY :{
         address = getAddr(_cycles, _mem, adressingMode::ZPY);
         HEX_PRINT("address after addition: ", address);
         break;
      }
      case CPU::INS_LDX_ABS :{
         address = getAddr(_cycles, _mem, adressingMode::ABS);
         HEX_PRINT("address after addition: ", address);
         break;
      }
      case CPU::INS_LDX_ABSY :{
         address = getAddr(_cycles, _mem, adressingMode::ABSY);
         HEX_PRINT("address after addition: ", address);
         break;
      }
   }

   if(!immediete)
   {
      X  = ReadByte(_cycles, address, _mem);
   }

   HEX_PRINT("this is an address: ", address);
   HEX_PRINT("number of cycles: ", _cycles);

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
         safeCycleDecrement(_cycles);
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

