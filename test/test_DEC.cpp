
#include "test.hpp"

TEST_F(TEST_6502, DEX_simple)
{
   cpu_.X = 0x6A;
   mem_.debug_set(0xFFFC, CPU::INS_DEX);
   auto cyclesLeft = cpu_.execute(2, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ((int)cpu_.X, 0x69);
   // EXPECT_FALSE((int)cpu_.Z);
   // EXPECT_FALSE((int)cpu_.N);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}

TEST_F(TEST_6502, DEY_simple)
{
   cpu_.Y = 0x6A;
   mem_.debug_set(0xFFFC, CPU::INS_DEY);
   auto cyclesLeft = cpu_.execute(2, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ((int)cpu_.Y, 0x69);
   // EXPECT_FALSE((int)cpu_.Z);
   // EXPECT_FALSE((int)cpu_.N);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}
