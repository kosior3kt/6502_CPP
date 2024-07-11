#ifndef __TEST2__
#define __TEST2__

#include "defines.h"
#include "memory.h"

void LDA_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode);
void LDX_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode);
void LDY_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode);

void STA_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode);
void STY_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode);
void STX_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode);

void INC_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode);
void INX_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode);
void INY_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode);

void DEC_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode);
void DEX_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode);
void DEY_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode);

void JSR_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode);
void RTS_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode);
void JMP_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode);

void TSX_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode);
void TXS_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode);
void PHA_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode);
void PHP_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode);
void PLA_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode);
void PLP_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode);

void TYA_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode);
void TAY_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode);
void TXA_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode);
void TAX_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode);

void AND_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode);
void EOR_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode);
void ORA_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode);
void BIT_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode);

void BCC_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode);
void BCS_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode);
void BEQ_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode);
void BMI_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode);
void BNE_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode);
void BPL_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode);
void BVC_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode);
void BVS_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode);

void ASL_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode);
void LSR_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode);
void ROL_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode);
void ROR_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode);

void ADC_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode);
void SBC_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode);
void CMP_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode);
void CPX_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode);
void CPY_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode);

void CLC_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode);
void CLD_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode);
void CLI_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode);
void CLV_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode);
void SEC_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode);
void SED_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode);
void SEI_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode);

void BRK_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode);
void NOP_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode);
void RTI_TEST(u32 &_cycles, Mem &_mem, const Byte& _opCode);

#endif
