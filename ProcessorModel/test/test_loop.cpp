#include "test.hpp"

TEST_F(TEST_6502, loopTest)
{
   cpu_.Reset(mem_, 0xFF00);

   mem_.set(0xFF00, CPU::INS_LDA_IM);
   mem_.set(0xFF01, 0);
   mem_.set(0xFF02, CPU::INS_CLC);
   ///here loop begins

   mem_.set(0xFF03, CPU::INS_ADC_IM);
   mem_.set(0xFF04, 1);

   mem_.set(0xFF05, CPU::INS_CMP_IM);
   mem_.set(0xFF06, 8);   ///not hex values
                                 
   mem_.set(0xFF07, CPU::INS_BNE);
   mem_.set(0xFF08, (Byte)-6);   ///does this work?

   ///end of loop
   mem_.set(0xFF09, CPU::INS_LDX_IM);
   mem_.set(0xFF0A, 0x69);


   auto cyclesLeft = cpu_.execute(100, mem_);
   HEX_PRINT("value of A: ", cpu_.A);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ((int)cpu_.X, 0x69);

   // EXPECT_FALSE((int)cpu_.Z);
   // EXPECT_FALSE((int)cpu_.N);
   // EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}
