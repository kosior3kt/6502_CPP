#include "CPU.h"


void CPU::BRK(u32 &_cycles, Mem &_mem, const Byte& _opCode)
{
   // HEX_PRINT("value of A: ", A);
   // HEX_PRINT("value of C: ", C);
   // HEX_PRINT("value of V: ", V);
   PC++; //this thing is 2 cycle instruction or sth, blah balh blah
   pushWordToStack(_cycles, _mem, PC);
   CPU::PHP(_cycles, _mem, static_cast<const Byte>(NULL));   ///yeah, sure, why not?
                                                            
   // HEX_PRINT("value of now A: ", A);
   // HEX_PRINT("value of now C: ", C);
   // HEX_PRINT("value of now V: ", V);

   Word interruptVectorAddr = 0xFFFE;
   auto newPCAddr = readWord(_cycles, interruptVectorAddr, _mem);
   /////now we can do 
   PC = newPCAddr;
   I = 1;

   
   HEX_PRINT("\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!BRK CALLED!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
   HEX_PRINT("number of cycles: ", _cycles);
}

void CPU::NOP(u32 &_cycles, Mem &_mem, const Byte& _opCode)
{
   PC++;       //just spinning bby
}

void CPU::RTI(u32 &_cycles, Mem &_mem, const Byte& _opCode)
{
   HEX_PRINT("\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!RTI CALLED!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
   CPU::PLP(_cycles, _mem, static_cast<const Byte>(NULL));
   auto retrievedPC = popWordFromStack(_cycles, _mem);
   PC = retrievedPC;
}

void CPU::NOTHING_(u32 &_cycles, Mem &_mem, const Byte& _opCode)
{
   ///just does nothing, so may as well set _cycles to zero
   _cycles = 0;
}

