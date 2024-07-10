#include "test.hpp"


TEST_F(TEST_6502, ASL)
{
    cpu_.Reset(mem_, 0x8000);
    cpu_.A = 0b00001000;
    mem_.debug_set(0x8000, CPU::INS_ASL_ACC);

    auto cyclesLeft = cpu_.execute(4, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ(cpu_.A, 0b00010000);
}

TEST_F(TEST_6502, ASL_complicated)
{
    cpu_.Reset(mem_, 0x8000);
    cpu_.A = 0b10000000;
    mem_.debug_set(0x8000, CPU::INS_ASL_ACC);

    auto cyclesLeft = cpu_.execute(4, mem_);

    ///TODO: should the Z flag be set or the N flag???????
    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ(cpu_.A, 0b00000000);
    EXPECT_TRUE(cpu_.CPU::C); // Overflow flag not set
}

TEST_F(TEST_6502, ASL_ZP)
{
    cpu_.Reset(mem_, 0x8000);
    mem_.debug_set(0x0042, 0b00001000);
    mem_.debug_set(0x8000, CPU::INS_ASL_ZP);
    mem_.debug_set(0x8001, 0x42);

    auto cyclesLeft = cpu_.execute(20, mem_);
    auto temp = mem_.debug_get(0x0042);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ(temp, 0b00010000);
    mem_.debug_dumpMemory("ASL_ZP");
}

TEST_F(TEST_6502, ASL_ZPX)
{
    cpu_.Reset(mem_, 0x8000);
    cpu_.X = 0x01;
    mem_.debug_set(0x0042, 0b00001000);
    mem_.debug_set(0x8000, CPU::INS_ASL_ZPX);
    mem_.debug_set(0x8001, 0x41);

    auto cyclesLeft = cpu_.execute(20, mem_);
    auto temp = mem_.debug_get(0x0042);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ(temp, 0b00010000);
    mem_.debug_dumpMemory("ASL_ZPX");
}
