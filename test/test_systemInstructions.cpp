#include "test.hpp"

TEST_F(TEST_6502, PLP_ensuring)
{
   cpu_.Reset(mem_, 0xFF00);

   cpu_.N = 1;   
   cpu_.D = 1;   
   cpu_.Z = 0;   

   auto tempCopy = cpu_;

   uint8_t currentFlagsBefore = cpu_.getCurrentFlags();
   std::bitset<8> before(currentFlagsBefore);
   HEX_PRINT("those are the falgs before: ", before);


   mem_.set(0xFF00, CPU::INS_PHP);
   mem_.set(0xFF01, CPU::INS_LDA_IM);  ///this thing changes Z flag into 1
   mem_.set(0xFF02, 0x00);
   mem_.set(0xFF03, CPU::INS_PLP);

   auto cyclesLeft = cpu_.execute(10, mem_);

   uint8_t currentFlagsAfter = cpu_.getCurrentFlags();
   std::bitset<8> after(currentFlagsAfter);
   HEX_PRINT("those are the falgs after: ", after);
   
   EXPECT_EQ(cyclesLeft, 0);
   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, tempCopy));
}

TEST_F(TEST_6502, BRK_TRIVIAL)
{
    cpu_.Reset(mem_, 0xFF00);
    mem_.set(0xFF00, CPU::INS_BRK); 
    mem_.set(0xFFFE, 0x00);
    mem_.set(0xFFFF, 0x80);
    mem_.set(0x8000, CPU::INS_LDA_IM); 
    mem_.set(0x8001, 0x69); 
    mem_.set(0x8002, CPU::INS_NOTHING); 
    auto cyclesLeft = cpu_.execute(30, mem_);


    EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ((uint8_t)cpu_.A, 0x69) ;
    EXPECT_EQ(cpu_.C, 0);
    EXPECT_EQ(cpu_.N, 0);
    EXPECT_EQ(cpu_.Z, 0);
}

TEST_F(TEST_6502, RTI_TRIVIAL)
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.C = 1;
    cpu_.V = 1;
    cpu_.Z = 0;
    cpu_.A = 0x17;
    mem_.set(0xFF00, CPU::INS_BRK); 
    mem_.set(0xFF02, CPU::INS_NOTHING); 
    mem_.set(0xFFFE, 0x00);
    mem_.set(0xFFFF, 0x80);
    mem_.set(0x8000, CPU::INS_LDA_IM);    ///this thing changes Z flag into 1, but then it shoutld be rolled back to zero
    mem_.set(0x8001, 0x69); 
    mem_.set(0x8002, CPU::INS_RTI);
    mem_.set(0x8003, CPU::INS_NOTHING); 
    auto cyclesLeft = cpu_.execute(100, mem_);


    ///EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ((uint8_t)cpu_.A, 0x69) ; ///this thing stays the same after interupt
    EXPECT_EQ(cpu_.C, 1);
    EXPECT_EQ(cpu_.V, 1);
    EXPECT_EQ(cpu_.N, 0);
    EXPECT_EQ(cpu_.Z, 0);
}

TEST_F(TEST_6502, RTI_nonTrivial)
{
    cpu_.Reset(mem_, 0xFF00);
    cpu_.C = 1;
    cpu_.V = 1;
    cpu_.Z = 0;
    cpu_.A = 0x17;
    mem_.set(0xFF00, CPU::INS_LDA_IM); 
    mem_.set(0xFF01, 0x00);                  ///now flag Z is 1
    mem_.set(0xFF02, CPU::INS_BRK);          ///now all the flags are on stack
    mem_.set(0xFF03, CPU::INS_NOTHING); 
    mem_.set(0xFFFE, 0x00);
    mem_.set(0xFFFF, 0x80);
    mem_.set(0x8000, CPU::INS_LDA_IM);       ///this thing changes Z flag to be non zero now
    mem_.set(0x8001, 0x69); 
    mem_.set(0x8002, CPU::INS_RTI);          ///after returning flag Z should be 1 
    mem_.set(0x8003, CPU::INS_NOTHING); 
    auto cyclesLeft = cpu_.execute(100, mem_);

    ///EXPECT_EQ(cyclesLeft, 0);
    EXPECT_EQ((uint8_t)cpu_.A, 0x69) ; ///this thing stays the same after interupt
    EXPECT_EQ(cpu_.C, 1);
    EXPECT_EQ(cpu_.V, 1);
    EXPECT_EQ(cpu_.N, 0);
    EXPECT_EQ(cpu_.Z, 1);
}

