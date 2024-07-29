#ifndef __INSTRUCTION_CODES__
#define __INSTRUCTION_CODES__

#include <vector>
#include "traits.hpp"
#include <iostream>
#include "defines.h"

#define am adressingMode


///this thing is scarry af, please dont kill me for introducing it xD
class Addressable TRAIT
{
   virtual const Byte getOPCode(const adressingMode _addr);
};

////////////////////////////////////// Load/Store
/// LDA instructions


struct LDA IMPL(Addressable)
{

   const Byte getOPCode(const adressingMode _addr)
   {
      switch(_addr)
      {
         case am::IM:
            return 0xA9;
         case am::ZP:
            return 0xA5;
         case am::ABS:
            return 0xAD;
         case am::ZPX:
            return 0xB5;
         case am::ABSY:
            return 0xB9;
         case am::ABSX:
            return 0xBD;
         case am::INDX:
            return 0xA1;
         case am::INDY:
            return 0xB1;
         default:
            std::cout<<"unexpected addressing mode for LDA instruction";
            exit(-1);
      }   
   }
};


struct LDX IMPL(Addressable)
{
   const Byte getOPCode(const adressingMode _addr) override
   {
      switch(_addr)
      {
         case am::IM:
            return 0xA2;
         case am::ZP:
            return 0xA6;
         case am::ABS:
            return 0xAE;
         case am::ZPY:
            return 0xB6;
         case am::ABSY:
            return 0xB9;
         default:
            std::cout<<"unexpected addressing mode for LDX instruction";
            exit(-1);
      }   
   }
};

struct LDY IMPL(Addressable)
{
   const Byte getOPCode(const adressingMode _addr) override
   {
      switch(_addr)
      {
         case am::IM:
            return 0xA0;
         case am::ZP:
            return 0xA4;
         case am::ABS:
            return 0xAC;
         case am::ZPY:
            return 0xB4;
         case am::ABSY:
            return 0xBC;
         default:
            std::cout<<"unexpected addressing mode for LDY instruction";
            exit(-1);
      }   
   }
};

struct STA IMPL(Addressable)
{
   const Byte getOPCode(const adressingMode _addr) override
   {
      switch(_addr)
      {
         case am::ZP:
            return 0x85;
         case am::ZPX:
            return 0x95;
         case am::ABS:
            return 0x8D;
         case am::ABSX:
            return 0x9D;
         case am::ABSY:
            return 0x99;
         case am::INDX:
            return 0x81;
         case am::INDY:
            return 0x91;
         default:
            std::cout << "unexpected addressing mode for STA instruction";
            exit(-1);
      }   
   }
};

struct STX IMPL(Addressable)
{
   const Byte getOPCode(const adressingMode _addr) override
   {
      switch(_addr)
      {
         case am::ZP:
            return 0x86;
         case am::ZPY:
            return 0x96;
         case am::ABS:
            return 0x8E;
         default:
            std::cout << "unexpected addressing mode for STX instruction";
            exit(-1);
      }   
   }
};

struct STY IMPL(Addressable)
{
   const Byte getOPCode(const adressingMode _addr) override
   {
      switch(_addr)
      {
         case am::ZP:
            return 0x84;
         case am::ZPX:
            return 0x94;
         case am::ABS:
            return 0x8C;
         default:
            std::cout << "unexpected addressing mode for STY instruction";
            exit(-1);
      }   
   }
};

struct INC IMPL(Addressable)
{
   const Byte getOPCode(const adressingMode _addr) override
   {
      switch(_addr)
      {
         case am::ZP:
            return 0xE6;
         case am::ZPX:
            return 0xF6;
         case am::ABS:
            return 0xEE;
         case am::ABSX:
            return 0xFE;
         default:
            std::cout << "unexpected addressing mode for INC instruction";
            exit(-1);
      }   
   }
};

struct INX IMPL(Addressable)
{
   const Byte getOPCode(const adressingMode _addr) override
   {
      switch(_addr)
      {
         case am::IMP:
            return 0xE8;
         default:
            std::cout << "unexpected addressing mode for INX instruction";
            exit(-1);
      }   
   }
};

struct INY IMPL(Addressable)
{
   const Byte getOPCode(const adressingMode _addr) override
   {
      switch(_addr)
      {
         case am::IMP:
            return 0xC8;
         default:
            std::cout << "unexpected addressing mode for INY instruction";
            exit(-1);
      }   
   }
};

struct DEC IMPL(Addressable)
{
   const Byte getOPCode(const adressingMode _addr) override
   {
      switch(_addr)
      {
         case am::ZP:
            return 0xC6;
         case am::ZPX:
            return 0xD6;
         case am::ABS:
            return 0xCE;
         case am::ABSX:
            return 0xDE;
         default:
            std::cout << "unexpected addressing mode for DEC instruction";
            exit(-1);
      }   
   }
};

struct DEX IMPL(Addressable)
{
   const Byte getOPCode(const adressingMode _addr) override
   {
      switch(_addr)
      {
         case am::IMP:
            return 0xCA;
         default:
            std::cout << "unexpected addressing mode for DEX instruction";
            exit(-1);
      }   
   }
};

struct DEY IMPL(Addressable)
{
   const Byte getOPCode(const adressingMode _addr) override
   {
      switch(_addr)
      {
         case am::IMP:
            return 0x88;
         default:
            std::cout << "unexpected addressing mode for DEY instruction";
            exit(-1);
      }   
   }
};

struct JSR IMPL(Addressable)
{
   const Byte getOPCode(const adressingMode _addr) override
   {
      switch(_addr)
      {
         case am::ABS:
            return 0x20;
         default:
            std::cout << "unexpected addressing mode for JSR instruction";
            exit(-1);
      }   
   }
};

struct RTS IMPL(Addressable)
{
   const Byte getOPCode(const adressingMode _addr) override
   {
      switch(_addr)
      {
         case am::IMP:
            return 0x40;
         default:
            std::cout << "unexpected addressing mode for RTS instruction";
            exit(-1);
      }   
   }
};

struct JMP IMPL(Addressable)
{
   const Byte getOPCode(const adressingMode _addr) override
   {
      switch(_addr)
      {
         case am::ABS:
            return 0x4C;
         case am::IND:
            return 0x6C;
         default:
            std::cout << "unexpected addressing mode for JMP instruction";
            exit(-1);
      }   
   }
};

struct TSX IMPL(Addressable)
{
   const Byte getOPCode(const adressingMode _addr) override
   {
      switch(_addr)
      {
         case am::IMP:
            return 0xBA;
         default:
            std::cout << "unexpected addressing mode for TSX instruction";
            exit(-1);
      }   
   }
};

struct TXS IMPL(Addressable)
{
   const Byte getOPCode(const adressingMode _addr) override
   {
      switch(_addr)
      {
         case am::IMP:
            return 0x9A;
         default:
            std::cout << "unexpected addressing mode for TXS instruction";
            exit(-1);
      }   
   }
};

struct PHA IMPL(Addressable)
{
   const Byte getOPCode(const adressingMode _addr) override
   {
      switch(_addr)
      {
         case am::IMP:
            return 0x08;
         default:
            std::cout << "unexpected addressing mode for PHA instruction";
            exit(-1);
      }   
   }
};

struct PHP IMPL(Addressable)
{
   const Byte getOPCode(const adressingMode _addr) override
   {
      switch(_addr)
      {
         case am::IMP:
            return 0x48;
         default:
            std::cout << "unexpected addressing mode for PHP instruction";
            exit(-1);
      }   
   }
};

struct PLA IMPL(Addressable)
{
   const Byte getOPCode(const adressingMode _addr) override
   {
      switch(_addr)
      {
         case am::IMP:
            return 0x68;
         default:
            std::cout << "unexpected addressing mode for PLA instruction";
            exit(-1);
      }   
   }
};

struct PLP IMPL(Addressable)
{
   const Byte getOPCode(const adressingMode _addr) override
   {
      switch(_addr)
      {
         case am::IMP:
            return 0x28;
         default:
            std::cout << "unexpected addressing mode for PLP instruction";
            exit(-1);
      }   
   }
};

struct TAX IMPL(Addressable)
{
   const Byte getOPCode(const adressingMode _addr) override
   {
      switch(_addr)
      {
         case am::IMP:
            return 0xAA;
         default:
            std::cout << "unexpected addressing mode for TAX instruction";
            exit(-1);
      }   
   }
};

struct TAY IMPL(Addressable)
{
   const Byte getOPCode(const adressingMode _addr) override
   {
      switch(_addr)
      {
         case am::IMP:
            return 0xA8;
         default:
            std::cout << "unexpected addressing mode for TAY instruction";
            exit(-1);
      }   
   }
};

struct TXA IMPL(Addressable)
{
   const Byte getOPCode(const adressingMode _addr) override
   {
      switch(_addr)
      {
         case am::IMP:
            return 0x8A;
         default:
            std::cout << "unexpected addressing mode for TXA instruction";
            exit(-1);
      }   
   }
};

struct TYA IMPL(Addressable)
{
   const Byte getOPCode(const adressingMode _addr) override
   {
      switch(_addr)
      {
         case am::IMP:
            return 0x98;
         default:
            std::cout << "unexpected addressing mode for TYA instruction";
            exit(-1);
      }   
   }
};

struct AND IMPL(Addressable)
{
   const Byte getOPCode(const adressingMode _addr) override
   {
      switch(_addr)
      {
         case am::IM:
            return 0x29;
         case am::ZP:
            return 0x25;
         case am::ZPX:
            return 0x35;
         case am::ABS:
            return 0x2D;
         case am::ABSX:
            return 0x3D;
         case am::ABSY:
            return 0x39;
         case am::INDX:
            return 0x21;
         case am::INDY:
            return 0x31;
         default:
            std::cout << "unexpected addressing mode for AND instruction";
            exit(-1);
      }   
   }
};

struct EOR IMPL(Addressable)
{
   const Byte getOPCode(const adressingMode _addr) override
   {
      switch(_addr)
      {
         case am::IM:
            return 0x49;
         case am::ZP:
            return 0x45;
         case am::ZPX:
            return 0x55;
         case am::ABS:
            return 0x4D;
         case am::ABSX:
            return 0x5D;
         case am::ABSY:
            return 0x59;
         case am::INDX:
            return 0x41;
         case am::INDY:
            return 0x51;
         default:
            std::cout << "unexpected addressing mode for EOR instruction";
            exit(-1);
      }   
   }
};

struct ORA IMPL(Addressable)
{
   const Byte getOPCode(const adressingMode _addr) override
   {
      switch(_addr)
      {
         case am::IM:
            return 0x09;
         case am::ZP:
            return 0x05;
         case am::ZPX:
            return 0x15;
         case am::ABS:
            return 0x0D;
         case am::ABSX:
            return 0x1D;
         case am::ABSY:
            return 0x19;
         case am::INDX:
            return 0x01;
         case am::INDY:
            return 0x11;
         default:
            std::cout << "unexpected addressing mode for ORA instruction";
            exit(-1);
      }   
   }
};

struct BIT IMPL(Addressable)
{
   const Byte getOPCode(const adressingMode _addr) override
   {
      switch(_addr)
      {
         case am::ZP:
            return 0x24;
         case am::ABS:
            return 0x2C;
         default:
            std::cout << "unexpected addressing mode for BIT instruction";
            exit(-1);
      }   
   }
};

struct BCC IMPL(Addressable)
{
   const Byte getOPCode(const adressingMode _addr) override
   {
      switch(_addr)
      {
         case am::REL:
            return 0x90;
         default:
            std::cout << "unexpected addressing mode for BCC instruction";
            exit(-1);
      }   
   }
};

struct BCS IMPL(Addressable)
{
   const Byte getOPCode(const adressingMode _addr) override
   {
      switch(_addr)
      {
         case am::REL:
            return 0xB0;
         default:
            std::cout << "unexpected addressing mode for BCS instruction";
            exit(-1);
      }   
   }
};

struct BEQ IMPL(Addressable)
{
   const Byte getOPCode(const adressingMode _addr) override
   {
      switch(_addr)
      {
         case am::REL:
            return 0xF0;
         default:
            std::cout << "unexpected addressing mode for BEQ instruction";
            exit(-1);
      }   
   }
};

struct BMI IMPL(Addressable)
{
   const Byte getOPCode(const adressingMode _addr) override
   {
      switch(_addr)
      {
         case am::REL:
            return 0x30;
         default:
            std::cout << "unexpected addressing mode for BMI instruction";
            exit(-1);
      }   
   }
};

struct BNE IMPL(Addressable)
{
   const Byte getOPCode(const adressingMode _addr) override
   {
      switch(_addr)
      {
         case am::REL:
            return 0xD0;
         default:
            std::cout << "unexpected addressing mode for BNE instruction";
            exit(-1);
      }   
   }
};

struct BPL IMPL(Addressable)
{
   const Byte getOPCode(const adressingMode _addr) override
   {
      switch(_addr)
      {
         case am::REL:
            return 0x10;
         default:
            std::cout << "unexpected addressing mode for BPL instruction";
            exit(-1);
      }   
   }
};

struct BVC IMPL(Addressable)
{
   const Byte getOPCode(const adressingMode _addr) override
   {
      switch(_addr)
      {
         case am::REL:
            return 0x50;
         default:
            std::cout << "unexpected addressing mode for BVC instruction";
            exit(-1);
      }   
   }
};

struct BVS IMPL(Addressable)
{
   const Byte getOPCode(const adressingMode _addr) override
   {
      switch(_addr)
      {
         case am::REL:
            return 0x70;
         default:
            std::cout << "unexpected addressing mode for BVS instruction";
            exit(-1);
      }   
   }
};

struct ASL IMPL(Addressable)
{
   const Byte getOPCode(const adressingMode _addr) override
   {
      switch(_addr)
      {
         case am::ACC:
            return 0x0A;
         case am::ZP:
            return 0x06;
         case am::ZPX:
            return 0x16;
         case am::ABS:
            return 0x0E;
         case am::ABSX:
            return 0x1E;
         default:
            std::cout << "unexpected addressing mode for ASL instruction";
            exit(-1);
      }   
   }
};

struct LSR IMPL(Addressable)
{
   const Byte getOPCode(const adressingMode _addr) override
   {
      switch(_addr)
      {
         case am::ACC:
            return 0x4A;
         case am::ZP:
            return 0x46;
         case am::ZPX:
            return 0x56;
         case am::ABS:
            return 0x4E;
         case am::ABSX:
            return 0x5E;
         default:
            std::cout << "unexpected addressing mode for LSR instruction";
            exit(-1);
      }   
   }
};

struct ROL IMPL(Addressable)
{
   const Byte getOPCode(const adressingMode _addr) override
   {
      switch(_addr)
      {
         case am::ACC:
            return 0x2A;
         case am::ZP:
            return 0x26;
         case am::ZPX:
            return 0x36;
         case am::ABS:
            return 0x2E;
         case am::ABSX:
            return 0x3E;
         default:
            std::cout << "unexpected addressing mode for ROL instruction";
            exit(-1);
      }   
   }
};

struct ROR IMPL(Addressable)
{
   const Byte getOPCode(const adressingMode _addr) override
   {
      switch(_addr)
      {
         case am::ACC:
            return 0x6A;
         case am::ZP:
            return 0x66;
         case am::ZPX:
            return 0x76;
         case am::ABS:
            return 0x6E;
         case am::ABSX:
            return 0x7E;
         default:
            std::cout << "unexpected addressing mode for ROR instruction";
            exit(-1);
      }   
   }
};

struct ADC IMPL(Addressable)
{
   const Byte getOPCode(const adressingMode _addr) override
   {
      switch(_addr)
      {
         case am::IM:
            return 0x69;
         case am::ZP:
            return 0x65;
         case am::ZPX:
            return 0x75;
         case am::ABS:
            return 0x6D;
         case am::ABSX:
            return 0x7D;
         case am::ABSY:
            return 0x79;
         case am::INDX:
            return 0x61;
         case am::INDY:
            return 0x71;
         default:
            std::cout << "unexpected addressing mode for ADC instruction";
            exit(-1);
      }   
   }
};

struct SBC IMPL(Addressable)
{
   const Byte getOPCode(const adressingMode _addr) override
   {
      switch(_addr)
      {
         case am::IM:
            return 0xE9;
         case am::ZP:
            return 0xE5;
         case am::ZPX:
            return 0xF5;
         case am::ABS:
            return 0xED;
         case am::ABSX:
            return 0xFD;
         case am::ABSY:
            return 0xF9;
         case am::INDX:
            return 0xE1;
         case am::INDY:
            return 0xF1;
         default:
            std::cout << "unexpected addressing mode for SBC instruction";
            exit(-1);
      }   
   }
};

struct CMP IMPL(Addressable)
{
   const Byte getOPCode(const adressingMode _addr) override
   {
      switch(_addr)
      {
         case am::IM:
            return 0xC9;
         case am::ZP:
            return 0xC5;
         case am::ZPX:
            return 0xD5;
         case am::ABS:
            return 0xCD;
         case am::ABSX:
            return 0xDD;
         case am::ABSY:
            return 0xD9;
         case am::INDX:
            return 0xC1;
         case am::INDY:
            return 0xD1;
         default:
            std::cout << "unexpected addressing mode for CMP instruction";
            exit(-1);
      }   
   }
};

struct CPX IMPL(Addressable)
{
   const Byte getOPCode(const adressingMode _addr) override
   {
      switch(_addr)
      {
         case am::IM:
            return 0xE0;
         case am::ZP:
            return 0xE4;
         case am::ABS:
            return 0xEC;
         default:
            std::cout << "unexpected addressing mode for CPX instruction";
            exit(-1);
      }   
   }
};

struct CPY IMPL(Addressable)
{
   const Byte getOPCode(const adressingMode _addr) override
   {
      switch(_addr)
      {
         case am::IM:
            return 0xC0;
         case am::ZP:
            return 0xC4;
         case am::ABS:
            return 0xCC;
         default:
            std::cout << "unexpected addressing mode for CPY instruction";
            exit(-1);
      }   
   }
};

struct CLC IMPL(Addressable)
{
   const Byte getOPCode(const adressingMode _addr) override
   {
      switch(_addr)
      {
         case am::IMP:
            return 0x18;
         default:
            std::cout << "unexpected addressing mode for CLC instruction";
            exit(-1);
      }   
   }
};

struct CLD IMPL(Addressable)
{
   const Byte getOPCode(const adressingMode _addr) override
   {
      switch(_addr)
      {
         case am::IMP:
            return 0xD8;
         default:
            std::cout << "unexpected addressing mode for CLD instruction";
            exit(-1);
      }   
   }
};

struct CLI IMPL(Addressable)
{
   const Byte getOPCode(const adressingMode _addr) override
   {
      switch(_addr)
      {
         case am::IMP:
            return 0x58;
         default:
            std::cout << "unexpected addressing mode for CLI instruction";
            exit(-1);
      }   
   }
};

struct CLV IMPL(Addressable)
{
   const Byte getOPCode(const adressingMode _addr) override
   {
      switch(_addr)
      {
         case am::IMP:
            return 0xB8;
         default:
            std::cout << "unexpected addressing mode for CLV instruction";
            exit(-1);
      }   
   }
};

struct SEC IMPL(Addressable)
{
   const Byte getOPCode(const adressingMode _addr) override
   {
      switch(_addr)
      {
         case am::IMP:
            return 0x38;
         default:
            std::cout << "unexpected addressing mode for SEC instruction";
            exit(-1);
      }   
   }
};

struct SED IMPL(Addressable)
{
   const Byte getOPCode(const adressingMode _addr) override
   {
      switch(_addr)
      {
         case am::IMP:
            return 0xF8;
         default:
            std::cout << "unexpected addressing mode for SED instruction";
            exit(-1);
      }   
   }
};

struct SEI IMPL(Addressable)
{
   const Byte getOPCode(const adressingMode _addr) override
   {
      switch(_addr)
      {
         case am::IMP:
            return 0x78;
         default:
            std::cout << "unexpected addressing mode for SEI instruction";
            exit(-1);
      }   
   }
};

struct BRK IMPL(Addressable)
{
   const Byte getOPCode(const adressingMode _addr) override
   {
      switch(_addr)
      {
         case am::IMP:
            return 0x00;
         default:
            std::cout << "unexpected addressing mode for BRK instruction";
            exit(-1);
      }   
   }
};

struct NOP IMPL(Addressable)
{
   const Byte getOPCode(const adressingMode _addr) override
   {
      switch(_addr)
      {
         case am::IMP:
            return 0xEA;
         default:
            std::cout << "unexpected addressing mode for NOP instruction";
            exit(-1);
      }   
   }
};

struct RTI IMPL(Addressable)
{
   const Byte getOPCode(const adressingMode _addr) override
   {
      switch(_addr)
      {
         case am::IMP:
            return 0x60;
         default:
            std::cout << "unexpected addressing mode for RTI instruction";
            exit(-1);
      }   
   }
};

struct NOTHING IMPL(Addressable)
{
   const Byte getOPCode(const adressingMode _addr) override
   {
      switch(_addr)
      {
         case am::IMP:
            return 0xFF;
         default:
            std::cout << "unexpected addressing mode for NOTHING instruction";
            exit(-1);
      }   
   }
};


#undef Byte

#endif
