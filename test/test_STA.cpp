#include "test.hpp"

////////////////STA

TEST_F(TEST_6502, STA_ZP_SIMPLE)
{
   mem_.debug_set(0xFFFC, CPU::INS_STA_ZP);
   mem_.debug_set(0xFFFD, 0x42);
   cpu_.A = 0x69;
   auto cyclesLeft = cpu_.execute(3, mem_);

   Byte res = mem_.debug_get(0x0042);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ((int)res, 0x69);

   ///nothing shuold be changed
   EXPECT_TRUE(testHelper::allFlagsUnchanged(cpu_, copyCPU_));
}

TEST_F(TEST_6502, STA_ZPX_SIMPLE)
{
   mem_.debug_set(0xFFFC, CPU::INS_STA_ZPX);
   mem_.debug_set(0xFFFD, 0x41);
   cpu_.A = 0x69;
   cpu_.X = 0x01;
   auto cyclesLeft = cpu_.execute(4, mem_);

   Byte res = mem_.debug_get(0x0042);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ((int)res, 0x69);

   ///nothing shuold be changed
   EXPECT_TRUE(testHelper::allFlagsUnchanged(cpu_, copyCPU_));
}

TEST_F(TEST_6502, STA_ABS_SIMPLE)
{
   mem_.debug_set(0xFFFC, CPU::INS_STA_ABS);
   mem_.debug_set(0xFFFD, 0x42);
   mem_.debug_set(0xFFFE, 0x42);
   cpu_.A = 0x69;
   auto cyclesLeft = cpu_.execute(4, mem_);

   Byte res = mem_.debug_get(0x4242);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ((int)res, 0x69);

   ///nothing shuold be changed
   EXPECT_TRUE(testHelper::allFlagsUnchanged(cpu_, copyCPU_));
}

TEST_F(TEST_6502, STA_ABSX_SIMPLE)
{
   mem_.debug_set(0xFFFC, CPU::INS_STA_ABSX);
   mem_.debug_set(0xFFFD, 0x41);
   mem_.debug_set(0xFFFE, 0x42);
   cpu_.A = 0x69;
   cpu_.X = 0x0001;
   auto cyclesLeft = cpu_.execute(5, mem_);

   Byte res = mem_.debug_get(0x4242);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ((int)res, 0x69);

   ///nothing shuold be changed
   EXPECT_TRUE(testHelper::allFlagsUnchanged(cpu_, copyCPU_));
}

TEST_F(TEST_6502, STA_ABSY_SIMPLE)
{
   mem_.debug_set(0xFFFC, CPU::INS_STA_ABSY);
   mem_.debug_set(0xFFFD, 0x41);
   mem_.debug_set(0xFFFE, 0x42);
   cpu_.A = 0x69;
   cpu_.Y = 0x0001;
   auto cyclesLeft = cpu_.execute(5, mem_);

   Byte res = mem_.debug_get(0x4242);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ((int)res, 0x69);

   ///nothing shuold be changed
   EXPECT_TRUE(testHelper::allFlagsUnchanged(cpu_, copyCPU_));
}

TEST_F(TEST_6502, STA_INDX_SIMPLE)
{
   mem_.debug_set(0xFFFC, CPU::INS_STA_INDX);
   mem_.debug_set(0xFFFD, 0x41);
   cpu_.A = 0x69;
   cpu_.X = 0x0001;

   mem_.debug_set(0x0042, 0x69);
   mem_.debug_set(0x0043, 0x69);
   
   auto cyclesLeft = cpu_.execute(6, mem_);

   Byte res = mem_.debug_get(0x6969);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ((int)res, 0x69);

   ///nothing shuold be changed
   EXPECT_TRUE(testHelper::allFlagsUnchanged(cpu_, copyCPU_));
}

TEST_F(TEST_6502, STA_INDY_SIMPLE)
{
   mem_.debug_set(0xFFFC, CPU::INS_STA_INDY);
   mem_.debug_set(0xFFFD, 0x42);
   cpu_.A = 0x69;
   cpu_.Y = 0x0001;
   mem_.debug_set(0x0042, 0x68);
   mem_.debug_set(0x0043, 0x69);
   auto cyclesLeft = cpu_.execute(6, mem_);

   Byte res = mem_.debug_get(0x6969);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ((int)res, 0x69);

   ///nothing shuold be changed
   EXPECT_TRUE(testHelper::allFlagsUnchanged(cpu_, copyCPU_));
}


////////////////STX

TEST_F(TEST_6502, STX_ZP_SIMPLE)
{
   mem_.debug_set(0xFFFC, CPU::INS_STX_ZP);
   mem_.debug_set(0xFFFD, 0x42);
   cpu_.X = 0x69;
   auto cyclesLeft = cpu_.execute(4, mem_);

   Byte res = mem_.debug_get(0x0042);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ((int)res, 0x69);

   ///nothing shuold be changed
   EXPECT_TRUE(testHelper::allFlagsUnchanged(cpu_, copyCPU_));
}

TEST_F(TEST_6502, STX_ZPY_SIMPLE)
{
   mem_.debug_set(0xFFFC, CPU::INS_STX_ZPY);
   mem_.debug_set(0xFFFD, 0x41);
   cpu_.X = 0x69;
   cpu_.Y = 0x01;
   auto cyclesLeft = cpu_.execute(4, mem_);

   Byte res = mem_.debug_get(0x0042);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ((int)res, 0x69);

   ///nothing shuold be changed
   EXPECT_TRUE(testHelper::allFlagsUnchanged(cpu_, copyCPU_));
}

TEST_F(TEST_6502, STX_ABS_SIMPLE)
{
   mem_.debug_set(0xFFFC, CPU::INS_STX_ABS);
   mem_.debug_set(0xFFFD, 0x42);
   mem_.debug_set(0xFFFE, 0x42);
   cpu_.X = 0x69;
   auto cyclesLeft = cpu_.execute(4, mem_);

   Byte res = mem_.debug_get(0x4242);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ((int)res, 0x69);

   ///nothing shuold be changed
   EXPECT_TRUE(testHelper::allFlagsUnchanged(cpu_, copyCPU_));
}

////////////////STY

TEST_F(TEST_6502, STY_ZP_SIMPLE)
{
   mem_.debug_set(0xFFFC, CPU::INS_STY_ZP);
   mem_.debug_set(0xFFFD, 0x42);
   cpu_.Y = 0x69;
   auto cyclesLeft = cpu_.execute(3, mem_);

   Byte res = mem_.debug_get(0x0042);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ((int)res, 0x69);

   ///nothing shuold be changed
   EXPECT_TRUE(testHelper::allFlagsUnchanged(cpu_, copyCPU_));
}

TEST_F(TEST_6502, STY_ZPX_SIMPLE)
{
   mem_.debug_set(0xFFFC, CPU::INS_STY_ZPX);
   mem_.debug_set(0xFFFD, 0x41);
   cpu_.Y = 0x69;
   cpu_.X = 0x01;
   auto cyclesLeft = cpu_.execute(4, mem_);

   Byte res = mem_.debug_get(0x0042);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ((int)res, 0x69);

   ///nothing shuold be changed
   EXPECT_TRUE(testHelper::allFlagsUnchanged(cpu_, copyCPU_));
}

TEST_F(TEST_6502, STY_ABS_SIMPLE)
{
   mem_.debug_set(0xFFFC, CPU::INS_STY_ABS);
   mem_.debug_set(0xFFFD, 0x42);
   mem_.debug_set(0xFFFE, 0x42);
   cpu_.Y = 0x69;
   auto cyclesLeft = cpu_.execute(4, mem_);

   Byte res = mem_.debug_get(0x4242);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ((int)res, 0x69);

   ///nothing shuold be changed
   EXPECT_TRUE(testHelper::allFlagsUnchanged(cpu_, copyCPU_));
}
