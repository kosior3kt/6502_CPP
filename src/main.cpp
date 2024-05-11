#include <cassert>
#include <iostream>
#include <memory>
#include <stdio.h>
#include <stdlib.h>

using Byte = unsigned char;
using Word = unsigned short;

using u32 = unsigned int;

struct Mem
{
      static constexpr u32 MAX_MEM = 1024 * 64;
      Byte Data[MAX_MEM];

      void Initialise()
      {
         for(u32 i = 0; i < MAX_MEM; ++i)
         {
            Data[i] = 0;
         }
      }

      Byte operator[](const u32& _addr) const
      {
         assert(_addr < MAX_MEM);
         return Data[_addr];
      }

      Byte &operator[](const u32& _addr)
      {
         assert(_addr < MAX_MEM);
         return Data[_addr];
      }

      void writeByte(u32& _cycles, const u32& _addr, const u32& _val)
      {
         assert(_addr < MAX_MEM);
         Data[_addr] = _val;
         --_cycles;
      }

      void writeWord(u32& _cycles, const u32& _addr, const Word& _val)
      {
         assert(_addr < MAX_MEM);
         Data[_addr] = _val & 0xFF;
         Data[_addr + 1] = (_val >> 8);
         _cycles -= 2;
      }

      void debug_set(const u32& _addr, const u32& _val)
      {
         assert(_addr < MAX_MEM);
         Data[_addr] = _val;
      }
};

struct CPU
{

      Word PC; /// program counter
      Word SP; /// stack pointer

      Byte A, X, Y; /// registers

      Byte C : 1; // status flag
      Byte Z : 1; // status flag
      Byte I : 1; // status flag
      Byte D : 1; // status flag
      Byte B : 1; // status flag
      Byte V : 1; // status flag
      Byte N : 1; // status flag

      void Reset(Mem &_mem)
      {
         PC = 0xFFFC;
         SP = 0x0100;
         C = Z = I = D = B = V = N = 0;
         A = X = Y = 0;
         _mem.Initialise();
         // ///TODO: take care of this nonsense
         // _mem[0xFFFC] = 0xA9;
         // _mem[0XFFFD] = 0x42;
      }

      Byte FetchByte(u32 &_cycles, const Mem &_mem)
      {
         Byte data = _mem[PC];
         ++PC;
         --_cycles;
         return data;
      }

      Word FetchWord(u32 &_cycles, const Mem &_mem)
      {
         //6502 is little endian - so the first is the least significant byte
         Word data = _mem[PC];
         data |= (_mem[PC] << 8);

         PC += 2 ;
         _cycles -= 2;

         ///good old endiannes ifdef here (if you care ofc...)
         
         return data;
      }

      Byte ReadByte(u32 &_cycles, const Byte &_addr, const Mem &_mem)
      {
         Byte data = _mem[_addr];
         --_cycles;
         return data;
      }

      // [[noreturn]] Byte ReadWord(u32 &_cycles, const Byte &_addr, const Mem &_mem)
      // {
      //    ///will implement this later
      // }

      void LDASetStatus()
      {
         Z = (A == 0);
         N = (A & 0b10000000) > 0; /// is this correct?
      }

      static constexpr Byte INS_LDA_IM  = 0xA9;
      static constexpr Byte INS_LDA_ZP  = 0xA5;
      static constexpr Byte INS_LDA_ZPX = 0xB5;
      static constexpr Byte INS_JSR     = 0x20;

      void Execute(u32 _cycles, Mem &_mem)
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
            } break;

            case INS_LDA_ZP:
            {
               Byte zeroPageAddress = FetchByte(_cycles, _mem);
               A                    = ReadByte(_cycles, zeroPageAddress, _mem);
               LDASetStatus();
            } break;

            case INS_LDA_ZPX:
            {
               Byte zeroPageAddress = FetchByte(_cycles, _mem);
               zeroPageAddress += X;
               if(zeroPageAddress > _mem.MAX_MEM)
               {
                  std::cout
                      << "instrukcja LDA ZPX przekroczyla obszar pamieci";
                  return;
               }
               A = ReadByte(_cycles, zeroPageAddress, _mem);
               LDASetStatus();
            } break;
            case INS_JSR:

            {
               Word subRoutineAddr = FetchWord(_cycles, _mem);
               _mem.writeWord(_cycles, SP + 1, PC - 1);
               //_mem.writeWord(_cycles, SP , PC - 1);
               PC = subRoutineAddr;
               --_cycles;
            } break;

            default:
            {
               printf("Not handled %d\n", inst);
            }
            break;
            }
         }
      }
};

int main()
{
   ///start - boot
   Mem mem;
   CPU cpu;
   cpu.Reset(mem);
   ///end - boot

   // start - inline program
   mem.debug_set(0xFFFC, CPU::INS_JSR);
   mem.debug_set(0xFFFD, 0x42);
   mem.debug_set(0xFFFE, 0x42);
   mem.debug_set(0x4242, CPU::INS_LDA_IM);
   mem.debug_set(0x4243, 0x69);
   // end - inline program

   cpu.Execute(8, mem);

   ///start - test 
   std::cout<<cpu.A<<std::endl;
   ///end - test

   return 0;
}
