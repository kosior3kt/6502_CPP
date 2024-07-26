#include "CPU.h"

#define ALMOST_OVERFLOW 0b10000000  ///when overflow is to occure we need to do some flags magic
#define BINARY_ONE      0b00000001


void CPU::ASL_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode)
{
   Word address{};

   switch(_opCode){
      case CPU::INS_ASL_ACC :{
         if(A >= ALMOST_OVERFLOW)
         {
            C = 1;
         }
         A = A << 1;
         safeCycleDecrement(_cycles);
         safeCycleDecrement(_cycles);
         A &= 0b11111110;  //make sure the last bit is beingi filled with 0
         Byte flag = (N_f | Z_f); /// does this work(?)
         setCustomFlagsWithRegister(Register::A, flag);
         return;
      }
      case CPU::INS_ASL_ZP :{
         address = getAddr(_cycles, _mem, adressingMode::ZP);
         break;
      }
      case CPU::INS_ASL_ZPX :{
         address = getAddr(_cycles, _mem, adressingMode::ZPX);
         break;
      }
      case CPU::INS_ASL_ABS :{
         address = getAddr(_cycles, _mem, adressingMode::ABS);
         break;
      }
      case CPU::INS_ASL_ABSX :{
         address = getAddr(_cycles, _mem, adressingMode::ABSX);
         break;
      }
   }
   
   applyToMemory(_cycles, address, _mem, 
       [this](const Byte &_val) -> Byte 
       { 
            if(_val >= ALMOST_OVERFLOW) {
               C = 1;
            }
            auto temp = _val << 1;
            temp &= 0b11111110;  //make sure the last bit is beingi filled with 0
            Byte flag = (N_f | Z_f); 
            setCustomFlagsWithValue(_val, flag);
            return temp;
        }
   );
}

void CPU::LSR_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode)
{
   Word address{};

   switch(_opCode){
      case CPU::INS_LSR_ACC :{
         if(A & BINARY_ONE)
         {
            C = 1;
         }
         A = A >> 1;
         safeCycleDecrement(_cycles);
         safeCycleDecrement(_cycles);
         A &= 0b01111111;  //make sure the last bit is beingi filled with 0
         Byte flag =  (N_f | Z_f); /// does this work(?)
         setCustomFlagsWithRegister(Register::A, flag);
         return;
      }
      case CPU::INS_LSR_ZP :{
         address = getAddr(_cycles, _mem, adressingMode::ZP);
         break;
      }
      case CPU::INS_LSR_ZPX :{
         address = getAddr(_cycles, _mem, adressingMode::ZPX);
         break;
      }
      case CPU::INS_LSR_ABS :{
         address = getAddr(_cycles, _mem, adressingMode::ABS);
         break;
      }
      case CPU::INS_LSR_ABSX :{
         address = getAddr(_cycles, _mem, adressingMode::ABSX);
         break;
      }
   }
   
   applyToMemory(_cycles, address, _mem, 
       [this](const Byte &_val) -> Byte 
       { 
            if(_val & BINARY_ONE) {
               C = 1;
            }
            auto temp = _val >> 1;
            temp &= 0b01111111;  //make sure the last bit is beingi filled with 0
            Byte flag = (N_f | Z_f); 
            setCustomFlagsWithValue(_val, flag);
            return temp;
         }
   );
}

void CPU::ROL_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode)
{
   Word address{};

   switch(_opCode){
      case CPU::INS_ROL_ACC :{
         auto tempC = C;
         if(A >= ALMOST_OVERFLOW)
         {
            C = 1;
         }
         A = A << 1;
         A |= tempC;
         safeCycleDecrement(_cycles);
         safeCycleDecrement(_cycles);
         Byte flag =  (N_f | Z_f); /// does this work(?)
         setCustomFlagsWithRegister(Register::A, flag);
         return;
      }
      case CPU::INS_ROL_ZP :{
         address = getAddr(_cycles, _mem, adressingMode::ZP);
         break;
      }
      case CPU::INS_ROL_ZPX :{
         address = getAddr(_cycles, _mem, adressingMode::ZPX);
         break;
      }
      case CPU::INS_ROL_ABS :{
         address = getAddr(_cycles, _mem, adressingMode::ABS);
         break;
      }
      case CPU::INS_ROL_ABSX :{
         address = getAddr(_cycles, _mem, adressingMode::ABSX);
         break;
      }
   }
   
   applyToMemory(_cycles, address, _mem, 
       [this](const Byte &_val) -> Byte 
       { 
            auto tempC = C;
            if(_val >= ALMOST_OVERFLOW) {
               C = 1;
            }
            auto temp = _val << 1;
            temp |= tempC;
            Byte flag = (N_f | Z_f); 
            setCustomFlagsWithValue(_val, flag);
            return temp;
         }
   );
}

void CPU::ROR_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode)
{
   Word address{};

   switch(_opCode){
      case CPU::INS_ROR_ACC :{
         auto tempC = C;
         if(A & BINARY_ONE)
         {
            C = 1;
         }
         A = A >> 1;
         A |= tempC << 7;
         safeCycleDecrement(_cycles);
         safeCycleDecrement(_cycles);
         Byte flag =  (N_f | Z_f); /// does this work(?)
         setCustomFlagsWithRegister(Register::A, flag);
         return;
      }
      case CPU::INS_ROR_ZP :{
         address = getAddr(_cycles, _mem, adressingMode::ZP);
         break;
      }
      case CPU::INS_ROR_ZPX :{
         address = getAddr(_cycles, _mem, adressingMode::ZPX);
         break;
      }
      case CPU::INS_ROR_ABS :{
         address = getAddr(_cycles, _mem, adressingMode::ABS);
         break;
      }
      case CPU::INS_ROR_ABSX :{
         address = getAddr(_cycles, _mem, adressingMode::ABSX);
         break;
      }
   }
   
   applyToMemory(_cycles, address, _mem, 
       [this](const Byte &_val) -> Byte 
       { 
            auto tempC = C;
            if(_val & BINARY_ONE) {
               C = 1;
            }
            auto temp = _val >> 1; 
            temp |= tempC << 7;
            Byte flag = (N_f | Z_f); 
            setCustomFlagsWithValue(_val, flag);
            return temp;
         }
   );
}

#undef ALMOST_OVERFLOW 
#undef BINARY_ONE      

