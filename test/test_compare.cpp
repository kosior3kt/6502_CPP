#include "test.hpp"

#define SIGNED_BYTE(x) ((Byte)x)

TEST_F(TEST_6502, CMP_Trivial)
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.A = 0x10;
    mem_.debug_set(0xFF00, CPU::INS_CMP_IM); ///immediete
    mem_.debug_set(0xFF01, 0x10); // Zero page address
    auto cyclesLeft = cpu_.execute(5, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ((uint8_t)cpu_.A, 0x10);
    EXPECT_EQ(cpu_.C, 1);
    EXPECT_EQ(cpu_.N, 0);
    EXPECT_EQ(cpu_.V, 0);
    EXPECT_EQ(cpu_.Z, 1);
}

TEST_F(TEST_6502, CMP_Immediate_CanCompareTwoIdenticalValues)
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.A = 0x10;
    mem_.debug_set(0xFF00, CPU::INS_CMP_IM);
    mem_.debug_set(0xFF01, 0x10);
    auto cyclesLeft = cpu_.execute(2, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ((uint8_t)cpu_.A, 0x10);
    EXPECT_EQ(cpu_.C, 1);
    EXPECT_EQ(cpu_.N, 0);
    EXPECT_EQ(cpu_.Z, 1);
}

TEST_F(TEST_6502, CMP_Immediate_CanCompareALargePositiveToASmallPositive)
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.A = 0x50;
    mem_.debug_set(0xFF00, CPU::INS_CMP_IM);
    mem_.debug_set(0xFF01, 0x10);
    auto cyclesLeft = cpu_.execute(2, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ((uint8_t)cpu_.A, 0x50);
    EXPECT_EQ(cpu_.C, 1);
    EXPECT_EQ(cpu_.N, 0);
    EXPECT_EQ(cpu_.Z, 0);
}

TEST_F(TEST_6502, CMPImmediateCanCompareTwoIdenticalValues)
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.A = 26;
    mem_.debug_set(0xFF00, CPU::INS_CMP_IM);
    mem_.debug_set(0xFF01, 26);
    auto cyclesLeft = cpu_.execute(2, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ(cpu_.A, 26);
    EXPECT_EQ(cpu_.C, 1);
    EXPECT_EQ(cpu_.N, 0);
    EXPECT_EQ(cpu_.Z, 1);
}

TEST_F(TEST_6502, CMPImmediateCanCompareALargePositiveToASmallPositive)
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.A = 48;
    mem_.debug_set(0xFF00, CPU::INS_CMP_IM);
    mem_.debug_set(0xFF01, 26);
    auto cyclesLeft = cpu_.execute(2, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ(cpu_.A, 48);
    EXPECT_EQ(cpu_.C, 1);
    EXPECT_EQ(cpu_.N, 0);
    EXPECT_EQ(cpu_.Z, 0);
}

TEST_F(TEST_6502, CMPImmediateCanCompareANegativeNumberToAPositive)
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.A = SIGNED_BYTE(-2); // Negative number
    mem_.debug_set(0xFF00, CPU::INS_CMP_IM);
    mem_.debug_set(0xFF01, SIGNED_BYTE(26));
    auto cyclesLeft = cpu_.execute(2, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ(cpu_.A, SIGNED_BYTE(-2));
    EXPECT_EQ(cpu_.C, 1);
    EXPECT_EQ(cpu_.N, 1);
    EXPECT_EQ(cpu_.Z, 0);
}

TEST_F(TEST_6502, CMPImmediateCanCompareTwoValuesThatResultInANegativeFlagSet)
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.A = 8;
    mem_.debug_set(0xFF00, CPU::INS_CMP_IM);
    mem_.debug_set(0xFF01, 26);
    auto cyclesLeft = cpu_.execute(2, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ(cpu_.A, 8);
    EXPECT_EQ(cpu_.C, 0);
    EXPECT_EQ(cpu_.N, 1);
    EXPECT_EQ(cpu_.Z, 0);
}

//-- Zero Page

TEST_F(TEST_6502, CMPZeroPageCanCompareTwoIdenticalValues)
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.A = 26;
    mem_.debug_set(0xFF00, CPU::INS_CMP_ZP);
    mem_.debug_set(0xFF01, 0x42);
    mem_.debug_set(0x0042, 26);
    auto cyclesLeft = cpu_.execute(3, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ(cpu_.A, 26);
    EXPECT_EQ(cpu_.C, 1);
    EXPECT_EQ(cpu_.N, 0);
    EXPECT_EQ(cpu_.Z, 1);
}

TEST_F(TEST_6502, CMPZeroPageCanCompareALargePositiveToASmallPositive)
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.A = 48;
    mem_.debug_set(0xFF00, CPU::INS_CMP_ZP);
    mem_.debug_set(0xFF01, 0x42);
    mem_.debug_set(0x0042, 26);
    auto cyclesLeft = cpu_.execute(3, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ(cpu_.A, 48);
    EXPECT_EQ(cpu_.C, 1);
    EXPECT_EQ(cpu_.N, 0);
    EXPECT_EQ(cpu_.Z, 0);
}

TEST_F(TEST_6502, CMPZeroPageCanCompareANegativeNumberToAPositive)
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.A = SIGNED_BYTE(-10); // Negative number
    mem_.debug_set(0xFF00, CPU::INS_CMP_ZP);
    mem_.debug_set(0xFF01, 0x42);
    mem_.debug_set(0x0042, SIGNED_BYTE(26));
    auto cyclesLeft = cpu_.execute(3, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ(cpu_.A, SIGNED_BYTE(-10));
    EXPECT_EQ(cpu_.C, 1);
    EXPECT_EQ(cpu_.N, 1);
    EXPECT_EQ(cpu_.Z, 0);
}

TEST_F(TEST_6502, CMPZeroPageCanCompareTwoValuesThatResultInANegativeFlagSet)
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.A = 8;
    mem_.debug_set(0xFF00, CPU::INS_CMP_ZP);
    mem_.debug_set(0xFF01, 0x42);
    mem_.debug_set(0x0042, 26);
    auto cyclesLeft = cpu_.execute(3, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ(cpu_.A, 8);
    EXPECT_EQ(cpu_.C, 0);
    EXPECT_EQ(cpu_.N, 1);
    EXPECT_EQ(cpu_.Z, 0);
}

TEST_F(TEST_6502, CMPImmediate_CompareTwoIdenticalValues)
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.A = 26;
    mem_.debug_set(0xFF00, CPU::INS_CMP_IM);
    mem_.debug_set(0xFF01, 26);
    auto cyclesLeft = cpu_.execute(2, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ(cpu_.A, 26);
    EXPECT_EQ(cpu_.C, 1);
    EXPECT_EQ(cpu_.N, 0);
    EXPECT_EQ(cpu_.Z, 1);
}

TEST_F(TEST_6502, CMPImmediate_CompareALargePositiveToASmallPositive)
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.A = 48;
    mem_.debug_set(0xFF00, CPU::INS_CMP_IM);
    mem_.debug_set(0xFF01, 26);
    auto cyclesLeft = cpu_.execute(2, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ(cpu_.A, 48);
    EXPECT_EQ(cpu_.C, 1);
    EXPECT_EQ(cpu_.N, 0);
    EXPECT_EQ(cpu_.Z, 0);
}

TEST_F(TEST_6502, CMPImmediate_CompareANegativeNumberToAPositive)
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.A = SIGNED_BYTE(-36);
    mem_.debug_set(0xFF00, CPU::INS_CMP_IM);
    mem_.debug_set(0xFF01, SIGNED_BYTE(26));
    auto cyclesLeft = cpu_.execute(2, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ(cpu_.A, SIGNED_BYTE(-36));
    EXPECT_EQ(cpu_.C, 1);
    EXPECT_EQ(cpu_.N, 1);
    EXPECT_EQ(cpu_.Z, 0);
}

TEST_F(TEST_6502, CMPImmediate_CompareTwoValuesThatResultInANegativeFlagSet)
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.A = 8;
    mem_.debug_set(0xFF00, CPU::INS_CMP_IM);
    mem_.debug_set(0xFF01, 26);
    auto cyclesLeft = cpu_.execute(2, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ(cpu_.A, 8);
    EXPECT_EQ(cpu_.C, 0);
    EXPECT_EQ(cpu_.N, 1);
    EXPECT_EQ(cpu_.Z, 0);
}

TEST_F(TEST_6502, CMP_ZeroPage_CanCompareTwoIdenticalValues)
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.A = SIGNED_BYTE(26);
    mem_.debug_set(0xFF00, CPU::INS_CMP_ZP); // Zero Page
    mem_.debug_set(0xFF01, 0x42);
    mem_.debug_set(0x0042, SIGNED_BYTE(26)); 
    auto cyclesLeft = cpu_.execute(5, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ((uint8_t)cpu_.A, SIGNED_BYTE(26));
    EXPECT_EQ(cpu_.C, 1);
    EXPECT_EQ(cpu_.N, 0);
    EXPECT_EQ(cpu_.Z, 1);
}

TEST_F(TEST_6502, CMP_ZeroPage_CanCompareALargePositiveToASmallPositive)
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.A = SIGNED_BYTE(48);
    mem_.debug_set(0xFF00, CPU::INS_CMP_ZP); // Zero Page
    mem_.debug_set(0xFF01, 0x42);
    mem_.debug_set(0x0042, SIGNED_BYTE(26)); 
    auto cyclesLeft = cpu_.execute(5, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ((uint8_t)cpu_.A, SIGNED_BYTE(48));
    EXPECT_EQ(cpu_.C, 1);
    EXPECT_EQ(cpu_.N, 0);
    EXPECT_EQ(cpu_.Z, 0);
}

TEST_F(TEST_6502, CMP_ZeroPage_CanCompareANegativeNumberToAPositive)
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.A = SIGNED_BYTE(-10);
    mem_.debug_set(0xFF00, CPU::INS_CMP_ZP); // Zero Page
    mem_.debug_set(0xFF01, 0x42);
    mem_.debug_set(0x0042, SIGNED_BYTE(10)); 
    auto cyclesLeft = cpu_.execute(5, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ((uint8_t)cpu_.A, SIGNED_BYTE(-10));
    EXPECT_EQ(cpu_.C, 1);
    EXPECT_EQ(cpu_.N, 1);
    EXPECT_EQ(cpu_.Z, 0);
}

TEST_F(TEST_6502, CMP_ZeroPage_CanCompareTwoValuesThatResultInANegativeFlagSet)
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.A = SIGNED_BYTE(8);
    mem_.debug_set(0xFF00, CPU::INS_CMP_ZP); // Zero Page
    mem_.debug_set(0xFF01, 0x42);
    mem_.debug_set(0x0042, SIGNED_BYTE(26)); 
    auto cyclesLeft = cpu_.execute(5, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ((uint8_t)cpu_.A, SIGNED_BYTE(8));
    EXPECT_EQ(cpu_.C, 0);
    EXPECT_EQ(cpu_.N, 1);
    EXPECT_EQ(cpu_.Z, 0);
}

//-- Zero Page X

TEST_F(TEST_6502, CMP_ZeroPageX_CanCompareTwoIdenticalValues)
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.A = SIGNED_BYTE(26);
    cpu_.X = SIGNED_BYTE(4);
    mem_.debug_set(0xFF00, CPU::INS_CMP_ZPX); // Zero Page X
    mem_.debug_set(0xFF01, 0x42);
    mem_.debug_set(0x0042 + 0x4, SIGNED_BYTE(26)); 
    auto cyclesLeft = cpu_.execute(5, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ((uint8_t)cpu_.A, SIGNED_BYTE(26));
    EXPECT_EQ(cpu_.C, 1);
    EXPECT_EQ(cpu_.N, 0);
    EXPECT_EQ(cpu_.Z, 1);
}

TEST_F(TEST_6502, CMP_ZeroPageX_CanCompareALargePositiveToASmallPositive)
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.A = SIGNED_BYTE(48);
    cpu_.X = SIGNED_BYTE(4);
    mem_.debug_set(0xFF00, CPU::INS_CMP_ZPX); // Zero Page X
    mem_.debug_set(0xFF01, 0x42);
    mem_.debug_set(0x0042 + 0x4, SIGNED_BYTE(26)); 
    auto cyclesLeft = cpu_.execute(5, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ((uint8_t)cpu_.A, SIGNED_BYTE(48));
    EXPECT_EQ(cpu_.C, 1);
    EXPECT_EQ(cpu_.N, 0);
    EXPECT_EQ(cpu_.Z, 0);
}

TEST_F(TEST_6502, CMP_ZeroPageX_CanCompareANegativeNumberToAPositive)
{

    cpu_.Reset(mem_, 0xFF00);
    cpu_.A = SIGNED_BYTE(-36);
    cpu_.X = 0x01;
    mem_.debug_set(0xFF00, CPU::INS_CMP_ZPX);
    mem_.debug_set(0xFF01, 0x68);
    mem_.debug_set(0x0069, SIGNED_BYTE(10)); ///zero page place

    auto cyclesLeft = cpu_.execute(4, mem_);


    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ(cpu_.A, SIGNED_BYTE(-36));
    EXPECT_EQ(cpu_.C, 1);
    EXPECT_EQ(cpu_.N, 1);
    EXPECT_EQ(cpu_.Z, 0);


}

TEST_F(TEST_6502, CMP_ZeroPageX_CanCompareTwoValuesThatResultInANegativeFlagSet)
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.A = SIGNED_BYTE(8);
    cpu_.X = SIGNED_BYTE(4);
    mem_.debug_set(0xFF00, CPU::INS_CMP_ZPX); // Zero Page X
    mem_.debug_set(0xFF01, 0x42);
    mem_.debug_set(0x0042 + 0x4, SIGNED_BYTE(26)); 
    auto cyclesLeft = cpu_.execute(5, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ((uint8_t)cpu_.A, SIGNED_BYTE(8));
    EXPECT_EQ(cpu_.C, 0);
    EXPECT_EQ(cpu_.N, 1);
    EXPECT_EQ(cpu_.Z, 0);
}

//-- Absolute

TEST_F(TEST_6502, CMP_Absolute_CanCompareTwoIdenticalValues)
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.A = SIGNED_BYTE(26);
    mem_.debug_set(0xFF00, CPU::INS_CMP_ABS); // Absolute
    mem_.debug_set(0xFF01, 0x00);
    mem_.debug_set(0xFF02, 0x80);
    mem_.debug_set(0x8000, SIGNED_BYTE(26)); 
    auto cyclesLeft = cpu_.execute(5, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ((uint8_t)cpu_.A, SIGNED_BYTE(26));
    EXPECT_EQ(cpu_.C, 1);
    EXPECT_EQ(cpu_.N, 0);
    EXPECT_EQ(cpu_.Z, 1);
}

TEST_F(TEST_6502, CMP_Absolute_CanCompareALargePositiveToASmallPositive)
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.A = SIGNED_BYTE(48);
    mem_.debug_set(0xFF00, CPU::INS_CMP_ABS); // Absolute
    mem_.debug_set(0xFF01, 0x00);
    mem_.debug_set(0xFF02, 0x80);
    mem_.debug_set(0x8000, SIGNED_BYTE(26)); 
    auto cyclesLeft = cpu_.execute(5, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ((uint8_t)cpu_.A, SIGNED_BYTE(48));
    EXPECT_EQ(cpu_.C, 1);
    EXPECT_EQ(cpu_.N, 0);
    EXPECT_EQ(cpu_.Z, 0);
}

TEST_F(TEST_6502, CMP_Absolute_CanCompareANegativeNumberToAPositive)
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.A = SIGNED_BYTE(-10);
    mem_.debug_set(0xFF00, CPU::INS_CMP_ABS); // Absolute
    mem_.debug_set(0xFF01, 0x00);
    mem_.debug_set(0xFF02, 0x80);
    mem_.debug_set(0x8000, SIGNED_BYTE(10)); 
    auto cyclesLeft = cpu_.execute(5, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ((uint8_t)cpu_.A, SIGNED_BYTE(-10));
    EXPECT_EQ(cpu_.C, 1);
    EXPECT_EQ(cpu_.N, 1);
    EXPECT_EQ(cpu_.Z, 0);
}

TEST_F(TEST_6502, CMP_Absolute_CanCompareTwoValuesThatResultInANegativeFlagSet)
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.A = SIGNED_BYTE(8);
    mem_.debug_set(0xFF00, CPU::INS_CMP_ABS); // Absolute
    mem_.debug_set(0xFF01, 0x00);
    mem_.debug_set(0xFF02, 0x80);
    mem_.debug_set(0x8000, SIGNED_BYTE(26)); 
    auto cyclesLeft = cpu_.execute(5, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ((uint8_t)cpu_.A, SIGNED_BYTE(8));
    EXPECT_EQ(cpu_.C, 0);
    EXPECT_EQ(cpu_.N, 1);
    EXPECT_EQ(cpu_.Z, 0);
}

//-- Absolute X

TEST_F(TEST_6502, CMP_AbsoluteX_CanCompareTwoIdenticalValues)
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.A = SIGNED_BYTE(26);
    cpu_.X = SIGNED_BYTE(4);
    mem_.debug_set(0xFF00, CPU::INS_CMP_ABSX); // Absolute X
    mem_.debug_set(0xFF01, 0x00);
    mem_.debug_set(0xFF02, 0x80);
    mem_.debug_set(0x8000 + 0x4, SIGNED_BYTE(26)); 
    auto cyclesLeft = cpu_.execute(5, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ((uint8_t)cpu_.A, SIGNED_BYTE(26));
    EXPECT_EQ(cpu_.C, 1);
    EXPECT_EQ(cpu_.N, 0);
    EXPECT_EQ(cpu_.Z, 1);
}

TEST_F(TEST_6502, CMP_AbsoluteX_CanCompareALargePositiveToASmallPositive)
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.A = SIGNED_BYTE(48);
    cpu_.X = SIGNED_BYTE(4);
    mem_.debug_set(0xFF00, CPU::INS_CMP_ABSX); // Absolute X
    mem_.debug_set(0xFF01, 0x00);
    mem_.debug_set(0xFF02, 0x80);
    mem_.debug_set(0x8000 + 0x4, SIGNED_BYTE(26)); 
    auto cyclesLeft = cpu_.execute(5, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ((uint8_t)cpu_.A, SIGNED_BYTE(48));
    EXPECT_EQ(cpu_.C, 1);
    EXPECT_EQ(cpu_.N, 0);
    EXPECT_EQ(cpu_.Z, 0);
}

TEST_F(TEST_6502, CMP_AbsoluteX_CanCompareANegativeNumberToAPositive)
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.A = SIGNED_BYTE(-10);
    cpu_.X = SIGNED_BYTE(4);
    mem_.debug_set(0xFF00, CPU::INS_CMP_ABSX); // Absolute X
    mem_.debug_set(0xFF01, 0x00);
    mem_.debug_set(0xFF02, 0x80);
    mem_.debug_set(0x8000 + 0x4, SIGNED_BYTE(10)); 
    auto cyclesLeft = cpu_.execute(5, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ((uint8_t)cpu_.A, SIGNED_BYTE(-10));
    EXPECT_EQ(cpu_.C, 1);
    EXPECT_EQ(cpu_.N, 1);
    EXPECT_EQ(cpu_.Z, 0);
}

TEST_F(TEST_6502, CMP_AbsoluteX_CanCompareTwoValuesThatResultInANegativeFlagSet)
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.A = SIGNED_BYTE(8);
    cpu_.X = SIGNED_BYTE(4);
    mem_.debug_set(0xFF00, CPU::INS_CMP_ABSX); // Absolute X
    mem_.debug_set(0xFF01, 0x00);
    mem_.debug_set(0xFF02, 0x80);
    mem_.debug_set(0x8000 + 0x4, SIGNED_BYTE(26)); 
    auto cyclesLeft = cpu_.execute(5, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ((uint8_t)cpu_.A, SIGNED_BYTE(8));
    EXPECT_EQ(cpu_.C, 0);
    EXPECT_EQ(cpu_.N, 1);
    EXPECT_EQ(cpu_.Z, 0);
}

//-- Absolute Y

TEST_F(TEST_6502, CMP_AbsoluteY_CanCompareTwoIdenticalValues)
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.A = SIGNED_BYTE(26);
    cpu_.Y = SIGNED_BYTE(4);
    mem_.debug_set(0xFF00, CPU::INS_CMP_ABSY); // Absolute Y
    mem_.debug_set(0xFF01, 0x00);
    mem_.debug_set(0xFF02, 0x80);
    mem_.debug_set(0x8000 + 0x4, SIGNED_BYTE(26)); 
    auto cyclesLeft = cpu_.execute(5, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ((uint8_t)cpu_.A, SIGNED_BYTE(26));
    EXPECT_EQ(cpu_.C, 1);
    EXPECT_EQ(cpu_.N, 0);
    EXPECT_EQ(cpu_.Z, 1);
}

TEST_F(TEST_6502, CMP_AbsoluteY_CanCompareALargePositiveToASmallPositive)
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.A = SIGNED_BYTE(48);
    cpu_.Y = SIGNED_BYTE(4);
    mem_.debug_set(0xFF00, CPU::INS_CMP_ABSY); // Absolute Y
    mem_.debug_set(0xFF01, 0x00);
    mem_.debug_set(0xFF02, 0x80);
    mem_.debug_set(0x8000 + 0x4, SIGNED_BYTE(26)); 
    auto cyclesLeft = cpu_.execute(5, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ((uint8_t)cpu_.A, SIGNED_BYTE(48));
    EXPECT_EQ(cpu_.C, 1);
    EXPECT_EQ(cpu_.N, 0);
    EXPECT_EQ(cpu_.Z, 0);
}

TEST_F(TEST_6502, CMP_AbsoluteY_CanCompareANegativeNumberToAPositive)
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.A = SIGNED_BYTE(-10);
    cpu_.Y = SIGNED_BYTE(4);
    mem_.debug_set(0xFF00, CPU::INS_CMP_ABSY); // Absolute Y
    mem_.debug_set(0xFF01, 0x00);
    mem_.debug_set(0xFF02, 0x80);
    mem_.debug_set(0x8000 + 0x4, SIGNED_BYTE(10)); 
    auto cyclesLeft = cpu_.execute(5, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ((uint8_t)cpu_.A, SIGNED_BYTE(-10));
    EXPECT_EQ(cpu_.C, 1);
    EXPECT_EQ(cpu_.N, 1);
    EXPECT_EQ(cpu_.Z, 0);
}

TEST_F(TEST_6502, CMP_AbsoluteY_CanCompareTwoValuesThatResultInANegativeFlagSet)
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.A = SIGNED_BYTE(8);
    cpu_.Y = SIGNED_BYTE(4);
    mem_.debug_set(0xFF00, CPU::INS_CMP_ABSY); // Absolute Y
    mem_.debug_set(0xFF01, 0x00);
    mem_.debug_set(0xFF02, 0x80);
    mem_.debug_set(0x8000 + 0x4, SIGNED_BYTE(26)); 
    auto cyclesLeft = cpu_.execute(5, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ((uint8_t)cpu_.A, SIGNED_BYTE(8));
    EXPECT_EQ(cpu_.C, 0);
    EXPECT_EQ(cpu_.N, 1);
    EXPECT_EQ(cpu_.Z, 0);
}




////////////////////////////////////CMX

TEST_F(TEST_6502, CPX_Trivial)
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.X = 0x10;
    mem_.debug_set(0xFF00, CPU::INS_CPX_IM); ///immediete
    mem_.debug_set(0xFF01, 0x10); // Zero page address
    auto cyclesLeft = cpu_.execute(5, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ((uint8_t)cpu_.X, 0x10);
    EXPECT_EQ(cpu_.C, 1);
    EXPECT_EQ(cpu_.N, 0);
    EXPECT_EQ(cpu_.V, 0);
    EXPECT_EQ(cpu_.Z, 1);
}

TEST_F(TEST_6502, CPX_Immediate_CanCompareTwoIdenticalValues)
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.X = 0x10;
    mem_.debug_set(0xFF00, CPU::INS_CPX_IM);
    mem_.debug_set(0xFF01, 0x10);
    auto cyclesLeft = cpu_.execute(2, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ((uint8_t)cpu_.X, 0x10);
    EXPECT_EQ(cpu_.C, 1);
    EXPECT_EQ(cpu_.N, 0);
    EXPECT_EQ(cpu_.Z, 1);
}

TEST_F(TEST_6502, CPX_Immediate_CanComparaXLargePositiveToASmallPositive)
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.X = 0x50;
    mem_.debug_set(0xFF00, CPU::INS_CPX_IM);
    mem_.debug_set(0xFF01, 0x10);
    auto cyclesLeft = cpu_.execute(2, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ((uint8_t)cpu_.X, 0x50);
    EXPECT_EQ(cpu_.C, 1);
    EXPECT_EQ(cpu_.N, 0);
    EXPECT_EQ(cpu_.Z, 0);
}

TEST_F(TEST_6502, CPXImmediateCanCompareTwoIdenticalValues)
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.X = 26;
    mem_.debug_set(0xFF00, CPU::INS_CPX_IM);
    mem_.debug_set(0xFF01, 26);
    auto cyclesLeft = cpu_.execute(2, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ(cpu_.X, 26);
    EXPECT_EQ(cpu_.C, 1);
    EXPECT_EQ(cpu_.N, 0);
    EXPECT_EQ(cpu_.Z, 1);
}

TEST_F(TEST_6502, CPXImmediateCanCompareXLargePositiveToASmallPositive)
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.X = 48;
    mem_.debug_set(0xFF00, CPU::INS_CPX_IM);
    mem_.debug_set(0xFF01, 26);
    auto cyclesLeft = cpu_.execute(2, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ(cpu_.X, 48);
    EXPECT_EQ(cpu_.C, 1);
    EXPECT_EQ(cpu_.N, 0);
    EXPECT_EQ(cpu_.Z, 0);
}

TEST_F(TEST_6502, CPXImmediateCanCompareXNegativeNumberToAPositive)
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.X = SIGNED_BYTE(-2); // Negative number
    mem_.debug_set(0xFF00, CPU::INS_CPX_IM);
    mem_.debug_set(0xFF01, SIGNED_BYTE(26));
    auto cyclesLeft = cpu_.execute(2, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ(cpu_.X, SIGNED_BYTE(-2));
    EXPECT_EQ(cpu_.C, 1);
    EXPECT_EQ(cpu_.N, 1);
    EXPECT_EQ(cpu_.Z, 0);
}

TEST_F(TEST_6502, CPXImmediateCanCompareTwoValuesThatResultAINegativeFlagSet)
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.X = 8;
    mem_.debug_set(0xFF00, CPU::INS_CPX_IM);
    mem_.debug_set(0xFF01, 26);
    auto cyclesLeft = cpu_.execute(2, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ(cpu_.X, 8);
    EXPECT_EQ(cpu_.C, 0);
    EXPECT_EQ(cpu_.N, 1);
    EXPECT_EQ(cpu_.Z, 0);
}

//-- Zero Page


TEST_F(TEST_6502, CPXZeroPageCanCompareTwoIdenticalValues)
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.X = 26;
    mem_.debug_set(0xFF00, CPU::INS_CPX_ZP);
    mem_.debug_set(0xFF01, 0x42);
    mem_.debug_set(0x0042, 26);
    auto cyclesLeft = cpu_.execute(3, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ(cpu_.X, 26);
    EXPECT_EQ(cpu_.C, 1);
    EXPECT_EQ(cpu_.N, 0);
    EXPECT_EQ(cpu_.Z, 1);
}

TEST_F(TEST_6502, CPXZeroPageCanCompareALargePositiveToASmallPositive)
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.X = 48;
    mem_.debug_set(0xFF00, CPU::INS_CPX_ZP);
    mem_.debug_set(0xFF01, 0x42);
    mem_.debug_set(0x0042, 26);
    auto cyclesLeft = cpu_.execute(3, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ(cpu_.X, 48);
    EXPECT_EQ(cpu_.C, 1);
    EXPECT_EQ(cpu_.N, 0);
    EXPECT_EQ(cpu_.Z, 0);
}

TEST_F(TEST_6502, CPXZeroPageCanCompareANegativeNumberToAPositive)
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.X = SIGNED_BYTE(-10); // Negative number
    mem_.debug_set(0xFF00, CPU::INS_CPX_ZP);
    mem_.debug_set(0xFF01, 0x42);
    mem_.debug_set(0x0042, SIGNED_BYTE(26));
    auto cyclesLeft = cpu_.execute(3, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ(cpu_.X, SIGNED_BYTE(-10));
    EXPECT_EQ(cpu_.C, 1);
    EXPECT_EQ(cpu_.N, 1);
    EXPECT_EQ(cpu_.Z, 0);
}

TEST_F(TEST_6502, CPXZeroPageCanCompareTwoValuesThatResultInANegativeFlagSet)
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.X = 8;
    mem_.debug_set(0xFF00, CPU::INS_CPX_ZP);
    mem_.debug_set(0xFF01, 0x42);
    mem_.debug_set(0x0042, 26);
    auto cyclesLeft = cpu_.execute(3, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ(cpu_.X, 8);
    EXPECT_EQ(cpu_.C, 0);
    EXPECT_EQ(cpu_.N, 1);
    EXPECT_EQ(cpu_.Z, 0);
}

TEST_F(TEST_6502, CPXImmediate_CompareTwoIdenticalValues)
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.X = 26;
    mem_.debug_set(0xFF00, CPU::INS_CPX_IM);
    mem_.debug_set(0xFF01, 26);
    auto cyclesLeft = cpu_.execute(2, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ(cpu_.X, 26);
    EXPECT_EQ(cpu_.C, 1);
    EXPECT_EQ(cpu_.N, 0);
    EXPECT_EQ(cpu_.Z, 1);
}

TEST_F(TEST_6502, CPXImmediate_CompareALargePositiveToASmallPositive)
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.X = 48;
    mem_.debug_set(0xFF00, CPU::INS_CPX_IM);
    mem_.debug_set(0xFF01, 26);
    auto cyclesLeft = cpu_.execute(2, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ(cpu_.X, 48);
    EXPECT_EQ(cpu_.C, 1);
    EXPECT_EQ(cpu_.N, 0);
    EXPECT_EQ(cpu_.Z, 0);
}

TEST_F(TEST_6502, CPXImmediate_CompareANegativeNumberToAPositive)
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.X = SIGNED_BYTE(-36);
    mem_.debug_set(0xFF00, CPU::INS_CPX_IM);
    mem_.debug_set(0xFF01, SIGNED_BYTE(26));
    auto cyclesLeft = cpu_.execute(2, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ(cpu_.X, SIGNED_BYTE(-36));
    EXPECT_EQ(cpu_.C, 1);
    EXPECT_EQ(cpu_.N, 1);
    EXPECT_EQ(cpu_.Z, 0);
}

TEST_F(TEST_6502, CPXImmediate_CompareTwoValuesThatResultInANegativeFlagSet)
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.X = 8;
    mem_.debug_set(0xFF00, CPU::INS_CPX_IM);
    mem_.debug_set(0xFF01, 26);
    auto cyclesLeft = cpu_.execute(2, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ(cpu_.X, 8);
    EXPECT_EQ(cpu_.C, 0);
    EXPECT_EQ(cpu_.N, 1);
    EXPECT_EQ(cpu_.Z, 0);
}

TEST_F(TEST_6502, CPX_ZeroPage_CanCompareTwoIdenticalValues)
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.X = SIGNED_BYTE(26);
    mem_.debug_set(0xFF00, CPU::INS_CPX_ZP); // Zero Page
    mem_.debug_set(0xFF01, 0x42);
    mem_.debug_set(0x0042, SIGNED_BYTE(26)); 
    auto cyclesLeft = cpu_.execute(5, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ((uint8_t)cpu_.X, SIGNED_BYTE(26));
    EXPECT_EQ(cpu_.C, 1);
    EXPECT_EQ(cpu_.N, 0);
    EXPECT_EQ(cpu_.Z, 1);
}

TEST_F(TEST_6502, CPX_ZeroPage_CanCompareALargePositiveToASmallPositive)
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.X = SIGNED_BYTE(48);
    mem_.debug_set(0xFF00, CPU::INS_CPX_ZP); // Zero Page
    mem_.debug_set(0xFF01, 0x42);
    mem_.debug_set(0x0042, SIGNED_BYTE(26)); 
    auto cyclesLeft = cpu_.execute(5, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ((uint8_t)cpu_.X, SIGNED_BYTE(48));
    EXPECT_EQ(cpu_.C, 1);
    EXPECT_EQ(cpu_.N, 0);
    EXPECT_EQ(cpu_.Z, 0);
}

TEST_F(TEST_6502, CPX_ZeroPage_CanCompareANegativeNumberToAPositive)
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.X = SIGNED_BYTE(-10);
    mem_.debug_set(0xFF00, CPU::INS_CPX_ZP); // Zero Page
    mem_.debug_set(0xFF01, 0x42);
    mem_.debug_set(0x0042, SIGNED_BYTE(10)); 
    auto cyclesLeft = cpu_.execute(5, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ((uint8_t)cpu_.X, SIGNED_BYTE(-10));
    EXPECT_EQ(cpu_.C, 1);
    EXPECT_EQ(cpu_.N, 1);
    EXPECT_EQ(cpu_.Z, 0);
}

TEST_F(TEST_6502, CPX_ZeroPage_CanCompareTwoValuesThatResultInANegativeFlagSet)
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.X = SIGNED_BYTE(8);
    mem_.debug_set(0xFF00, CPU::INS_CPX_ZP); // Zero Page
    mem_.debug_set(0xFF01, 0x42);
    mem_.debug_set(0x0042, SIGNED_BYTE(26)); 
    auto cyclesLeft = cpu_.execute(5, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ((uint8_t)cpu_.X, SIGNED_BYTE(8));
    EXPECT_EQ(cpu_.C, 0);
    EXPECT_EQ(cpu_.N, 1);
    EXPECT_EQ(cpu_.Z, 0);
}



TEST_F(TEST_6502, CPX_Absolute_CanCompareTwoIdenticalValues)
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.X = SIGNED_BYTE(26);
    mem_.debug_set(0xFF00, CPU::INS_CPX_ABS); // Absolute
    mem_.debug_set(0xFF01, 0x00);
    mem_.debug_set(0xFF02, 0x80);
    mem_.debug_set(0x8000, SIGNED_BYTE(26)); 
    auto cyclesLeft = cpu_.execute(5, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ((uint8_t)cpu_.X, SIGNED_BYTE(26));
    EXPECT_EQ(cpu_.C, 1);
    EXPECT_EQ(cpu_.N, 0);
    EXPECT_EQ(cpu_.Z, 1);
}

TEST_F(TEST_6502, CPX_Absolute_CanCompareALargePositiveToASmallPositive)
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.X = SIGNED_BYTE(48);
    mem_.debug_set(0xFF00, CPU::INS_CPX_ABS); // Absolute
    mem_.debug_set(0xFF01, 0x00);
    mem_.debug_set(0xFF02, 0x80);
    mem_.debug_set(0x8000, SIGNED_BYTE(26)); 
    auto cyclesLeft = cpu_.execute(5, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ((uint8_t)cpu_.X, SIGNED_BYTE(48));
    EXPECT_EQ(cpu_.C, 1);
    EXPECT_EQ(cpu_.N, 0);
    EXPECT_EQ(cpu_.Z, 0);
}

TEST_F(TEST_6502, CPX_Absolute_CanCompareANegativeNumberToAPositive)
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.X = SIGNED_BYTE(-10);
    mem_.debug_set(0xFF00, CPU::INS_CPX_ABS); // Absolute
    mem_.debug_set(0xFF01, 0x00);
    mem_.debug_set(0xFF02, 0x80);
    mem_.debug_set(0x8000, SIGNED_BYTE(10)); 
    auto cyclesLeft = cpu_.execute(5, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ((uint8_t)cpu_.X, SIGNED_BYTE(-10));
    EXPECT_EQ(cpu_.C, 1);
    EXPECT_EQ(cpu_.N, 1);
    EXPECT_EQ(cpu_.Z, 0);
}

TEST_F(TEST_6502, CPX_Absolute_CanCompareTwoValuesThatResultInANegativeFlagSet)
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.X = SIGNED_BYTE(8);
    mem_.debug_set(0xFF00, CPU::INS_CPX_ABS); // Absolute
    mem_.debug_set(0xFF01, 0x00);
    mem_.debug_set(0xFF02, 0x80);
    mem_.debug_set(0x8000, SIGNED_BYTE(26)); 
    auto cyclesLeft = cpu_.execute(5, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ((uint8_t)cpu_.X, SIGNED_BYTE(8));
    EXPECT_EQ(cpu_.C, 0);
    EXPECT_EQ(cpu_.N, 1);
    EXPECT_EQ(cpu_.Z, 0);
}


///////////////////////////CPY


TEST_F(TEST_6502, CPY_Trivial)
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.Y = 0x10;
    mem_.debug_set(0xFF00, CPU::INS_CPY_IM); ///immediete
    mem_.debug_set(0xFF01, 0x10); // Zero page address
    auto cyclesLeft = cpu_.execute(5, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ((uint8_t)cpu_.Y, 0x10);
    EXPECT_EQ(cpu_.C, 1);
    EXPECT_EQ(cpu_.N, 0);
    EXPECT_EQ(cpu_.V, 0);
    EXPECT_EQ(cpu_.Z, 1);
}

TEST_F(TEST_6502, CPY_Immediate_CanCompareTwoIdenticalValues)
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.Y = 0x10;
    mem_.debug_set(0xFF00, CPU::INS_CPY_IM);
    mem_.debug_set(0xFF01, 0x10);
    auto cyclesLeft = cpu_.execute(2, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ((uint8_t)cpu_.Y, 0x10);
    EXPECT_EQ(cpu_.C, 1);
    EXPECT_EQ(cpu_.N, 0);
    EXPECT_EQ(cpu_.Z, 1);
}

TEST_F(TEST_6502, CPY_Immediate_CanComparaXLargePositiveToASmallPositive)
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.Y = 0x50;
    mem_.debug_set(0xFF00, CPU::INS_CPY_IM);
    mem_.debug_set(0xFF01, 0x10);
    auto cyclesLeft = cpu_.execute(2, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ((uint8_t)cpu_.Y, 0x50);
    EXPECT_EQ(cpu_.C, 1);
    EXPECT_EQ(cpu_.N, 0);
    EXPECT_EQ(cpu_.Z, 0);
}

TEST_F(TEST_6502, CPYImmediateCanCompareTwoIdenticalValues)
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.Y = 26;
    mem_.debug_set(0xFF00, CPU::INS_CPY_IM);
    mem_.debug_set(0xFF01, 26);
    auto cyclesLeft = cpu_.execute(2, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ(cpu_.Y, 26);
    EXPECT_EQ(cpu_.C, 1);
    EXPECT_EQ(cpu_.N, 0);
    EXPECT_EQ(cpu_.Z, 1);
}

TEST_F(TEST_6502, CPYImmediateCanCompareXLargePositiveToASmallPositive)
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.Y = 48;
    mem_.debug_set(0xFF00, CPU::INS_CPY_IM);
    mem_.debug_set(0xFF01, 26);
    auto cyclesLeft = cpu_.execute(2, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ(cpu_.Y, 48);
    EXPECT_EQ(cpu_.C, 1);
    EXPECT_EQ(cpu_.N, 0);
    EXPECT_EQ(cpu_.Z, 0);
}

TEST_F(TEST_6502, CPYImmediateCanCompareXNegativeNumberToAPositive)
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.Y = SIGNED_BYTE(-2); // Negative number
    mem_.debug_set(0xFF00, CPU::INS_CPY_IM);
    mem_.debug_set(0xFF01, SIGNED_BYTE(26));
    auto cyclesLeft = cpu_.execute(2, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ(cpu_.Y, SIGNED_BYTE(-2));
    EXPECT_EQ(cpu_.C, 1);
    EXPECT_EQ(cpu_.N, 1);
    EXPECT_EQ(cpu_.Z, 0);
}

TEST_F(TEST_6502, CPYImmediateCanCompareTwoValuesThatResultAINegativeFlagSet)
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.Y = 8;
    mem_.debug_set(0xFF00, CPU::INS_CPY_IM);
    mem_.debug_set(0xFF01, 26);
    auto cyclesLeft = cpu_.execute(2, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ(cpu_.Y, 8);
    EXPECT_EQ(cpu_.C, 0);
    EXPECT_EQ(cpu_.N, 1);
    EXPECT_EQ(cpu_.Z, 0);
}

//-- Zero Page


TEST_F(TEST_6502, CPYZeroPageCanCompareTwoIdenticalValues)
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.Y = 26;
    mem_.debug_set(0xFF00, CPU::INS_CPY_ZP);
    mem_.debug_set(0xFF01, 0x42);
    mem_.debug_set(0x0042, 26);
    auto cyclesLeft = cpu_.execute(3, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ(cpu_.Y, 26);
    EXPECT_EQ(cpu_.C, 1);
    EXPECT_EQ(cpu_.N, 0);
    EXPECT_EQ(cpu_.Z, 1);
}

TEST_F(TEST_6502, CPYZeroPageCanCompareALargePositiveToASmallPositive)
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.Y = 48;
    mem_.debug_set(0xFF00, CPU::INS_CPY_ZP);
    mem_.debug_set(0xFF01, 0x42);
    mem_.debug_set(0x0042, 26);
    auto cyclesLeft = cpu_.execute(3, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ(cpu_.Y, 48);
    EXPECT_EQ(cpu_.C, 1);
    EXPECT_EQ(cpu_.N, 0);
    EXPECT_EQ(cpu_.Z, 0);
}

TEST_F(TEST_6502, CPYZeroPageCanCompareANegativeNumberToAPositive)
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.Y = SIGNED_BYTE(-10); // Negative number
    mem_.debug_set(0xFF00, CPU::INS_CPY_ZP);
    mem_.debug_set(0xFF01, 0x42);
    mem_.debug_set(0x0042, SIGNED_BYTE(26));
    auto cyclesLeft = cpu_.execute(3, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ(cpu_.Y, SIGNED_BYTE(-10));
    EXPECT_EQ(cpu_.C, 1);
    EXPECT_EQ(cpu_.N, 1);
    EXPECT_EQ(cpu_.Z, 0);
}

TEST_F(TEST_6502, CPYZeroPageCanCompareTwoValuesThatResultInANegativeFlagSet)
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.Y = 8;
    mem_.debug_set(0xFF00, CPU::INS_CPY_ZP);
    mem_.debug_set(0xFF01, 0x42);
    mem_.debug_set(0x0042, 26);
    auto cyclesLeft = cpu_.execute(3, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ(cpu_.Y, 8);
    EXPECT_EQ(cpu_.C, 0);
    EXPECT_EQ(cpu_.N, 1);
    EXPECT_EQ(cpu_.Z, 0);
}

TEST_F(TEST_6502, CPYImmediate_CompareTwoIdenticalValues)
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.Y = 26;
    mem_.debug_set(0xFF00, CPU::INS_CPY_IM);
    mem_.debug_set(0xFF01, 26);
    auto cyclesLeft = cpu_.execute(2, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ(cpu_.Y, 26);
    EXPECT_EQ(cpu_.C, 1);
    EXPECT_EQ(cpu_.N, 0);
    EXPECT_EQ(cpu_.Z, 1);
}

TEST_F(TEST_6502, CPYImmediate_CompareALargePositiveToASmallPositive)
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.Y = 48;
    mem_.debug_set(0xFF00, CPU::INS_CPY_IM);
    mem_.debug_set(0xFF01, 26);
    auto cyclesLeft = cpu_.execute(2, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ(cpu_.Y, 48);
    EXPECT_EQ(cpu_.C, 1);
    EXPECT_EQ(cpu_.N, 0);
    EXPECT_EQ(cpu_.Z, 0);
}

TEST_F(TEST_6502, CPYImmediate_CompareANegativeNumberToAPositive)
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.Y = SIGNED_BYTE(-36);
    mem_.debug_set(0xFF00, CPU::INS_CPY_IM);
    mem_.debug_set(0xFF01, SIGNED_BYTE(26));
    auto cyclesLeft = cpu_.execute(2, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ(cpu_.Y, SIGNED_BYTE(-36));
    EXPECT_EQ(cpu_.C, 1);
    EXPECT_EQ(cpu_.N, 1);
    EXPECT_EQ(cpu_.Z, 0);
}

TEST_F(TEST_6502, CPYImmediate_CompareTwoValuesThatResultInANegativeFlagSet)
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.Y = 8;
    mem_.debug_set(0xFF00, CPU::INS_CPY_IM);
    mem_.debug_set(0xFF01, 26);
    auto cyclesLeft = cpu_.execute(2, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ(cpu_.Y, 8);
    EXPECT_EQ(cpu_.C, 0);
    EXPECT_EQ(cpu_.N, 1);
    EXPECT_EQ(cpu_.Z, 0);
}

TEST_F(TEST_6502, CPY_ZeroPage_CanCompareTwoIdenticalValues)
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.Y = SIGNED_BYTE(26);
    mem_.debug_set(0xFF00, CPU::INS_CPY_ZP); // Zero Page
    mem_.debug_set(0xFF01, 0x42);
    mem_.debug_set(0x0042, SIGNED_BYTE(26)); 
    auto cyclesLeft = cpu_.execute(5, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ((uint8_t)cpu_.Y, SIGNED_BYTE(26));
    EXPECT_EQ(cpu_.C, 1);
    EXPECT_EQ(cpu_.N, 0);
    EXPECT_EQ(cpu_.Z, 1);
}

TEST_F(TEST_6502, CPY_ZeroPage_CanCompareALargePositiveToASmallPositive)
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.Y = SIGNED_BYTE(48);
    mem_.debug_set(0xFF00, CPU::INS_CPY_ZP); // Zero Page
    mem_.debug_set(0xFF01, 0x42);
    mem_.debug_set(0x0042, SIGNED_BYTE(26)); 
    auto cyclesLeft = cpu_.execute(5, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ((uint8_t)cpu_.Y, SIGNED_BYTE(48));
    EXPECT_EQ(cpu_.C, 1);
    EXPECT_EQ(cpu_.N, 0);
    EXPECT_EQ(cpu_.Z, 0);
}

TEST_F(TEST_6502, CPY_ZeroPage_CanCompareANegativeNumberToAPositive)
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.Y = SIGNED_BYTE(-10);
    mem_.debug_set(0xFF00, CPU::INS_CPY_ZP); // Zero Page
    mem_.debug_set(0xFF01, 0x42);
    mem_.debug_set(0x0042, SIGNED_BYTE(10)); 
    auto cyclesLeft = cpu_.execute(5, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ((uint8_t)cpu_.Y, SIGNED_BYTE(-10));
    EXPECT_EQ(cpu_.C, 1);
    EXPECT_EQ(cpu_.N, 1);
    EXPECT_EQ(cpu_.Z, 0);
}

TEST_F(TEST_6502, CPY_ZeroPage_CanCompareTwoValuesThatResultInANegativeFlagSet)
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.Y = SIGNED_BYTE(8);
    mem_.debug_set(0xFF00, CPU::INS_CPY_ZP); // Zero Page
    mem_.debug_set(0xFF01, 0x42);
    mem_.debug_set(0x0042, SIGNED_BYTE(26)); 
    auto cyclesLeft = cpu_.execute(5, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ((uint8_t)cpu_.Y, SIGNED_BYTE(8));
    EXPECT_EQ(cpu_.C, 0);
    EXPECT_EQ(cpu_.N, 1);
    EXPECT_EQ(cpu_.Z, 0);
}



TEST_F(TEST_6502, CPY_Absolute_CanCompareTwoIdenticalValues)
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.Y = SIGNED_BYTE(26);
    mem_.debug_set(0xFF00, CPU::INS_CPY_ABS); // Absolute
    mem_.debug_set(0xFF01, 0x00);
    mem_.debug_set(0xFF02, 0x80);
    mem_.debug_set(0x8000, SIGNED_BYTE(26)); 
    auto cyclesLeft = cpu_.execute(5, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ((uint8_t)cpu_.Y, SIGNED_BYTE(26));
    EXPECT_EQ(cpu_.C, 1);
    EXPECT_EQ(cpu_.N, 0);
    EXPECT_EQ(cpu_.Z, 1);
}

TEST_F(TEST_6502, CPY_Absolute_CanCompareALargePositiveToASmallPositive)
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.Y = SIGNED_BYTE(48);
    mem_.debug_set(0xFF00, CPU::INS_CPY_ABS); // Absolute
    mem_.debug_set(0xFF01, 0x00);
    mem_.debug_set(0xFF02, 0x80);
    mem_.debug_set(0x8000, SIGNED_BYTE(26)); 
    auto cyclesLeft = cpu_.execute(5, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ((uint8_t)cpu_.Y, SIGNED_BYTE(48));
    EXPECT_EQ(cpu_.C, 1);
    EXPECT_EQ(cpu_.N, 0);
    EXPECT_EQ(cpu_.Z, 0);
}

TEST_F(TEST_6502, CPY_Absolute_CanCompareANegativeNumberToAPositive)
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.Y = SIGNED_BYTE(-10);
    mem_.debug_set(0xFF00, CPU::INS_CPY_ABS); // Absolute
    mem_.debug_set(0xFF01, 0x00);
    mem_.debug_set(0xFF02, 0x80);
    mem_.debug_set(0x8000, SIGNED_BYTE(10)); 
    auto cyclesLeft = cpu_.execute(5, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ((uint8_t)cpu_.Y, SIGNED_BYTE(-10));
    EXPECT_EQ(cpu_.C, 1);
    EXPECT_EQ(cpu_.N, 1);
    EXPECT_EQ(cpu_.Z, 0);
}

TEST_F(TEST_6502, CPY_Absolute_CanCompareTwoValuesThatResultInANegativeFlagSet)
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.Y = SIGNED_BYTE(8);
    mem_.debug_set(0xFF00, CPU::INS_CPY_ABS); // Absolute
    mem_.debug_set(0xFF01, 0x00);
    mem_.debug_set(0xFF02, 0x80);
    mem_.debug_set(0x8000, SIGNED_BYTE(26)); 
    auto cyclesLeft = cpu_.execute(5, mem_);

    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ((uint8_t)cpu_.Y, SIGNED_BYTE(8));
    EXPECT_EQ(cpu_.C, 0);
    EXPECT_EQ(cpu_.N, 1);
    EXPECT_EQ(cpu_.Z, 0);
}
