#include "test.hpp"

TEST_F(TEST_6502, TSX)
{
   cpu_.SP = 0x69;
   mem_.set(0xFFFC, CPU::INS_TSX);
   auto cyclesLeft = cpu_.execute(2, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ((int)cpu_.X, 0x69);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}

TEST_F(TEST_6502, TXS)
{
   cpu_.X = 0x69;
   mem_.set(0xFFFC, CPU::INS_TXS);
   auto cyclesLeft = cpu_.execute(2, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ((int)cpu_.SP, 0x69);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}


TEST_F(TEST_6502, PHA)
{
   cpu_.A = 0x69;
   mem_.set(0xFFFC, CPU::INS_PHA);
   mem_.set(0xFFFD, CPU::INS_NOTHING);  
   // cpu_.A = 0x00;
   auto addr = 0x0100 + cpu_.SP;
   HEX_PRINT("searching in location: ", addr);
   //mem_.debug_dumpMemory("PHA");

   auto cyclesLeft = cpu_.execute(10, mem_);
   auto retValue = mem_.at(addr);

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

   mem_.set(0xFFFC, CPU::INS_PHP);
   auto addr = 0x0100 + cpu_.SP;
   HEX_PRINT("searching in location: ", addr);

   auto cyclesLeft = cpu_.execute(10, mem_);
   auto retValue = mem_.at(addr);

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
   mem_.set(0xFF00, CPU::INS_PHA);
   mem_.set(0xFF01, CPU::INS_LDA_IM);
   mem_.set(0xFF02, 0x00);
   mem_.set(0xFF03, CPU::INS_PLA);

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


   mem_.set(0xFF00, CPU::INS_PHP);
   mem_.set(0xFF01, CPU::INS_LDA_IM);  ///this thing changes Z flag into 1
   mem_.set(0xFF02, 0x00);
   mem_.set(0xFF03, CPU::INS_PLP);

   auto cyclesLeft = cpu_.execute(10, mem_);

   uint8_t currentFlagsAfter = cpu_.getCurrentFlags();
   std::bitset<8> after(currentFlagsAfter);
   HEX_PRINT("those are the falgs after: ", after);
   
   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, tempCopy));
}
