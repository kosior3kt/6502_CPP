#include "test.hpp"


TEST_F(TEST_6502, BRK_TRIVIAL)
{
    cpu_.Reset(mem_, 0xFF00);
    mem_.debug_set(0xFF00, CPU::INS_BRK); 
    mem_.debug_set(0xFFFE, 0x00);
    mem_.debug_set(0xFFFF, 0x80);
    mem_.debug_set(0x8000, CPU::INS_LDA_IM); 
    mem_.debug_set(0x8001, 0x69); 
    mem_.debug_set(0x8002, CPU::INS_NOTHING); 
    auto cyclesLeft = cpu_.execute(30, mem_);


    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ((uint8_t)cpu_.A, 0x69) ;
    EXPECT_EQ(cpu_.C, 0);
    EXPECT_EQ(cpu_.N, 0);
    EXPECT_EQ(cpu_.Z, 0);
}

