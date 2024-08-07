#include "test.hpp"


TEST_F(TEST_6502, veryFuckingConvolutedTest)
{
   cpu_.Reset(mem_, 0xFF00);
   mem_.set(0xFF00, CPU::INS_JSR);  
   mem_.set(0xFF01, 0x00);
   mem_.set(0xFF02, 0x60);
   mem_.set(0x6000, CPU::INS_LDX_ZP);  
   mem_.set(0x6001, 0x33);
   mem_.set(0x0033, 0x69);
   mem_.set(0x6002, CPU::INS_JSR);  
   mem_.set(0x6003, 0x20);  
   mem_.set(0x6004, 0x10);  
   mem_.set(0x1020, CPU::INS_LDY_ABS);  
   mem_.set(0x1021, 0x00);  
   mem_.set(0x1022, 0x17);  
   mem_.set(0x1700, 0x63);  
   mem_.set(0x1023, CPU::INS_RTS);  
   mem_.set(0x6005, CPU::INS_RTS);  
   mem_.set(0xFF03, CPU::INS_LDA_IM);  
   mem_.set(0xFF04, 0x69);

   auto cyclesLeft = cpu_.execute(44, mem_);

   mem_.debug_dumpMemory("convoluted");

   // EXPECT_EQ(cyclesLeft, 0);  //imma do this later on...
   EXPECT_EQ((int)cpu_.A, 0x69);
   EXPECT_EQ((int)cpu_.X, 0x69);
   EXPECT_EQ((int)cpu_.Y, 0x63);
   EXPECT_FALSE((int)cpu_.Z);
   EXPECT_FALSE((int)cpu_.N);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}


TEST_F(TEST_6502, JMP_ABS_andOtherTrash)
{
   cpu_.Reset(mem_, 0xFF00);
   mem_.set(0xFF00, CPU::INS_JMP_ABS);  
   mem_.set(0xFF01, 0x0010);  
   mem_.set(0xFF02, 0x0020);  
   mem_.set(0x2010, CPU::INS_LDA_IM);  
   mem_.set(0x2011, 0x69);  

   auto cyclesLeft = cpu_.execute(8, mem_);

   EXPECT_EQ(cyclesLeft, 0);  //imma do this later on...
   EXPECT_EQ((int)cpu_.A, 0x69);
   EXPECT_FALSE((int)cpu_.Z);
   EXPECT_FALSE((int)cpu_.N);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}

TEST_F(TEST_6502, JMP_IND_andOtherTrashAsWell)
{
   cpu_.Reset(mem_, 0xFF00);
   mem_.set(0xFF00, CPU::INS_JMP_IND);  
   mem_.set(0xFF01, 0x0010);  
   mem_.set(0xFF02, 0x0020);  
   mem_.set(0x2010, 0x10);  
   mem_.set(0x2011, 0x69);  
   mem_.set(0x6910, CPU::INS_LDA_ZP);  
   mem_.set(0x6911, 0x42);  
   mem_.set(0x0042, 0x69);  

   auto cyclesLeft = cpu_.execute(14, mem_);

   EXPECT_EQ(cyclesLeft, 0);  //imma do this later on...
   EXPECT_EQ((int)cpu_.A, 0x69);
   EXPECT_FALSE((int)cpu_.Z);
   EXPECT_FALSE((int)cpu_.N);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));

}

