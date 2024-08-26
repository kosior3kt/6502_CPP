#include "test.hpp"


TEST_F(TEST_6502, helperFunctionsTest_falgsState)
{
   cpu_.C = 1;
   cpu_.I = 1;
   cpu_.D = 1;

   auto copy = cpu_;
   
   auto currentFlags = cpu_.getCurrentFlags();


   copy.setCurrentFlags(currentFlags);

   EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copy));
}




