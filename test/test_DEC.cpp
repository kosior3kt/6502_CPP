
#include "test.hpp"

TEST_F(TEST_6502, DEX_simple)
{
   cpu_.X = 0x6A;
   mem_.debug_set(0xFFFC, CPU::INS_DEX);
   auto cyclesLeft = cpu_.execute(2, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ((int)cpu_.X, 0x69);
   // EXPECT_FALSE((int)cpu_.Z);
   // EXPECT_FALSE((int)cpu_.N);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}

TEST_F(TEST_6502, DEY_simple)
{
   cpu_.Y = 0x6A;
   mem_.debug_set(0xFFFC, CPU::INS_DEY);
   auto cyclesLeft = cpu_.execute(2, mem_);

   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ((int)cpu_.Y, 0x69);
   // EXPECT_FALSE((int)cpu_.Z);
   // EXPECT_FALSE((int)cpu_.N);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}

TEST_F(TEST_6502, DEC_ZP_simple)
{
   auto MEM_ADDR = 0x0069;
   mem_.debug_set(MEM_ADDR, 0x6A);
   mem_.debug_set(0xFFFC, CPU::INS_DEC_ZP);
   mem_.debug_set(0xFFFD, MEM_ADDR);
   auto cyclesLeft = cpu_.execute(5, mem_);

   auto temp = mem_.Data[MEM_ADDR];
   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ(temp, 0x69);
   EXPECT_FALSE((int)cpu_.Z);
   EXPECT_FALSE((int)cpu_.N);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}

TEST_F(TEST_6502, DEC_ZPX_simple)
{
   auto MEM_ADDR = 0x0068;
   cpu_.X        = 0x01;
   mem_.debug_set(MEM_ADDR + cpu_.X, 0x6A);
   mem_.debug_set(0xFFFC, CPU::INS_DEC_ZPX);
   mem_.debug_set(0xFFFD, MEM_ADDR);
   auto cyclesLeft = cpu_.execute(5, mem_);

   auto temp = mem_.Data[MEM_ADDR + cpu_.X];
   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ(temp, 0x69);
   EXPECT_FALSE((int)cpu_.Z);
   EXPECT_FALSE((int)cpu_.N);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}

TEST_F(TEST_6502, DEC_ABS_simple)
{
   auto MEM_ADDR = 0x6969;
   mem_.debug_set(MEM_ADDR, 0x6A);
   mem_.debug_set(0xFFFC, CPU::INS_DEC_ABS);
   mem_.debug_set(0xFFFD, 0x69);
   mem_.debug_set(0xFFFE, 0x69); /// later take care of endianness here
   auto cyclesLeft = cpu_.execute(6, mem_);

   auto temp = mem_.Data[MEM_ADDR];
   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ((int)temp, 0x69);
   EXPECT_FALSE((int)cpu_.Z);
   EXPECT_FALSE((int)cpu_.N);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
}

TEST_F(TEST_6502, DEC_ZPX_PageCrossing)
{   auto MEM_ADDR = 0x00FF;   ///page corssing so we expect it to be at the adress 0x00. Hope it is not reserved or sth
   cpu_.X        = 0x01;
   mem_.debug_set(0x00, 0x6A);
   mem_.debug_set(0xFFFC, CPU::INS_DEC_ZPX);
   mem_.debug_set(0xFFFD, MEM_ADDR);
   auto cyclesLeft = cpu_.execute(5, mem_);

   auto temp = mem_.Data[0x00];
   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_EQ(temp, 0x69);
   EXPECT_FALSE((int)cpu_.Z);
   EXPECT_FALSE((int)cpu_.N);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));

}
