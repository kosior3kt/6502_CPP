#include "CPU.h"

void CPU::Reset(Mem &_mem)
{
   PC = 0xFFFC;
   SP = 0x0100;
   C = Z = I = D = B = V = N = 0;
   A = X = Y = 0;
   _mem.Initialise();
}

[[nodiscard]] Byte CPU::FetchByte(u32 &_cycles, const Mem &_mem)
{
   Byte data = _mem[PC];
   ++PC;
   --_cycles;
   return data;
}

[[nodiscard]] Word CPU::FetchWord(u32 &_cycles, const Mem &_mem)
{
   // 6502 is little endian - so the first is the least significant byte
   Word data = _mem[PC];
   data |= (_mem[PC] << 8);
   PC += 2;
   _cycles -= 2;
   /// good old endiannes ifdef here (if you care ofc...)
   return data;
}

[[nodiscard]] Byte CPU::ReadByte(u32 &_cycles, const Byte &_addr, const Mem &_mem)
{
   Byte data = _mem[_addr];
   --_cycles;
   return data;
}

[[nodiscard]] Byte CPU::ReadByte(u32 &_cycles, const Word &_addr, const Mem &_mem)
{
   Byte data = _mem[_addr];
   --_cycles;
   return data;
}

 void CPU::WriteByte(
    u32 &_cycles, const Word &_addr, Mem &_mem, const Byte &_val
)
{
   _mem.debug_set(_addr, _val);
   --_cycles;
}

void CPU::WriteByte(
    u32 &_cycles, const Byte &_addr, Mem &_mem, const Byte &_val
)
{
   _mem.debug_set(_addr, _val);
   --_cycles;
}

[[nodiscard]] Byte CPU::ReadWord(u32 &_cycles, const Byte &_addr, const Mem &_mem)
{
   assert(_addr + 0x0001 < Mem::MAX_MEM);
   Word ea; /// ea => effective address
   Byte eaLow  = ReadByte(_cycles, _addr, _mem);
   Byte eaHigh = ReadByte(_cycles, _addr, _mem);
   ea          = eaLow + (eaHigh << 8);
   return ea;
}

[[nodiscard]] Byte CPU::ReadWord(u32 &_cycles, const Word &_addr, const Mem &_mem)
{
   assert(_addr + 0x0001 < Mem::MAX_MEM);
   Word ea;
   Byte eaLow  = ReadByte(_cycles, _addr, _mem);
   Byte eaHigh = ReadByte(_cycles, _addr, _mem);
   ea          = eaLow + (eaHigh << 8);
   return ea;
}

void CPU::ApplyToMemory(
    u32 &_cycles, const Word &_addr, Mem &_mem,
    std::function<Byte(const Byte &)> _fun
)
{
   Byte tempVal = ReadByte(_cycles, _addr, _mem);
   WriteByte(_cycles, _addr, _mem, _fun(tempVal));
}

void CPU::ApplyToMemory(
    u32 &_cycles, const Byte &_addr, Mem &_mem,
    std::function<Byte(const Byte &)> _fun
)
{
   Byte tempVal = ReadByte(_cycles, _addr, _mem);
   WriteByte(_cycles, _addr, _mem, _fun(tempVal));
}

void CPU::SetNZWithRegister(const Register &_reg)
{
   Byte temp;
   switch(_reg)
   {
   case Register::A:
      temp = A;
      break;
   case Register::X:
      temp = X;
      break;
   case Register::Y:
      temp = Y;
      break;
   }
   Z = (temp == 0);
   N = ((Byte)(temp & 0b10000000)) > 0;
}

void CPU::SetNZWithValue(const Byte &_val)   ///this thing exists only so that I can do less in lambdas
{
   Z = (_val == 0);
   N = ((Byte)(_val & 0b10000000)) > 0;
}

void CPU::SetCustomFlagsWithValue(const Byte &_val, Byte &_flags)
{
   ///will fill this later on
   if(_flags & C_f)
   {
   }
   if(_flags & Z_f)
   {
      Z = (_val == 0);
   }
   if(_flags & I_f)
   {
   }
   if(_flags & D_f)
   {
   }
   if(_flags & B_f)
   {
   }
   if(_flags & V_f)
   {
   }
   if(_flags & N_f)
   {
      N = ((Byte)(_val & 0b10000000)) > 0;
   }
}

void CPU::SetCustomFlagsWithRegister(const Register &_reg, Byte &_flags)
{

   Byte val;
   switch(_reg)
   {
   case Register::A:
      val = A;
      break;
   case Register::X:
      val = X;
      break;
   case Register::Y:
      val = Y;
      break;
   }

   if(_flags & C_f)
   {
   }
   if(_flags & Z_f)
   {
      Z = (val == 0);
   }
   if(_flags & I_f)
   {
   }
   if(_flags & D_f)
   {
   }
   if(_flags & B_f)
   {
   }
   if(_flags & V_f)
   {
   }
   if(_flags & N_f)
   {
      N = ((Byte)(val & 0b10000000)) > 0;
   }
}
