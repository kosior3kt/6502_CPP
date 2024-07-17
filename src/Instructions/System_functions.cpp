#include "CPU.h"


void CPU::BRK_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode)
{
   PC++; //this thing is 2 cycle instruction or sth, blah balh blah
   pushWordToStack(_cycles, _mem, PC);
   CPU::PHP(_cycles, _mem);   ///yeah, sure, why not?

   Word interruptVectorAddr = 0xFFFE;
   auto newPCAddr = ReadWord(_cycles, interruptVectorAddr, _mem);
   /////now we can do 
   PC = newPCAddr;
   I = 1;
}

void CPU::NOP_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode)
{
   PC++;       //just spinning bby
}

void CPU::RTI_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode)
{
   CPU::PLP(_cycles, _mem);
   auto retrievedPC = popWordFromStack(_cycles, _mem);
   PC = retrievedPC;
}


////////////////////////////////////// System Functions
void CPU::BRK (u32& _cycles, Mem &_mem){}
void CPU::NOP (u32& _cycles, Mem &_mem){}
void CPU::RTI (u32& _cycles, Mem &_mem){}
