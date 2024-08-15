#include "test.hpp"

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
