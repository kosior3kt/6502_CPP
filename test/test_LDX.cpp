#include "test.hpp"

TEST_F(TEST_6502, LDX_IM)
{
   test_LD(CPU::INS_LDX_IM, Register::X);
}

TEST_F(TEST_6502, LDX_ZP)
{
   mem_.debug_set(0xFFFC, CPU::INS_LDX_ZP);
   mem_.debug_set(0xFFFD, 0x42);
   mem_.debug_set(0x0042, 0x69);
   auto cyclesLeft = cpu_.execute(3, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ((int)cpu_.X, 0x69);
   EXPECT_FALSE((int)cpu_.Z);
   EXPECT_FALSE((int)cpu_.N);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}

TEST_F(TEST_6502, LDX_ZPY)
{
   cpu_.Y = 0x5;
   mem_.debug_set(0xFFFC, CPU::INS_LDX_ZPY);
   mem_.debug_set(0xFFFD, 0x42);
   mem_.debug_set(0x0047, 0x69);
   auto cyclesLeft = cpu_.execute(3, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ((int)cpu_.X, 0x69);
   EXPECT_FALSE((int)cpu_.Z);
   EXPECT_FALSE((int)cpu_.N);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}

TEST_F(TEST_6502, LDX_AbsoluteAddressing)
{
   mem_.debug_set(0xFFFC, CPU::INS_LDX_ABS);
   mem_.debug_set(0xFFFD, 0x80);
   mem_.debug_set(0xFFFE, 0x69); /// 0x6980
   mem_.debug_set(0x6980, 0x69);
   auto cyclesLeft = cpu_.execute(4, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ((int)cpu_.X, 0x69);
   EXPECT_FALSE((int)cpu_.Z);
   EXPECT_FALSE((int)cpu_.N);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}

TEST_F(TEST_6502, LDXY_AbsoluteAddressing_noPageCrossing)
{
   cpu_.Y = 0x0001;
   mem_.debug_set(0xFFFC, CPU::INS_LDX_ABSY);
   mem_.debug_set(0xFFFD, 0x80);
   mem_.debug_set(0xFFFE, 0x69); /// 0x6980 + 0x0001 = 0x6981
   mem_.debug_set(0x6981, 0x69);
   auto cyclesLeft = cpu_.execute(4, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ((int)cpu_.X, 0x69);
   EXPECT_FALSE((int)cpu_.Z);
   EXPECT_FALSE((int)cpu_.N);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}


