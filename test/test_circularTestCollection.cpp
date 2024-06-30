#include "test.hpp"


TEST_F(TEST_6502, LDA_Circular)
{
   cpu_.Reset(mem_, 0xFF00);
   mem_.debug_set(0xFF00, CPU::INS_LDA_IM);
   mem_.debug_set(0xFF01, 0x54); 

   mem_.debug_set(0xFF02, CPU::INS_STA_ABS);
   mem_.debug_set(0xFF03, 0x10); 
   mem_.debug_set(0xFF04, 0x20); 

   mem_.debug_set(0xFF05, CPU::INS_LDX_ABS);
   mem_.debug_set(0xFF06, 0x10);
   mem_.debug_set(0xFF07, 0x20);

   auto cyclesLeft = cpu_.execute(10, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ((int)cpu_.A, (int)cpu_.X);
   EXPECT_FALSE((int)cpu_.Z);
   EXPECT_FALSE((int)cpu_.N);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}

TEST_F(TEST_6502, LDA_Circular_dupa)
{
   cpu_.Reset(mem_, 0xFF00);
   mem_.debug_set(0xFF00, CPU::INS_LDA_IM);
   mem_.debug_set(0xFF01, 0x54); 

   mem_.debug_set(0xFF02, CPU::INS_STA_ABS);
   mem_.debug_set(0xFF03, 0x10); 
   mem_.debug_set(0xFF04, 0x20); 

   mem_.debug_set(0xFF05, CPU::INS_LDX_ABS);
   mem_.debug_set(0xFF06, 0x10);
   mem_.debug_set(0xFF07, 0x20);

   auto cyclesLeft = cpu_.execute(10, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ((int)cpu_.A, (int)cpu_.X);
   EXPECT_FALSE((int)cpu_.Z);
   EXPECT_FALSE((int)cpu_.N);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}
