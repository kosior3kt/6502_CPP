#include "test.hpp"


TEST_F(TEST_6502, BCC_simple)
{
    cpu_.Reset(mem_, 0x8000);
    cpu_.C = 0;
    mem_.debug_set(0x8000, CPU::INS_BCC);
    mem_.debug_set(0x8001, 0b00001000);
    mem_.debug_set(0x800A, CPU::INS_LDA_IM);
    mem_.debug_set(0x800B, 0x69);

    auto cyclesLeft = cpu_.execute(10, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ(cpu_.A, 0x69);
}

TEST_F(TEST_6502, BCS_simple)
{
    cpu_.Reset(mem_, 0x8000);
    cpu_.C = 1;
    mem_.debug_set(0x8000, CPU::INS_BCS);
    mem_.debug_set(0x8001, 0b00001000);
    mem_.debug_set(0x800A, CPU::INS_LDA_IM);
    mem_.debug_set(0x800B, 0x69);

    auto cyclesLeft = cpu_.execute(10, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ(cpu_.A, 0x69);
}

TEST_F(TEST_6502, BEQ_simple)
{
    cpu_.Reset(mem_, 0x8000);
    cpu_.Z = 1;
    mem_.debug_set(0x8000, CPU::INS_BEQ);
    mem_.debug_set(0x8001, 0b00001000);
    mem_.debug_set(0x800A, CPU::INS_LDA_IM);
    mem_.debug_set(0x800B, 0x69);

    auto cyclesLeft = cpu_.execute(10, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ(cpu_.A, 0x69);
}

TEST_F(TEST_6502, BNE_simple)
{
    cpu_.Reset(mem_, 0x8000);
    cpu_.Z = 0;
    mem_.debug_set(0x8000, CPU::INS_BNE);
    mem_.debug_set(0x8001, 0b00001000);
    mem_.debug_set(0x800A, CPU::INS_LDA_IM);
    mem_.debug_set(0x800B, 0x69);

    auto cyclesLeft = cpu_.execute(10, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ(cpu_.A, 0x69);
}

TEST_F(TEST_6502, BMI_simple)
{
    cpu_.Reset(mem_, 0x8000);
    cpu_.N = 1;
    mem_.debug_set(0x8000, CPU::INS_BMI);
    mem_.debug_set(0x8001, 0b00001000);
    mem_.debug_set(0x800A, CPU::INS_LDA_IM);
    mem_.debug_set(0x800B, 0x69);

    auto cyclesLeft = cpu_.execute(10, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ(cpu_.A, 0x69);
}

TEST_F(TEST_6502, BPL_simple)
{
    cpu_.Reset(mem_, 0x8000);
    cpu_.N = 0;
    mem_.debug_set(0x8000, CPU::INS_BPL);
    mem_.debug_set(0x8001, 0b00001000);
    mem_.debug_set(0x800A, CPU::INS_LDA_IM);
    mem_.debug_set(0x800B, 0x69);

    auto cyclesLeft = cpu_.execute(10, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ(cpu_.A, 0x69);
}


TEST_F(TEST_6502, BVC_simple)
{
    cpu_.Reset(mem_, 0x8000);
    cpu_.V = 0;
    mem_.debug_set(0x8000, CPU::INS_BVC);
    mem_.debug_set(0x8001, 0b00001000);
    mem_.debug_set(0x800A, CPU::INS_LDA_IM);
    mem_.debug_set(0x800B, 0x69);

    auto cyclesLeft = cpu_.execute(10, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ(cpu_.A, 0x69);
}

TEST_F(TEST_6502, BVS_simple)
{
    cpu_.Reset(mem_, 0x8000);
    cpu_.V = 1;
    mem_.debug_set(0x8000, CPU::INS_BVS);
    mem_.debug_set(0x8001, 0b00001000);
    mem_.debug_set(0x800A, CPU::INS_LDA_IM);
    mem_.debug_set(0x800B, 0x69);

    auto cyclesLeft = cpu_.execute(10, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ(cpu_.A, 0x69);
}
