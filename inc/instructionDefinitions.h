#ifndef __INSTRUCTION_DEFINITIONS__
#define __INSTRUCTION_DEFINITIONS__

#include "defines.h"
#include "memory.h"

//////READ ME
///yeah. It aint pretty, but this was my idea and we roll with it now

void NULL_INS(u32 &_cycles, Mem &_mem);      ///this isnt even real thing :(

////////////////////////////////////// Load/Store
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

///STA
void STA_ZP(u32 &_cycles, Mem &_mem);
void STA_ZPX(u32 &_cycles, Mem &_mem);
void STA_ABS(u32 &_cycles, Mem &_mem);
void STA_ABSX(u32 &_cycles, Mem &_mem);
void STA_ABSY(u32 &_cycles, Mem &_mem);
void STA_INDX(u32 &_cycles, Mem &_mem);
void STA_INDY(u32 &_cycles, Mem &_mem);

///STX
void STX_ZP(u32 &_cycles, Mem &_mem);
void STX_ZPY(u32 &_cycles, Mem &_mem);
void STX_ABS(u32 &_cycles, Mem &_mem);

///STY
void STY_ZP(u32 &_cycles, Mem &_mem);
void STY_ZPX(u32 &_cycles, Mem &_mem);
void STY_ABS(u32 &_cycles, Mem &_mem);


////////////////////////////////////// Increment/Decrement

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

////////////////////////////////////// Jumps/Calls
/// JSR - this instruction jumps to the subrutine  (and preasumably
/// returns)
void JSR(u32 &_cycles, Mem &_mem);
///RTS
void RTS(u32 &_cycles, Mem &_mem);

///JMP
void JMP_ABS(u32 &_cycles, Mem &_mem);
void JMP_IND(u32 &_cycles, Mem &_mem);


////////////////////////////////////// Stack Operations

void TSX(u32& _cycles, Mem &_mem);
void TXS(u32& _cycles, Mem &_mem);
void PHA(u32& _cycles, Mem &_mem);
void PHP(u32& _cycles, Mem &_mem);
void PLA(u32& _cycles, Mem &_mem);
void PLP(u32& _cycles, Mem &_mem);

////////////////////////////////////// Register Transfers
void TAX(u32& _cycles, Mem &_mem);
void TAY(u32& _cycles, Mem &_mem);
void TXA(u32& _cycles, Mem &_mem);
void TYA(u32& _cycles, Mem &_mem);

////////////////////////////////////// Logical
void AND_IM (u32& _cycles, Mem &_mem);
void AND_ZP (u32& _cycles, Mem &_mem);
void AND_ZPX(u32& _cycles, Mem &_mem);
void AND_ABS(u32& _cycles, Mem &_mem);
void AND_ABSX(u32& _cycles, Mem &_mem);
void AND_ABSY(u32& _cycles, Mem &_mem);
void AND_INDX(u32& _cycles, Mem &_mem);
void AND_INDY(u32& _cycles, Mem &_mem);

void EOR_IM (u32& _cycles, Mem &_mem);
void EOR_ZP (u32& _cycles, Mem &_mem);
void EOR_ZPX(u32& _cycles, Mem &_mem);
void EOR_ABS(u32& _cycles, Mem &_mem);
void EOR_ABSX(u32& _cycles, Mem &_mem);
void EOR_ABSY(u32& _cycles, Mem &_mem);
void EOR_INDX(u32& _cycles, Mem &_mem);
void EOR_INDY(u32& _cycles, Mem &_mem);

///ORA 
void ORA_IM (u32& _cycles, Mem &_mem);
void ORA_ZP (u32& _cycles, Mem &_mem);
void ORA_ZPX(u32& _cycles, Mem &_mem);
void ORA_ABS(u32& _cycles, Mem &_mem);
void ORA_ABSX(u32& _cycles, Mem &_mem);
void ORA_ABSY(u32& _cycles, Mem &_mem);
void ORA_INDX(u32& _cycles, Mem &_mem);
void ORA_INDY(u32& _cycles, Mem &_mem);

/// BIT
void BIT_ZP (u32& _cycles, Mem &_mem);
void BIT_ZBS(u32& _cycles, Mem &_mem);

////////////////////////////////////// Branches
void BCC (u32& _cycles, Mem &_mem);
void BCS (u32& _cycles, Mem &_mem);
void BEQ (u32& _cycles, Mem &_mem);
void BMI (u32& _cycles, Mem &_mem);
void BNE (u32& _cycles, Mem &_mem);
void BPL (u32& _cycles, Mem &_mem);
void BVC (u32& _cycles, Mem &_mem);
void BVS (u32& _cycles, Mem &_mem);

////////////////////////////////////// Shifts
///ASL
void ASL_ACC(u32& _cycles, Mem &_mem);
void ASL_ZP (u32& _cycles, Mem &_mem);
void ASL_ZPX(u32& _cycles, Mem &_mem);
void ASL_ABS(u32& _cycles, Mem &_mem);
void ASL_ABSX(u32& _cycles, Mem &_mem);

///LSR
void LSR_ACC(u32& _cycles, Mem &_mem);
void LSR_ZP (u32& _cycles, Mem &_mem);
void LSR_ZPX(u32& _cycles, Mem &_mem);
void LSR_ABS(u32& _cycles, Mem &_mem);
void LSR_ABSX(u32& _cycles, Mem &_mem);

///ROL
void ROL_ACC(u32& _cycles, Mem &_mem);
void ROL_ZP (u32& _cycles, Mem &_mem);
void ROL_ZPX(u32& _cycles, Mem &_mem);
void ROL_ABS(u32& _cycles, Mem &_mem);
void ROL_ABSX(u32& _cycles, Mem &_mem);

///ROR
void ROR_ACC(u32& _cycles, Mem &_mem);
void ROR_ZP (u32& _cycles, Mem &_mem);
void ROR_ZPX(u32& _cycles, Mem &_mem);
void ROR_ABS(u32& _cycles, Mem &_mem);
void ROR_ABSX(u32& _cycles, Mem &_mem);


////////////////////////////////////// Arithmetic
///ADC
void ADC_IM (u32& _cycles, Mem &_mem);
void ADC_ZP (u32& _cycles, Mem &_mem);
void ADC_ZPX(u32& _cycles, Mem &_mem);
void ADC_ABS(u32& _cycles, Mem &_mem);
void ADC_ABSX(u32& _cycles, Mem &_mem);
void ADC_ABSY(u32& _cycles, Mem &_mem);
void ADC_INDX(u32& _cycles, Mem &_mem);
void ADC_INDY(u32& _cycles, Mem &_mem);

/// SBC
void SBC_IM (u32& _cycles, Mem &_mem);
void SBC_ZP (u32& _cycles, Mem &_mem);
void SBC_ZPX(u32& _cycles, Mem &_mem);
void SBC_ABS(u32& _cycles, Mem &_mem);
void SBC_ABSX(u32& _cycles, Mem &_mem);
void SBC_ABSY(u32& _cycles, Mem &_mem);
void SBC_INDX(u32& _cycles, Mem &_mem);
void SBC_INDY(u32& _cycles, Mem &_mem);

/// CMP
void CMP_IM (u32& _cycles, Mem &_mem);
void CMP_ZP (u32& _cycles, Mem &_mem);
void CMP_ZPX(u32& _cycles, Mem &_mem);
void CMP_ABS(u32& _cycles, Mem &_mem);
void CMP_ABSX(u32& _cycles, Mem &_mem);
void CMP_ABSY(u32& _cycles, Mem &_mem);
void CMP_INDX(u32& _cycles, Mem &_mem);
void CMP_INDY(u32& _cycles, Mem &_mem);

///CPX
void CPX_IM (u32& _cycles, Mem &_mem);
void CPX_ZP (u32& _cycles, Mem &_mem);
void CPX_ABS(u32& _cycles, Mem &_mem);

///CPY
void CPY_IM (u32& _cycles, Mem &_mem);
void CPY_ZP (u32& _cycles, Mem &_mem);
void CPY_ABS(u32& _cycles, Mem &_mem);

      
////////////////////////////////////// Status Flag Changes
void CLC (u32& _cycles, Mem &_mem);
void CLD (u32& _cycles, Mem &_mem);
void CLI (u32& _cycles, Mem &_mem);
void CLV (u32& _cycles, Mem &_mem);
void SEC (u32& _cycles, Mem &_mem);
void SED (u32& _cycles, Mem &_mem);
void SEI (u32& _cycles, Mem &_mem);

////////////////////////////////////// System Functions
void BRK (u32& _cycles, Mem &_mem);
void NOP (u32& _cycles, Mem &_mem);
void RTI (u32& _cycles, Mem &_mem);

#endif
