#include "test.hpp"


TEST_F(TEST_6502, LDY_IM)
{
   test_LD(CPU::INS_LDY_IM, Register::Y);
}

TEST_F(TEST_6502, LDY_ZP)
{
   mem_.debug_set(0xFFFC, CPU::INS_LDY_ZP);
   mem_.debug_set(0xFFFD, 0x42);
   mem_.debug_set(0x0042, 0x69);
   auto cyclesLeft = cpu_.execute(3, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ((int)cpu_.Y, 0x69);
   EXPECT_FALSE((int)cpu_.Z);
   EXPECT_FALSE((int)cpu_.N);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}

TEST_F(TEST_6502, LDY_ZPX)
{
   cpu_.X = 0x5;
   mem_.debug_set(0xFFFC, CPU::INS_LDY_ZPX);
   mem_.debug_set(0xFFFD, 0x42);
   mem_.debug_set(0x0047, 0x69);
   auto cyclesLeft = cpu_.execute(4, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ((int)cpu_.Y, 0x69);
   EXPECT_FALSE((int)cpu_.Z);
   EXPECT_FALSE((int)cpu_.N);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}

TEST_F(TEST_6502, LDY_ZPX_withWrapping)
{
   cpu_.X = 0xFF;
   mem_.debug_set(0xFFFC, CPU::INS_LDY_ZPX);
   mem_.debug_set(0xFFFD, 0x80);
   mem_.debug_set(0x007F, 0x69);
   auto cyclesLeft = cpu_.execute(4, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ((int)cpu_.Y, 0x69);
   EXPECT_FALSE((int)cpu_.Z);
   EXPECT_FALSE((int)cpu_.N);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}

TEST_F(TEST_6502, LDY_AbsoluteAddressing)
{
   mem_.debug_set(0xFFFC, CPU::INS_LDY_ABS);
   mem_.debug_set(0xFFFD, 0x80);
   mem_.debug_set(0xFFFE, 0x69); /// 0x6980
   mem_.debug_set(0x6980, 0x69);
   auto cyclesLeft = cpu_.execute(4, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ((int)cpu_.Y, 0x69);
   EXPECT_FALSE((int)cpu_.Z);
   EXPECT_FALSE((int)cpu_.N);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}

TEST_F(TEST_6502, LDY_AbsoluteAddressing_noPageCrossing)
{
   cpu_.X = 0x0001;
   mem_.debug_set(0xFFFC, CPU::INS_LDY_ABSX);
   mem_.debug_set(0xFFFD, 0x80);
   mem_.debug_set(0xFFFE, 0x69); /// 0x6980 + 0x0001 = 0x6981
   mem_.debug_set(0x6981, 0x69);
   auto cyclesLeft = cpu_.execute(4, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ((int)cpu_.Y, 0x69);
   EXPECT_FALSE((int)cpu_.Z);
   EXPECT_FALSE((int)cpu_.N);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}

TEST_F(TEST_6502, LDY_AbsoluteAddressing_withPageCrossing)
{
   cpu_.X = 0x27;
   mem_.debug_set(0xFFFC, CPU::INS_LDY_ABSX);
   mem_.debug_set(0xFFFD, 0xFF);
   mem_.debug_set(0xFFFE, 0xFF); /// 0xFFFF + 0x0027 = (in this case we take into considerationg page crossing) = 0x0027 - 0x0001 (for page crossing compensation)
   mem_.debug_set(0x0026, 0x69);
   auto cyclesLeft = cpu_.execute(5, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ((int)cpu_.Y, 0x69);
   EXPECT_FALSE((int)cpu_.Z);
   EXPECT_FALSE((int)cpu_.N);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}
