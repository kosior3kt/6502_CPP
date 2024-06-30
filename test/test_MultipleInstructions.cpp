#include"test.hpp"



TEST_F(TEST_6502, MemoryDumpTest)
{
   mem_.debug_dumpMemory("dupa.txt");
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
   auto cyclesLeft = cpu_.execute(18, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ((int)cpu_.A, 0x6B);
   EXPECT_FALSE((int)cpu_.Z);
   EXPECT_FALSE((int)cpu_.N);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}

TEST_F(TEST_6502, slightlyMoreComplicatedProgramWithMemoryManipulation)
{
   cpu_.Reset(mem_, 0xFF00);
   mem_.debug_set(0xFF00, CPU::INS_JSR);
   mem_.debug_set(0xFF01, 0x42);
   mem_.debug_set(0xFF02, 0x42);
   mem_.debug_set(0x4242, CPU::INS_LDA_IM);
   mem_.debug_set(0x4243, 0x69);
   mem_.debug_set(0x4244, CPU::INS_JSR);
   mem_.debug_set(0x4245, 0x69);
   mem_.debug_set(0x4246, 0x69);
   mem_.debug_set(0x6969, CPU::INS_LDA_IM);
   mem_.debug_set(0x696A, 0x6B);
   auto cyclesLeft = cpu_.execute(18, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ((int)cpu_.A, 0x6B);
   EXPECT_FALSE((int)cpu_.Z);
   EXPECT_FALSE((int)cpu_.N);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}


TEST_F(TEST_6502, forthAndBack)
{
   cpu_.Reset(mem_, 0xFF00);
   mem_.debug_set(0xFF00, CPU::INS_JSR);  ///6 cycles
   mem_.debug_set(0xFF01, 0x60);
   mem_.debug_set(0xFF02, 0x00);
   mem_.debug_set(0x6000, CPU::INS_RTS);  ///6 cycles
   mem_.debug_set(0xFF03, CPU::INS_LDA_IM);  ///2 cycles?
   mem_.debug_set(0xFF04, 0x42);

   auto cyclesLeft = cpu_.execute(16, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ((int)cpu_.A, 0x42);
   EXPECT_FALSE((int)cpu_.Z);
   EXPECT_FALSE((int)cpu_.N);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
   mem_.debug_dumpMemory("pleaseWork.txt");
}

