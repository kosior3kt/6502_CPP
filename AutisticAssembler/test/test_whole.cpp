#include "test.hpp"
#include "asm.h"
#include "tokenizer.h"


class wholeTest: public ::testing::Test 
{
     
protected:

};


TEST_F(wholeTest, sanityCheck)
{
     ASSERT_EQ(1, 1); 
}


TEST_F(wholeTest, writingSimpleValuesToFile)
{
   std::string outputFileName = "test1";
   std::ofstream oFile(outputFileName);
   Asm::DEBUG::streamToFile(oFile, 69);

   oFile.close();

   std::ifstream iFile(outputFileName);
   std::stringstream dupa;
   if(!iFile) std::cout<<"died\n";
   dupa<<iFile.rdbuf();

   iFile.close();
   std::string temp(dupa.str());
   std::cout<<temp<<"\n";
   uint8_t a = temp[0];

   EXPECT_EQ(69, (uint8_t)a);

}


/*
(std::vector<token>) size=7 {
  [0] = (contents = "LDA", type = instruction)
  [1] = (contents = "#$10", type = operand)
  [2] = (contents = "STA", type = instruction)
  [3] = (contents = "$4000", type = operand)
  [4] = (contents = "LDX", type = instruction)
  [5] = (contents = "#$69", type = operand)
  [6] = (contents = "TXA", type = instruction)
}
 */



// TEST_F(wholeTest, justGenerateMachineCode)
// {
//
//    std::vector<token> tokens
//    {
//       {"LDA", token::tokenType::instruction},
//       {"#$10", token::tokenType::operand},
//       {"STA", token::tokenType::instruction},
//       {"$4000", token::tokenType::operand},
//       {"LDX", token::tokenType::instruction},
//       {"#$69", token::tokenType::operand},
//       {"TXA", token::tokenType::instruction},
//    };
//
//    Asm::generateMachineCode(tokens, "outputTemp");
//
//
//
//    ASSERT_EQ(1, 1);
// }



TEST_F(wholeTest, normalWays)
{
   std::ofstream output("temp2");   
   using lines = std::string;

   std::vector<lines> fileContents
   {
      {"LDA #$10\n"},
      {"STA $4000\n"},  ///change it to 40 00 later when I figure out how I want to convert them fomr 0x to dec and the other way around
      {"LDX #$69\n"},
      {"TXA\n"},
   };

   for(const auto& ln: fileContents)
   {
      output << ln;      
   }

   output.close();

   Asm::generate("temp2", "outputTemp");

   ASSERT_EQ(1, 1);
}

