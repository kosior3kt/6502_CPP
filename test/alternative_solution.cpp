#include "test.hpp"

 
TEST_F(TEST_6502, LDA_IM)
{
   test_LD_alternative(CPU::INS_LDA_IM, Register::A);
}


