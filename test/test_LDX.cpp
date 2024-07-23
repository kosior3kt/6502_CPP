#include "test.hpp"

TEST_F(TEST_6502, LDX_IM)
{
   test_LD(CPU::INS_LDX_IM, Register::X);
}

TEST_F(TEST_6502, LDX_ZP)
{
   mem_.debug_set(0xFFFC, CPU::INS_LDX_ZP);
   mem_.debug_set(0xFFFD, 0x42);
   mem_.debug_set(0x0042, 0x69);
   auto cyclesLeft = cpu_.execute(4, mem_);
   std::cout<<"dupa\n";

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ((int)cpu_.X, 0x69);
   EXPECT_FALSE((int)cpu_.Z);
   EXPECT_FALSE((int)cpu_.N);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}

TEST_F(TEST_6502, LDX_ZPY)
{
   cpu_.Y = 0x5;
   mem_.debug_set(0xFFFC, CPU::INS_LDX_ZPY);
   mem_.debug_set(0xFFFD, 0x42);
   mem_.debug_set(0x0047, 0x69);
   auto cyclesLeft = cpu_.execute(3, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ((int)cpu_.X, 0x69);
   EXPECT_FALSE((int)cpu_.Z);
   EXPECT_FALSE((int)cpu_.N);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}

TEST_F(TEST_6502, LDA_ZPY_withWrapping)
{
   cpu_.Y = 0xFF;
   mem_.debug_set(0xFFFC, CPU::INS_LDX_ZPY);
   mem_.debug_set(0xFFFD, 0x80);
   mem_.debug_set(0x007F, 0x69);
   auto cyclesLeft = cpu_.execute(3, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ((int)cpu_.X, 0x69);
   EXPECT_FALSE((int)cpu_.Z);
   EXPECT_FALSE((int)cpu_.N);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}

TEST_F(TEST_6502, LDX_AbsoluteAddressing)
{
   mem_.debug_set(0xFFFC, CPU::INS_LDX_ABS);
   mem_.debug_set(0xFFFD, 0x80);
   mem_.debug_set(0xFFFE, 0x69); /// 0x6980
   mem_.debug_set(0x6980, 0x69);
   auto cyclesLeft = cpu_.execute(4, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ((int)cpu_.X, 0x69);
   EXPECT_FALSE((int)cpu_.Z);
   EXPECT_FALSE((int)cpu_.N);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}

TEST_F(TEST_6502, LDX_AbsoluteAddressingWTF)
{
   mem_.debug_set(0xFFFC, CPU::INS_LDX_ABS);
   mem_.debug_set(0xFFFD, 0xFF);
   mem_.debug_set(0xFFFE, 0xF0); /// 0x6980
   mem_.debug_set(0xF0FF, 0x69);
   auto cyclesLeft = cpu_.execute(4, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ((int)cpu_.X, 0x69);
   EXPECT_FALSE((int)cpu_.Z);
   EXPECT_FALSE((int)cpu_.N);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}

TEST_F(TEST_6502, LDX_AbsoluteAddressingWTF_v2)
{
   cpu_.Reset(mem_, 0xFF00);

   mem_.debug_set(0xFF00, CPU::INS_LDX_ABS);
   mem_.debug_set(0xFF01, 0xFF);
   mem_.debug_set(0xFF02, 0xFF); /// 0x6980
   mem_.debug_set(0xFF03, CPU::INS_LDY_ABS);
   mem_.debug_set(0xFF04, 0x00);
   mem_.debug_set(0xFF05, 0x00);
   mem_.debug_set(0x0000, 0x12);
   mem_.debug_set(0xFFFF, 0x69);
   auto cyclesLeft = cpu_.execute(10, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ((int)cpu_.X, 0x69);
   EXPECT_EQ((int)cpu_.Y, 0x12);
   EXPECT_FALSE((int)cpu_.Z);
   EXPECT_FALSE((int)cpu_.N);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}

TEST_F(TEST_6502, LDXY_AbsoluteAddressing_noPageCrossing)
{
   cpu_.Y = 0x0001;
   mem_.debug_set(0xFFFC, CPU::INS_LDX_ABSY);
   mem_.debug_set(0xFFFD, 0x80);
   mem_.debug_set(0xFFFE, 0x69); /// 0x6980 + 0x0001 = 0x6981
   mem_.debug_set(0x6981, 0x69);
   auto cyclesLeft = cpu_.execute(4, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ((int)cpu_.X, 0x69);
   EXPECT_FALSE((int)cpu_.Z);
   EXPECT_FALSE((int)cpu_.N);
   mem_.debug_dumpMemory("LDXY_NPC");
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}

TEST_F(TEST_6502, LDXY_AbsoluteAddressing_withPageCrossing)
{
   cpu_.Y = 0x27;
   mem_.debug_set(0xFFFC, CPU::INS_LDX_ABSY);
   mem_.debug_set(0xFFFD, 0xFF);
   mem_.debug_set(0xFFFE, 0xFF); /// 0xFFFF + 0x0027 = (in this case we take into considerationg page crossing) = 0x0027 - 0x0001 (for page crossing compensation)
   mem_.debug_set(0x0026, 0x69);
   auto cyclesLeft = cpu_.execute(4, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ((int)cpu_.X, 0x69);
   EXPECT_FALSE((int)cpu_.Z);
   EXPECT_FALSE((int)cpu_.N);
   mem_.debug_dumpMemory("LDXY_PC");
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}
