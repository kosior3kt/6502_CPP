#include "test.hpp"

////////////////////////////AND
TEST_F(TEST_6502, AND_IM)
{
   cpu_.A = 0b10101010;
   mem_.debug_set(0xFFFC, CPU::INS_AND_IM);
   mem_.debug_set(0xFFFD, 0b11111111);
   mem_.debug_set(0xFFFE, CPU::INS_NOTHING);
   mem_.debug_set(0xFFFE, CPU::INS_NOTHING);
   auto cyclesLeft = cpu_.execute(40, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ(cpu_.A, 0b10101010);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}

TEST_F(TEST_6502, AND_IM_moreAdvancedOrSth)
{
   mem_.debug_set(0xFFFE, CPU::INS_NOTHING);
   cpu_.A = 0b10101010;
   mem_.debug_set(0xFFFC, CPU::INS_AND_IM);
   mem_.debug_set(0xFFFD, 0b11110000);
   mem_.debug_set(0xFFFE, CPU::INS_NOTHING);
   mem_.debug_set(0xFFFE, CPU::INS_NOTHING);
   auto cyclesLeft = cpu_.execute(40, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ(cpu_.A, 0b10100000);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}

TEST_F(TEST_6502, AND_ZP)
{
   cpu_.A = 0b10101010;
   mem_.debug_set(0xFFFC, CPU::INS_AND_ZP);
   mem_.debug_set(0xFFFD, 0x69);
   mem_.debug_set(0x0069, 0b11111111);
   mem_.debug_set(0x006A, CPU::INS_NOTHING);
   mem_.debug_set(0xFFFE, CPU::INS_NOTHING);
   auto cyclesLeft = cpu_.execute(40, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ((uint8_t)cpu_.A, (uint8_t)0b10101010);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}

TEST_F(TEST_6502, AND_ZP_moreAdvancedOrSth)
{
   cpu_.A = 0b10101010;
   mem_.debug_set(0xFFFC, CPU::INS_AND_ZP);
   mem_.debug_set(0xFFFD, 0x69);
   mem_.debug_set(0x0069, 0b11110000);
   mem_.debug_set(0x006A, CPU::INS_NOTHING);
   mem_.debug_set(0xFFFE, CPU::INS_NOTHING);
   auto cyclesLeft = cpu_.execute(40, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ((uint8_t)cpu_.A, (uint8_t)0b10100000);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}

TEST_F(TEST_6502, AND_ZPX)
{
   cpu_.X = 0x01;
   cpu_.A = 0b10101010;
   mem_.debug_set(0xFFFC, CPU::INS_AND_ZPX);
   mem_.debug_set(0xFFFD, 0x68);
   mem_.debug_set(0x0069, 0b11111111);
   mem_.debug_set(0x006A, CPU::INS_NOTHING);
   mem_.debug_set(0xFFFE, CPU::INS_NOTHING);
   auto cyclesLeft = cpu_.execute(40, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ((uint8_t)cpu_.A, (uint8_t)0b10101010);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}

TEST_F(TEST_6502, AND_ZPX_moreAdvancedOrSth)
{
   cpu_.X = 0x01;
   cpu_.A = 0b10101010;
   mem_.debug_set(0xFFFC, CPU::INS_AND_ZPX);
   mem_.debug_set(0xFFFD, 0x68);
   mem_.debug_set(0x0069, 0b11110000);
   mem_.debug_set(0xFFFE, CPU::INS_NOTHING);
   auto cyclesLeft = cpu_.execute(40, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ((uint8_t)cpu_.A, (uint8_t)0b10100000);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}

TEST_F(TEST_6502, AND_ABS)
{
   cpu_.A = 0b10101010;
   mem_.debug_set(0xFFFC, CPU::INS_AND_ABS);
   mem_.debug_set(0xFFFD, 0x69);
   mem_.debug_set(0xFFFE, 0x10);
   mem_.debug_set(0x1069, 0b11111111);
   mem_.debug_set(0x106A, CPU::INS_NOTHING);
   mem_.debug_set(0xFFFF, CPU::INS_NOTHING);
   auto cyclesLeft = cpu_.execute(40, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ((uint8_t)cpu_.A, (uint8_t)0b10101010);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}

TEST_F(TEST_6502, AND_ABS_moreAdvancedOrSth) {
   cpu_.A = 0b10101010;
   mem_.debug_set(0xFFFC, CPU::INS_AND_ABS);
   mem_.debug_set(0xFFFD, 0x69);
   mem_.debug_set(0xFFFE, 0x10);
   mem_.debug_set(0x1069, 0b11110000);
   mem_.debug_set(0x106A, CPU::INS_NOTHING);
   mem_.debug_set(0xFFFF, CPU::INS_NOTHING);
   auto cyclesLeft = cpu_.execute(40, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ((uint8_t)cpu_.A, (uint8_t)0b10100000);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}

TEST_F(TEST_6502, AND_ABSX)
{
   cpu_.X = 1;
   cpu_.A = 0b10101010;
   mem_.debug_set(0xFFFC, CPU::INS_AND_ABSX);
   mem_.debug_set(0xFFFD, 0x68);
   mem_.debug_set(0xFFFE, 0x10);
   mem_.debug_set(0x1069, 0b11111111);
   mem_.debug_set(0x106A, CPU::INS_NOTHING);
   mem_.debug_set(0xFFFF, CPU::INS_NOTHING);
   auto cyclesLeft = cpu_.execute(40, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ((uint8_t)cpu_.A, (uint8_t)0b10101010);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}

TEST_F(TEST_6502, AND_ABSX_moreAdvancedOrSth)
{
   cpu_.X = 1;
   cpu_.A = 0b10101010;
   mem_.debug_set(0xFFFC, CPU::INS_AND_ABSX);
   mem_.debug_set(0xFFFD, 0x68);
   mem_.debug_set(0xFFFE, 0x10);
   mem_.debug_set(0x1069, 0b11110000);
   mem_.debug_set(0x106A, CPU::INS_NOTHING);
   mem_.debug_set(0xFFFF, CPU::INS_NOTHING);
   auto cyclesLeft = cpu_.execute(40, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ((uint8_t)cpu_.A, (uint8_t)0b10100000);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}


TEST_F(TEST_6502, AND_ABSY)
{
   cpu_.Y = 1;
   cpu_.A = 0b10101010;
   mem_.debug_set(0xFFFC, CPU::INS_AND_ABSY);
   mem_.debug_set(0xFFFD, 0x68);
   mem_.debug_set(0xFFFE, 0x10);
   mem_.debug_set(0x1069, 0b11111111);
   mem_.debug_set(0x106A, CPU::INS_NOTHING);
   mem_.debug_set(0xFFFF, CPU::INS_NOTHING);
   auto cyclesLeft = cpu_.execute(40, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ((uint8_t)cpu_.A, (uint8_t)0b10101010);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}

TEST_F(TEST_6502, AND_ABSY_moreAdvancedOrSth)
{
   cpu_.Y = 1;
   cpu_.A = 0b10101010;
   mem_.debug_set(0xFFFC, CPU::INS_AND_ABSY);
   mem_.debug_set(0xFFFD, 0x68);
   mem_.debug_set(0xFFFE, 0x10);
   mem_.debug_set(0x1069, 0b11110000);
   mem_.debug_set(0x106A, CPU::INS_NOTHING);
   mem_.debug_set(0xFFFF, CPU::INS_NOTHING);
   auto cyclesLeft = cpu_.execute(40, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ((uint8_t)cpu_.A, (uint8_t)0b10100000);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}

TEST_F(TEST_6502, AND_INDX)
{
   cpu_.X = 1;
   cpu_.A = 0b10101010;
   mem_.debug_set(0xFFFC, CPU::INS_AND_INDX);
   mem_.debug_set(0xFFFD, 0x68);
   mem_.debug_set(0x0069, 0x69);
   mem_.debug_set(0x006A, 0x10);
   mem_.debug_set(0x1069, 0b11111111);
   mem_.debug_set(0x106A, CPU::INS_NOTHING);
   mem_.debug_set(0xFFFE, CPU::INS_NOTHING);
   auto cyclesLeft = cpu_.execute(40, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ((uint8_t)cpu_.A, (uint8_t)0b10101010);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}

TEST_F(TEST_6502, AND_INDX_moreAdvancedOrSth)
{
   cpu_.X = 1;
   cpu_.A = 0b10101010;
   mem_.debug_set(0xFFFC, CPU::INS_AND_INDX);
   mem_.debug_set(0xFFFD, 0x68);
   mem_.debug_set(0x0069, 0x69);
   mem_.debug_set(0x006A, 0x10);
   mem_.debug_set(0x1069, 0b11110000);
   mem_.debug_set(0x106A, CPU::INS_NOTHING);
   mem_.debug_set(0xFFFE, CPU::INS_NOTHING);
   auto cyclesLeft = cpu_.execute(40, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ((uint8_t)cpu_.A, (uint8_t)0b10100000);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}

TEST_F(TEST_6502, AND_INDY)
{
   cpu_.Y = 1;
   cpu_.A = 0b10101010;
   mem_.debug_set(0xFFFC, CPU::INS_AND_INDY);
   mem_.debug_set(0xFFFD, 0x69);
   mem_.debug_set(0x0069, 0x68);
   mem_.debug_set(0x006A, 0x10);
   mem_.debug_set(0x1069, 0b11111111);
   mem_.debug_set(0x106A, CPU::INS_NOTHING);
   mem_.debug_set(0xFFFE, CPU::INS_NOTHING);
   auto cyclesLeft = cpu_.execute(40, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ((uint8_t)cpu_.A, (uint8_t)0b10101010);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}

TEST_F(TEST_6502, AND_INDY_moreAdvancedOrSth)
{
   cpu_.Y = 1;
   cpu_.A = 0b10101010;
   mem_.debug_set(0xFFFC, CPU::INS_AND_INDY);
   mem_.debug_set(0xFFFD, 0x69);
   mem_.debug_set(0x0069, 0x68);
   mem_.debug_set(0x006A, 0x10);
   mem_.debug_set(0x1069, 0b11110000);
   mem_.debug_set(0x106A, CPU::INS_NOTHING);
   mem_.debug_set(0xFFFE, CPU::INS_NOTHING);
   auto cyclesLeft = cpu_.execute(40, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ((uint8_t)cpu_.A, (uint8_t)0b10100000);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}

//////////////////////////////XOR
TEST_F(TEST_6502, EOR_IM)
{
   cpu_.A = 0b10101010;
   mem_.debug_set(0xFFFC, CPU::INS_EOR_IM);
   mem_.debug_set(0xFFFD, 0b11111111);
   mem_.debug_set(0xFFFF, CPU::INS_NOTHING);
   mem_.debug_set(0xFFFE, CPU::INS_NOTHING);
   auto cyclesLeft = cpu_.execute(40, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ(cpu_.A, 0b01010101);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}

TEST_F(TEST_6502,EOR_IM_moreAdvancedOrSth)
{
   cpu_.A = 0b10101010;
   mem_.debug_set(0xFFFC, CPU::INS_EOR_IM);
   mem_.debug_set(0xFFFD, 0b11110000);
   mem_.debug_set(0xFFFF, CPU::INS_NOTHING);
   mem_.debug_set(0xFFFE, CPU::INS_NOTHING);
   auto cyclesLeft = cpu_.execute(40, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ(cpu_.A, 0b01011010);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}


TEST_F(TEST_6502, EOR_ZP)
{
   cpu_.A = 0b10101010;
   mem_.debug_set(0xFFFC, CPU::INS_EOR_ZP);
   mem_.debug_set(0xFFFD, 0x69);
   mem_.debug_set(0x0069, 0b11111111);
   mem_.debug_set(0x006A, CPU::INS_NOTHING);
   mem_.debug_set(0xFFFE, CPU::INS_NOTHING);
   auto cyclesLeft = cpu_.execute(40, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ(cpu_.A, 0b01010101);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}

TEST_F(TEST_6502, EOR_ZP_moreAdvancedOrSth)
{
   cpu_.A = 0b10101010;
   mem_.debug_set(0xFFFC, CPU::INS_EOR_ZP);
   mem_.debug_set(0xFFFD, 0x69);
   mem_.debug_set(0x0069, 0b11110000);
   mem_.debug_set(0x006A, CPU::INS_NOTHING);
   mem_.debug_set(0xFFFE, CPU::INS_NOTHING);
   auto cyclesLeft = cpu_.execute(40, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ(cpu_.A, 0b01011010);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}


TEST_F(TEST_6502, EOR_ZPX)
{
   cpu_.X = 0x01;
   cpu_.A = 0b10101010;
   mem_.debug_set(0xFFFC, CPU::INS_EOR_ZPX);
   mem_.debug_set(0xFFFD, 0x68);
   mem_.debug_set(0x0069, 0b11111111);
   mem_.debug_set(0x006A, CPU::INS_NOTHING);
   mem_.debug_set(0xFFFE, CPU::INS_NOTHING);
   auto cyclesLeft = cpu_.execute(40, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ(cpu_.A, 0b01010101);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}

TEST_F(TEST_6502, EOR_ZPX_moreAdvancedOrSth)
{
   cpu_.X = 0x01;
   cpu_.A = 0b10101010;
   mem_.debug_set(0xFFFC, CPU::INS_EOR_ZPX);
   mem_.debug_set(0xFFFD, 0x68);
   mem_.debug_set(0x0069, 0b11110000);
   mem_.debug_set(0x006A, CPU::INS_NOTHING);
   mem_.debug_set(0xFFFE, CPU::INS_NOTHING);
   auto cyclesLeft = cpu_.execute(40, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ(cpu_.A, 0b01011010);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}

TEST_F(TEST_6502, EOR_ABS)
{
   cpu_.A = 0b10101010;
   mem_.debug_set(0xFFFC, CPU::INS_EOR_ABS);
   mem_.debug_set(0xFFFD, 0x69);
   mem_.debug_set(0xFFFE, 0x10);
   mem_.debug_set(0x1069, 0b11111111);
   mem_.debug_set(0x106A, CPU::INS_NOTHING);
   mem_.debug_set(0xFFFF, CPU::INS_NOTHING);
   auto cyclesLeft = cpu_.execute(40, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ(cpu_.A, 0b01010101);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}

TEST_F(TEST_6502, EOR_ABS_moreAdvancedOrSth)
{
   cpu_.A = 0b10101010;
   mem_.debug_set(0xFFFC, CPU::INS_EOR_ABS);
   mem_.debug_set(0xFFFD, 0x69);
   mem_.debug_set(0xFFFE, 0x10);
   mem_.debug_set(0x1069, 0b11110000);
   mem_.debug_set(0x106A, CPU::INS_NOTHING);
   mem_.debug_set(0xFFFF, CPU::INS_NOTHING);
   auto cyclesLeft = cpu_.execute(40, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ(cpu_.A, 0b01011010);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}

TEST_F(TEST_6502, EOR_ABSX)
{
   cpu_.X = 1;
   cpu_.A = 0b10101010;
   mem_.debug_set(0xFFFC, CPU::INS_EOR_ABSX);
   mem_.debug_set(0xFFFD, 0x68);
   mem_.debug_set(0xFFFE, 0x10);
   mem_.debug_set(0x1069, 0b11111111);
   mem_.debug_set(0x106A, CPU::INS_NOTHING);
   mem_.debug_set(0xFFFF, CPU::INS_NOTHING);
   auto cyclesLeft = cpu_.execute(40, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ(cpu_.A, 0b01010101);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}

TEST_F(TEST_6502, EOR_ABSX_moreAdvancedOrSth)
{
   cpu_.X = 1;
   cpu_.A = 0b10101010;
   mem_.debug_set(0xFFFC, CPU::INS_EOR_ABSX);
   mem_.debug_set(0xFFFD, 0x68);
   mem_.debug_set(0xFFFE, 0x10);
   mem_.debug_set(0x1069, 0b11110000);
   mem_.debug_set(0x106A, CPU::INS_NOTHING);
   mem_.debug_set(0xFFFF, CPU::INS_NOTHING);
   auto cyclesLeft = cpu_.execute(40, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ(cpu_.A, 0b01011010);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}

TEST_F(TEST_6502, EOR_ABSY)
{
   cpu_.Y = 1;
   cpu_.A = 0b10101010;
   mem_.debug_set(0xFFFC, CPU::INS_EOR_ABSY);
   mem_.debug_set(0xFFFD, 0x68);
   mem_.debug_set(0xFFFE, 0x10);
   mem_.debug_set(0x1069, 0b11111111);
   mem_.debug_set(0x106A, CPU::INS_NOTHING);
   mem_.debug_set(0xFFFF, CPU::INS_NOTHING);
   auto cyclesLeft = cpu_.execute(40, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ(cpu_.A, 0b01010101);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}

TEST_F(TEST_6502, EOR_ABSY_moreAdvancedOrSth)
{
   cpu_.Y = 1;
   cpu_.A = 0b10101010;
   mem_.debug_set(0xFFFC, CPU::INS_EOR_ABSY);
   mem_.debug_set(0xFFFD, 0x68);
   mem_.debug_set(0xFFFE, 0x10);
   mem_.debug_set(0x1069, 0b11110000);
   mem_.debug_set(0x106A, CPU::INS_NOTHING);
   mem_.debug_set(0xFFFF, CPU::INS_NOTHING);
   auto cyclesLeft = cpu_.execute(40, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ(cpu_.A, 0b01011010);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}


TEST_F(TEST_6502, EOR_INDX)
{
   cpu_.X = 1;
   cpu_.A = 0b10101010;
   mem_.debug_set(0xFFFC, CPU::INS_EOR_INDX);
   mem_.debug_set(0xFFFD, 0x68);
   mem_.debug_set(0x0069, 0x69);
   mem_.debug_set(0x006A, 0x10);
   mem_.debug_set(0x1069, 0b11111111);
   mem_.debug_set(0x106A, CPU::INS_NOTHING);
   mem_.debug_set(0xFFFE, CPU::INS_NOTHING);
   auto cyclesLeft = cpu_.execute(40, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ(cpu_.A, 0b01010101);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}

TEST_F(TEST_6502, EOR_INDX_moreAdvancedOrSth)
{
   cpu_.X = 1;
   cpu_.A = 0b10101010;
   mem_.debug_set(0xFFFC, CPU::INS_EOR_INDX);
   mem_.debug_set(0xFFFD, 0x68);
   mem_.debug_set(0x0069, 0x69);
   mem_.debug_set(0x006A, 0x10);
   mem_.debug_set(0x1069, 0b11110000);
   mem_.debug_set(0x106A, CPU::INS_NOTHING);
   mem_.debug_set(0xFFFE, CPU::INS_NOTHING);
   auto cyclesLeft = cpu_.execute(40, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ(cpu_.A, 0b01011010);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}


TEST_F(TEST_6502, EOR_INDY)
{
   cpu_.Y = 1;
   cpu_.A = 0b10101010;
   mem_.debug_set(0xFFFC, CPU::INS_EOR_INDY);
   mem_.debug_set(0xFFFD, 0x69);
   mem_.debug_set(0x0069, 0x68);
   mem_.debug_set(0x006A, 0x10);
   mem_.debug_set(0x1069, 0b11111111);
   mem_.debug_set(0x106A, CPU::INS_NOTHING);
   mem_.debug_set(0xFFFE, CPU::INS_NOTHING);
   auto cyclesLeft = cpu_.execute(40, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ(cpu_.A, 0b01010101);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}

TEST_F(TEST_6502, EOR_INDY_moreAdvancedOrSth)
{
   cpu_.Y = 1;
   cpu_.A = 0b10101010;
   mem_.debug_set(0xFFFC, CPU::INS_EOR_INDY);
   mem_.debug_set(0xFFFD, 0x69);
   mem_.debug_set(0x0069, 0x68);
   mem_.debug_set(0x006A, 0x10);
   mem_.debug_set(0x1069, 0b11110000);
   mem_.debug_set(0x106A, CPU::INS_NOTHING);
   mem_.debug_set(0xFFFE, CPU::INS_NOTHING);
   auto cyclesLeft = cpu_.execute(40, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ(cpu_.A, 0b01011010);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}

///////OR

TEST_F(TEST_6502, ORA_IM)
{
   cpu_.A = 0b10101010;
   mem_.debug_set(0xFFFC, CPU::INS_ORA_IM);
   mem_.debug_set(0xFFFD, 0b01010101);
   mem_.debug_set(0xFFFF, CPU::INS_NOTHING);
   mem_.debug_set(0xFFFE, CPU::INS_NOTHING);
   auto cyclesLeft = cpu_.execute(40, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ(cpu_.A, 0b11111111);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}

TEST_F(TEST_6502,ORA_IM_moreAdvancedOrSth)
{
   cpu_.A = 0b10101010;
   mem_.debug_set(0xFFFC, CPU::INS_ORA_IM);
   mem_.debug_set(0xFFFD, 0b11110000);
   mem_.debug_set(0xFFFF, CPU::INS_NOTHING);
   mem_.debug_set(0xFFFE, CPU::INS_NOTHING);
   auto cyclesLeft = cpu_.execute(40, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ(cpu_.A, 0b11111010);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}


TEST_F(TEST_6502, ORA_ZP)
{
   cpu_.A = 0b10101010;
   mem_.debug_set(0xFFFC, CPU::INS_ORA_ZP);
   mem_.debug_set(0xFFFD, 0x69);
   mem_.debug_set(0x0069, 0b01010101);
   mem_.debug_set(0x006A, CPU::INS_NOTHING);
   mem_.debug_set(0xFFFE, CPU::INS_NOTHING);
   auto cyclesLeft = cpu_.execute(40, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ(cpu_.A, 0b11111111);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}

TEST_F(TEST_6502, ORA_ZP_moreAdvancedOrSth)
{
   cpu_.A = 0b10101010;
   mem_.debug_set(0xFFFC, CPU::INS_ORA_ZP);
   mem_.debug_set(0xFFFD, 0x69);
   mem_.debug_set(0x0069, 0b11110000);
   mem_.debug_set(0x006A, CPU::INS_NOTHING);
   mem_.debug_set(0xFFFE, CPU::INS_NOTHING);
   auto cyclesLeft = cpu_.execute(40, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ(cpu_.A, 0b11111010);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}


TEST_F(TEST_6502, ORA_ZPX)
{
   cpu_.X = 0x01;
   cpu_.A = 0b10101010;
   mem_.debug_set(0xFFFC, CPU::INS_ORA_ZPX);
   mem_.debug_set(0xFFFD, 0x68);
   mem_.debug_set(0x0069, 0b01010101);
   mem_.debug_set(0xFFFE, CPU::INS_NOTHING);
   mem_.debug_set(0xFFFE, CPU::INS_NOTHING);
   auto cyclesLeft = cpu_.execute(40, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ(cpu_.A, 0b11111111);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}

TEST_F(TEST_6502, ORA_ZPX_moreAdvancedOrSth)
{
   cpu_.X = 0x01;
   cpu_.A = 0b10101010;
   mem_.debug_set(0xFFFC, CPU::INS_ORA_ZPX);
   mem_.debug_set(0xFFFD, 0x68);
   mem_.debug_set(0x0069, 0b11110000);
   mem_.debug_set(0xFFFE, CPU::INS_NOTHING);
   auto cyclesLeft = cpu_.execute(40, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ(cpu_.A, 0b11111010);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}

TEST_F(TEST_6502, ORA_ABS)
{
   cpu_.A = 0b10101010;
   mem_.debug_set(0xFFFC, CPU::INS_ORA_ABS);
   mem_.debug_set(0xFFFD, 0x69);
   mem_.debug_set(0xFFFE, 0x10);
   mem_.debug_set(0x1069, 0b01010101);
   mem_.debug_set(0xFFFF, CPU::INS_NOTHING);
   auto cyclesLeft = cpu_.execute(40, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ(cpu_.A, 0b11111111);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}

TEST_F(TEST_6502, ORA_ABS_moreAdvancedOrSth)
{
   cpu_.A = 0b10101010;
   mem_.debug_set(0xFFFC, CPU::INS_ORA_ABS);
   mem_.debug_set(0xFFFD, 0x69);
   mem_.debug_set(0xFFFE, 0x10);
   mem_.debug_set(0x1069, 0b11110000);
   mem_.debug_set(0xFFFF, CPU::INS_NOTHING);
   auto cyclesLeft = cpu_.execute(40, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ(cpu_.A, 0b11111010);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}

TEST_F(TEST_6502, ORA_ABSX)
{
   cpu_.X = 1;
   cpu_.A = 0b10101010;
   mem_.debug_set(0xFFFC, CPU::INS_ORA_ABSX);
   mem_.debug_set(0xFFFD, 0x68);
   mem_.debug_set(0xFFFE, 0x10);
   mem_.debug_set(0x1069, 0b01010101);
   mem_.debug_set(0xFFFF, CPU::INS_NOTHING);
   auto cyclesLeft = cpu_.execute(40, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ(cpu_.A, 0b11111111);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}

TEST_F(TEST_6502, ORA_ABSX_moreAdvancedOrSth)
{
   cpu_.X = 1;
   cpu_.A = 0b10101010;
   mem_.debug_set(0xFFFC, CPU::INS_ORA_ABSX);
   mem_.debug_set(0xFFFD, 0x68);
   mem_.debug_set(0xFFFE, 0x10);
   mem_.debug_set(0x1069, 0b11110000);
   mem_.debug_set(0xFFFF, CPU::INS_NOTHING);
   auto cyclesLeft = cpu_.execute(40, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ(cpu_.A, 0b11111010);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}

TEST_F(TEST_6502, ORA_ABSY)
{
   cpu_.Y = 1;
   cpu_.A = 0b10101010;
   mem_.debug_set(0xFFFC, CPU::INS_ORA_ABSY);
   mem_.debug_set(0xFFFD, 0x68);
   mem_.debug_set(0xFFFE, 0x10);
   mem_.debug_set(0x1069, 0b01010101);
   mem_.debug_set(0xFFFF, CPU::INS_NOTHING);
   auto cyclesLeft = cpu_.execute(40, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ(cpu_.A, 0b11111111);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}

TEST_F(TEST_6502, ORA_ABSY_moreAdvancedOrSth)
{
   cpu_.Y = 1;
   cpu_.A = 0b10101010;
   mem_.debug_set(0xFFFC, CPU::INS_ORA_ABSY);
   mem_.debug_set(0xFFFD, 0x68);
   mem_.debug_set(0xFFFE, 0x10);
   mem_.debug_set(0x1069, 0b11110000);
   mem_.debug_set(0xFFFF, CPU::INS_NOTHING);
   auto cyclesLeft = cpu_.execute(40, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ(cpu_.A, 0b11111010);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}


TEST_F(TEST_6502, ORA_INDX)
{
   cpu_.X = 1;
   cpu_.A = 0b10101010;
   mem_.debug_set(0xFFFC, CPU::INS_ORA_INDX);
   mem_.debug_set(0xFFFD, 0x68);
   mem_.debug_set(0x0069, 0x69);
   mem_.debug_set(0x006A, 0x10);
   mem_.debug_set(0x1069, 0b01010101);
   mem_.debug_set(0xFFFE, CPU::INS_NOTHING);
   auto cyclesLeft = cpu_.execute(40, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ(cpu_.A, 0b11111111);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}

TEST_F(TEST_6502, ORA_INDX_moreAdvancedOrSth)
{
   cpu_.X = 1;
   cpu_.A = 0b10101010;
   mem_.debug_set(0xFFFC, CPU::INS_ORA_INDX);
   mem_.debug_set(0xFFFD, 0x68);
   mem_.debug_set(0x0069, 0x69);
   mem_.debug_set(0x006A, 0x10);
   mem_.debug_set(0x1069, 0b11110000);
   mem_.debug_set(0xFFFE, CPU::INS_NOTHING);
   auto cyclesLeft = cpu_.execute(40, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ(cpu_.A, 0b11111010);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}


TEST_F(TEST_6502, ORA_INDY)
{
   cpu_.Y = 1;
   cpu_.A = 0b10101010;
   mem_.debug_set(0xFFFC, CPU::INS_ORA_INDY);
   mem_.debug_set(0xFFFD, 0x69);
   mem_.debug_set(0x0069, 0x68);
   mem_.debug_set(0x006A, 0x10);
   mem_.debug_set(0x1069, 0b01010101);
   mem_.debug_set(0xFFFE, CPU::INS_NOTHING);
   auto cyclesLeft = cpu_.execute(40, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ(cpu_.A, 0b11111111);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}

TEST_F(TEST_6502, ORA_INDY_moreAdvancedOrSth)
{
   cpu_.Y = 1;
   cpu_.A = 0b10101010;
   mem_.debug_set(0xFFFC, CPU::INS_ORA_INDY);
   mem_.debug_set(0xFFFD, 0x69);
   mem_.debug_set(0x0069, 0x68);
   mem_.debug_set(0x006A, 0x10);
   mem_.debug_set(0x1069, 0b11110000);
   mem_.debug_set(0xFFFE, CPU::INS_NOTHING);
   auto cyclesLeft = cpu_.execute(40, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ(cpu_.A, 0b11111010);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}

TEST_F(TEST_6502, BIT_ZP)
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.A = 0b01110000;
    mem_.debug_set(0xFF00, CPU::INS_BIT_ZP);
    mem_.debug_set(0xFF01, 0x10);
    mem_.debug_set(0x0010, 0b01000000); // Memory operand with overflow flag set

   mem_.debug_set(0xFF02, CPU::INS_NOTHING);
    auto cyclesLeft = cpu_.execute(40, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ(cpu_.A, 0b01110000);
    EXPECT_TRUE(cpu_.V);  // Overflow flag set
    EXPECT_FALSE(cpu_.N); // Negative flag not set
    EXPECT_FALSE(cpu_.Z); // Zero flag not set
}

TEST_F(TEST_6502, BIT_ABS_NoFlags)
{
    cpu_.Reset(mem_, 0x8000);
    cpu_.A = 0b00000011;
    mem_.debug_set(0x8000, CPU::INS_BIT_ABS);
    mem_.debug_set(0x8001, 0x00);
    mem_.debug_set(0x8002, 0x20);
    mem_.debug_set(0x2000, 0b00000001); // Memory operand with no flags set

   mem_.debug_set(0x8003, CPU::INS_NOTHING);
    auto cyclesLeft = cpu_.execute(40, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_FALSE(cpu_.CPU::V); // Overflow flag not set
    EXPECT_FALSE(cpu_.CPU::N); // Negative flag not set
    EXPECT_FALSE(cpu_.CPU::Z); // Zero flag not set (0b00000011 & 0b00000001 != 0)
}

TEST_F(TEST_6502, BIT_ABS)
{
    cpu_.Reset(mem_, 0x8000);
    cpu_.A = 0b00000000;
    mem_.debug_set(0x8000, CPU::INS_BIT_ABS);
    mem_.debug_set(0x8001, 0x00);
    mem_.debug_set(0x8002, 0x20);
    mem_.debug_set(0x2000, 0b10000000); // Memory operand with bit 7 set (negative flag)

   mem_.debug_set(0x8003, CPU::INS_NOTHING);
    auto cyclesLeft = cpu_.execute(40, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ(cpu_.A, 0b00000000);
    EXPECT_FALSE(cpu_.V); // Overflow flag not set
    EXPECT_TRUE(cpu_.N);  // Negative flag set
    EXPECT_TRUE(cpu_.Z);      // Zero flag set
}
