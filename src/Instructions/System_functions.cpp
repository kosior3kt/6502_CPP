#include "CPU.h"


void CPU::BRK_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode)
{
   PC++; //this thing is 2 cycle instruction or sth, blah balh blah
   pushWordToStack(_cycles, _mem, PC);
   CPU::PHP_TEST(_cycles, _mem, static_cast<const Byte>(NULL));   ///yeah, sure, why not?

   Word interruptVectorAddr = 0xFFFE;
   auto newPCAddr = ReadWord(_cycles, interruptVectorAddr, _mem);
   /////now we can do 
   PC = newPCAddr;
   I = 1;


   HEX_PRINT("\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!BRK CALLED!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
   HEX_PRINT("number of cycles: ", _cycles);
}

void CPU::NOP_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode)
{
   PC++;       //just spinning bby
}

void CPU::RTI_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode)
{
   CPU::PLP_TEST(_cycles, _mem, static_cast<const Byte>(NULL));
   auto retrievedPC = popWordFromStack(_cycles, _mem);
   PC = retrievedPC;
}

void CPU::NOTHING_(u32 &_cycles, Mem &_mem, const Byte& _opCode)
{
   ///just does nothing, so may as well set _cycles to zero
   _cycles = 0;
}

