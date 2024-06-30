#ifndef __INSTRUCTION_CODES__
#define __INSTRUCTION_CODES__

#include "defines.h"

/// Empty instruction
static constexpr Byte INS_NULL = 0x00;

/// LDA instructions
static constexpr Byte INS_LDA_IM   = 0xA9;
static constexpr Byte INS_LDA_ZP   = 0xA5;
static constexpr Byte INS_LDA_ABS  = 0xAD;
static constexpr Byte INS_LDA_ZPX  = 0xB5;
static constexpr Byte INS_LDA_ABSY = 0xB9;
static constexpr Byte INS_LDA_ABSX = 0xBD;
static constexpr Byte INS_LDA_INDX = 0xA1;
static constexpr Byte INS_LDA_INDY = 0xB1;

/// JSR instruction
static constexpr Byte INS_JSR = 0x20;

/// LDX instructions
static constexpr Byte INS_LDX_IM   = 0xA2;
static constexpr Byte INS_LDX_ZP   = 0xA6;
static constexpr Byte INS_LDX_ZPY  = 0xB6;
static constexpr Byte INS_LDX_ABS  = 0xAE;
static constexpr Byte INS_LDX_ABSY = 0xBE;

/// LDY instructions
static constexpr Byte INS_LDY_IM   = 0xA0;
static constexpr Byte INS_LDY_ZP   = 0xA4;
static constexpr Byte INS_LDY_ZPX  = 0xB4;
static constexpr Byte INS_LDY_ABS  = 0xAC;
static constexpr Byte INS_LDY_ABSX = 0xBC;

/// INC instructions
static constexpr Byte INS_INC_ZP   = 0xE6;
static constexpr Byte INS_INC_ZPX  = 0xF6;
static constexpr Byte INS_INC_ABS  = 0xEE;
static constexpr Byte INS_INC_ABSX = 0xFE;

/// INX and INY
static constexpr Byte INS_INX = 0xE8;
static constexpr Byte INS_INY = 0xC8;

/// DEC incstructions
static constexpr Byte INS_DEC_ZP   = 0xC6;
static constexpr Byte INS_DEC_ZPX  = 0xD6;
static constexpr Byte INS_DEC_ABS  = 0xCE;
static constexpr Byte INS_DEC_ABSX = 0xDE;

/// DEX and DEY
static constexpr Byte INS_DEX = 0xCA;
static constexpr Byte INS_DEY = 0x88;

/// STA instructions
static constexpr Byte INS_STA_ZP   = 0x85;
static constexpr Byte INS_STA_ZPX  = 0x95;
static constexpr Byte INS_STA_ABS  = 0x8D;
static constexpr Byte INS_STA_ABSX = 0x9D;
static constexpr Byte INS_STA_ABSY = 0x99;
static constexpr Byte INS_STA_INDX = 0x81;
static constexpr Byte INS_STA_INDY = 0x91;

/// STX
static constexpr Byte INS_STX_ZP  = 0x86;
static constexpr Byte INS_STX_ZPY = 0x96;
static constexpr Byte INS_STX_ABS = 0x8E;

/// STY
static constexpr Byte INS_STY_ZP  = 0x84;
static constexpr Byte INS_STY_ZPX = 0x94;
static constexpr Byte INS_STY_ABS = 0x8C;

/// RTS
static constexpr Byte INS_RTS = 0x60;

/// JMP
static constexpr Byte INS_JMP_ABS = 0x4C;
static constexpr Byte INS_JMP_IND = 0x6C;

#endif
