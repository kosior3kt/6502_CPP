#include "test.hpp"


////////////////////////////////////////  ASL
TEST_F(TEST_6502, ASL)
{
    cpu_.Reset(mem_, 0x8000);
    cpu_.A = 0b00001000;
    mem_.set(0x8000, CPU::INS_ASL_ACC);

    auto cyclesLeft = cpu_.execute(4, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ(cpu_.A, 0b00010000);
}

TEST_F(TEST_6502, ASL_complicated)
{
    cpu_.Reset(mem_, 0x8000);
    cpu_.A = 0b10000000;
    mem_.set(0x8000, CPU::INS_ASL_ACC);

    auto cyclesLeft = cpu_.execute(4, mem_);

    ///TODO: should the Z flag be set or the N flag???????
    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ(cpu_.A, 0b00000000);
    EXPECT_TRUE(cpu_.CPU::C); // Overflow flag not set
}

TEST_F(TEST_6502, ASL_ZP)
{
    cpu_.Reset(mem_, 0x8000);
    mem_.set(0x0042, 0b00001000);
    mem_.set(0x8000, CPU::INS_ASL_ZP);
    mem_.set(0x8001, 0x42);

    auto cyclesLeft = cpu_.execute(20, mem_);
    auto temp = mem_.at(0x0042);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ(temp, 0b00010000);
}

TEST_F(TEST_6502, ASL_ZPX)
{
    cpu_.Reset(mem_, 0x8000);
    cpu_.X = 0x01;
    mem_.set(0x0042, 0b00001000);
    mem_.set(0x8000, CPU::INS_ASL_ZPX);
    mem_.set(0x8001, 0x41);

    auto cyclesLeft = cpu_.execute(20, mem_);
    auto temp = mem_.at(0x0042);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ(temp, 0b00010000);
}

TEST_F(TEST_6502, ASL_ABS)
{
    cpu_.Reset(mem_, 0x8000);
    mem_.set(0x1042, 0b00001000);
    mem_.set(0x8000, CPU::INS_ASL_ABS);
    mem_.set(0x8001, 0x42);
    mem_.set(0x8002, 0x10);

    auto cyclesLeft = cpu_.execute(20, mem_);
    auto temp = mem_.at(0x1042);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ(temp, 0b00010000);
}

TEST_F(TEST_6502, ASL_ABSX)
{
    cpu_.Reset(mem_, 0x8000);
    cpu_.X = 0x01;
    mem_.set(0x1042, 0b00001000);
    mem_.set(0x8000, CPU::INS_ASL_ABSX);
    mem_.set(0x8001, 0x41);
    mem_.set(0x8002, 0x10);

    auto cyclesLeft = cpu_.execute(20, mem_);
    auto temp = mem_.at(0x1042);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ(temp, 0b00010000);
}

////////////////////////////////////////  LSR

TEST_F(TEST_6502, LSR)
{
    cpu_.Reset(mem_, 0x8000);
    cpu_.A = 0b00001000;
    mem_.set(0x8000, CPU::INS_LSR_ACC);

    auto cyclesLeft = cpu_.execute(4, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ(cpu_.A, 0b00000100);
}


TEST_F(TEST_6502, LSR_complicated)
{
    cpu_.Reset(mem_, 0x8000);
    cpu_.A = 0b00000001;
    mem_.set(0x8000, CPU::INS_LSR_ACC);

    auto cyclesLeft = cpu_.execute(4, mem_);

    ///TODO: should the Z flag be set or the N flag???????
    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ(cpu_.A, 0b00000000);
    EXPECT_TRUE(cpu_.CPU::C); // Overflow flag not set
}

TEST_F(TEST_6502, LSR_ZP)
{
    cpu_.Reset(mem_, 0x8000);
    mem_.set(0x0042, 0b00001000);
    mem_.set(0x8000, CPU::INS_LSR_ZP);
    mem_.set(0x8001, 0x42);

    auto cyclesLeft = cpu_.execute(20, mem_);
    auto temp = mem_.at(0x0042);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ(temp, 0b00000100);
}

TEST_F(TEST_6502, LSR_ZPX)
{
    cpu_.Reset(mem_, 0x8000);
    cpu_.X = 0x01;
    mem_.set(0x0042, 0b00001000);
    mem_.set(0x8000, CPU::INS_LSR_ZPX);
    mem_.set(0x8001, 0x41);

    auto cyclesLeft = cpu_.execute(20, mem_);
    auto temp = mem_.at(0x0042);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ(temp, 0b00000100);
}

TEST_F(TEST_6502, LSR_ABS)
{
    cpu_.Reset(mem_, 0x8000);
    mem_.set(0x1042, 0b00001000);
    mem_.set(0x8000, CPU::INS_LSR_ABS);
    mem_.set(0x8001, 0x42);
    mem_.set(0x8002, 0x10);

    auto cyclesLeft = cpu_.execute(20, mem_);
    auto temp = mem_.at(0x1042);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ(temp, 0b00000100);
}

TEST_F(TEST_6502, LSR_ABSX)
{
    cpu_.Reset(mem_, 0x8000);
    cpu_.X = 0x01;
    mem_.set(0x1042, 0b00001000);
    mem_.set(0x8000, CPU::INS_LSR_ABSX);
    mem_.set(0x8001, 0x41);
    mem_.set(0x8002, 0x10);

    auto cyclesLeft = cpu_.execute(20, mem_);
    auto temp = mem_.at(0x1042);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ(temp, 0b00000100);
}

////////////////////////////////////////  ROL

TEST_F(TEST_6502, ROL)
{
    cpu_.Reset(mem_, 0x8000);
    cpu_.A = 0b00001000;
    mem_.set(0x8000, CPU::INS_ROL_ACC);

    auto cyclesLeft = cpu_.execute(4, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ(cpu_.A, 0b00010000);
}

TEST_F(TEST_6502, ROL_complicated)
{
    cpu_.Reset(mem_, 0x8000);
    cpu_.A = 0b10000000;
    mem_.set(0x8000, CPU::INS_ROL_ACC);

    auto cyclesLeft = cpu_.execute(4, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ(cpu_.A, 0b00000000);
    EXPECT_TRUE(cpu_.CPU::C); // Overflow flag not set
}

TEST_F(TEST_6502, ROL_complicated2)
{
    cpu_.Reset(mem_, 0x8000);
    cpu_.A = 0b10000000;
    cpu_.C = 0x01;
    mem_.set(0x8000, CPU::INS_ROL_ACC);

    auto cyclesLeft = cpu_.execute(4, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ(cpu_.A, 0b00000001);
    EXPECT_TRUE(cpu_.CPU::C); // Overflow flag not set
}

TEST_F(TEST_6502, ROL_ZP)
{
    cpu_.Reset(mem_, 0x8000);
    mem_.set(0x0042, 0b00001000);
    mem_.set(0x8000, CPU::INS_ROL_ZP);
    mem_.set(0x8001, 0x42);

    auto cyclesLeft = cpu_.execute(20, mem_);
    auto temp = mem_.at(0x0042);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ(temp, 0b00010000);
}

TEST_F(TEST_6502, ROL_ZPX)
{
    cpu_.Reset(mem_, 0x8000);
    cpu_.X = 0x01;
    mem_.set(0x0042, 0b00001000);
    mem_.set(0x8000, CPU::INS_ROL_ZPX);
    mem_.set(0x8001, 0x41);

    auto cyclesLeft = cpu_.execute(20, mem_);
    auto temp = mem_.at(0x0042);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ(temp, 0b00010000);
}

TEST_F(TEST_6502, ROL_ABS)
{
    cpu_.Reset(mem_, 0x8000);
    mem_.set(0x1042, 0b00001000);
    mem_.set(0x8000, CPU::INS_ROL_ABS);
    mem_.set(0x8001, 0x42);
    mem_.set(0x8002, 0x10);

    auto cyclesLeft = cpu_.execute(20, mem_);
    auto temp = mem_.at(0x1042);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ(temp, 0b00010000);
}

TEST_F(TEST_6502, ROL_ABSX)
{
    cpu_.Reset(mem_, 0x8000);
    cpu_.X = 0x01;
    mem_.set(0x1042, 0b00001000);
    mem_.set(0x8000, CPU::INS_ROL_ABSX);
    mem_.set(0x8001, 0x41);
    mem_.set(0x8002, 0x10);

    auto cyclesLeft = cpu_.execute(20, mem_);
    auto temp = mem_.at(0x1042);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ(temp, 0b00010000);
}


////////////////////////////////////////  ROR



TEST_F(TEST_6502, ROR)
{
    cpu_.Reset(mem_, 0x8000);
    cpu_.A = 0b00001000;
    mem_.set(0x8000, CPU::INS_ROR_ACC);

    auto cyclesLeft = cpu_.execute(4, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ(cpu_.A, 0b00000100);
}

TEST_F(TEST_6502, ROR_complicated)
{
    cpu_.Reset(mem_, 0x8000);
    cpu_.A = 0b00000001;
    mem_.set(0x8000, CPU::INS_ROR_ACC);

    auto cyclesLeft = cpu_.execute(4, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ(cpu_.A, 0b00000000);
    EXPECT_TRUE(cpu_.CPU::C); // Overflow flag not set
}

TEST_F(TEST_6502, ROR_complicated2)
{
    cpu_.Reset(mem_, 0x8000);
    cpu_.A = 0b00000001;
    cpu_.C = 0x01;
    mem_.set(0x8000, CPU::INS_ROR_ACC);

    auto cyclesLeft = cpu_.execute(4, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ(cpu_.A, 0b10000000);
    EXPECT_TRUE(cpu_.CPU::C); // Overflow flag not set
}

TEST_F(TEST_6502, ROR_ZP)
{
    cpu_.Reset(mem_, 0x8000);
    mem_.set(0x0042, 0b00001000);
    mem_.set(0x8000, CPU::INS_ROR_ZP);
    mem_.set(0x8001, 0x42);

    auto cyclesLeft = cpu_.execute(20, mem_);
    auto temp = mem_.at(0x0042);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ(temp, 0b00000100);
}

TEST_F(TEST_6502, ROR_ZPX)
{
    cpu_.Reset(mem_, 0x8000);
    cpu_.X = 0x01;
    mem_.set(0x0042, 0b00001000);
    mem_.set(0x8000, CPU::INS_ROR_ZPX);
    mem_.set(0x8001, 0x41);

    auto cyclesLeft = cpu_.execute(20, mem_);
    auto temp = mem_.at(0x0042);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ(temp, 0b00000100);
}

TEST_F(TEST_6502, ROR_ABS)
{
    cpu_.Reset(mem_, 0x8000);
    mem_.set(0x1042, 0b00001000);
    mem_.set(0x8000, CPU::INS_ROR_ABS);
    mem_.set(0x8001, 0x42);
    mem_.set(0x8002, 0x10);

    auto cyclesLeft = cpu_.execute(20, mem_);
    auto temp = mem_.at(0x1042);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ(temp, 0b00000100);
}

TEST_F(TEST_6502, ROR_ABSX)
{
    cpu_.Reset(mem_, 0x8000);
    cpu_.X = 0x01;
    mem_.set(0x1042, 0b00001000);
    mem_.set(0x8000, CPU::INS_ROR_ABSX);
    mem_.set(0x8001, 0x41);
    mem_.set(0x8002, 0x10);

    auto cyclesLeft = cpu_.execute(20, mem_);
    auto temp = mem_.at(0x1042);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ(temp, 0b00000100);
}

