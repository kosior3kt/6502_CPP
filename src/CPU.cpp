#include "CPU.h"

void CPU::Reset(Mem &_mem)
{
   PC = 0xFFFC;
   SP = 0x0100;
   C = Z = I = D = B = V = N = 0;
   A = X = Y = 0;
   _mem.Initialise();
}

Byte CPU::FetchByte(u32 &_cycles, const Mem &_mem)
{
   Byte data = _mem[PC];
   ++PC;
   --_cycles;
   return data;
}

Word CPU::FetchWord(u32 &_cycles, const Mem &_mem)
{
   // 6502 is little endian - so the first is the least significant byte
   Word data = _mem[PC];
   data |= (_mem[PC] << 8);
   PC += 2;
   _cycles -= 2;
   /// good old endiannes ifdef here (if you care ofc...)
   return data;
}

Byte CPU::ReadByte(u32 &_cycles, const Byte &_addr, const Mem &_mem)
{
   Byte data = _mem[_addr];
   --_cycles;
   return data;
}

void CPU::LDASetStatus()
{
   Z = (A == 0);
   N = (A & 0b10000000) > 0; /// is this correct?
}

s32 CPU::Execute(u32 _cycles, Mem &_mem)
{
   while(_cycles)
   {
      Byte inst = FetchByte(_cycles, _mem);
      switch(inst)
      {
      case INS_LDA_IM:
      {
         Byte val = FetchByte(_cycles, _mem);
         A        = val;
         LDASetStatus();
      }
      break;

      case INS_LDA_ZP:
      {
         Byte zeroPageAddress = FetchByte(_cycles, _mem);
         A                    = ReadByte(_cycles, zeroPageAddress, _mem);
         LDASetStatus();
      }
      break;

      case INS_LDA_ZPX:
      {
         Byte zeroPageAddress = FetchByte(_cycles, _mem);
         zeroPageAddress += X;
         if(zeroPageAddress > _mem.MAX_MEM)
         {
            std::cout << "instrukcja LDA ZPX przekroczyla obszar pamieci";
            return _cycles;
         }
         A = ReadByte(_cycles, zeroPageAddress, _mem);
         LDASetStatus();
      }
      break;
      case INS_JSR:

      {
         Word subRoutineAddr = FetchWord(_cycles, _mem);
         _mem.writeWord(_cycles, SP + 1, PC - 1);
         //_mem.writeWord(_cycles, SP , PC - 1);
         PC = subRoutineAddr;
         --_cycles;
      }
      break;

      default:
      {
         printf("Not handled %d\n", inst);
      }
      break;
      }
   }
   return _cycles;
}
