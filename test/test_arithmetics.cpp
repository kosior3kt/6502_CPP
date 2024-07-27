#include "test.hpp"

#define SIGNED_BYTE(x) ((Byte)x)

TEST_F(TEST_6502, ADC_ABS_TRIVIAL) 
{
   cpu_.Reset(mem_, 0xFF00);
   cpu_.A = 0;
   cpu_.C = 0;
   mem_.set(0xFF00, CPU::INS_ADC_ABS);
   mem_.set(0xFF01, 0x00);
   mem_.set(0xFF02, 0x80);
   mem_.set(0x8000, 0x00);
   auto cyclesLeft = cpu_.execute(9, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ((uint8_t)cpu_.A, (uint8_t)0x00);
   EXPECT_EQ((uint8_t)cpu_.C, (uint8_t)0x00);
   EXPECT_EQ((uint8_t)cpu_.Z, (uint8_t)0x01);
   EXPECT_EQ((uint8_t)cpu_.N, (uint8_t)0x00);
   EXPECT_EQ((uint8_t)cpu_.V, (uint8_t)0x00);
}

TEST_F(TEST_6502, ADC_ABS_LESS_TRIVIAL) 
{
   cpu_.Reset(mem_, 0xFF00);
   cpu_.A = 0;
   cpu_.C = 1;
   mem_.set(0xFF00, CPU::INS_ADC_ABS);
   mem_.set(0xFF01, 0x00);
   mem_.set(0xFF02, 0x80);
   mem_.set(0x8000, 0x00);
   auto cyclesLeft = cpu_.execute(9, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ((uint8_t)cpu_.A, (uint8_t)0x01);
   EXPECT_EQ((uint8_t)cpu_.C, (uint8_t)0x00);
   EXPECT_EQ((uint8_t)cpu_.Z, (uint8_t)0x00);
   EXPECT_EQ((uint8_t)cpu_.N, (uint8_t)0x00);
   EXPECT_EQ((uint8_t)cpu_.V, (uint8_t)0x00);
}

TEST_F(TEST_6502, ADC_ABS_twoUnsignedNumberAndCarry) 
{
   cpu_.Reset(mem_, 0xFF00);
   cpu_.A = 0x60;
   cpu_.C = 1;
   mem_.set(0xFF00, CPU::INS_ADC_ABS);
   mem_.set(0xFF01, 0x00);
   mem_.set(0xFF02, 0x80);
   mem_.set(0x8000, 0x08);
   auto cyclesLeft = cpu_.execute(9, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ((uint8_t)cpu_.A, (uint8_t)0x69);
   EXPECT_EQ((uint8_t)cpu_.C, (uint8_t)0x00);
   EXPECT_EQ((uint8_t)cpu_.Z, (uint8_t)0x00);
   EXPECT_EQ((uint8_t)cpu_.N, (uint8_t)0x00);
   EXPECT_EQ((uint8_t)cpu_.V, (uint8_t)0x00);
}

TEST_F(TEST_6502, ADC_ABS_twoSignedNumberAndCarry) 
{

   //////bewere, some numbers here are decimal instead of hex...
   cpu_.Reset(mem_, 0xFF00);
   cpu_.A = SIGNED_BYTE(-17);
   cpu_.C = 1;
   mem_.set(0xFF00, CPU::INS_ADC_ABS);
   mem_.set(0xFF01, 0x00);
   mem_.set(0xFF02, 0x80);
   mem_.set(0x8000, 20);
   auto cyclesLeft = cpu_.execute(9, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ((uint8_t)cpu_.A, (uint8_t)4);
   EXPECT_EQ((uint8_t)cpu_.C, (uint8_t)0x01);
   EXPECT_EQ((uint8_t)cpu_.Z, (uint8_t)0x00);
   EXPECT_EQ((uint8_t)cpu_.N, (uint8_t)0x00);
   EXPECT_EQ((uint8_t)cpu_.V, (uint8_t)0x00);
}

TEST_F(TEST_6502, ADC_ABS_twoUnsignedNumberCauseCarry) 
{
   cpu_.Reset(mem_, 0xFF00);
   cpu_.A = 0xFF;
   cpu_.C = 0;
   mem_.set(0xFF00, CPU::INS_ADC_ABS);
   mem_.set(0xFF01, 0x00);
   mem_.set(0xFF02, 0x80);
   mem_.set(0x8000, 0x01);
   auto cyclesLeft = cpu_.execute(9, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ((uint8_t)cpu_.A, (uint8_t)0x00);
   EXPECT_EQ((uint8_t)cpu_.C, (uint8_t)0x01);
   EXPECT_EQ((uint8_t)cpu_.Z, (uint8_t)0x01);
   EXPECT_EQ((uint8_t)cpu_.N, (uint8_t)0x00);
   EXPECT_EQ((uint8_t)cpu_.V, (uint8_t)0x00);
}


TEST_F(TEST_6502, ADC_ABS_negativeFlag) 
{
   cpu_.Reset(mem_, 0xFF00);
   cpu_.A = 0x00;
   cpu_.C = 0;
   uint8_t operand = SIGNED_BYTE(-1);   /// i handle signs myself, so idgaf about uint/int thingy
   mem_.set(0xFF00, CPU::INS_ADC_ABS);
   mem_.set(0xFF01, 0x00);
   mem_.set(0xFF02, 0x80);
   mem_.set(0x8000, operand);
   auto cyclesLeft = cpu_.execute(9, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ((uint8_t)cpu_.A, SIGNED_BYTE(-1));
   EXPECT_EQ((uint8_t)cpu_.C, (uint8_t)0x00);
   EXPECT_EQ((uint8_t)cpu_.Z, (uint8_t)0x00);
   EXPECT_EQ((uint8_t)cpu_.N, (uint8_t)0x01);
   EXPECT_EQ((uint8_t)cpu_.V, (uint8_t)0x00);
}


TEST_F(TEST_6502, ADC_ABS_SetTheOverflowFlagWhenSignedNegativeAddtionFails) 
{
  // A: 10000000 -128
  // O: 11111111 -1
  // =: 01111111 127
  // C:1 N:0 V:1 Z:0
   cpu_.Reset(mem_, 0xFF00);
   cpu_.A = SIGNED_BYTE(-128);   ///is this even legal?
   cpu_.C = 0;
   uint8_t operand = SIGNED_BYTE(-1);
   mem_.set(0xFF00, CPU::INS_ADC_ABS);
   mem_.set(0xFF01, 0x00);
   mem_.set(0xFF02, 0x80);
   mem_.set(0x8000, operand);
   auto cyclesLeft = cpu_.execute(9, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ((uint8_t)cpu_.A, SIGNED_BYTE(127));
   EXPECT_EQ((uint8_t)cpu_.C, (uint8_t)0x01);
   EXPECT_EQ((uint8_t)cpu_.Z, (uint8_t)0x00);
   EXPECT_EQ((uint8_t)cpu_.N, (uint8_t)0x00);
   EXPECT_EQ((uint8_t)cpu_.V, (uint8_t)0x01);
}

TEST_F(TEST_6502, ADC_ABS_SetTheOverflowFlagWhenSignedNegativeAddtionPassedDueToInitalCarryFlag) 
{
  // C: 00000001
  // A: 10000000 -128
  // O: 11111111 -1
  // =: 10000000 -128
  // C:1 N:1 V:0 Z:0
   cpu_.Reset(mem_, 0xFF00);
   cpu_.A = SIGNED_BYTE(-128);   ///is this even legal?
   cpu_.C = 1;
   uint8_t operand = SIGNED_BYTE(-1);
   mem_.set(0xFF00, CPU::INS_ADC_ABS);
   mem_.set(0xFF01, 0x00);
   mem_.set(0xFF02, 0x80);
   mem_.set(0x8000, operand);
   auto cyclesLeft = cpu_.execute(9, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ((uint8_t)cpu_.A, SIGNED_BYTE(-128));
   EXPECT_EQ((uint8_t)cpu_.C, (uint8_t)0x01);
   EXPECT_EQ((uint8_t)cpu_.Z, (uint8_t)0x00);
   EXPECT_EQ((uint8_t)cpu_.N, (uint8_t)0x01);
   EXPECT_EQ((uint8_t)cpu_.V, (uint8_t)0x00);
}


TEST_F(TEST_6502, ADC_ABS_negativeAdditionWithInitialCarry) 
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.A = SIGNED_BYTE(-128); // -128
    cpu_.C = 1;    // Initial carry
    mem_.set(0xFF00, CPU::INS_ADC_ABS);
    mem_.set(0xFF01, 0x00);
    mem_.set(0xFF02, 0x80);
    mem_.set(0x8000, 0xFF); // -1
    auto cyclesLeft = cpu_.execute(9, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ((uint8_t)cpu_.A, SIGNED_BYTE(-128));   // -128
    EXPECT_EQ((uint8_t)cpu_.C, 1);
    EXPECT_EQ((uint8_t)cpu_.N, 1);
    EXPECT_EQ((uint8_t)cpu_.V, 0);
    EXPECT_EQ((uint8_t)cpu_.Z, 0);
}

TEST_F(TEST_6502, ADC_ABS_positiveAdditionWithOverflow) 
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.A = SIGNED_BYTE(127); // 127
    cpu_.C = 0;
    mem_.set(0xFF00, CPU::INS_ADC_ABS);
    mem_.set(0xFF01, 0x00);
    mem_.set(0xFF02, 0x80);
    mem_.set(0x8000, 0x01); // 1
    auto cyclesLeft = cpu_.execute(9, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ((uint8_t)cpu_.A, SIGNED_BYTE(128));   // 128
    EXPECT_EQ((uint8_t)cpu_.C, 0);
    EXPECT_EQ((uint8_t)cpu_.N, 1);
    EXPECT_EQ((uint8_t)cpu_.V, 1);
    EXPECT_EQ((uint8_t)cpu_.Z, 0);
}
TEST_F(TEST_6502, ADC_IM_unsignedAddition) 
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.A = 20;
    cpu_.C = 1;
    mem_.set(0xFF00, CPU::INS_ADC_IM);
    mem_.set(0xFF01, 17); // Immediate value 17
    auto cyclesLeft = cpu_.execute(2, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ((uint8_t)cpu_.A, 38);
    EXPECT_EQ((uint8_t)cpu_.C, 0);
    EXPECT_EQ((uint8_t)cpu_.N, 0);
    EXPECT_EQ((uint8_t)cpu_.V, 0);
    EXPECT_EQ((uint8_t)cpu_.Z, 0);
}

TEST_F(TEST_6502, ADC_IM_canAddAPositiveAndNegativeNumber) 
{
    // A: 00010100 20
    // O: 11101111 -17
    // =: 00000011
    // C:1 N:0 V:0 Z:0

    cpu_.Reset(mem_, 0xFF00);
    cpu_.A = 20;
    cpu_.C = 1;
    mem_.set(0xFF00, CPU::INS_ADC_IM);
    mem_.set(0xFF01, SIGNED_BYTE(-17)); // Immediate value -17
    auto cyclesLeft = cpu_.execute(2, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ((uint8_t)cpu_.A, 4);
    EXPECT_EQ((uint8_t)cpu_.C, 1);
    EXPECT_EQ((uint8_t)cpu_.N, 0);
    EXPECT_EQ((uint8_t)cpu_.V, 0);
    EXPECT_EQ((uint8_t)cpu_.Z, 0);
}

TEST_F(TEST_6502, ADC_ZP_canAddTwoUnsignedNumbers) 
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.A = 20;
    cpu_.C = 1;
    mem_.set(0xFF00, CPU::INS_ADC_ZP);
    mem_.set(0xFF01, 0x10); // Zero page address 0x10
    mem_.set(0x0010, 17);
    auto cyclesLeft = cpu_.execute(3, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ((uint8_t)cpu_.A, 38);
    EXPECT_EQ((uint8_t)cpu_.C, 0);
    EXPECT_EQ((uint8_t)cpu_.N, 0);
    EXPECT_EQ((uint8_t)cpu_.V, 0);
    EXPECT_EQ((uint8_t)cpu_.Z, 0);
}

TEST_F(TEST_6502, ADC_ZP_canAddAPositiveAndNegativeNumber) 
{
    // A: 00010100 20
    // O: 11101111 -17
    // =: 00000011
    // C:1 N:0 V:0 Z:0

    cpu_.Reset(mem_, 0xFF00);
    cpu_.A = 20;
    cpu_.C = 1;
    mem_.set(0xFF00, CPU::INS_ADC_ZP);
    mem_.set(0xFF01, 0x10); // Zero page address 0x10
    mem_.set(0x0010, SIGNED_BYTE(-17));
    auto cyclesLeft = cpu_.execute(3, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ((uint8_t)cpu_.A, 4);
    EXPECT_EQ((uint8_t)cpu_.C, 1);
    EXPECT_EQ((uint8_t)cpu_.N, 0);
    EXPECT_EQ((uint8_t)cpu_.V, 0);
    EXPECT_EQ((uint8_t)cpu_.Z, 0);
}

TEST_F(TEST_6502, ADC_ZPX_canAddTwoUnsignedNumbers) 
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.A = 20;
    cpu_.C = 1;
    cpu_.X = 0x01; // Offset X
    mem_.set(0xFF00, CPU::INS_ADC_ZPX);
    mem_.set(0xFF01, 0x10); // Zero page base address 0x10
    mem_.set(0x0011, 17); // Address 0x10 + X = 0x11
    auto cyclesLeft = cpu_.execute(4, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ((uint8_t)cpu_.A, 38);
    EXPECT_EQ((uint8_t)cpu_.C, 0);
    EXPECT_EQ((uint8_t)cpu_.N, 0);
    EXPECT_EQ((uint8_t)cpu_.V, 0);
    EXPECT_EQ((uint8_t)cpu_.Z, 0);
}

TEST_F(TEST_6502, ADC_ZPX_canAddAPositiveAndNegativeNumber) 
{
    // A: 00010100 20
    // O: 11101111 -17
    // =: 00000011
    // C:1 N:0 V:0 Z:0

    cpu_.Reset(mem_, 0xFF00);
    cpu_.A = 20;
    cpu_.C = 1;
    cpu_.X = 0x01; // Offset X
    mem_.set(0xFF00, CPU::INS_ADC_ZPX);
    mem_.set(0xFF01, 0x10); // Zero page base address 0x10
    mem_.set(0x0011, SIGNED_BYTE(-17)); // Address 0x10 + X = 0x11
    auto cyclesLeft = cpu_.execute(4, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ((uint8_t)cpu_.A, 4);
    EXPECT_EQ((uint8_t)cpu_.C, 1);
    EXPECT_EQ((uint8_t)cpu_.N, 0);
    EXPECT_EQ((uint8_t)cpu_.V, 0);
    EXPECT_EQ((uint8_t)cpu_.Z, 0);
}

TEST_F(TEST_6502, ADC_ABSX_canAddTwoUnsignedNumbers) 
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.A = 20;
    cpu_.C = 1;
    cpu_.X = 0x01; // Offset X
    mem_.set(0xFF00, CPU::INS_ADC_ABSX);
    mem_.set(0xFF01, 0x00);
    mem_.set(0xFF02, 0x80);
    mem_.set(0x8001, 17); // Absolute address 0x8000 + X = 0x8001
    auto cyclesLeft = cpu_.execute(9, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ((uint8_t)cpu_.A, 38);
    EXPECT_EQ((uint8_t)cpu_.C, 0);
    EXPECT_EQ((uint8_t)cpu_.N, 0);
    EXPECT_EQ((uint8_t)cpu_.V, 0);
    EXPECT_EQ((uint8_t)cpu_.Z, 0);
}

TEST_F(TEST_6502, ADC_ABSX_canAddAPositiveAndNegativeNumber) 
{
    // A: 00010100 20
    // O: 11101111 -17
    // =: 00000011
    // C:1 N:0 V:0 Z:0

    cpu_.Reset(mem_, 0xFF00);
    cpu_.A = 20;
    cpu_.C = 1;
    cpu_.X = 0x01; // Offset X
    mem_.set(0xFF00, CPU::INS_ADC_ABSX);
    mem_.set(0xFF01, 0x00);
    mem_.set(0xFF02, 0x80);
    mem_.set(0x8001, SIGNED_BYTE(-17)); // Absolute address 0x8000 + X = 0x8001
    auto cyclesLeft = cpu_.execute(9, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ((uint8_t)cpu_.A, 4);
    EXPECT_EQ((uint8_t)cpu_.C, 1);
    EXPECT_EQ((uint8_t)cpu_.N, 0);
    EXPECT_EQ((uint8_t)cpu_.V, 0);
    EXPECT_EQ((uint8_t)cpu_.Z, 0);
}

TEST_F(TEST_6502, ADC_ABSY_canAddTwoUnsignedNumbers) 
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.A = 20;
    cpu_.C = 1;
    cpu_.Y = 0x01; // Offset Y
    mem_.set(0xFF00, CPU::INS_ADC_ABSY);
    mem_.set(0xFF01, 0x00);
    mem_.set(0xFF02, 0x80);
    mem_.set(0x8001, 17); // Absolute address 0x8000 + Y = 0x8001
    auto cyclesLeft = cpu_.execute(9, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ((uint8_t)cpu_.A, 38);
    EXPECT_EQ((uint8_t)cpu_.C, 0);
    EXPECT_EQ((uint8_t)cpu_.N, 0);
    EXPECT_EQ((uint8_t)cpu_.V, 0);
    EXPECT_EQ((uint8_t)cpu_.Z, 0);
}

TEST_F(TEST_6502, ADC_ABSY_canAddAPositiveAndNegativeNumber) 
{
    // A: 00010100 20
    // O: 11101111 -17
    // =: 00000011
    // C:1 N:0 V:0 Z:0

    cpu_.Reset(mem_, 0xFF00);
    cpu_.A = 20;
    cpu_.C = 1;
    cpu_.Y = 0x01; // Offset Y
    mem_.set(0xFF00, CPU::INS_ADC_ABSY);
    mem_.set(0xFF01, 0x00);
    mem_.set(0xFF02, 0x80);
    mem_.set(0x8001, SIGNED_BYTE(-17)); // Absolute address 0x8000 + Y = 0x8001
    auto cyclesLeft = cpu_.execute(9, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ((uint8_t)cpu_.A, 4);
    EXPECT_EQ((uint8_t)cpu_.C, 1);
    EXPECT_EQ((uint8_t)cpu_.N, 0);
    EXPECT_EQ((uint8_t)cpu_.V, 0);
    EXPECT_EQ((uint8_t)cpu_.Z, 0);
}

TEST_F(TEST_6502, ADC_INDX_canAddTwoUnsignedNumbers) 
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.A = 20;
    cpu_.C = 1;
    cpu_.X = 0x04; // Offset X
    mem_.set(0xFF00, CPU::INS_ADC_INDX);
    mem_.set(0xFF01, 0x10); // Base address 0x10
    mem_.set(0x0014, 0x00); // Low byte of effective address (0x0010 + X)
    mem_.set(0x0015, 0x80); // High byte of effective address (0x0010 + X)
    mem_.set(0x8000, 17); // Effective address 0x8000
    auto cyclesLeft = cpu_.execute(6, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ((uint8_t)cpu_.A, 38);
    EXPECT_EQ((uint8_t)cpu_.C, 0);
    EXPECT_EQ((uint8_t)cpu_.N, 0);
    EXPECT_EQ((uint8_t)cpu_.V, 0);
    EXPECT_EQ((uint8_t)cpu_.Z, 0);
}

TEST_F(TEST_6502, ADC_INDX_canAddAPositiveAndNegativeNumber) 
{
    // A: 00010100 20
    // O: 11101111 -17
    // =: 00000011
    // C:1 N:0 V:0 Z:0

    cpu_.Reset(mem_, 0xFF00);
    cpu_.A = 20;
    cpu_.C = 1;
    cpu_.X = 0x04; // Offset X
    mem_.set(0xFF00, CPU::INS_ADC_INDX);
    mem_.set(0xFF01, 0x10); // Base address 0x10
    mem_.set(0x0014, 0x00); // Low byte of effective address (0x0010 + X)
    mem_.set(0x0015, 0x80); // High byte of effective address (0x0010 + X)
    mem_.set(0x8000, SIGNED_BYTE(-17)); // Effective address 0x8000
    auto cyclesLeft = cpu_.execute(6, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ((uint8_t)cpu_.A, 4);
    EXPECT_EQ((uint8_t)cpu_.C, 1);
    EXPECT_EQ((uint8_t)cpu_.N, 0);
    EXPECT_EQ((uint8_t)cpu_.V, 0);
    EXPECT_EQ((uint8_t)cpu_.Z, 0);
}

TEST_F(TEST_6502, ADC_INDY_canAddTwoUnsignedNumbers) 
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.A = 20;
    cpu_.C = 1;
    cpu_.Y = 0x01; // Offset Y
    mem_.set(0xFF00, CPU::INS_ADC_INDY);
    mem_.set(0xFF01, 0x10); // Base address 0x10
    mem_.set(0x0010, 0x00); // Low byte of effective address
    mem_.set(0x0011, 0x80); // High byte of effective address
    mem_.set(0x8001, 17); // Effective address 0x8000 + Y = 0x8001
    auto cyclesLeft = cpu_.execute(5, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ((uint8_t)cpu_.A, 38);
    EXPECT_EQ((uint8_t)cpu_.C, 0);
    EXPECT_EQ((uint8_t)cpu_.N, 0);
    EXPECT_EQ((uint8_t)cpu_.V, 0);
    EXPECT_EQ((uint8_t)cpu_.Z, 0);
}

TEST_F(TEST_6502, ADC_INDY_canAddAPositiveAndNegativeNumber) 
{
    // A: 00010100 20
    // O: 11101111 -17
    // =: 00000011
    // C:1 N:0 V:0 Z:0

    cpu_.Reset(mem_, 0xFF00);
    cpu_.A = 20;
    cpu_.C = 1;
    cpu_.Y = 0x01; // Offset Y
    mem_.set(0xFF00, CPU::INS_ADC_INDY);
    mem_.set(0xFF01, 0x10); // Base address 0x10
    mem_.set(0x0010, 0x00); // Low byte of effective address
    mem_.set(0x0011, 0x80); // High byte of effective address
    mem_.set(0x8001, SIGNED_BYTE(-17)); // Effective address 0x8000 + Y = 0x8001
    auto cyclesLeft = cpu_.execute(5, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ((uint8_t)cpu_.A, 4);
    EXPECT_EQ((uint8_t)cpu_.C, 1);
    EXPECT_EQ((uint8_t)cpu_.N, 0);
    EXPECT_EQ((uint8_t)cpu_.V, 0);
    EXPECT_EQ((uint8_t)cpu_.Z, 0);
}

///////////////////SBC stuff here
TEST_F(TEST_6502, SBC_ABS_canSubtractZeroFromZeroAndGetZero) 
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.A = 0b00;
    cpu_.C = 1; // Carry is set to true
    mem_.set(0xFF00, CPU::INS_SBC_ABS);
    mem_.set(0xFF01, 0x00);
    mem_.set(0xFF02, 0x80);
    mem_.set(0x8000, 0b00); // Operand at effective address
    auto cyclesLeft = cpu_.execute(4, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ((uint8_t)cpu_.A, 0x00);
    EXPECT_EQ((uint8_t)cpu_.C, 1);
    EXPECT_EQ((uint8_t)cpu_.N, 0);
    EXPECT_EQ((uint8_t)cpu_.V, 0);
    EXPECT_EQ((uint8_t)cpu_.Z, 1);
}

TEST_F(TEST_6502, SBC_ABS_canSubtractZeroFromZeroAndCarryAndGetMinusOne) 
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.A = 0;
    cpu_.C = 0; // Carry is set to false
    mem_.set(0xFF00, CPU::INS_SBC_ABS);
    mem_.set(0xFF01, 0x00);
    mem_.set(0xFF02, 0x80);
    mem_.set(0x8000, 0x00); // Operand at effective address
    auto cyclesLeft = cpu_.execute(4, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ((uint8_t)cpu_.A, SIGNED_BYTE(-1)); // -1 in 8-bit representation
    EXPECT_EQ((uint8_t)cpu_.C, 0);
    EXPECT_EQ((uint8_t)cpu_.N, 1);
    EXPECT_EQ((uint8_t)cpu_.V, 0);
    EXPECT_EQ((uint8_t)cpu_.Z, 0);
}

TEST_F(TEST_6502, SBC_ABS_canSubtractOneFromZeroAndGetMinusOne) 
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.A = 0;
    cpu_.C = 1; // Carry is set to true
    mem_.set(0xFF00, CPU::INS_SBC_ABS);
    mem_.set(0xFF01, 0x00);
    mem_.set(0xFF02, 0x80);
    mem_.set(0x8000, 0x01); // Operand at effective address
    auto cyclesLeft = cpu_.execute(4, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ((uint8_t)cpu_.A, SIGNED_BYTE(-1)); // -1 in 8-bit representation
    EXPECT_EQ((uint8_t)cpu_.C, 0);
    EXPECT_EQ((uint8_t)cpu_.N, 1);
    EXPECT_EQ((uint8_t)cpu_.V, 0);
    EXPECT_EQ((uint8_t)cpu_.Z, 0);
}

TEST_F(TEST_6502, SBC_ABS_canSubtractOneFromZeroWithCarryAndGetMinusTwo) 
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.A = 0;
    cpu_.C = 0; // Carry is set to false
    mem_.set(0xFF00, CPU::INS_SBC_ABS);
    mem_.set(0xFF01, 0x00);
    mem_.set(0xFF02, 0x80);
    mem_.set(0x8000, 0x01); // Operand at effective address
    auto cyclesLeft = cpu_.execute(4, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ((uint8_t)cpu_.A, SIGNED_BYTE(-2)); // -2 in 8-bit representation
    EXPECT_EQ((uint8_t)cpu_.C, 0);
    EXPECT_EQ((uint8_t)cpu_.N, 1);
    EXPECT_EQ((uint8_t)cpu_.V, 0);
    EXPECT_EQ((uint8_t)cpu_.Z, 0);
}

////

TEST_F(TEST_6502, SBC_ABS_canSubtractTwoNegativeNumbersAndGetSignedOverflow) 
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.A = SIGNED_BYTE(-128);
    cpu_.C = 1; // Carry is set to true
    mem_.set(0xFF00, CPU::INS_SBC_ABS);
    mem_.set(0xFF01, 0x00);
    mem_.set(0xFF02, 0x80);
    mem_.set(0x8000, 0x01); // Operand at effective address
    auto cyclesLeft = cpu_.execute(4, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ((uint8_t)cpu_.A, 127);
    EXPECT_EQ((uint8_t)cpu_.C, 1);
    EXPECT_EQ((uint8_t)cpu_.N, 0);
    EXPECT_EQ((uint8_t)cpu_.V, 1);
    EXPECT_EQ((uint8_t)cpu_.Z, 0);
}

TEST_F(TEST_6502, SBC_ABS_canSubtractAPositiveAndNegativeNumberAndGetSignedOverflow) 
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.A = 127;
    cpu_.C = 1; // Carry is set to true
    mem_.set(0xFF00, CPU::INS_SBC_ABS);
    mem_.set(0xFF01, 0x00);
    mem_.set(0xFF02, 0x80);
    mem_.set(0x8000, SIGNED_BYTE(-1)); // Operand at effective address
    auto cyclesLeft = cpu_.execute(4, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ((uint8_t)cpu_.A, 128);
    EXPECT_EQ((uint8_t)cpu_.C, 0);
    EXPECT_EQ((uint8_t)cpu_.N, 1);
    EXPECT_EQ((uint8_t)cpu_.V, 1);
    EXPECT_EQ((uint8_t)cpu_.Z, 0);
}

TEST_F(TEST_6502, SBC_ABS_canSubtractTwoUnsignedNumbers) 
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.A = 20;
    cpu_.C = 1; // Carry is set to true
    mem_.set(0xFF00, CPU::INS_SBC_ABS);
    mem_.set(0xFF01, 0x00);
    mem_.set(0xFF02, 0x80);
    mem_.set(0x8000, 17); // Operand at effective address
    auto cyclesLeft = cpu_.execute(4, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ((uint8_t)cpu_.A, 3);
    EXPECT_EQ((uint8_t)cpu_.C, 1);
    EXPECT_EQ((uint8_t)cpu_.N, 0);
    EXPECT_EQ((uint8_t)cpu_.V, 0);
    EXPECT_EQ((uint8_t)cpu_.Z, 0);
}

TEST_F(TEST_6502, SBC_ABS_canSubtractTwoNegativeNumbers) 
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.A = SIGNED_BYTE(-20);
    cpu_.C = 1; // Carry is set to true
    mem_.set(0xFF00, CPU::INS_SBC_ABS);
    mem_.set(0xFF01, 0x00);
    mem_.set(0xFF02, 0x80);
    mem_.set(0x8000, SIGNED_BYTE(-17)); // Operand at effective address
    auto cyclesLeft = cpu_.execute(4, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ((uint8_t)cpu_.A, SIGNED_BYTE(-3));
    EXPECT_EQ((uint8_t)cpu_.C, 0);
    EXPECT_EQ((uint8_t)cpu_.N, 1);
    EXPECT_EQ((uint8_t)cpu_.V, 0);
    EXPECT_EQ((uint8_t)cpu_.Z, 0);
}

TEST_F(TEST_6502, SBC_ZP_canSubtractZeroFromZeroAndGetZero) 
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.A = 0;
    cpu_.C = 1; // Carry is set to true
    mem_.set(0xFF00, CPU::INS_SBC_ZP);
    mem_.set(0xFF01, 0x10); // Zero page address
    mem_.set(0x0010, 0x00); // Operand at zero page address
    auto cyclesLeft = cpu_.execute(3, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ((uint8_t)cpu_.A, 0x00);
    EXPECT_EQ((uint8_t)cpu_.C, 1);
    EXPECT_EQ((uint8_t)cpu_.N, 0);
    EXPECT_EQ((uint8_t)cpu_.V, 0);
    EXPECT_EQ((uint8_t)cpu_.Z, 1);
}

TEST_F(TEST_6502, SBC_ZP_canSubtractZeroFromZeroAndCarryAndGetMinusOne) 
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.A = 0;
    cpu_.C = 0; // Carry is set to false
    mem_.set(0xFF00, CPU::INS_SBC_ZP);
    mem_.set(0xFF01, 0x10); // Zero page address
    mem_.set(0x0010, 0x00); // Operand at zero page address
    auto cyclesLeft = cpu_.execute(3, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ((uint8_t)cpu_.A, SIGNED_BYTE(-1));
    EXPECT_EQ((uint8_t)cpu_.C, 0);
    EXPECT_EQ((uint8_t)cpu_.N, 1);
    EXPECT_EQ((uint8_t)cpu_.V, 0);
    EXPECT_EQ((uint8_t)cpu_.Z, 0);
}

TEST_F(TEST_6502, SBC_ZP_canSubtractOneFromZeroAndGetMinusOne) 
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.A = 0;
    cpu_.C = 1; // Carry is set to true
    mem_.set(0xFF00, CPU::INS_SBC_ZP);
    mem_.set(0xFF01, 0x10); // Zero page address
    mem_.set(0x0010, 0x01); // Operand at zero page address
    auto cyclesLeft = cpu_.execute(3, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ((uint8_t)cpu_.A, SIGNED_BYTE(-1));
    EXPECT_EQ((uint8_t)cpu_.C, 0);
    EXPECT_EQ((uint8_t)cpu_.N, 1);
    EXPECT_EQ((uint8_t)cpu_.V, 0);
    EXPECT_EQ((uint8_t)cpu_.Z, 0);
}

TEST_F(TEST_6502, SBC_ZP_canSubtractOneFromZeroWithCarryAndGetMinusTwo) 
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.A = 0;
    cpu_.C = 0; // Carry is set to false
    mem_.set(0xFF00, CPU::INS_SBC_ZP);
    mem_.set(0xFF01, 0x10); // Zero page address
    mem_.set(0x0010, 0x01); // Operand at zero page address
    auto cyclesLeft = cpu_.execute(3, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ((uint8_t)cpu_.A, SIGNED_BYTE(-2));
    EXPECT_EQ((uint8_t)cpu_.C, 0);
    EXPECT_EQ((uint8_t)cpu_.N, 1);
    EXPECT_EQ((uint8_t)cpu_.V, 0);
    EXPECT_EQ((uint8_t)cpu_.Z, 0);
}

TEST_F(TEST_6502, SBC_ZP_canSubtractTwoNegativeNumbersAndGetSignedOverflow) 
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.A = SIGNED_BYTE(-128);
    cpu_.C = 1; // Carry is set to true
    mem_.set(0xFF00, CPU::INS_SBC_ZP);
    mem_.set(0xFF01, 0x10); // Zero page address
    mem_.set(0x0010, 0x01); // Operand at zero page address
    auto cyclesLeft = cpu_.execute(3, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ((uint8_t)cpu_.A, 127);
    EXPECT_EQ((uint8_t)cpu_.C, 1);
    EXPECT_EQ((uint8_t)cpu_.N, 0);
    EXPECT_EQ((uint8_t)cpu_.V, 1);
    EXPECT_EQ((uint8_t)cpu_.Z, 0);
}

TEST_F(TEST_6502, SBC_ZP_canSubtractAPositiveAndNegativeNumberAndGetSignedOverflow) 
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.A = 127;
    cpu_.C = 1; // Carry is set to true
    mem_.set(0xFF00, CPU::INS_SBC_ZP);
    mem_.set(0xFF01, 0x10); // Zero page address
    mem_.set(0x0010, SIGNED_BYTE(-1)); // Operand at zero page address
    auto cyclesLeft = cpu_.execute(3, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ((uint8_t)cpu_.A, 128);
    EXPECT_EQ((uint8_t)cpu_.C, 0);
    EXPECT_EQ((uint8_t)cpu_.N, 1);
    EXPECT_EQ((uint8_t)cpu_.V, 1);
    EXPECT_EQ((uint8_t)cpu_.Z, 0);
}

TEST_F(TEST_6502, SBC_ZP_canSubtractTwoUnsignedNumbers) 
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.A = 20;
    cpu_.C = 1; // Carry is set to true
    mem_.set(0xFF00, CPU::INS_SBC_ZP);
    mem_.set(0xFF01, 0x10); // Zero page address
    mem_.set(0x0010, 17); // Operand at zero page address
    auto cyclesLeft = cpu_.execute(3, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ((uint8_t)cpu_.A, 3);
    EXPECT_EQ((uint8_t)cpu_.C, 1);
    EXPECT_EQ((uint8_t)cpu_.N, 0);
    EXPECT_EQ((uint8_t)cpu_.V, 0);
    EXPECT_EQ((uint8_t)cpu_.Z, 0);
}

TEST_F(TEST_6502, SBC_ZP_canSubtractTwoNegativeNumbers) 
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.A = SIGNED_BYTE(-20);
    cpu_.C = 1; // Carry is set to true
    mem_.set(0xFF00, CPU::INS_SBC_ZP);
    mem_.set(0xFF01, 0x10); // Zero page address
    mem_.set(0x0010, SIGNED_BYTE(-17)); // Operand at zero page address
    auto cyclesLeft = cpu_.execute(3, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ((uint8_t)cpu_.A, SIGNED_BYTE(-3));
    EXPECT_EQ((uint8_t)cpu_.C, 0);
    EXPECT_EQ((uint8_t)cpu_.N, 1);
    EXPECT_EQ((uint8_t)cpu_.V, 0);
    EXPECT_EQ((uint8_t)cpu_.Z, 0);
}


//////Immediate
TEST_F(TEST_6502, SBC_IM_canSubtractZeroFromZeroAndGetZero) 
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.A = 0;
    cpu_.C = 1; // Carry is set to true
    mem_.set(0xFF00, CPU::INS_SBC_IM);
    mem_.set(0xFF01, 0x00); // Immediate value
    auto cyclesLeft = cpu_.execute(2, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ(cpu_.A, 0);
    EXPECT_EQ(cpu_.C, 1);
    EXPECT_EQ(cpu_.N, 0);
    EXPECT_EQ(cpu_.V, 0);
    EXPECT_EQ(cpu_.Z, 1);
}

TEST_F(TEST_6502, SBC_IM_canSubtractZeroFromZeroAndCarryAndGetMinusOne) 
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.A = 0;
    cpu_.C = 0; // Carry is set to false
    mem_.set(0xFF00, CPU::INS_SBC_IM);
    mem_.set(0xFF01, 0x00); // Immediate value
    auto cyclesLeft = cpu_.execute(2, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ((uint8_t)cpu_.A, SIGNED_BYTE(-1));
    EXPECT_EQ(cpu_.C, 0);
    EXPECT_EQ(cpu_.N, 1);
    EXPECT_EQ(cpu_.V, 0);
    EXPECT_EQ(cpu_.Z, 0);
}

TEST_F(TEST_6502, SBC_IM_canSubtractOneFromZeroAndGetMinusOne) 
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.A = 0;
    cpu_.C = 1; // Carry is set to true
    mem_.set(0xFF00, CPU::INS_SBC_IM);
    mem_.set(0xFF01, 0x01); // Immediate value
    auto cyclesLeft = cpu_.execute(2, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ((uint8_t)cpu_.A, SIGNED_BYTE(-1));
    EXPECT_EQ(cpu_.C, 0);
    EXPECT_EQ(cpu_.N, 1);
    EXPECT_EQ(cpu_.V, 0);
    EXPECT_EQ(cpu_.Z, 0);
}

TEST_F(TEST_6502, SBC_IM_canSubtractOneFromZeroWithCarryAndGetMinusTwo) 
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.A = 0;
    cpu_.C = 0; // Carry is set to false
    mem_.set(0xFF00, CPU::INS_SBC_IM);
    mem_.set(0xFF01, 0x01); // Immediate value
    auto cyclesLeft = cpu_.execute(2, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ((uint8_t)cpu_.A, SIGNED_BYTE(-2));
    EXPECT_EQ(cpu_.C, 0);
    EXPECT_EQ(cpu_.N, 1);
    EXPECT_EQ(cpu_.V, 0);
    EXPECT_EQ(cpu_.Z, 0);
}

TEST_F(TEST_6502, SBC_IM_canSubtractTwoNegativeNumbersAndGetSignedOverflow) 
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.A = SIGNED_BYTE(-128);
    cpu_.C = 1; // Carry is set to true
    mem_.set(0xFF00, CPU::INS_SBC_IM);
    mem_.set(0xFF01, 0x01); // Immediate value
    auto cyclesLeft = cpu_.execute(2, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ((uint8_t)cpu_.A, 127);
    EXPECT_EQ(cpu_.C, 1);
    EXPECT_EQ(cpu_.N, 0);
    EXPECT_EQ(cpu_.V, 1);
    EXPECT_EQ(cpu_.Z, 0);
}

TEST_F(TEST_6502, SBC_IM_canSubtractAPositiveAndNegativeNumberAndGetSignedOverflow) 
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.A = 127;
    cpu_.C = 1; // Carry is set to true
    mem_.set(0xFF00, CPU::INS_SBC_IM);
    mem_.set(0xFF01, SIGNED_BYTE(-1)); // Immediate value
    auto cyclesLeft = cpu_.execute(2, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ((uint8_t)cpu_.A, 128);
    EXPECT_EQ(cpu_.C, 0);
    EXPECT_EQ(cpu_.N, 1);
    EXPECT_EQ(cpu_.V, 1);
    EXPECT_EQ(cpu_.Z, 0);
}

TEST_F(TEST_6502, SBC_IM_canSubtractTwoUnsignedNumbers) 
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.A = 20;
    cpu_.C = 1; // Carry is set to true
    mem_.set(0xFF00, CPU::INS_SBC_IM);
    mem_.set(0xFF01, 0x11); // Immediate value
    auto cyclesLeft = cpu_.execute(2, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ(cpu_.A, 3);
    EXPECT_EQ(cpu_.C, 1);
    EXPECT_EQ(cpu_.N, 0);
    EXPECT_EQ(cpu_.V, 0);
    EXPECT_EQ(cpu_.Z, 0);
}

TEST_F(TEST_6502, SBC_IM_canSubtractTwoNegativeNumbers) 
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.A = SIGNED_BYTE(-20);
    cpu_.C = 1; // Carry is set to true
    mem_.set(0xFF00, CPU::INS_SBC_IM);
    mem_.set(0xFF01, SIGNED_BYTE(-17)); // Immediate value
    auto cyclesLeft = cpu_.execute(2, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ((uint8_t)cpu_.A, SIGNED_BYTE(-3));
    EXPECT_EQ(cpu_.C, 0);
    EXPECT_EQ(cpu_.N, 1);
    EXPECT_EQ(cpu_.V, 0);
    EXPECT_EQ(cpu_.Z, 0);
}

TEST_F(TEST_6502, SBC_ZPX_canSubtractZeroFromZeroAndGetZero) 
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.A = 0;
    cpu_.C = 1; // Carry is set to true
    mem_.set(0xFF00, CPU::INS_SBC_ZPX);
    mem_.set(0xFF01, 0x10); // Zero page address
    cpu_.X = 0x00;
    mem_.set(0x0010, 0x00); // Operand at zero page address + X
    auto cyclesLeft = cpu_.execute(4, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ(cpu_.A, 0);
    EXPECT_EQ(cpu_.C, 1);
    EXPECT_EQ(cpu_.N, 0);
    EXPECT_EQ(cpu_.V, 0);
    EXPECT_EQ(cpu_.Z, 1);
}

TEST_F(TEST_6502, SBC_ZPX_canSubtractZeroFromZeroAndCarryAndGetMinusOne) 
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.A = 0;
    cpu_.C = 0; // Carry is set to false
    mem_.set(0xFF00, CPU::INS_SBC_ZPX);
    mem_.set(0xFF01, 0x10); // Zero page address
    cpu_.X = 0x00;
    mem_.set(0x0010, 0x00); // Operand at zero page address + X
    auto cyclesLeft = cpu_.execute(4, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ((uint8_t)cpu_.A, SIGNED_BYTE(-1));
    EXPECT_EQ(cpu_.C, 0);
    EXPECT_EQ(cpu_.N, 1);
    EXPECT_EQ(cpu_.V, 0);
    EXPECT_EQ(cpu_.Z, 0);
}

TEST_F(TEST_6502, SBC_ZPX_canSubtractOneFromZeroAndGetMinusOne) 
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.A = 0;
    cpu_.C = 1; // Carry is set to true
    mem_.set(0xFF00, CPU::INS_SBC_ZPX);
    mem_.set(0xFF01, 0x10); // Zero page address
    cpu_.X = 0x00;
    mem_.set(0x0010, 0x01); // Operand at zero page address + X
    auto cyclesLeft = cpu_.execute(4, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ((uint8_t)cpu_.A, SIGNED_BYTE(-1));
    EXPECT_EQ(cpu_.C, 0);
    EXPECT_EQ(cpu_.N, 1);
    EXPECT_EQ(cpu_.V, 0);
    EXPECT_EQ(cpu_.Z, 0);
}

TEST_F(TEST_6502, SBC_ZPX_canSubtractOneFromZeroWithCarryAndGetMinusTwo) 
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.A = 0;
    cpu_.C = 0; // Carry is set to false
    mem_.set(0xFF00, CPU::INS_SBC_ZPX);
    mem_.set(0xFF01, 0x10); // Zero page address
    cpu_.X = 0x00;
    mem_.set(0x0010, 0x01); // Operand at zero page address + X
    auto cyclesLeft = cpu_.execute(4, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ((uint8_t)cpu_.A, SIGNED_BYTE(-2));
    EXPECT_EQ(cpu_.C, 0);
    EXPECT_EQ(cpu_.N, 1);
    EXPECT_EQ(cpu_.V, 0);
    EXPECT_EQ(cpu_.Z, 0);
}

TEST_F(TEST_6502, SBC_ZPX_canSubtractTwoNegativeNumbersAndGetSignedOverflow) 
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.A = SIGNED_BYTE(-128);
    cpu_.C = 1; // Carry is set to true
    mem_.set(0xFF00, CPU::INS_SBC_ZPX);
    mem_.set(0xFF01, 0x10); // Zero page address
    cpu_.X = 0x00;
    mem_.set(0x0010, 0x01); // Operand at zero page address + X
    auto cyclesLeft = cpu_.execute(4, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ((uint8_t)cpu_.A, 127);
    EXPECT_EQ(cpu_.C, 1);
    EXPECT_EQ(cpu_.N, 0);
    EXPECT_EQ(cpu_.V, 1);
    EXPECT_EQ(cpu_.Z, 0);
}

TEST_F(TEST_6502, SBC_ZPX_canSubtractAPositiveAndNegativeNumberAndGetSignedOverflow) 
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.A = 127;
    cpu_.C = 1; // Carry is set to true
    mem_.set(0xFF00, CPU::INS_SBC_ZPX);
    mem_.set(0xFF01, 0x10); // Zero page address
    cpu_.X = 0x00;
    mem_.set(0x0010, SIGNED_BYTE(-1)); // Operand at zero page address + X
    auto cyclesLeft = cpu_.execute(4, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ((uint8_t)cpu_.A, 128);
    EXPECT_EQ(cpu_.C, 0);
    EXPECT_EQ(cpu_.N, 1);
    EXPECT_EQ(cpu_.V, 1);
    EXPECT_EQ(cpu_.Z, 0);
}

TEST_F(TEST_6502, SBC_ZPX_canSubtractTwoUnsignedNumbers) 
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.A = 20;
    cpu_.C = 1; // Carry is set to true
    mem_.set(0xFF00, CPU::INS_SBC_ZPX);
    mem_.set(0xFF01, 0x10); // Zero page address
    cpu_.X = 0x00;
    mem_.set(0x0010, 0x11); // Operand at zero page address + X
    auto cyclesLeft = cpu_.execute(4, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ(cpu_.A, 3);
    EXPECT_EQ(cpu_.C, 1);
    EXPECT_EQ(cpu_.N, 0);
    EXPECT_EQ(cpu_.V, 0);
    EXPECT_EQ(cpu_.Z, 0);
}

TEST_F(TEST_6502, SBC_ZPX_canSubtractTwoNegativeNumbers)
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.A = SIGNED_BYTE(-20);
    cpu_.C = 1; // Carry is set to true
    mem_.set(0xFF00, CPU::INS_SBC_ZPX);
    mem_.set(0xFF01, 0x10); // Zero page address
    cpu_.X = 0x00;
    mem_.set(0x0010, SIGNED_BYTE(-17)); // Operand at zero page address + X
    auto cyclesLeft = cpu_.execute(4, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ((uint8_t)cpu_.A, SIGNED_BYTE(-3));
    EXPECT_EQ(cpu_.C, 0);
    EXPECT_EQ(cpu_.N, 1);
    EXPECT_EQ(cpu_.V, 0);
    EXPECT_EQ(cpu_.Z, 0);
}

TEST_F(TEST_6502, SBC_ABSX_canSubtractZeroFromZeroAndGetZero)
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.A = 0;
    cpu_.C = 1; // Carry is set to true
    mem_.set(0xFF00, CPU::INS_SBC_ABSX);
    mem_.set(0xFF01, 0x10); // Absolute address low byte
    mem_.set(0xFF02, 0x20); // Absolute address high byte
    cpu_.X = 0x00;
    mem_.set(0x2010, 0x00); // Operand at absolute address + X
    auto cyclesLeft = cpu_.execute(4, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ(cpu_.A, 0);
    EXPECT_EQ(cpu_.C, 1);
    EXPECT_EQ(cpu_.N, 0);
    EXPECT_EQ(cpu_.V, 0);
    EXPECT_EQ(cpu_.Z, 1);
}

TEST_F(TEST_6502, SBC_ABSX_canSubtractZeroFromZeroAndCarryAndGetMinusOne)
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.A = 0;
    cpu_.C = 0; // Carry is set to false
    mem_.set(0xFF00, CPU::INS_SBC_ABSX);
    mem_.set(0xFF01, 0x10); // Absolute address low byte
    mem_.set(0xFF02, 0x20); // Absolute address high byte
    cpu_.X = 0x00;
    mem_.set(0x2010, 0x00); // Operand at absolute address + X
    auto cyclesLeft = cpu_.execute(4, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ((uint8_t)cpu_.A, SIGNED_BYTE(-1));
    EXPECT_EQ(cpu_.C, 0);
    EXPECT_EQ(cpu_.N, 1);
    EXPECT_EQ(cpu_.V, 0);
    EXPECT_EQ(cpu_.Z, 0);
}

TEST_F(TEST_6502, SBC_ABSX_canSubtractOneFromZeroAndGetMinusOne)
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.A = 0;
    cpu_.C = 1; // Carry is set to true
    mem_.set(0xFF00, CPU::INS_SBC_ABSX);
    mem_.set(0xFF01, 0x10); // Absolute address low byte
    mem_.set(0xFF02, 0x20); // Absolute address high byte
    cpu_.X = 0x00;
    mem_.set(0x2010, 0x01); // Operand at absolute address + X
    auto cyclesLeft = cpu_.execute(4, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ((uint8_t)cpu_.A, SIGNED_BYTE(-1));
    EXPECT_EQ(cpu_.C, 0);
    EXPECT_EQ(cpu_.N, 1);
    EXPECT_EQ(cpu_.V, 0);
    EXPECT_EQ(cpu_.Z, 0);
}

TEST_F(TEST_6502, SBC_ABSX_canSubtractOneFromZeroWithCarryAndGetMinusTwo)
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.A = 0;
    cpu_.C = 0; // Carry is set to false
    mem_.set(0xFF00, CPU::INS_SBC_ABSX);
    mem_.set(0xFF01, 0x10); // Absolute address low byte
    mem_.set(0xFF02, 0x20); // Absolute address high byte
    cpu_.X = 0x00;
    mem_.set(0x2010, 0x01); // Operand at absolute address + X
    auto cyclesLeft = cpu_.execute(4, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ((uint8_t)cpu_.A, SIGNED_BYTE(-2));
    EXPECT_EQ(cpu_.C, 0);
    EXPECT_EQ(cpu_.N, 1);
    EXPECT_EQ(cpu_.V, 0);
    EXPECT_EQ(cpu_.Z, 0);
}

TEST_F(TEST_6502, SBC_ABSX_canSubtractTwoNegativeNumbersAndGetSignedOverflow)
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.A = SIGNED_BYTE(-128);
    cpu_.C = 1; // Carry is set to true
    mem_.set(0xFF00, CPU::INS_SBC_ABSX);
    mem_.set(0xFF01, 0x10); // Absolute address low byte
    mem_.set(0xFF02, 0x20); // Absolute address high byte
    cpu_.X = 0x00;
    mem_.set(0x2010, 0x01); // Operand at absolute address + X
    auto cyclesLeft = cpu_.execute(4, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ((uint8_t)cpu_.A, 127);
    EXPECT_EQ(cpu_.C, 1);
    EXPECT_EQ(cpu_.N, 0);
    EXPECT_EQ(cpu_.V, 1);
    EXPECT_EQ(cpu_.Z, 0);
}

TEST_F(TEST_6502, SBC_ABSX_canSubtractAPositiveAndNegativeNumbersAndGetSignedOverflow)
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.A = 127;
    cpu_.C = 1; // Carry is set to true
    mem_.set(0xFF00, CPU::INS_SBC_ABSX);
    mem_.set(0xFF01, 0x10); // Absolute address low byte
    mem_.set(0xFF02, 0x20); // Absolute address high byte
    cpu_.X = 0x00;
    mem_.set(0x2010, SIGNED_BYTE(-1)); // Operand at absolute address + X
    auto cyclesLeft = cpu_.execute(4, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ((uint8_t)cpu_.A, 128);
    EXPECT_EQ(cpu_.C, 0);
    EXPECT_EQ(cpu_.N, 1);
    EXPECT_EQ(cpu_.V, 1);
    EXPECT_EQ(cpu_.Z, 0);
}

TEST_F(TEST_6502, SBC_ABSX_canSubtractTwoUnsignedNumbers)
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.A = 20;
    cpu_.C = 1; // Carry is set to true
    mem_.set(0xFF00, CPU::INS_SBC_ABSX);
    mem_.set(0xFF01, 0x10); // Absolute address low byte
    mem_.set(0xFF02, 0x20); // Absolute address high byte
    cpu_.X = 0x00;
    mem_.set(0x2010, 0x11); // Operand at absolute address + X
    auto cyclesLeft = cpu_.execute(4, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ(cpu_.A, 3);
    EXPECT_EQ(cpu_.C, 1);
    EXPECT_EQ(cpu_.N, 0);
    EXPECT_EQ(cpu_.V, 0);
    EXPECT_EQ(cpu_.Z, 0);
}

TEST_F(TEST_6502, SBC_ABSX_canSubtractTwoNegativeNumbers)
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.A = SIGNED_BYTE(-20);
    cpu_.C = 1; // Carry is set to true
    mem_.set(0xFF00, CPU::INS_SBC_ABSX);
    mem_.set(0xFF01, 0x10); // Absolute address low byte
    mem_.set(0xFF02, 0x20); // Absolute address high byte
    cpu_.X = 0x00;
    mem_.set(0x2010, SIGNED_BYTE(-17)); // Operand at absolute address + X
    auto cyclesLeft = cpu_.execute(4, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ((uint8_t)cpu_.A, SIGNED_BYTE(-3));
    EXPECT_EQ(cpu_.C, 0);
    EXPECT_EQ(cpu_.N, 1);
    EXPECT_EQ(cpu_.V, 0);
    EXPECT_EQ(cpu_.Z, 0);
}

// SBC Absolute, Y

TEST_F(TEST_6502, SBC_ABSY_canSubtractZeroFromZeroAndGetZero)
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.A = 0;
    cpu_.C = 1; // Carry is set to true
    mem_.set(0xFF00, CPU::INS_SBC_ABSY);
    mem_.set(0xFF01, 0x10); // Absolute address low byte
    mem_.set(0xFF02, 0x20); // Absolute address high byte
    cpu_.Y = 0x00;
    mem_.set(0x2010, 0x00); // Operand at absolute address + Y
    auto cyclesLeft = cpu_.execute(4, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ(cpu_.A, 0);
    EXPECT_EQ(cpu_.C, 1);
    EXPECT_EQ(cpu_.N, 0);
    EXPECT_EQ(cpu_.V, 0);
    EXPECT_EQ(cpu_.Z, 1);
}

TEST_F(TEST_6502, SBC_ABSY_canSubtractZeroFromZeroAndCarryAndGetMinusOne)
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.A = 0;
    cpu_.C = 0; // Carry is set to false
    mem_.set(0xFF00, CPU::INS_SBC_ABSY);
    mem_.set(0xFF01, 0x10); // Absolute address low byte
    mem_.set(0xFF02, 0x20); // Absolute address high byte
    cpu_.Y = 0x00;
    mem_.set(0x2010, 0x00); // Operand at absolute address + Y
    auto cyclesLeft = cpu_.execute(4, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ((uint8_t)cpu_.A, SIGNED_BYTE(-1));
    EXPECT_EQ(cpu_.C, 0);
    EXPECT_EQ(cpu_.N, 1);
    EXPECT_EQ(cpu_.V, 0);
    EXPECT_EQ(cpu_.Z, 0);
}

TEST_F(TEST_6502, SBC_ABSY_canSubtractOneFromZeroAndGetMinusOne)
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.A = 0;
    cpu_.C = 1; // Carry is set to true
    mem_.set(0xFF00, CPU::INS_SBC_ABSY);
    mem_.set(0xFF01, 0x10); // Absolute address low byte
    mem_.set(0xFF02, 0x20); // Absolute address high byte
    cpu_.Y = 0x00;
    mem_.set(0x2010, 0x01); // Operand at absolute address + Y
    auto cyclesLeft = cpu_.execute(4, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ((uint8_t)cpu_.A, SIGNED_BYTE(-1));
    EXPECT_EQ(cpu_.C, 0);
    EXPECT_EQ(cpu_.N, 1);
    EXPECT_EQ(cpu_.V, 0);
    EXPECT_EQ(cpu_.Z, 0);
}

TEST_F(TEST_6502, SBC_ABSY_canSubtractOneFromZeroWithCarryAndGetMinusTwo)
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.A = 0;
    cpu_.C = 0; // Carry is set to false
    mem_.set(0xFF00, CPU::INS_SBC_ABSY);
    mem_.set(0xFF01, 0x10); // Absolute address low byte
    mem_.set(0xFF02, 0x20); // Absolute address high byte
    cpu_.Y = 0x00;
    mem_.set(0x2010, 0x01); // Operand at absolute address + Y
    auto cyclesLeft = cpu_.execute(4, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ((uint8_t)cpu_.A, SIGNED_BYTE(-2));
    EXPECT_EQ(cpu_.C, 0);
    EXPECT_EQ(cpu_.N, 1);
    EXPECT_EQ(cpu_.V, 0);
    EXPECT_EQ(cpu_.Z, 0);
}

TEST_F(TEST_6502, SBC_ABSY_canSubtractTwoNegativeNumbersAndGetSignedOverflow)
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.A = SIGNED_BYTE(-128);
    cpu_.C = 1; // Carry is set to true
    mem_.set(0xFF00, CPU::INS_SBC_ABSY);
    mem_.set(0xFF01, 0x10); // Absolute address low byte
    mem_.set(0xFF02, 0x20); // Absolute address high byte
    cpu_.Y = 0x00;
    mem_.set(0x2010, 0x01); // Operand at absolute address + Y
    auto cyclesLeft = cpu_.execute(4, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ((uint8_t)cpu_.A, 127);
    EXPECT_EQ(cpu_.C, 1);
    EXPECT_EQ(cpu_.N, 0);
    EXPECT_EQ(cpu_.V, 1);
    EXPECT_EQ(cpu_.Z, 0);
}

TEST_F(TEST_6502, SBC_ABSY_canSubtractAPositiveAndNegativeNumbersAndGetSignedOverflow)
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.A = 127;
    cpu_.C = 1; // Carry is set to true
    mem_.set(0xFF00, CPU::INS_SBC_ABSY);
    mem_.set(0xFF01, 0x10); // Absolute address low byte
    mem_.set(0xFF02, 0x20); // Absolute address high byte
    cpu_.Y = 0x00;
    mem_.set(0x2010, SIGNED_BYTE(-1)); // Operand at absolute address + Y
    auto cyclesLeft = cpu_.execute(4, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ((uint8_t)cpu_.A, 128);
    EXPECT_EQ(cpu_.C, 0);
    EXPECT_EQ(cpu_.N, 1);
    EXPECT_EQ(cpu_.V, 1);
    EXPECT_EQ(cpu_.Z, 0);
}

TEST_F(TEST_6502, SBC_ABSY_canSubtractTwoUnsignedNumbers)
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.A = 20;
    cpu_.C = 1; // Carry is set to true
    mem_.set(0xFF00, CPU::INS_SBC_ABSY);
    mem_.set(0xFF01, 0x10); // Absolute address low byte
    mem_.set(0xFF02, 0x20); // Absolute address high byte
    cpu_.Y = 0x00;
    mem_.set(0x2010, 0x11); // Operand at absolute address + Y
    auto cyclesLeft = cpu_.execute(4, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ(cpu_.A, 3);
    EXPECT_EQ(cpu_.C, 1);
    EXPECT_EQ(cpu_.N, 0);
    EXPECT_EQ(cpu_.V, 0);
    EXPECT_EQ(cpu_.Z, 0);
}

TEST_F(TEST_6502, SBC_ABSY_canSubtractTwoNegativeNumbers)
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.A = SIGNED_BYTE(-20);
    cpu_.C = 1; // Carry is set to true
    mem_.set(0xFF00, CPU::INS_SBC_ABSY);
    mem_.set(0xFF01, 0x10); // Absolute address low byte
    mem_.set(0xFF02, 0x20); // Absolute address high byte
    cpu_.Y = 0x00;
    mem_.set(0x2010, SIGNED_BYTE(-17)); // Operand at absolute address + Y
    auto cyclesLeft = cpu_.execute(4, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ((uint8_t)cpu_.A, SIGNED_BYTE(-3));
    EXPECT_EQ(cpu_.C, 0);
    EXPECT_EQ(cpu_.N, 1);
    EXPECT_EQ(cpu_.V, 0);
    EXPECT_EQ(cpu_.Z, 0);
}

// SBC Indirect, X

TEST_F(TEST_6502, SBC_INDX_canSubtractZeroFromZeroAndGetZero)
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.A = 0;
    cpu_.C = 1; // Carry is set to true
    mem_.set(0xFF00, CPU::INS_SBC_INDX);
    mem_.set(0xFF01, 0x10); // Zero page address
    cpu_.X = 0x00;
    mem_.set(0x0010, 0x20); // Operand low byte at zero page address + X
    mem_.set(0x0011, 0x00); // Operand high byte at zero page address + X
    mem_.set(0x2000, 0x00); // Operand at final address
    auto cyclesLeft = cpu_.execute(6, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ(cpu_.A, 0);
    EXPECT_EQ(cpu_.C, 1);
    EXPECT_EQ(cpu_.N, 0);
    EXPECT_EQ(cpu_.V, 0);
    EXPECT_EQ(cpu_.Z, 1);
}

TEST_F(TEST_6502, SBC_INDX_canSubtractZeroFromZeroAndCarryAndGetMinusOne)
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.A = 0;
    cpu_.C = 0; // Carry is set to false
    mem_.set(0xFF00, CPU::INS_SBC_INDX);
    mem_.set(0xFF01, 0x10); // Zero page address
    cpu_.X = 0x00;
    mem_.set(0x0010, 0x20); // Operand low byte at zero page address + X
    mem_.set(0x0011, 0x00); // Operand high byte at zero page address + X
    mem_.set(0x2000, 0x00); // Operand at final address
    auto cyclesLeft = cpu_.execute(6, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ((uint8_t)cpu_.A, SIGNED_BYTE(-1));
    EXPECT_EQ(cpu_.C, 0);
    EXPECT_EQ(cpu_.N, 1);
    EXPECT_EQ(cpu_.V, 0);
    EXPECT_EQ(cpu_.Z, 0);
}

TEST_F(TEST_6502, SBC_INDX_canSubtractOneFromZeroAndGetMinusOne)
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.A = 0;
    cpu_.C = 1; // Carry is set to true
    mem_.set(0xFF00, CPU::INS_SBC_INDX);
    mem_.set(0xFF01, 0x10); // Zero page address
    cpu_.X = 0x00;
    mem_.set(0x0010, 0x00); // Operand low byte at zero page address + X
    mem_.set(0x0011, 0x20); // Operand high byte at zero page address + X
    mem_.set(0x2000, 0x01); // Operand at final address
    auto cyclesLeft = cpu_.execute(6, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ((uint8_t)cpu_.A, SIGNED_BYTE(-1));
    EXPECT_EQ(cpu_.C, 0);
    EXPECT_EQ(cpu_.N, 1);
    EXPECT_EQ(cpu_.V, 0);
    EXPECT_EQ(cpu_.Z, 0);
}

TEST_F(TEST_6502, SBC_INDX_canSubtractOneFromZeroWithCarryAndGetMinusTwo)
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.A = 0;
    cpu_.C = 0; // Carry is set to false
    mem_.set(0xFF00, CPU::INS_SBC_INDX);
    mem_.set(0xFF01, 0x10); // Zero page address
    cpu_.X = 0x00;
    mem_.set(0x0010, 0x00); // Operand low byte at zero page address + X
    mem_.set(0x0011, 0x20); // Operand high byte at zero page address + X
    mem_.set(0x2000, 0x01); // Operand at final address
    auto cyclesLeft = cpu_.execute(6, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ((uint8_t)cpu_.A, SIGNED_BYTE(-2));
    EXPECT_EQ(cpu_.C, 0);
    EXPECT_EQ(cpu_.N, 1);
    EXPECT_EQ(cpu_.V, 0);
    EXPECT_EQ(cpu_.Z, 0);
}

////////////////////here
// SBC Indirect, X

TEST_F(TEST_6502, SBC_INDX_canSubtractTwoNegativeNumbersAndGetSignedOverflow)
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.A = SIGNED_BYTE(-128);
    cpu_.C = 1; // Carry is set to true
    mem_.set(0xFF00, CPU::INS_SBC_INDX);
    mem_.set(0xFF01, 0x10); // Zero page address
    cpu_.X = 0x00;
    mem_.set(0x0010, 0x00); // Operand low byte at zero page address + X
    mem_.set(0x0011, 0x20); // Operand high byte at zero page address + X
    mem_.set(0x2000, 0x01); // Operand at final address
    auto cyclesLeft = cpu_.execute(6, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ((uint8_t)cpu_.A, 127);
    EXPECT_EQ(cpu_.C, 1);
    EXPECT_EQ(cpu_.N, 0);
    EXPECT_EQ(cpu_.V, 1);
    EXPECT_EQ(cpu_.Z, 0);
}

TEST_F(TEST_6502, SBC_INDX_canSubtractAPositiveAndNegativeNumbersAndGetSignedOverflow)
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.A = 127;
    cpu_.C = 1; // Carry is set to true
    mem_.set(0xFF00, CPU::INS_SBC_INDX);
    mem_.set(0xFF01, 0x10); // Zero page address
    cpu_.X = 0x00;
    mem_.set(0x0010, 0x00); // Operand low byte at zero page address + X
    mem_.set(0x0011, 0x20); // Operand high byte at zero page address + X
    mem_.set(0x2000, SIGNED_BYTE(-1)); // Operand at final address
    auto cyclesLeft = cpu_.execute(6, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ((uint8_t)cpu_.A, 128);
    EXPECT_EQ(cpu_.C, 0);
    EXPECT_EQ(cpu_.N, 1);
    EXPECT_EQ(cpu_.V, 1);
    EXPECT_EQ(cpu_.Z, 0);
}

TEST_F(TEST_6502, SBC_INDX_canSubtractTwoUnsignedNumbers)
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.A = 20;
    cpu_.C = 1; // Carry is set to true
    mem_.set(0xFF00, CPU::INS_SBC_INDX);
    mem_.set(0xFF01, 0x10); // Zero page address
    cpu_.X = 0x00;
    mem_.set(0x0010, 0x00); // Operand low byte at zero page address + X
    mem_.set(0x0011, 0x20); // Operand high byte at zero page address + X
    mem_.set(0x2000, 0x11); // Operand at final address
    auto cyclesLeft = cpu_.execute(6, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ(cpu_.A, 3);
    EXPECT_EQ(cpu_.C, 1);
    EXPECT_EQ(cpu_.N, 0);
    EXPECT_EQ(cpu_.V, 0);
    EXPECT_EQ(cpu_.Z, 0);
}

TEST_F(TEST_6502, SBC_INDX_canSubtractTwoNegativeNumbers)
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.A = SIGNED_BYTE(-20);
    cpu_.C = 1; // Carry is set to true
    mem_.set(0xFF00, CPU::INS_SBC_INDX);
    mem_.set(0xFF01, 0x10); // Zero page address
    cpu_.X = 0x00;
    mem_.set(0x0010, 0x00); // Operand low byte at zero page address + X
    mem_.set(0x0011, 0x20); // Operand high byte at zero page address + X
    mem_.set(0x2000, SIGNED_BYTE(-17)); // Operand at final address
    auto cyclesLeft = cpu_.execute(6, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ((uint8_t)cpu_.A, SIGNED_BYTE(-3));
    EXPECT_EQ(cpu_.C, 0);
    EXPECT_EQ(cpu_.N, 1);
    EXPECT_EQ(cpu_.V, 0);
    EXPECT_EQ(cpu_.Z, 0);
}

// SBC Indirect, Y

TEST_F(TEST_6502, SBC_INDY_canSubtractZeroFromZeroAndGetZero)
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.A = 0;
    cpu_.C = 1; // Carry is set to true
    mem_.set(0xFF00, CPU::INS_SBC_INDY);
    mem_.set(0xFF01, 0x10); // Zero page address
    cpu_.Y = 0x00;
    mem_.set(0x0010, 0x00); // Operand low byte at zero page address
    mem_.set(0x0011, 0x20); // Operand high byte at zero page address
    mem_.set(0x2000, 0x00); // Operand at final address + Y
    auto cyclesLeft = cpu_.execute(5, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ(cpu_.A, 0);
    EXPECT_EQ(cpu_.C, 1);
    EXPECT_EQ(cpu_.N, 0);
    EXPECT_EQ(cpu_.V, 0);
    EXPECT_EQ(cpu_.Z, 1);
}

TEST_F(TEST_6502, SBC_INDY_canSubtractZeroFromZeroAndCarryAndGetMinusOne)
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.A = 0;
    cpu_.C = 0; // Carry is set to false
    mem_.set(0xFF00, CPU::INS_SBC_INDY);
    mem_.set(0xFF01, 0x10); // Zero page address
    cpu_.Y = 0x00;
    mem_.set(0x0010, 0x00); // Operand low byte at zero page address
    mem_.set(0x0011, 0x20); // Operand high byte at zero page address
    mem_.set(0x2000, 0x00); // Operand at final address + Y
    auto cyclesLeft = cpu_.execute(5, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ((uint8_t)cpu_.A, SIGNED_BYTE(-1));
    EXPECT_EQ(cpu_.C, 0);
    EXPECT_EQ(cpu_.N, 1);
    EXPECT_EQ(cpu_.V, 0);
    EXPECT_EQ(cpu_.Z, 0);
}

TEST_F(TEST_6502, SBC_INDY_canSubtractOneFromZeroAndGetMinusOne)
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.A = 0;
    cpu_.C = 1; // Carry is set to true
    mem_.set(0xFF00, CPU::INS_SBC_INDY);
    mem_.set(0xFF01, 0x10); // Zero page address
    cpu_.Y = 0x00;
    mem_.set(0x0010, 0x00); // Operand low byte at zero page address
    mem_.set(0x0011, 0x20); // Operand high byte at zero page address
    mem_.set(0x2000, 0x01); // Operand at final address + Y
    auto cyclesLeft = cpu_.execute(5, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ((uint8_t)cpu_.A, SIGNED_BYTE(-1));
    EXPECT_EQ(cpu_.C, 0);
    EXPECT_EQ(cpu_.N, 1);
    EXPECT_EQ(cpu_.V, 0);
    EXPECT_EQ(cpu_.Z, 0);
}

TEST_F(TEST_6502, SBC_INDY_canSubtractOneFromZeroWithCarryAndGetMinusTwo)
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.A = 0;
    cpu_.C = 0; // Carry is set to false
    mem_.set(0xFF00, CPU::INS_SBC_INDY);
    mem_.set(0xFF01, 0x10); // Zero page address
    cpu_.Y = 0x00;
    mem_.set(0x0010, 0x00); // Operand low byte at zero page address
    mem_.set(0x0011, 0x20); // Operand high byte at zero page address
    mem_.set(0x2000, 0x01); // Operand at final address + Y
    auto cyclesLeft = cpu_.execute(5, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ((uint8_t)cpu_.A, SIGNED_BYTE(-2));
    EXPECT_EQ(cpu_.C, 0);
    EXPECT_EQ(cpu_.N, 1);
    EXPECT_EQ(cpu_.V, 0);
    EXPECT_EQ(cpu_.Z, 0);
}

TEST_F(TEST_6502, SBC_INDY_canSubtractTwoNegativeNumbersAndGetSignedOverflow)
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.A = SIGNED_BYTE(-128);
    cpu_.C = 1; // Carry is set to true
    mem_.set(0xFF00, CPU::INS_SBC_INDY);
    mem_.set(0xFF01, 0x10); // Zero page address
    cpu_.Y = 0x00;
    mem_.set(0x0010, 0x00); // Operand low byte at zero page address
    mem_.set(0x0011, 0x20); // Operand high byte at zero page address
    mem_.set(0x2000, 0x01); // Operand at final address + Y
    auto cyclesLeft = cpu_.execute(5, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ((uint8_t)cpu_.A, 127);
    EXPECT_EQ(cpu_.C, 1);
    EXPECT_EQ(cpu_.N, 0);
    EXPECT_EQ(cpu_.V, 1);
    EXPECT_EQ(cpu_.Z, 0);
}

TEST_F(TEST_6502, SBC_INDY_canSubtractAPositiveAndNegativeNumbersAndGetSignedOverflow)
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.A = 127;
    cpu_.C = 1; // Carry is set to true
    mem_.set(0xFF00, CPU::INS_SBC_INDY);
    mem_.set(0xFF01, 0x10); // Zero page address
    cpu_.Y = 0x00;
    mem_.set(0x0010, 0x00); // Operand low byte at zero page address
    mem_.set(0x0011, 0x20); // Operand high byte at zero page address
    mem_.set(0x2000, SIGNED_BYTE(-1)); // Operand at final address + Y
    auto cyclesLeft = cpu_.execute(5, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ((uint8_t)cpu_.A, 128);
    EXPECT_EQ(cpu_.C, 0);
    EXPECT_EQ(cpu_.N, 1);
    EXPECT_EQ(cpu_.V, 1);
    EXPECT_EQ(cpu_.Z, 0);
}

TEST_F(TEST_6502, SBC_INDY_canSubtractTwoUnsignedNumbers)
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.A = 20;
    cpu_.C = 1; // Carry is set to true
    mem_.set(0xFF00, CPU::INS_SBC_INDY);
    mem_.set(0xFF01, 0x10); // Zero page address
    cpu_.Y = 0x00;
    mem_.set(0x0010, 0x00); // Operand low byte at zero page address
    mem_.set(0x0011, 0x20); // Operand high byte at zero page address
    mem_.set(0x2000, 0x11); // Operand at final address + Y
    auto cyclesLeft = cpu_.execute(5, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ(cpu_.A, 3);
    EXPECT_EQ(cpu_.C, 1);
    EXPECT_EQ(cpu_.N, 0);
    EXPECT_EQ(cpu_.V, 0);
    EXPECT_EQ(cpu_.Z, 0);
}

TEST_F(TEST_6502, SBC_INDY_canSubtractTwoNegativeNumbers)
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.A = SIGNED_BYTE(-20);
    cpu_.C = 1; // Carry is set to true
    mem_.set(0xFF00, CPU::INS_SBC_INDY);
    mem_.set(0xFF01, 0x10); // Zero page address
    cpu_.Y = 0x00;
    mem_.set(0x0010, 0x00); // Operand low byte at zero page address
    mem_.set(0x0011, 0x20); // Operand high byte at zero page address
    mem_.set(0x2000, SIGNED_BYTE(-17)); // Operand at final address + Y
    auto cyclesLeft = cpu_.execute(5, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ((uint8_t)cpu_.A, SIGNED_BYTE(-3));
    EXPECT_EQ(cpu_.C, 0);
    EXPECT_EQ(cpu_.N, 1);
    EXPECT_EQ(cpu_.V, 0);
    EXPECT_EQ(cpu_.Z, 0);
}

