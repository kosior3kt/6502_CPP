#include "CPU.h"

void CPU::JSR_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode)
{
   Word address = getAddr(_cycles, _mem, adressingMode::ABS);
   pushWordToStack(_cycles, _mem, PC);
   HEX_PRINT("jumping there: ", address);
   PC = address;
}

void CPU::RTS_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode)
{
   auto retAddr = popWordFromStack(_cycles, _mem);
   PC = retAddr;
   HEX_PRINT("jumping there: ", retAddr);
   --_cycles;
}

void CPU::JMP_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode)
{
   Word address;
   switch(_opCode){
      case INS_JMP_ABS:{
         address = getAddr(_cycles, _mem, adressingMode::ABS);
         break;
      }
      case INS_JMP_IND:{
         address = getAddr(_cycles, _mem, adressingMode::IND);
         address = ReadWord(_cycles, address, _mem);
         break;
      }
   }
   HEX_PRINT("jumping there: ", address);
   PC = address;
   --_cycles;
}

/////////////////////////////////////// JSR
void CPU::JSR(u32 &_cycles, Mem &_mem)
{
   Word address = getAddr(_cycles, _mem, adressingMode::ABS);
   pushWordToStack(_cycles, _mem, PC);
   PC = address;
}
/// JMP
void CPU::JMP_ABS(u32 &_cycles, Mem &_mem)
{
   Word address = getAddr(_cycles, _mem, adressingMode::ABS);
   --_cycles;
   PC = address;
}

void CPU::JMP_IND(u32 &_cycles, Mem &_mem)
{
   Word address = getAddr(_cycles, _mem, adressingMode::IND);
   Word setAddrEffective = ReadWord(_cycles, address, _mem);
   --_cycles;
   PC = setAddrEffective;
}

/// RTS
void CPU::RTS(u32 &_cycles, Mem &_mem)
{
   auto retAddr = popWordFromStack(_cycles, _mem);
   PC = retAddr;
   --_cycles;
}
