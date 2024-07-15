#include "CPU.h"

#define OVERFLOW_MASK 0b10000000

enum class result : uint8_t{
   ///same sign
   POSITIVE = 0,
   NEGATIVE = 1,
   ///opposite signe - we don't care anymore
   OPPOSITE_SIGN
};

static std::ostream& operator<<(std::ostream& os, const result& Token) noexcept   ///does it even matter for operator overloading?
{
  switch(Token)
  {
    case result::POSITIVE:
      os << "POSITIVE";
    break;
    case result::NEGATIVE:
      os << "NEGATIVE";
    break;
    case result::OPPOSITE_SIGN:
      os << "OPPOSITE_SIGN";
    break;
  }
  return os;
}

void CPU::ADC_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode)
{
   bool immediete = false;
   Word address{};
   Byte operand{};

   switch(_opCode){
      case CPU::INS_ADC_IM :{
         operand = FetchByte(_cycles, _mem);
         immediete = true;
         break;
      }
      case CPU::INS_ADC_ZP :{
         address = getAddr(_cycles, _mem, adressingMode::ZP);
         break;
      }
      case CPU::INS_ADC_ZPX :{
         address = getAddr(_cycles, _mem, adressingMode::ZPX);
         break;
      }
      case CPU::INS_ADC_ABS :{
         address = getAddr(_cycles, _mem, adressingMode::ABS);
         break;
      }
      case CPU::INS_ADC_ABSX :{
         address = getAddr(_cycles, _mem, adressingMode::ABSX);
         break;
      }
      case CPU::INS_ADC_ABSY :{
         address = getAddr(_cycles, _mem, adressingMode::ABSY);
         break;
      }
      case CPU::INS_ADC_INDX :{
         address = getAddr(_cycles, _mem, adressingMode::INDX);
         --_cycles;
         break;
      }
      case CPU::INS_ADC_INDY :{
         address = getAddr(_cycles, _mem, adressingMode::INDY);
         break;
      }
   }
   result before{}, after{};

   if(!immediete)
   {
      operand = ReadByte(_cycles, address, _mem);
   }

   if(!((A>>7) ^ (operand>>7)))   ///dude...  basically this guarantees that only two same singned numbers that would overflow overflow flag set
   {
      before = (result)(A>>7);   ///if it's negative 7th bit is set
   }
   else{
      before = result::OPPOSITE_SIGN;
   }
   
   int wideA_temp = A;

   wideA_temp += operand;
   wideA_temp += C;

   after = (result)((wideA_temp >> 7) & 0b01);   ///if it's negative 7th bit is set. But we have to make is take only this bit instead of everything left from 7th bit

   ///this is a bit verbose and coule easily be shortened but I like it
   if(after != before && before != result::OPPOSITE_SIGN)
   {
      V = 1;
   }
   else
   {
      V = 0;   
   }

   C = (wideA_temp & 0b1'0000'0000) ? 1 : 0;

   A = wideA_temp & 0b11111111;

   Byte flag = (N_f | Z_f);
   SetCustomFlagsWithRegister(Register::A, flag);
}

void CPU::SBC_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode)
{
   bool immediete = false;
   Word address{};
   Byte operand{};

   switch(_opCode){
      case CPU::INS_SBC_IM :{
         operand = FetchByte(_cycles, _mem);
         immediete = true;
         break;
      }
      case CPU::INS_SBC_ZP :{
         address = getAddr(_cycles, _mem, adressingMode::ZP);
         break;
      }
      case CPU::INS_SBC_ZPX :{
         address = getAddr(_cycles, _mem, adressingMode::ZPX);
         break;
      }
      case CPU::INS_SBC_ABS :{
         address = getAddr(_cycles, _mem, adressingMode::ABS);
         break;
      }
      case CPU::INS_SBC_ABSX :{
         address = getAddr(_cycles, _mem, adressingMode::ABSX);
         break;
      }
      case CPU::INS_SBC_ABSY :{
         address = getAddr(_cycles, _mem, adressingMode::ABSY);
         break;
      }
      case CPU::INS_SBC_INDX :{
         address = getAddr(_cycles, _mem, adressingMode::INDX);
         --_cycles;
         break;
      }
      case CPU::INS_SBC_INDY :{
         address = getAddr(_cycles, _mem, adressingMode::INDY);
         break;
      }
   }

   if(!immediete)
   {
      operand = ReadByte(_cycles, address, _mem);
   }

   auto signA       = (A       & OVERFLOW_MASK);
   auto signOperand = (operand & OVERFLOW_MASK);
   auto tempC = (1 - C);
   PRINT("tempC:    ", tempC);
   std::cout<<"tempC:   "<< tempC << std::endl;

   
   PRINT("A before:    ", A);
   PRINT("operand:     ", operand);
   std::cout<<"operand:   "<< tempC << std::endl;
   int wideA_temp = A;
   wideA_temp -= operand;
   wideA_temp -= tempC; ///does this work, or do I need to (1 - C) this mother sucker?
   PRINT("A after:     ", wideA_temp);

   auto signRes = (wideA_temp & OVERFLOW_MASK);

   C = (wideA_temp & 0b1'0000'0000) ? 0 : 1;

   V = 0;
   if( signA != signRes && signOperand == signRes)
   {
      V = 1;
   }

   A = wideA_temp & 0b11111111;

   Byte flag = (N_f | Z_f);
   SetCustomFlagsWithRegister(Register::A, flag);

}

void CPU::CMP_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode)
{
   
   bool immediete = false;
   Word address{};
   Byte operand{};

   switch(_opCode){
      case CPU::INS_CMP_IM :{
         operand = FetchByte(_cycles, _mem);
         immediete = true;
         break;
      }
      case CPU::INS_CMP_ZP :{
         address = getAddr(_cycles, _mem, adressingMode::ZP);
         break;
      }
      case CPU::INS_CMP_ZPX :{
         address = getAddr(_cycles, _mem, adressingMode::ZPX);
         break;
      }
      case CPU::INS_CMP_ABS :{
         address = getAddr(_cycles, _mem, adressingMode::ABS);
         break;
      }
      case CPU::INS_CMP_ABSX :{
         address = getAddr(_cycles, _mem, adressingMode::ABSX);
         break;
      }
      case CPU::INS_CMP_ABSY :{
         address = getAddr(_cycles, _mem, adressingMode::ABSY);
         break;
      }
      case CPU::INS_CMP_INDX :{
         address = getAddr(_cycles, _mem, adressingMode::INDX);
         --_cycles;
         break;
      }
      case CPU::INS_CMP_INDY :{
         address = getAddr(_cycles, _mem, adressingMode::INDY);
         break;
      }
   }

   if(!immediete)
   {
      operand = ReadByte(_cycles, address, _mem);
   }
   
   auto res = A - operand;
   HEX_PRINT("A:        ", bitset_f(A));
   HEX_PRINT("operand:  ", bitset_f(operand));
   HEX_PRINT("res:      ", bitset_f(res));

   Z = (A == operand)         ? 1 : 0;
   C = (A >= operand)         ? 1 : 0;

   ///TODO: fix location of places in which we change flags later

   Byte flag = (N_f);   ///zero is being handled earlier
   SetCustomFlagsWithValue(res, flag);
}

void CPU::CPX_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode)
{

}

void CPU::CPY_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode)
{

}



////////////////////////////////////// Arithmetic
///ADC
void CPU::ADC_IM (u32& _cycles, Mem &_mem){}
void CPU::ADC_ZP (u32& _cycles, Mem &_mem){}
void CPU::ADC_ZPX(u32& _cycles, Mem &_mem){}
void CPU::ADC_ABS(u32& _cycles, Mem &_mem){}
void CPU::ADC_ABSX(u32& _cycles, Mem &_mem){}
void CPU::ADC_ABSY(u32& _cycles, Mem &_mem){}
void CPU::ADC_INDX(u32& _cycles, Mem &_mem){}
void CPU::ADC_INDY(u32& _cycles, Mem &_mem){}

/// SBC
void CPU::SBC_IM (u32& _cycles, Mem &_mem){}
void CPU::SBC_ZP (u32& _cycles, Mem &_mem){}
void CPU::SBC_ZPX(u32& _cycles, Mem &_mem){}
void CPU::SBC_ABS(u32& _cycles, Mem &_mem){}
void CPU::SBC_ABSX(u32& _cycles, Mem &_mem){}
void CPU::SBC_ABSY(u32& _cycles, Mem &_mem){}
void CPU::SBC_INDX(u32& _cycles, Mem &_mem){}
void CPU::SBC_INDY(u32& _cycles, Mem &_mem){}

/// CMP
void CPU::CMP_IM (u32& _cycles, Mem &_mem){}
void CPU::CMP_ZP (u32& _cycles, Mem &_mem){}
void CPU::CMP_ZPX(u32& _cycles, Mem &_mem){}
void CPU::CMP_ABS(u32& _cycles, Mem &_mem){}
void CPU::CMP_ABSX(u32& _cycles, Mem &_mem){}
void CPU::CMP_ABSY(u32& _cycles, Mem &_mem){}
void CPU::CMP_INDX(u32& _cycles, Mem &_mem){}
void CPU::CMP_INDY(u32& _cycles, Mem &_mem){}

///CPX
void CPU::CPX_IM (u32& _cycles, Mem &_mem){}
void CPU::CPX_ZP (u32& _cycles, Mem &_mem){}
void CPU::CPX_ABS(u32& _cycles, Mem &_mem){}

///CPY
void CPU::CPY_IM (u32& _cycles, Mem &_mem){}
void CPU::CPY_ZP (u32& _cycles, Mem &_mem){}
void CPU::CPY_ABS(u32& _cycles, Mem &_mem){}


#undef OVERFLOW_MASK
