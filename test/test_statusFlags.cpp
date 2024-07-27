#include "test.hpp"

TEST_F(TEST_6502, CLC)
{
   cpu_.C = 1;
   mem_.set(0xFFFC, CPU::INS_CLC);
   auto cyclesLeft = cpu_.execute(3, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ((int)cpu_.C, 0x00);
}

TEST_F(TEST_6502, CLD)
{
   cpu_.D = 1;
   mem_.set(0xFFFC, CPU::INS_CLD);
   auto cyclesLeft = cpu_.execute(3, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ((int)cpu_.D, 0x00);
}

TEST_F(TEST_6502, CLI)
{
   cpu_.I = 1;
   mem_.set(0xFFFC, CPU::INS_CLI);
   auto cyclesLeft = cpu_.execute(3, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ((int)cpu_.I, 0x00);
}

TEST_F(TEST_6502, CLV)
{
   cpu_.V = 1;
   mem_.set(0xFFFC, CPU::INS_CLV);
   auto cyclesLeft = cpu_.execute(3, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ((int)cpu_.V, 0x00);
}

TEST_F(TEST_6502, SEC)
{
   cpu_.C = 0;
   mem_.set(0xFFFC, CPU::INS_SEC);
   auto cyclesLeft = cpu_.execute(3, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ((int)cpu_.C, 0x01);
}

TEST_F(TEST_6502, SED)
{
   cpu_.D = 0;
   mem_.set(0xFFFC, CPU::INS_SED);
   auto cyclesLeft = cpu_.execute(3, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ((int)cpu_.D, 0x01);
}

TEST_F(TEST_6502, SEI)
{
   cpu_.I = 0;
   mem_.set(0xFFFC, CPU::INS_SEI);
   auto cyclesLeft = cpu_.execute(3, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ((int)cpu_.I, 0x01);
}
