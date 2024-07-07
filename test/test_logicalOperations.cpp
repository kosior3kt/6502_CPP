#include "test.hpp"

////////////////////////////AND
TEST_F(TEST_6502, AND_IM)
{
   cpu_.A = 0b10101010;
   mem_.debug_set(0xFFFC, CPU::INS_AND_IM);
   mem_.debug_set(0xFFFD, 0b11111111);
   auto cyclesLeft = cpu_.execute(3, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ(cpu_.A, 0b10101010);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}

TEST_F(TEST_6502, AND_IM_moreAdvancedOrSth)
{
   cpu_.A = 0b10101010;
   mem_.debug_set(0xFFFC, CPU::INS_AND_IM);
   mem_.debug_set(0xFFFD, 0b11110000);
   auto cyclesLeft = cpu_.execute(3, mem_);

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
   auto cyclesLeft = cpu_.execute(3, mem_);

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
   auto cyclesLeft = cpu_.execute(3, mem_);

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
   auto cyclesLeft = cpu_.execute(4, mem_);

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
   auto cyclesLeft = cpu_.execute(4, mem_);

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
   auto cyclesLeft = cpu_.execute(6, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ((uint8_t)cpu_.A, (uint8_t)0b10101010);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}

TEST_F(TEST_6502, AND_ABS_moreAdvancedOrSth)
{
   cpu_.A = 0b10101010;
   mem_.debug_set(0xFFFC, CPU::INS_AND_ABS);
   mem_.debug_set(0xFFFD, 0x69);
   mem_.debug_set(0xFFFE, 0x10);
   mem_.debug_set(0x1069, 0b11110000);
   auto cyclesLeft = cpu_.execute(6, mem_);

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
   auto cyclesLeft = cpu_.execute(6, mem_);

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
   auto cyclesLeft = cpu_.execute(6, mem_);

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
   auto cyclesLeft = cpu_.execute(6, mem_);

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
   auto cyclesLeft = cpu_.execute(6, mem_);

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
   auto cyclesLeft = cpu_.execute(6, mem_);

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
   auto cyclesLeft = cpu_.execute(6, mem_);

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
   auto cyclesLeft = cpu_.execute(6, mem_);

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
   auto cyclesLeft = cpu_.execute(6, mem_);

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
   auto cyclesLeft = cpu_.execute(3, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ(cpu_.A, 0b01010101);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}

TEST_F(TEST_6502,EOR_IM_moreAdvancedOrSth)
{
   cpu_.A = 0b10101010;
   mem_.debug_set(0xFFFC, CPU::INS_EOR_IM);
   mem_.debug_set(0xFFFD, 0b11110000);
   auto cyclesLeft = cpu_.execute(3, mem_);

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
   auto cyclesLeft = cpu_.execute(3, mem_);

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
   auto cyclesLeft = cpu_.execute(3, mem_);

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
   auto cyclesLeft = cpu_.execute(4, mem_);

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
   auto cyclesLeft = cpu_.execute(4, mem_);

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
   auto cyclesLeft = cpu_.execute(6, mem_);

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
   auto cyclesLeft = cpu_.execute(6, mem_);

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
   auto cyclesLeft = cpu_.execute(6, mem_);

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
   auto cyclesLeft = cpu_.execute(6, mem_);

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
   auto cyclesLeft = cpu_.execute(6, mem_);

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
   auto cyclesLeft = cpu_.execute(6, mem_);

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
   auto cyclesLeft = cpu_.execute(6, mem_);

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
   auto cyclesLeft = cpu_.execute(6, mem_);

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
   auto cyclesLeft = cpu_.execute(6, mem_);

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
   auto cyclesLeft = cpu_.execute(6, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ(cpu_.A, 0b01011010);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}

