#include "test.hpp"



TEST_F(TEST_6502, TAX_simple)
{
   cpu_.Reset(mem_, 0xFF00);
   mem_.debug_set(0xFF00, CPU::INS_LDA_IM);  
   mem_.debug_set(0xFF01, 0x0069);  
   mem_.debug_set(0xFF02, CPU::INS_TAX);  

   auto cyclesLeft = cpu_.execute(20, mem_);

   EXPECT_EQ(cyclesLeft, 0);  //imma do this later on...
   EXPECT_EQ((int)cpu_.X, 0x69);
   EXPECT_FALSE((int)cpu_.Z);
   EXPECT_FALSE((int)cpu_.N);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}

TEST_F(TEST_6502, TAY_simple)
{
   cpu_.Reset(mem_, 0xFF00);
   mem_.debug_set(0xFF00, CPU::INS_LDA_IM);  
   mem_.debug_set(0xFF01, 0x0069);  
   mem_.debug_set(0xFF02, CPU::INS_TAY);  

   auto cyclesLeft = cpu_.execute(20, mem_);

   EXPECT_EQ(cyclesLeft, 0);  //imma do this later on...
   EXPECT_EQ((int)cpu_.Y, 0x69);
   EXPECT_FALSE((int)cpu_.Z);
   EXPECT_FALSE((int)cpu_.N);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}

TEST_F(TEST_6502, TXA_simple)
{
   cpu_.Reset(mem_, 0xFF00);
   mem_.debug_set(0xFF00, CPU::INS_LDX_IM);  
   mem_.debug_set(0xFF01, 0x0069);  
   mem_.debug_set(0xFF02, CPU::INS_TXA);  

   auto cyclesLeft = cpu_.execute(20, mem_);

   EXPECT_EQ(cyclesLeft, 0);  //imma do this later on...
   EXPECT_EQ((int)cpu_.A, 0x69);
   EXPECT_FALSE((int)cpu_.Z);
   EXPECT_FALSE((int)cpu_.N);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}

TEST_F(TEST_6502, TYA_simple)
{
   cpu_.Reset(mem_, 0xFF00);
   mem_.debug_set(0xFF00, CPU::INS_LDY_IM);  
   mem_.debug_set(0xFF01, 0x0069);  
   mem_.debug_set(0xFF02, CPU::INS_TYA);  

   auto cyclesLeft = cpu_.execute(20, mem_);

   EXPECT_EQ(cyclesLeft, 0);  //imma do this later on...
   EXPECT_EQ((int)cpu_.A, 0x69);
   EXPECT_FALSE((int)cpu_.Z);
   EXPECT_FALSE((int)cpu_.N);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}

