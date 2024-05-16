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

Byte CPU::ReadByte(u32 &_cycles, const Word &_addr, const Mem &_mem)
{
   Byte data = _mem[_addr];
   --_cycles;
   return data;
}

Byte CPU::ReadWord(u32 &_cycles, const Byte &_addr, const Mem &_mem)
{
   assert(_addr + 0x0001 < Mem::MAX_MEM);
   Word ea;
   Byte eaLow = ReadByte(_cycles, _addr, _mem);
   Byte eaHigh = ReadByte(_cycles, _addr, _mem);
   ea = eaLow + (eaHigh << 8);
   return ea;
}

Byte CPU::ReadWord(u32 &_cycles, const Word &_addr, const Mem &_mem)
{
   assert(_addr + 0x0001 < Mem::MAX_MEM);
   Word ea;
   Byte eaLow = ReadByte(_cycles, _addr, _mem);
   Byte eaHigh = ReadByte(_cycles, _addr, _mem);
   ea = eaLow + (eaHigh << 8);
   return ea;
}

void CPU::LDASetStatus()
{
   Z = (A == 0);
   N = (A & 0b10000000) > 0; /// is this correct?
}

s32 CPU::execute(u32 _cycles, Mem &_mem)
{
   while(_cycles)
   {
      Byte inst = FetchByte(_cycles, _mem);
      switch(inst)   ///TODO: abstaract this later into a std::map<INS, 'function pointer'>, so that it isnt such a massive boi
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

      case INS_LDA_ABS:
      {
         Word address
             = FetchByte(_cycles, _mem) | FetchByte(_cycles, _mem) << 8;
         A = ReadByte(_cycles, address, _mem);
         LDASetStatus();
      }
      break;

      case INS_LDA_ABSX:
      {
         Byte eaLow   = FetchByte(_cycles, _mem);
         Byte eaHigh  = FetchByte(_cycles, _mem);
         Word address = eaLow + (eaHigh << 8); /// Little endian daddyy
         address += X;
         // address = address % Mem::MAX_MEM;   ///Does it make sense???
         // (spoiler - it didn't)
         if(eaLow + X > 0xFF)
            --_cycles;
         A = ReadByte(_cycles, address, _mem);
         LDASetStatus();
      }
      break;

      case INS_LDA_ABSY:
      {
         Byte eaLow   = FetchByte(_cycles, _mem);
         Byte eaHigh  = FetchByte(_cycles, _mem);
         Word address = eaLow + (eaHigh << 8); /// Little endian daddyy
         address += Y;
         // address = address % Mem::MAX_MEM;   ///Does it make sense???
         if(eaLow + Y > 0xFF)
            --_cycles;
         A = ReadByte(_cycles, address, _mem);
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

      case INS_LDA_INDX:
      {
         Word adress = FetchByte(_cycles, _mem) + X;
         Byte eaLow = ReadByte(_cycles, adress, _mem);
         Byte eaHigh = ReadByte(_cycles, ++adress, _mem);
         Word ea = eaLow + (eaHigh << 8);
         --_cycles;  ///have to add this here
         A = ReadByte(_cycles, ea, _mem);
         LDASetStatus();
      }
      break;

      case INS_LDA_INDY:
      {         
         Word adress = FetchByte(_cycles, _mem);
         Byte eaLow = ReadByte(_cycles, adress, _mem);
         Byte eaHigh = ReadByte(_cycles, ++adress, _mem);      ///TODO: abstract this later on, and find out why this is supposed to be able to cross page
         if(eaLow + Y > 0xFF) --_cycles;
         Word ea = eaLow + (eaHigh << 8) + Y;
         A = ReadByte(_cycles, ea, _mem);
         LDASetStatus();
      }
      break;

      default:
      {
         /// TODO: decide later if we want to panic or sth in such case
         printf("Not handled %d\n", inst);
         return _cycles;
      }
      break;
      }
   }
   return _cycles;
}
