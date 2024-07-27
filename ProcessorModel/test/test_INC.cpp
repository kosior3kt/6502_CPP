#include "test.hpp"

TEST_F(TEST_6502, INX_simple)
{
   cpu_.X = 0x68;
   mem_.set(0xFFFC, CPU::INS_INX);
   auto cyclesLeft = cpu_.execute(2, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ((int)cpu_.X, 0x69);
   EXPECT_FALSE((int)cpu_.Z);
   EXPECT_FALSE((int)cpu_.N);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}

TEST_F(TEST_6502, INX_Negative)
{
   cpu_.X = 0b10000000;
   mem_.set(0xFFFC, CPU::INS_INX);
   auto cyclesLeft = cpu_.execute(2, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ((int)cpu_.X, 0b10000001);
   EXPECT_FALSE((int)cpu_.Z);
   EXPECT_TRUE((int)cpu_.N);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}

TEST_F(TEST_6502, INX_PageCrossing)
{
   cpu_.X = 0xFF;
   mem_.set(0xFFFC, CPU::INS_INX);
   auto cyclesLeft = cpu_.execute(2, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ((int)cpu_.X, 0x00);
   EXPECT_TRUE((int)cpu_.Z);
   EXPECT_FALSE((int)cpu_.N);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}

TEST_F(TEST_6502, INY_simple)
{
   cpu_.Y = 0x68;
   mem_.set(0xFFFC, CPU::INS_INY);
   auto cyclesLeft = cpu_.execute(2, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ((int)cpu_.Y, 0x69);
   EXPECT_FALSE((int)cpu_.Z);
   EXPECT_FALSE((int)cpu_.N);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}

TEST_F(TEST_6502, INY_Negative)
{
   cpu_.Y = 0b10000000;
   mem_.set(0xFFFC, CPU::INS_INY);
   auto cyclesLeft = cpu_.execute(2, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ((int)cpu_.Y, 0b10000001);
   EXPECT_FALSE((int)cpu_.Z);
   EXPECT_TRUE((int)cpu_.N);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}

TEST_F(TEST_6502, INY_PageCrossing)
{
   cpu_.Y = 0xFF;
   mem_.set(0xFFFC, CPU::INS_INY);
   auto cyclesLeft = cpu_.execute(2, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ((int)cpu_.Y, 0x00);
   EXPECT_TRUE((int)cpu_.Z);
   EXPECT_FALSE((int)cpu_.N);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}

TEST_F(TEST_6502, INC_ZP_simple)
{
   auto MEM_ADDR = 0x0069;
   mem_.set(MEM_ADDR, 0x68);
   mem_.set(0xFFFC, CPU::INS_INC_ZP);
   mem_.set(0xFFFD, MEM_ADDR);
   auto cyclesLeft = cpu_.execute(5, mem_);

   auto temp = mem_.Data[MEM_ADDR];
   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ(temp, 0x69);
   EXPECT_FALSE((int)cpu_.Z);
   EXPECT_FALSE((int)cpu_.N);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}

TEST_F(TEST_6502, INC_ZPX_simple)
{
   auto MEM_ADDR = 0x0068;
   cpu_.X        = 0x01;
   mem_.set(MEM_ADDR + cpu_.X, 0x68);
   mem_.set(0xFFFC, CPU::INS_INC_ZPX);
   mem_.set(0xFFFD, MEM_ADDR);
   auto cyclesLeft = cpu_.execute(5, mem_);

   auto temp = mem_.Data[MEM_ADDR + cpu_.X];
   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ(temp, 0x69);
   EXPECT_FALSE((int)cpu_.Z);
   EXPECT_FALSE((int)cpu_.N);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}

TEST_F(TEST_6502, INC_ABS_simple)
{
   auto MEM_ADDR = 0x6969;
   mem_.set(MEM_ADDR, 0x68);
   mem_.set(0xFFFC, CPU::INS_INC_ABS);
   mem_.set(0xFFFD, 0x69);
   mem_.set(0xFFFE, 0x69); /// later take care of endianness here
   auto cyclesLeft = cpu_.execute(6, mem_);

   auto temp = mem_.Data[MEM_ADDR];
   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ((int)temp, 0x69);
   EXPECT_FALSE((int)cpu_.Z);
   EXPECT_FALSE((int)cpu_.N);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}

TEST_F(TEST_6502, INC_ZPX_PageCrossing)
{   auto MEM_ADDR = 0x00FF;   ///page corssing so we expect it to be at the adress 0x00. Hope it is not reserved or sth
   cpu_.X        = 0x01;
   mem_.set(0x00, 0x68);
   mem_.set(0xFFFC, CPU::INS_INC_ZPX);
   mem_.set(0xFFFD, MEM_ADDR);
   auto cyclesLeft = cpu_.execute(5, mem_);

   auto temp = mem_.Data[0x00];
   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ(temp, 0x69);
   EXPECT_FALSE((int)cpu_.Z);
   EXPECT_FALSE((int)cpu_.N);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));

}
