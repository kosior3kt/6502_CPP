#include "test.hpp"


TEST_F(TEST_6502, LDX_IM)
{
   test_LD(CPU::INS_LDX_IM, Register::X);
}
