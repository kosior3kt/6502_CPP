#include "test.hpp"
#include "asm.h"
#include "tokenizer.h"

class TokenizerTests : public ::testing::Test {
protected:
    Tokenizer tokenizer;
};

TEST_F(TokenizerTests, aplittingTest)
{
   auto input = std::vector<token>
   {
      token("LDA #$44")
   };

   std::vector<token> expected 
   {
      token("LDA"), 
      token("#$44")
   };


   auto resVec = tokenizer.splitTokens(input);

   EXPECT_EQ(resVec.size(), expected.size());

   for(int i =0; i< resVec.size(); ++i)
   {
      EXPECT_EQ(resVec[i].contents, expected[i].contents);
   }
}

TEST_F(TokenizerTests, splittingMore)
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
      token("label:")
   };

   auto resToken = tokenizer.splitTokens(inputTokens);

   EXPECT_EQ(resToken.size(), expextedTokens.size());

   for(int i =0; i <  resToken.size(); ++i)
   {
      EXPECT_EQ(resToken[i].contents, expextedTokens[i].contents);
   }

};


TEST_F(TokenizerTests, splittingAndAssigningType)
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

   auto resToken = tokenizer.tokenize(inputTokens);

   EXPECT_EQ(resToken.size(), expextedTokens.size());

   for(int i =0; i <  resToken.size(); ++i)
   {
      EXPECT_EQ(resToken[i].contents, expextedTokens[i].contents);
   }
   ///TODO: take care of type of token later
};

