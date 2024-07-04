#include "CPU.h"



/////////////////////////////////////// JSR
void CPU::JSR(u32 &_cycles, Mem &_mem)
{
   Word subRoutineAddr = FetchWord(_cycles, _mem);
   pushWordToStack(_cycles, _mem, PC);
   
   PC = subRoutineAddr;
}
/// JMP
void CPU::JMP_ABS(u32 &_cycles, Mem &_mem)
{
   auto setAddr = FetchWord(_cycles, _mem);
   --_cycles;
   PC = setAddr;
}

void CPU::JMP_IND(u32 &_cycles, Mem &_mem)
{
   Word setAddr = FetchWord(_cycles, _mem);
   Word setAddrEffective = ReadWord(_cycles, setAddr, _mem);
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
