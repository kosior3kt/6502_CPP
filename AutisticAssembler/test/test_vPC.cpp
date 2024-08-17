#include "test.hpp"
#include "asm.h"
#include "tokenizer.h"

class vPCTest : public ::testing::Test {
     
protected:
    Tokenizer tokenizer;
};

TEST_F(vPCTest, vPCtest_dupa)
{
   std::vector<token> inputTokens
   {
      token("LDA #$44"),
      token("STA $2000"),
      token("JMP $FFFC"),
      token("label:")
   };

   std::vector<token> expextedTokens 
   {
      token("LDA"), token("#$44"),
      token("STA"), token("$2000"),
      token("JMP"), token("$FFFC"),
      token("label")
   };

   auto resToken = tokenizer.tokenize_firstPass(inputTokens);

   bool passed{false};

   EXPECT_EQ(resToken.size(), expextedTokens.size());

   for(int i =0; i <  resToken.size(); ++i)
   {
      EXPECT_EQ(resToken[i].contents, expextedTokens[i].contents);

      if(resToken[i].contents == "label")
      {
         std::cout<<"in if\n";
         std::cout<<tokenizer.knownLabels.size()<<std::endl;
         for(const auto& _label: tokenizer.knownLabels)
         {
            std::cout<<"name: "<<_label.name<<" vPC: "<<_label.vPC<<std::endl;
            if(_label.vPC == 4 && _label.name == "label") passed = true;
         }
      }
   }

   EXPECT_TRUE(passed);


};
