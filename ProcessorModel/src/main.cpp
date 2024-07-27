#include "CPU.h"

void createInlineProgram(Mem &);

int main()
{
   ////Here you can see how to use this library

   /// start - boot  
   Mem mem;
   CPU cpu;
   cpu.Reset(mem);   ///I want to explicitly reset memory instead of doing it in constructor
   /// end - boot
   
   std::cout<<"starting loading from file\n";
   mem.loadFromFile("testFile");
   std::cout<<"ending loading from file\n";

   return 0;
}

void createInlineProgram(Mem &_mem)
{
   // start - inline program
   _mem.set(0xFFFC, CPU::INS_JSR);
   _mem.set(0xFFFD, 0x42);
   _mem.set(0xFFFE, 0x42);
   _mem.set(0x4242, CPU::INS_LDA_IM);
   _mem.set(0x4243, 0x69);
   _mem.set(0x4244, CPU::INS_JSR);
   _mem.set(0x4245, 0x69);
   _mem.set(0x4246, 0x69);
   _mem.set(0x6969, CPU::INS_LDA_IM);
   _mem.set(0x696A, 0x6B);
   // end - inline program
};
