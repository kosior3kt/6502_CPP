#include "CPU.h"

void CPU::safeCycleDecrement(u32& _cycles)
{
   _cycles += (-!!_cycles);
}

void CPU::Reset(Mem &_mem, const Word& _PC_start)  ///_PC_start is by deafult 0xFFFC
{
   PC = _PC_start;
   SP = 0xFF;
   C = Z = I = D = B = V = N = 0;
   A = X = Y = 0;
   _mem.initialise();
}

[[nodiscard]] 
Byte CPU::fetchByte(u32 &_cycles, const Mem &_mem)
{
   Byte data = _mem[PC];
   HEX_PRINT("address of the next fetched byte: ", (int)PC);
   HEX_PRINT("value at this address: ", (int)_mem[PC]);
   ++PC;
   safeCycleDecrement(_cycles);
   return data;
}

[[nodiscard]] 
Word CPU::fetchWord(u32 &_cycles, const Mem &_mem)
{
   // 6502 is little endian - so the first is the least significant byte
   auto dataLow = _mem[PC];
   ++PC;
   auto dataHigh = _mem[PC];
   Word data = dataLow + (dataHigh << 8);
   ++PC;
   safeCycleDecrement(_cycles);
   safeCycleDecrement(_cycles);
   /// good old endiannes ifdef here (if you care ofc...)
   return data;
}

[[nodiscard]] 
Byte CPU::readByte(u32 &_cycles, const Byte &_addr, const Mem &_mem)
{
   Byte data = _mem[_addr];
   safeCycleDecrement(_cycles);
   return data;
}

[[nodiscard]] 
Byte CPU::readByte(u32 &_cycles, const Word &_addr, const Mem &_mem)
{
   Byte data = _mem[_addr];
   safeCycleDecrement(_cycles);
   return data;
}

void CPU::writeByte( u32 &_cycles, const Word &_addr, Mem &_mem, const Byte &_val)
{
   _mem.set(_addr, _val);  ///TODO: create different mechanism for this later
   safeCycleDecrement(_cycles);
}

void CPU::writeByte( u32 &_cycles, const Byte &_addr, Mem &_mem, const Byte &_val)
{
   _mem.set(_addr, _val);
   safeCycleDecrement(_cycles);
}

void CPU::writeWord( u32 &_cycles, const Byte &_addr, Mem &_mem, const Word&_val)
{
   _mem.set(_addr, (_val & 0xFF));
   _mem.set(_addr + 1, (_val << 8));
   safeCycleDecrement(_cycles);
   safeCycleDecrement(_cycles);
}

void CPU::writeWord( u32 &_cycles, const Word &_addr, Mem &_mem, const Word&_val)
{
   _mem.set(_addr, (_val & 0xFF));
   _mem.set(_addr + 1, (_val << 8));
   safeCycleDecrement(_cycles);
   safeCycleDecrement(_cycles);
}

[[nodiscard]] 
Word CPU::readWord(u32 &_cycles, const Byte &_addr, const Mem &_mem)
{
   assert(_addr + 0x0001 < MAX_MEM);
   Word ea; /// ea => effective address
   Byte eaHigh  = readByte(_cycles, _addr, _mem);
   Byte eaLow   = readByte(_cycles, _addr, _mem);
   ea          = eaLow + (eaHigh << 8);
   safeCycleDecrement(_cycles);
   safeCycleDecrement(_cycles);
   return ea;
}

[[nodiscard]]
Word CPU::readWord(u32 &_cycles, const Word &_addr, const Mem &_mem)
{
   Word ea;
   Byte eaLow = readByte(_cycles, _addr, _mem);
   Byte eaHigh  = readByte(_cycles, (Word)(_addr + 1), _mem);
   ea          = eaLow + (eaHigh << 8);
   safeCycleDecrement(_cycles);
   safeCycleDecrement(_cycles);
   return ea;
}

void CPU::applyToMemory(
    u32 &_cycles, const Word &_addr, Mem &_mem,
    std::function<Byte(const Byte &)> _fun
)
{
   Byte tempVal = readByte(_cycles, _addr, _mem);
   writeByte(_cycles, _addr, _mem, _fun(tempVal));
}

void CPU::applyToMemory(
    u32 &_cycles, const Byte &_addr, Mem &_mem,
    std::function<Byte(const Byte &)> _fun
)
{
   Byte tempVal = readByte(_cycles, _addr, _mem);
   writeByte(_cycles, _addr, _mem, _fun(tempVal));
}

///depricated
void CPU::setNZWithRegister(const Register &_reg)
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

///depricated
void CPU::setNZWithValue(const Byte &_val
) /// this thing exists only so that I can do less in lambdas
{
   Z = (_val == 0);
   N = ((Byte)(_val & 0b10000000)) > 0;
}

void CPU::setCustomFlagsWithValue(const Byte &_val, Byte &_flags)
{
   /// will fill this later on
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

void CPU::setCustomFlagsWithRegister(const Register &_reg, Byte &_flags)
{

   ///TODO: fix this garbage later...
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
      C = 1;
   }
   if(_flags & Z_f)
   {
      Z = (val == 0);
   }
   if(_flags & I_f)
   {
      I = 1;
   }
   if(_flags & D_f)
   {
      D = 1;
   }
   if(_flags & B_f)
   {
      B = 1;
   }
   if(_flags & V_f)
   {
      V = 1;
   }
   if(_flags & N_f)
   {
      N = ((Byte)(val & 0b10000000)) > 0;
   }
}

////////stack
void CPU::pushByteToStack(u32& _cycles, Mem& _mem, const Byte& _val) ///those should use one more cycle i believ
{
   auto addr = 0x0100 + SP;   ///safe, cause SP is Byte now
   _mem.set(addr, _val);
   safeCycleDecrement(_cycles);
   --SP;
   safeCycleDecrement(_cycles);
   HEX_PRINT("memory of the saved thing: ", addr);
}

void CPU::pushWordToStack(u32& _cycles, Mem& _mem, const Word& _val) ///those should use one more cycle i believ
{
   const Byte toPushLow  = (Byte)(_val);
   const Byte toPushHigh = (Byte)(_val>> 8);

   pushByteToStack(_cycles, _mem, toPushLow);
   pushByteToStack(_cycles, _mem, toPushHigh);
   //safeCycleDecrement(_cycles);
}

[[nodiscard]]
Byte CPU::popByteFromStack(u32& _cycles, Mem& _mem) ///those should use one more cycle i believ
{
   ++SP;
   auto addr = 0x0100 + SP;   ///safe, cause SP is Byte now
   safeCycleDecrement(_cycles);
   if(SP > 255) return 0; ///and cry in the darkness. Alone
   safeCycleDecrement(_cycles);
   return _mem.at(addr);
}

[[nodiscard]]
Word CPU::popWordFromStack(u32& _cycles, Mem& _mem) ///those should use one more cycle i believe
{
    const Byte retAddrHigh = popByteFromStack(_cycles, _mem);
    const Byte retAddrLow = popByteFromStack(_cycles, _mem);
    Word retAddr = retAddrLow | retAddrHigh << 8;

   safeCycleDecrement(_cycles);
   return retAddr;
}

Byte CPU::readByteFromStack(u32& _cycles, Mem& _mem)
{
   auto addr = 0x0100 + SP + 1;   ///we dont want to modify SP cause we are just reading, not poping or pushing
   return _mem.at(addr);
}

Word CPU::readWordFromStack(u32& _cycles, Mem& _mem)
{
    const Byte retAddrHigh = readByteFromStack(_cycles, _mem);
    SP++;
    const Byte retAddrLow = readByteFromStack(_cycles, _mem);
    SP--;
    ///be carefull, I will need to remove this if I ever want to go multithreaded

    Word retAddr = retAddrLow | retAddrHigh << 8;
    return retAddr;
}

void CPU::overwriteByteOnStack(u32& _cycles, Mem& _mem, const Word& _val)
{
   auto addr = 0x0100 + SP;
   _mem.set(addr, _val);
}

void CPU::overwriteWordOnStack(u32& _cycles, Mem& _mem, const Word& _val)
{
   Byte lowToWrite = _val & 0b11110000;
   Byte highToWrite = _val & 0b00001111;

   SP--;
   overwriteByteOnStack(_cycles, _mem, lowToWrite);
   SP++;
   overwriteByteOnStack(_cycles, _mem, highToWrite);
}

/////////////////////////////////addressing

Word CPU::getAddr(u32& _cycles, const Mem& _mem, const adressingMode& _am)
{
   safeCycleDecrement(_cycles);
   ///TODO: figure out cycles for these things later - all of these take at least one I guess...
   switch(_am){
      case adressingMode::ZP:{
         Byte temp = fetchByte(_cycles, _mem);
         HEX_PRINT("number of cycles: ", _cycles);
         return temp;
      }
      case adressingMode::ZPX:{
         safeCycleDecrement(_cycles);
         Byte temp = fetchByte(_cycles, _mem) + X;
         HEX_PRINT("number of cycles: ", _cycles);
         return temp;
      }
      case adressingMode::ZPY:{
         safeCycleDecrement(_cycles);
         Byte temp = fetchByte(_cycles, _mem) + Y;
         HEX_PRINT("number of cycles: ", _cycles);
         return temp;
      }
      case adressingMode::REL:{
         return fetchByte(_cycles, _mem); ///this just return relative address
         HEX_PRINT("number of cycles: ", _cycles);
      }
      case adressingMode::ABS:{
         safeCycleDecrement(_cycles);
         HEX_PRINT("number of cycles: ", _cycles);
         return fetchByte(_cycles, _mem) | fetchByte(_cycles, _mem) << 8;
      }
      case adressingMode::ABSX:{
         HEX_PRINT("number of cycles: ", _cycles);
         return (fetchByte(_cycles, _mem) | fetchByte(_cycles, _mem) << 8) + X;
      }
      case adressingMode::ABSY:{ ///I will take care of crossing page later...
         HEX_PRINT("number of cycles: ", _cycles);
         return (fetchByte(_cycles, _mem) | fetchByte(_cycles, _mem) << 8) + Y;
      }
      case adressingMode::IND:{
         safeCycleDecrement(_cycles);
         HEX_PRINT("number of cycles: ", _cycles);
         return fetchWord(_cycles, _mem); ///this takes two cycles
      }
      case adressingMode::INDX:{
         safeCycleDecrement(_cycles);
         safeCycleDecrement(_cycles);
         safeCycleDecrement(_cycles);
         Byte adress = fetchByte(_cycles, _mem) + X;
         Byte eaLow  = readByte(_cycles, adress, _mem);
         Byte eaHigh = readByte(_cycles, ++adress, _mem);
         if(eaLow + X > 0xFF)
            safeCycleDecrement(_cycles);
         HEX_PRINT("number of cycles: ", _cycles);
         return eaLow + (eaHigh << 8);
      }
      case adressingMode::INDY:{
         safeCycleDecrement(_cycles);
         safeCycleDecrement(_cycles);
         Word adress = fetchByte(_cycles, _mem);
         Byte eaLow  = readByte(_cycles, adress, _mem);
         Byte eaHigh = readByte( _cycles, ++adress, _mem); 
         if(eaLow + Y > 0xFF)
            safeCycleDecrement(_cycles);
         HEX_PRINT("number of cycles: ", _cycles);
         return (eaLow + (eaHigh << 8) + Y);
      }
      default:{
                 ///std::unreachable();   ///ignore this - it actually is just newer feature than my lsp... If u have older compiler just delete it or sth
         break;
      }
   }
}
