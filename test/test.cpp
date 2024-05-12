#include "test.hpp"

TEST_F(TEST_6502, LDA_IM)
{
   mem_.debug_set(0xFFFC, CPU::INS_LDA_IM);
   mem_.debug_set(0xFFFD, 0x69);
   auto cyclesLeft = cpu_.Execute(2, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ((int)cpu_.A, 0x69);
   EXPECT_FALSE((int)cpu_.Z);
   EXPECT_FALSE((int)cpu_.N);
   EXPECT_TRUE(testHelper::flagsUnchanged(cpu_, copyCPU));
}

TEST_F(TEST_6502, LDA_IM_NEGATIVE)
{
   mem_.debug_set(0xFFFC, CPU::INS_LDA_IM);
   mem_.debug_set(0xFFFD, 0b10000000); ///the 1 on the first bit of 8bit number is consider to make it negative - 2 complements or sth
   auto cyclesLeft = cpu_.Execute(2, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ((int)cpu_.A, 0b10000000);
   EXPECT_FALSE((int)cpu_.Z);
   EXPECT_TRUE((int)cpu_.N);
   EXPECT_TRUE(testHelper::flagsUnchanged(cpu_, copyCPU));
}

TEST_F(TEST_6502, LDA_ZP)
{
   mem_.debug_set(0xFFFC, CPU::INS_LDA_ZP);
   mem_.debug_set(0xFFFD, 0x42);
   mem_.debug_set(0x0042, 0x69);
   auto cyclesLeft = cpu_.Execute(3, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ((int)cpu_.A, 0x69);
   EXPECT_FALSE((int)cpu_.Z);
   EXPECT_FALSE((int)cpu_.N);
   EXPECT_TRUE(testHelper::flagsUnchanged(cpu_, copyCPU));
}


TEST_F(TEST_6502, LDA_ZPX)
{
   cpu_.X = 0x5;
   mem_.debug_set(0xFFFC, CPU::INS_LDA_ZPX);
   mem_.debug_set(0xFFFD, 0x42);
   mem_.debug_set(0x0047, 0x69);
   auto cyclesLeft = cpu_.Execute(3, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ((int)cpu_.A, 0x69);
   EXPECT_FALSE((int)cpu_.Z);
   EXPECT_FALSE((int)cpu_.N);
   EXPECT_TRUE(testHelper::flagsUnchanged(cpu_, copyCPU));
}

TEST_F(TEST_6502, LDA_ZPX_withWrapping)
{
   cpu_.X = 0xFF;
   mem_.debug_set(0xFFFC, CPU::INS_LDA_ZPX);
   mem_.debug_set(0xFFFD, 0x80);
   mem_.debug_set(0x007F, 0x69);
   auto cyclesLeft = cpu_.Execute(3, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ((int)cpu_.A, 0x69);
   EXPECT_FALSE((int)cpu_.Z);
   EXPECT_FALSE((int)cpu_.N);
   EXPECT_TRUE(testHelper::flagsUnchanged(cpu_, copyCPU));
}


TEST_F(TEST_6502, slightlyMoreComplicatedProgram)
{
   mem_.debug_set(0xFFFC, CPU::INS_JSR);
   mem_.debug_set(0xFFFD, 0x42);
   mem_.debug_set(0xFFFE, 0x42);
   mem_.debug_set(0x4242, CPU::INS_LDA_IM);
   mem_.debug_set(0x4243, 0x69);
   mem_.debug_set(0x4244, CPU::INS_JSR);
   mem_.debug_set(0x4245, 0x69);
   mem_.debug_set(0x4246, 0x69);
   mem_.debug_set(0x6969, CPU::INS_LDA_IM);
   mem_.debug_set(0x696A, 0x6B);
   auto cyclesLeft = cpu_.Execute(16, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ((int)cpu_.A, 0x6B);
   EXPECT_FALSE((int)cpu_.Z);
   EXPECT_FALSE((int)cpu_.N);
   EXPECT_TRUE(testHelper::flagsUnchanged(cpu_, copyCPU));
}


