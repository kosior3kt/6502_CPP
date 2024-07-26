#ifndef __INSTRUCTION_DEFINITIONS__
#define __INSTRUCTION_DEFINITIONS__

#include "defines.h"
#include "memory.h"

//////READ ME
///yeah. It aint pretty, but this was my idea and we roll with it now. Also we are in the middle of porting, sooo...


void LDA(u32 &_cycles, Mem &_mem, const Byte& _opCode);
void LDX(u32 &_cycles, Mem &_mem, const Byte& _opCode);
void LDY(u32 &_cycles, Mem &_mem, const Byte& _opCode);

void STA(u32 &_cycles, Mem &_mem, const Byte& _opCode);
void STY(u32 &_cycles, Mem &_mem, const Byte& _opCode);
void STX(u32 &_cycles, Mem &_mem, const Byte& _opCode);

void INC(u32 &_cycles, Mem &_mem, const Byte& _opCode);
void INX(u32 &_cycles, Mem &_mem, const Byte& _opCode);
void INY(u32 &_cycles, Mem &_mem, const Byte& _opCode);

void DEC(u32 &_cycles, Mem &_mem, const Byte& _opCode);
void DEX(u32 &_cycles, Mem &_mem, const Byte& _opCode);
void DEY(u32 &_cycles, Mem &_mem, const Byte& _opCode);

void JSR(u32 &_cycles, Mem &_mem, const Byte& _opCode);
void RTS(u32 &_cycles, Mem &_mem, const Byte& _opCode);
void JMP(u32 &_cycles, Mem &_mem, const Byte& _opCode);

void TSX(u32 &_cycles, Mem &_mem, const Byte& _opCode);
void TXS(u32 &_cycles, Mem &_mem, const Byte& _opCode);
void PHA(u32 &_cycles, Mem &_mem, const Byte& _opCode);
void PHP(u32 &_cycles, Mem &_mem, const Byte& _opCode);
void PLA(u32 &_cycles, Mem &_mem, const Byte& _opCode);
void PLP(u32 &_cycles, Mem &_mem, const Byte& _opCode);

void TYA(u32 &_cycles, Mem &_mem, const Byte& _opCode);
void TAY(u32 &_cycles, Mem &_mem, const Byte& _opCode);
void TXA(u32 &_cycles, Mem &_mem, const Byte& _opCode);
void TAX(u32 &_cycles, Mem &_mem, const Byte& _opCode);

void AND(u32 &_cycles, Mem &_mem, const Byte& _opCode);
void EOR(u32 &_cycles, Mem &_mem, const Byte& _opCode);
void ORA(u32 &_cycles, Mem &_mem, const Byte& _opCode);
void BIT(u32 &_cycles, Mem &_mem, const Byte& _opCode);

void BCC(u32 &_cycles, Mem &_mem, const Byte& _opCode);
void BCS(u32 &_cycles, Mem &_mem, const Byte& _opCode);
void BEQ(u32 &_cycles, Mem &_mem, const Byte& _opCode);
void BMI(u32 &_cycles, Mem &_mem, const Byte& _opCode);
void BNE(u32 &_cycles, Mem &_mem, const Byte& _opCode);
void BPL(u32 &_cycles, Mem &_mem, const Byte& _opCode);
void BVC(u32 &_cycles, Mem &_mem, const Byte& _opCode);
void BVS(u32 &_cycles, Mem &_mem, const Byte& _opCode);

void ASL(u32 &_cycles, Mem &_mem, const Byte& _opCode);
void LSR(u32 &_cycles, Mem &_mem, const Byte& _opCode);
void ROL(u32 &_cycles, Mem &_mem, const Byte& _opCode);
void ROR(u32 &_cycles, Mem &_mem, const Byte& _opCode);

void ADC(u32 &_cycles, Mem &_mem, const Byte& _opCode);
void SBC(u32 &_cycles, Mem &_mem, const Byte& _opCode);
void CMP(u32 &_cycles, Mem &_mem, const Byte& _opCode);
void CPX(u32 &_cycles, Mem &_mem, const Byte& _opCode);
void CPY(u32 &_cycles, Mem &_mem, const Byte& _opCode);

void CLC(u32 &_cycles, Mem &_mem, const Byte& _opCode);
void CLD(u32 &_cycles, Mem &_mem, const Byte& _opCode);
void CLI(u32 &_cycles, Mem &_mem, const Byte& _opCode);
void CLV(u32 &_cycles, Mem &_mem, const Byte& _opCode);
void SEC(u32 &_cycles, Mem &_mem, const Byte& _opCode);
void SED(u32 &_cycles, Mem &_mem, const Byte& _opCode);
void SEI(u32 &_cycles, Mem &_mem, const Byte& _opCode);

void BRK(u32 &_cycles, Mem &_mem, const Byte& _opCode);
void NOP(u32 &_cycles, Mem &_mem, const Byte& _opCode);
void RTI(u32 &_cycles, Mem &_mem, const Byte& _opCode);

void NOTHING_(u32 &_cycles, Mem &_mem, const Byte& _opCode);

#endif

