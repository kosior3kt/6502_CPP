#ifndef __INSTRUCTION_DEFINITIONS__
#define __INSTRUCTION_DEFINITIONS__

#include "defines.h"
#include "memory.h"

      void NULL_INS(u32 &_cycles, Mem &_mem);

      /// LDA - instruction LDA loads value from given memory location into the
      /// A register. It has 8 different adression modes - they are below
      void LDA_IM(u32 &_cycles, Mem &_mem);
      void LDA_ZP(u32 &_cycles, Mem &_mem);
      void LDA_ZPX(u32 &_cycles, Mem &_mem);
      void LDA_ABS(u32 &_cycles, Mem &_mem);
      void LDA_ABSY(u32 &_cycles, Mem &_mem);
      void LDA_ABSX(u32 &_cycles, Mem &_mem);
      void LDA_INDX(u32 &_cycles, Mem &_mem);
      void LDA_INDY(u32 &_cycles, Mem &_mem);

      /// JSR - this instruction jumps to the subrutine  (and preasumably
      /// returns)
      void JSR(u32 &_cycles, Mem &_mem);

      /// LDX  - instruction LDX loads value from given memory location into
      /// the X register. It has 5 different adressing modes
      void LDX_IM(u32 &_cycles, Mem &_mem);
      void LDX_ZP(u32 &_cycles, Mem &_mem);
      void LDX_ZPY(u32 &_cycles, Mem &_mem);
      void LDX_ABS(u32 &_cycles, Mem &_mem);
      void LDX_ABSY(u32 &_cycles, Mem &_mem);

      /// LDY - instruction LDX loads value from given memory location into the
      /// Y register. It has 5 different adressing modes
      void LDY_IM(u32 &_cycles, Mem &_mem);
      void LDY_ZP(u32 &_cycles, Mem &_mem);
      void LDY_ZPX(u32 &_cycles, Mem &_mem);
      void LDY_ABS(u32 &_cycles, Mem &_mem);
      void LDY_ABSX(u32 &_cycles, Mem &_mem);

      /// INC - instruction INC increments value in the given memory locatino
      /// void INC(u32& _cycles, Mem& _mem);

      void INC_ZP(u32 &_cycles, Mem &_mem);
      void INC_ZPX(u32 &_cycles, Mem &_mem);
      void INC_ABS(u32 &_cycles, Mem &_mem);
      void INC_ABSX(u32 &_cycles, Mem &_mem);

      /// INX - this instruction increments value stored in the X register
      void INX(u32 &_cycles, Mem &_mem);

      /// INY - this instruction increments value stored in the Y register
      void INY(u32 &_cycles, Mem &_mem);

      /// DEC
      void DEC_ZP(u32 &_cycles, Mem &_mem);
      void DEC_ZPX(u32 &_cycles, Mem &_mem);
      void DEC_ABS(u32 &_cycles, Mem &_mem);
      void DEC_ABSX(u32 &_cycles, Mem &_mem);

      /// DEX
      void DEX(u32 &_cycles, Mem &_mem);

      /// DEY
      void DEY(u32 &_cycles, Mem &_mem);


#endif
