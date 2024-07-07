#include "test.hpp"


// TEST_F(TEST_6502, PLA)
// {
//    mem_.debug_set(0xFFFC, CPU::INS_PLA);
//    mem_.debug_set( 0xFFFD, 0b10000000); /// the 1 on the first bit of 8bit number is consider to make it negative
//       /// - 2 complements or sth
//    auto cyclesLeft = cpu_.execute(2, mem_);
//
//    EXPECT_EQ(cyclesLeft, 0);
//    EXPECT_EQ((int)cpu_.A, 0b10000000);
//    EXPECT_FALSE((int)cpu_.Z);
//    EXPECT_TRUE((int)cpu_.N);
//    EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
// }

TEST_F(TEST_6502, TSX)
{
   cpu_.SP = 0x69;
   mem_.debug_set(0xFFFC, CPU::INS_TSX);
   auto cyclesLeft = cpu_.execute(2, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ((int)cpu_.X, 0x69);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}

TEST_F(TEST_6502, TXS)
{
   cpu_.X = 0x69;
   mem_.debug_set(0xFFFC, CPU::INS_TXS);
   auto cyclesLeft = cpu_.execute(2, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ((int)cpu_.SP, 0x69);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}


TEST_F(TEST_6502, PHA)
{
   cpu_.A = 0x69;
   mem_.debug_set(0xFFFC, CPU::INS_PHA);
   // cpu_.A = 0x00;
   auto addr = 0x0100 + cpu_.SP;
   HEX_PRINT("searching in location: ", addr);
   //mem_.debug_dumpMemory("PHA");

   auto cyclesLeft = cpu_.execute(10, mem_);
   auto retValue = mem_.debug_get(addr);

   //EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ((int)retValue, 0x69);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}

TEST_F(TEST_6502, PHP)
{
   cpu_.N = 1;   
   cpu_.D = 1;   
   cpu_.Z = 1;   

   uint8_t currentFlags = cpu_.getCurrentFlags();

   mem_.debug_set(0xFFFC, CPU::INS_PHP);
   auto addr = 0x0100 + cpu_.SP;
   HEX_PRINT("searching in location: ", addr);

   auto cyclesLeft = cpu_.execute(10, mem_);
   auto retValue = mem_.debug_get(addr);

   cpu_.N = 0;   
   cpu_.D = 0;   
   cpu_.Z = 0;   

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ(retValue, currentFlags);
   ///EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}

TEST_F(TEST_6502, PLA)
{   
   cpu_.Reset(mem_, 0xFF00);
   cpu_.A = 0x69;
   mem_.debug_set(0xFF00, CPU::INS_PHA);
   mem_.debug_set(0xFF01, CPU::INS_LDA_IM);
   mem_.debug_set(0xFF02, 0x00);
   mem_.debug_set(0xFF03, CPU::INS_PLA);

   auto cyclesLeft = cpu_.execute(10, mem_);


   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ(cpu_.A, 0x69);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}

TEST_F(TEST_6502, PLP)
{
   cpu_.Reset(mem_, 0xFF00);

   cpu_.N = 1;   
   cpu_.D = 1;   
   cpu_.Z = 0;   

   auto tempCopy = cpu_;

   uint8_t currentFlagsBefore = cpu_.getCurrentFlags();
   std::bitset<8> before(currentFlagsBefore);
   HEX_PRINT("those are the falgs before: ", before);


   mem_.debug_set(0xFF00, CPU::INS_PHP);
   mem_.debug_set(0xFF01, CPU::INS_LDA_IM);  ///this thing changes Z flag into 1
   mem_.debug_set(0xFF02, 0x00);
   mem_.debug_set(0xFF03, CPU::INS_PLP);

   auto cyclesLeft = cpu_.execute(10, mem_);

   uint8_t currentFlagsAfter = cpu_.getCurrentFlags();
   std::bitset<8> after(currentFlagsAfter);
   HEX_PRINT("those are the falgs after: ", after);
   
   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, tempCopy));
}
