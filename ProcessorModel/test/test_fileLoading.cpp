#include "test.hpp"




///TODO: change me later into a normal test daddy

#if 0

TEST_F(TEST_6502, fileLoading_generatedFromASM)
{
   mem_.loadFromFile("outputTemp");
   mem_.debug_dumpMemory("dupaaaa");

   cpu_.showCPUState(mem_, 1, 1, 0);

   auto cyclesLeft = cpu_.execute(100, mem_);

   cpu_.showCPUState(mem_, 1, 1, 1);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ((int)cpu_.A, 0x69);
   EXPECT_FALSE((int)cpu_.Z);
   EXPECT_FALSE((int)cpu_.N);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));

   cpu_.showCPUState(mem_, 1, 1, 2);

}

#endif

#if 1


TEST_F(TEST_6502, fileLoading_generatedFromASM_MAYBE_WORKING)
{
   mem_.set(0xFFFC, CPU::INS_JMP_ABS);
   mem_.set(0xFFFD, 0x00);
   mem_.set(0xFFFE, 0x80);

   mem_.set(0x8000, CPU::INS_LDA_IM);
   mem_.set(0x8001, 0x10);

   mem_.set(0x8002, CPU::INS_STA_ABS);
   mem_.set(0x8003, 0x00);
   mem_.set(0x8004, 0x40);

   mem_.set(0x8005, CPU::INS_LDX_IM);
   mem_.set(0x8006, 0x69);

   mem_.set(0x8007, CPU::INS_TXA);
   mem_.set(0x8008, CPU::INS_NOTHING);  


   /*
      {"LDA #$10\n"},
      {"STA $4000\n"},
      {"LDX #$69\n"},
      {"TXA\n"},
    */
   mem_.debug_dumpMemory("dupaaaa2");
   auto cyclesLeft = cpu_.execute(100, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ((int)cpu_.A, 0x69);
   EXPECT_FALSE((int)cpu_.Z);
   EXPECT_FALSE((int)cpu_.N);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));

}

#endif


///TODO: change all of those later on

#if 0 

TEST_F(TEST_6502, fileLoading_realUsageTest)
{
   mem_.loadFromFile("file.aa");
   mem_.debug_dumpMemory("file.dump");

   cpu_.showCPUState(mem_, 1, 1, 0);

   auto cyclesLeft = cpu_.execute(100, mem_);

   cpu_.showCPUState(mem_, 1, 1, 1);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ((int)cpu_.A, 0x69);
   EXPECT_FALSE((int)cpu_.Z);
   EXPECT_FALSE((int)cpu_.N);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));

   cpu_.showCPUState(mem_, 1, 1, 2);

}

#endif



#if 0

TEST_F(TEST_6502, fileLoading_LDA)
{
   mem_.loadFromFile("LDA");
   auto cyclesLeft = cpu_.execute(100, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ((int)cpu_.A, 0x69);
   EXPECT_FALSE((int)cpu_.Z);
   EXPECT_FALSE((int)cpu_.N);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));

}
#endif

///this is the thing that checks formatting of CPU stated displaying
#if 0 
TEST_F(TEST_6502, CPU_state)
{
   mem_.loadFromFile("LDA");
   auto cyclesLeft = cpu_.execute(100, mem_);

   cpu_.showCPUState(mem_, true, true);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ((int)cpu_.A, 0x69);
   EXPECT_FALSE((int)cpu_.Z);
   EXPECT_FALSE((int)cpu_.N);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));

}
#endif
