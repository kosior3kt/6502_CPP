#include "test.hpp"

TEST_F(TEST_6502, LDA_IM)
{
   test_LD(CPU::INS_LDA_IM, Register::A);
}

TEST_F(TEST_6502, LDA_IM_NEGATIVE)
{
   mem_.debug_set(0xFFFC, CPU::INS_LDA_IM);
   mem_.debug_set(
       0xFFFD, 0b10000000
   ); /// the 1 on the first bit of 8bit number is consider to make it negative
      /// - 2 complements or sth
   auto cyclesLeft = cpu_.execute(2, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ((int)cpu_.A, 0b10000000);
   EXPECT_FALSE((int)cpu_.Z);
   EXPECT_TRUE((int)cpu_.N);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}

TEST_F(TEST_6502, LDA_IM_NEGATIVE_AND_OVERRIDEN)
{
   cpu_.A = 0x69;
   mem_.debug_set(0xFFFC, CPU::INS_LDA_IM);
   mem_.debug_set(
       0xFFFD, 0b10000000
   ); /// the 1 on the first bit of 8bit number is consider to make it negative
      /// - 2 complements or sth
   auto cyclesLeft = cpu_.execute(2, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ((int)cpu_.A, 0b10000000);
   EXPECT_FALSE((int)cpu_.Z);
   EXPECT_TRUE((int)cpu_.N);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}

TEST_F(TEST_6502, LDA_IM_ZERO_AND_OVERRIDEN)
{
   cpu_.A = 0x69;
   mem_.debug_set(0xFFFC, CPU::INS_LDA_IM);
   mem_.debug_set(
       0xFFFD, 0
   ); /// the 1 on the first bit of 8bit number is consider to make it negative
      /// - 2 complements or sth
   auto cyclesLeft = cpu_.execute(2, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ((int)cpu_.A, 0);
   EXPECT_TRUE((int)cpu_.Z);
   EXPECT_FALSE((int)cpu_.N);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}

TEST_F(TEST_6502, LDA_ZP)
{
   mem_.debug_set(0xFFFC, CPU::INS_LDA_ZP);
   mem_.debug_set(0xFFFD, 0x42);
   mem_.debug_set(0x0042, 0x69);
   auto cyclesLeft = cpu_.execute(3, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ((int)cpu_.A, 0x69);
   EXPECT_FALSE((int)cpu_.Z);
   EXPECT_FALSE((int)cpu_.N);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}

TEST_F(TEST_6502, LDA_ZPX)
{
   cpu_.X = 0x5;
   mem_.debug_set(0xFFFC, CPU::INS_LDA_ZPX);
   mem_.debug_set(0xFFFD, 0x42);
   mem_.debug_set(0x0047, 0x69);
   auto cyclesLeft = cpu_.execute(4, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ((int)cpu_.A, 0x69);
   EXPECT_FALSE((int)cpu_.Z);
   EXPECT_FALSE((int)cpu_.N);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}

TEST_F(TEST_6502, LDA_ZPX_withWrapping)
{
   cpu_.X = 0xFF;
   mem_.debug_set(0xFFFC, CPU::INS_LDA_ZPX);
   mem_.debug_set(0xFFFD, 0x80);
   mem_.debug_set(0x007F, 0x69);
   auto cyclesLeft = cpu_.execute(4, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ((int)cpu_.A, 0x69);
   EXPECT_FALSE((int)cpu_.Z);
   EXPECT_FALSE((int)cpu_.N);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}

TEST_F(TEST_6502, idleCPU)
{
   auto cyclesAtTheBeggining = 69;
   auto cyclesLeft           = cpu_.execute(cyclesAtTheBeggining, mem_);

   EXPECT_EQ(
       cyclesLeft, cyclesAtTheBeggining - 1
   ); /// one cycle for fetchig instruction
   EXPECT_FALSE((int)cpu_.Z);
   EXPECT_FALSE((int)cpu_.N);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}

TEST_F(TEST_6502, LDA_AbsoluteAddressing)
{
   mem_.debug_set(0xFFFC, CPU::INS_LDA_ABS);
   mem_.debug_set(0xFFFD, 0x80);
   mem_.debug_set(0xFFFE, 0x69); /// 0x6980
   mem_.debug_set(0x6980, 0x69);
   auto cyclesLeft = cpu_.execute(4, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ((int)cpu_.A, 0x69);
   EXPECT_FALSE((int)cpu_.Z);
   EXPECT_FALSE((int)cpu_.N);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}

TEST_F(TEST_6502, LDAX_AbsoluteAddressing_noPageCrossing)
{
   cpu_.X = 0x0001;
   mem_.debug_set(0xFFFC, CPU::INS_LDA_ABSX);
   mem_.debug_set(0xFFFD, 0x80);
   mem_.debug_set(0xFFFE, 0x69); /// 0x6980 + 0x0001 = 0x6981
   mem_.debug_set(0x6981, 0x69);
   auto cyclesLeft = cpu_.execute(4, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ((int)cpu_.A, 0x69);
   EXPECT_FALSE((int)cpu_.Z);
   EXPECT_FALSE((int)cpu_.N);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}

TEST_F(TEST_6502, LDAY_AbsoluteAddressing_noPageCrossing)
{
   cpu_.Y = 0x0001;
   mem_.debug_set(0xFFFC, CPU::INS_LDA_ABSY);
   mem_.debug_set(0xFFFD, 0x80);
   mem_.debug_set(0xFFFE, 0x69); /// 0x6980 + 0x0001 = 0x6981
   mem_.debug_set(0x6981, 0x69);
   auto cyclesLeft = cpu_.execute(4, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ((int)cpu_.A, 0x69);
   EXPECT_FALSE((int)cpu_.Z);
   EXPECT_FALSE((int)cpu_.N);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}

TEST_F(TEST_6502, LDAX_AbsoluteAddressing_withPageCrossing)
{
   cpu_.X = 0x27;
   mem_.debug_set(0xFFFC, CPU::INS_LDA_ABSX);
   mem_.debug_set(0xFFFD, 0xFF);
   mem_.debug_set(0xFFFE, 0xFF); /// 0xFFFF + 0x0027 = (in this case we take into considerationg page crossing) = 0x0027 - 0x0001 (for page crossing compensation)
   mem_.debug_set(0x0026, 0x69);
   auto cyclesLeft = cpu_.execute(5, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ((int)cpu_.A, 0x69);
   EXPECT_FALSE((int)cpu_.Z);
   EXPECT_FALSE((int)cpu_.N);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}

TEST_F(TEST_6502, LDAY_AbsoluteAddressing_withPageCrossing)
{
   cpu_.Y = 0x27;
   mem_.debug_set(0xFFFC, CPU::INS_LDA_ABSY);
   mem_.debug_set(0xFFFD, 0xFF);
   mem_.debug_set(0xFFFE, 0xFF); /// 0xFFFF + 0x0027 = (in this case we take into considerationg page crossing) = 0x0027 - 0x0001 (for page crossing compensation)
   mem_.debug_set(0x0026, 0x69);
   auto cyclesLeft = cpu_.execute(5, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ((int)cpu_.A, 0x69);
   EXPECT_FALSE((int)cpu_.Z);
   EXPECT_FALSE((int)cpu_.N);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}

TEST_F(TEST_6502, LDA_IndirectAdressingY)
{  
   cpu_.Y = 0x01;
   mem_.debug_set(0xFFFC, CPU::INS_LDA_INDY);
   mem_.debug_set(0xFFFD, 0x004);
   mem_.debug_set(0x0004, 0x10); /// looking first at the original location
   mem_.debug_set(0x0005, 0x05); /// now we need to add Y to the lower byte
   mem_.debug_set(0x0511, 0x69); /// 0x05 ++ (0x10 + 0x01) = 0x0511  , or is it other way around?

   auto cyclesLeft = cpu_.execute(5, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ((int)cpu_.A, 0x69);
   EXPECT_FALSE((int)cpu_.Z);
   EXPECT_FALSE((int)cpu_.N);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}

TEST_F(TEST_6502, LDA_IndirectAdressingY_withPageCrossing)
{  
   cpu_.Y = 0xFF;
   mem_.debug_set(0xFFFC, CPU::INS_LDA_INDY);
   mem_.debug_set(0xFFFD, 0x04);
   mem_.debug_set(0x0004, 0x01); /// looking first at the original location and add it to Y => 0xFF + 0x01 = 0x100 + additional cycle
   mem_.debug_set(0x0005, 0x01); /// now higher byte => 0x0100 + 0x01 (high) = 0x0200
   mem_.debug_set(0x0200, 0x69); /// 

   auto cyclesLeft = cpu_.execute(6, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ((int)cpu_.A, 0x69);
   EXPECT_FALSE((int)cpu_.Z);
   EXPECT_FALSE((int)cpu_.N);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}

TEST_F(TEST_6502, LDA_IndirectAdressingX)
{  ///yeah, this is different than the Y version on purpose (apparently)
   cpu_.X = 0x02;
   mem_.debug_set(0xFFFC, CPU::INS_LDA_INDX);
   mem_.debug_set(0xFFFD, 0x004);
   mem_.debug_set(0x0006, 0x10); /// 0x02 + 0x04 = 0x06
   mem_.debug_set(0x0007, 0x05); ///we take 2 bits from there and sum up the result
   mem_.debug_set(0x0510, 0x69); 

   auto cyclesLeft = cpu_.execute(6, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ((int)cpu_.A, 0x69);
   EXPECT_FALSE((int)cpu_.Z);
   EXPECT_FALSE((int)cpu_.N);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}

