#include "CPU.h"

//////////////////////////////////// NULL not to be confused with NOP - NULL is
/// literally absent of instruction

void CPU::NULL_INS(u32 &_cycles, Mem &_mem)
{
   [[maybe_unused]] Byte val = fetchByte(_cycles, _mem);
   return;
}

