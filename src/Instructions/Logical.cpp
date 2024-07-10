#include "CPU.h"

////////////////////////////////////// Logical
///AND
void CPU::AND_IM (u32& _cycles, Mem &_mem)
{
   Byte val  = FetchByte(_cycles, _mem);  ///the fetched byte
   A        &= val;
   Byte flag = (N_f | Z_f); 
   SetCustomFlagsWithRegister(Register::A, flag);
}

void CPU::AND_ZP (u32& _cycles, Mem &_mem)
{
   Word address = getAddr(_cycles, _mem, adressingMode::ZP);
   A                   &= ReadByte(_cycles, address, _mem);
   Byte flag            = (N_f | Z_f); 
   SetCustomFlagsWithRegister(Register::A, flag);
}

void CPU::AND_ZPX(u32& _cycles, Mem &_mem)
{
   Word address = getAddr(_cycles, _mem, adressingMode::ZPX);
   A        &= ReadByte(_cycles, address , _mem);
   Byte flag = (N_f | Z_f); 
   SetCustomFlagsWithRegister(Register::A, flag);
}

void CPU::AND_ABS(u32& _cycles, Mem &_mem)
{
   Word address = getAddr(_cycles, _mem, adressingMode::ABS);
   A           &=    ReadByte(_cycles, address, _mem);
   Byte flag    = (N_f | Z_f); 
   SetCustomFlagsWithRegister(Register::A, flag);
}

void CPU::AND_ABSX(u32& _cycles, Mem &_mem)
{
   Word address = getAddr(_cycles, _mem, adressingMode::ABSX);
   A           &= ReadByte(_cycles, address, _mem);
   Byte flag    = (N_f | Z_f); 
   SetCustomFlagsWithRegister(Register::A, flag);
}

void CPU::AND_ABSY(u32& _cycles, Mem &_mem)
{  
   Word address = getAddr(_cycles, _mem, adressingMode::ABSY);
   A           &=   ReadByte(_cycles, address, _mem);
   Byte flag    = (N_f | Z_f); 
   SetCustomFlagsWithRegister(Register::A, flag);
}

void CPU::AND_INDX(u32& _cycles, Mem &_mem)
{
   Word address = getAddr(_cycles, _mem, adressingMode::INDX);
   A          &= ReadByte(_cycles, address, _mem);
   Byte flag   = (N_f | Z_f); 
   SetCustomFlagsWithRegister(Register::A, flag);
}

void CPU::AND_INDY(u32& _cycles, Mem &_mem)
{
   Word address = getAddr(_cycles, _mem, adressingMode::INDY);
   A        &= ReadByte(_cycles, address, _mem);
   Byte flag = (N_f | Z_f); 
   SetCustomFlagsWithRegister(Register::A, flag);
}

///EOR
void CPU::EOR_IM (u32& _cycles, Mem &_mem)
{
   Byte val  = FetchByte(_cycles, _mem);  ///the fetched byte
   A        ^= val;
   Byte flag = (N_f | Z_f); 
   SetCustomFlagsWithRegister(Register::A, flag);
}

void CPU::EOR_ZP (u32& _cycles, Mem &_mem)
{
   Word address = getAddr(_cycles, _mem, adressingMode::ZP);
   A                   ^= ReadByte(_cycles, address, _mem);
   Byte flag            = (N_f | Z_f); 
   SetCustomFlagsWithRegister(Register::A, flag);

}

void CPU::EOR_ZPX(u32& _cycles, Mem &_mem)
{
   Word address = getAddr(_cycles, _mem, adressingMode::ZPX);
   A        ^= ReadByte(_cycles, address, _mem);
   Byte flag = (N_f | Z_f); 
   SetCustomFlagsWithRegister(Register::A, flag);

}

void CPU::EOR_ABS(u32& _cycles, Mem &_mem)
{
   Word address = getAddr(_cycles, _mem, adressingMode::ABS);
   A           ^= ReadByte(_cycles, address, _mem);
   Byte flag    = (N_f | Z_f); 
   SetCustomFlagsWithRegister(Register::A, flag);

}

void CPU::EOR_ABSX(u32& _cycles, Mem &_mem)
{
   Word address = getAddr(_cycles, _mem, adressingMode::ABSX);
   A           ^=  ReadByte(_cycles, address, _mem);
   Byte flag    = (N_f | Z_f); 
   SetCustomFlagsWithRegister(Register::A, flag);
}

void CPU::EOR_ABSY(u32& _cycles, Mem &_mem)
{
   Word address = getAddr(_cycles, _mem, adressingMode::ABSY);
   A           ^= ReadByte(_cycles, address, _mem);
   Byte flag    = (N_f | Z_f); 
   SetCustomFlagsWithRegister(Register::A, flag);
}

void CPU::EOR_INDX(u32& _cycles, Mem &_mem)
{
   Word address = getAddr(_cycles, _mem, adressingMode::INDX);
   A          ^= ReadByte(_cycles, address, _mem);
   Byte flag   = (N_f | Z_f); 
   SetCustomFlagsWithRegister(Register::A, flag);
}

void CPU::EOR_INDY(u32& _cycles, Mem &_mem)
{
   Word address = getAddr(_cycles, _mem, adressingMode::INDY);
   A        ^= ReadByte(_cycles, address, _mem);
   Byte flag = (N_f | Z_f); 
   SetCustomFlagsWithRegister(Register::A, flag);
}


///ORA 
void CPU::ORA_IM (u32& _cycles, Mem &_mem)
{
   Byte val  = FetchByte(_cycles, _mem);  ///the fetched byte
   A        |= val;
   Byte flag = (N_f | Z_f); 
   SetCustomFlagsWithRegister(Register::A, flag);
}

void CPU::ORA_ZP (u32& _cycles, Mem &_mem)
{
   Word address = getAddr(_cycles, _mem, adressingMode::ZP);
   A                   |= ReadByte(_cycles, address, _mem);
   Byte flag            = (N_f | Z_f); 
   SetCustomFlagsWithRegister(Register::A, flag);

}

void CPU::ORA_ZPX(u32& _cycles, Mem &_mem)
{
   Word address = getAddr(_cycles, _mem, adressingMode::ZPX);
   A        |= ReadByte(_cycles, address, _mem);
   Byte flag = (N_f | Z_f); 
   SetCustomFlagsWithRegister(Register::A, flag);

}

void CPU::ORA_ABS(u32& _cycles, Mem &_mem)
{
   Word address = getAddr(_cycles, _mem, adressingMode::ABS);
   A           |=  ReadByte(_cycles, address, _mem);
   Byte flag    = (N_f | Z_f); 
   SetCustomFlagsWithRegister(Register::A, flag);

}

void CPU::ORA_ABSX(u32& _cycles, Mem &_mem)
{
   Word address = getAddr(_cycles, _mem, adressingMode::ABSX);
   A           |=  ReadByte(_cycles, address, _mem);
   Byte flag    = (N_f | Z_f); 
   SetCustomFlagsWithRegister(Register::A, flag);
}

void CPU::ORA_ABSY(u32& _cycles, Mem &_mem)
{
   Word address = getAddr(_cycles, _mem, adressingMode::ABSY);
   A           |=  ReadByte(_cycles, address, _mem);
   Byte flag    = (N_f | Z_f); 
   SetCustomFlagsWithRegister(Register::A, flag);
}

void CPU::ORA_INDX(u32& _cycles, Mem &_mem)
{
   Word address = getAddr(_cycles, _mem, adressingMode::INDX);
   A          |= ReadByte(_cycles, address, _mem);
   Byte flag   = (N_f | Z_f); 
   SetCustomFlagsWithRegister(Register::A, flag);
}

void CPU::ORA_INDY(u32& _cycles, Mem &_mem)
{
   Word address = getAddr(_cycles, _mem, adressingMode::INDY);
   A        |= ReadByte(_cycles, address, _mem);
   Byte flag = (N_f | Z_f); 
   SetCustomFlagsWithRegister(Register::A, flag);
}

/// BIT
void CPU::BIT_ZP (u32& _cycles, Mem &_mem)
{
   Word address = getAddr(_cycles, _mem, adressingMode::ZP);
   Byte operand = ReadByte(_cycles, address, _mem);
   Byte temp = A & operand; 

   Byte flag = 0b00000000;
   if(temp == 0){
      flag |= Z_f;
   }
   if(operand & N_f){
      N = 1;
   }
   else{
      N = 0;
   }
   if(operand & V_f){
      V = 1;
   }
   else{
      V = 0;   
   }
   SetCustomFlagsWithRegister(Register::A, flag);
}

void CPU::BIT_ABS(u32& _cycles, Mem &_mem)
{
   Word address = getAddr(_cycles, _mem, adressingMode::ABS);
   Byte operand = ReadByte(_cycles, address, _mem);
   Byte temp = A & operand;

   Byte flag = 0b00000000;
   if(temp == 0){
      flag |= Z_f;
   }
   if(operand & N_f){
      N = 1;
   }
   else{
      N = 0;
   }
   if(operand & V_f){
      V = 1;
   }
   else{
      V = 0;   
   }
   SetCustomFlagsWithRegister(Register::A, flag);
}

