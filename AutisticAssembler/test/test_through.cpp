#include "test.hpp"
#include "asm.h"
#include "tokenizer.h"
//#include "PGH/traits.hpp"

class ThroughTest : public ::testing::Test {
     
protected:
    Tokenizer tokenizer;
};

TEST_F(ThroughTest, splittingTest)
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

TEST_F(ThroughTest, splittingMore)
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


TEST_F(ThroughTest, splittingAndAssigningType)
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

   EXPECT_EQ(resToken.size(), expextedTokens.size());

   for(int i =0; i <  resToken.size(); ++i)
   {
      EXPECT_EQ(resToken[i].contents, expextedTokens[i].contents);
   }
   ///TODO: take care of type of token later
};



TEST_F(ThroughTest, splittingAndAssigningTypeLablezzzzz)
{
   std::vector<token> inputTokens
   {
      token("LDA #$44"),
      token("STA $2000"),
      token("damnnnn:"),
      token("JMP $FFFC"),
      token("label:"),
      token("dupa:"),
   };

   std::vector<token> expextedTokens 
   {
      token("LDA"), token("#$44"),
      token("STA"), token("$2000"),
      token("damnnnn"),
      token("JMP"), token("$FFFC"),
      token("label"),
      token("dupa"),
   };

   auto resToken = tokenizer.tokenize_firstPass(inputTokens);

   EXPECT_EQ(resToken.size(), expextedTokens.size());

   for(int i =0; i <  resToken.size(); ++i)
   {
      EXPECT_EQ(resToken[i].contents, expextedTokens[i].contents);
   }
   ///TODO: take care of type of token later
};





TEST_F(ThroughTest, splittingAndAssigningTypeLablezWithTypesChecked)
{
   std::vector<token> inputTokens
   {
      token("LDA #$44"),
      token("STA $2000"),
      token("damnnnn:"),
      token("JMP $FFFC"),
      token("label:"),
      token("dupa:"),
   };

   std::vector<token> expextedTokens 
   {
      token("LDA", token::tokenType::instruction), 
      token("#$44", token::tokenType::operand),
      token("STA", token::tokenType::instruction),
      token("$2000", token::tokenType::operand),
      token("damnnnn", token::tokenType::labelDefinition),
      token("JMP", token::tokenType::instruction),
      token("$FFFC", token::tokenType::operand),
      token("label", token::tokenType::labelDefinition),
      token("dupa", token::tokenType::labelDefinition),
   };

   auto resToken = tokenizer.tokenize_firstPass(inputTokens);

   EXPECT_EQ(resToken.size(), expextedTokens.size());

   for(int i =0; i <  resToken.size(); ++i)
   {
      EXPECT_EQ(resToken[i].contents, expextedTokens[i].contents);
      EXPECT_EQ(resToken[i].type, expextedTokens[i].type);
   }

};



TEST_F(ThroughTest, splittingAndAssigningTypeLablezWithTypesCheckedAdvanced)
{
   std::vector<token> inputTokens
   {
      token("LDA #$44"),
      token("STA $2000"),
      token("damnnnn:"),
      token("JMP $FFFC"),
      token("label:"),
      token("label"),
      token("dupa:"),
      token("dupa"),
   };

   std::vector<token> expextedTokens 
   {
      token("LDA", token::tokenType::instruction), 
      token("#$44", token::tokenType::operand),
      token("STA", token::tokenType::instruction),
      token("$2000", token::tokenType::operand),
      token("damnnnn", token::tokenType::labelDefinition),
      token("JMP", token::tokenType::instruction),
      token("$FFFC", token::tokenType::operand),
      token("label", token::tokenType::labelDefinition),
      token("label", token::tokenType::labelInstance),
      token("dupa", token::tokenType::labelDefinition),
      token("dupa", token::tokenType::labelInstance),
   };

   auto resToken = tokenizer.tokenize_firstPass(inputTokens);

   EXPECT_EQ(resToken.size(), expextedTokens.size());

   for(int i =0; i <  resToken.size(); ++i)
   {
      std::cout<<i<<" - name: "<<resToken[i].contents<<", type: "<<resToken[i].type<<"\n";
      EXPECT_EQ(resToken[i].contents, expextedTokens[i].contents);
      EXPECT_EQ(resToken[i].type, expextedTokens[i].type);
   }
};


TEST_F(ThroughTest, splittingAndAssigningTypeLablezWithTypesCheckedAdvancedSecondPass)
{
   std::vector<token> inputTokens
   {
      token("LDA #$44"),
      token("STA $2000"),
      token("damnnnn:"),
      token("JMP $FFFC"),
      token("dwa"),
      token("dwa:"),
      token("dupppa"),
      token("dupppa:"),
   };

   std::vector<token> expextedTokens 
   {
      token("LDA", token::tokenType::instruction), 
      token("#$44", token::tokenType::operand),
      token("STA", token::tokenType::instruction),
      token("$2000", token::tokenType::operand),
      token("damnnnn", token::tokenType::labelDefinition),
      token("JMP", token::tokenType::instruction),
      token("$FFFC", token::tokenType::operand),
      token("dwa", token::tokenType::unresolved),
      token("dwa", token::tokenType::labelDefinition),
      token("dupppa", token::tokenType::unresolved),
      token("dupppa", token::tokenType::labelDefinition),
   };

   auto resToken = tokenizer.tokenize_firstPass(inputTokens);

   EXPECT_EQ(resToken.size(), expextedTokens.size());

   for(int i =0; i <  resToken.size(); ++i)
   {
      EXPECT_EQ(resToken[i].contents, expextedTokens[i].contents);
      EXPECT_EQ(resToken[i].type, expextedTokens[i].type);
   }

   tokenizer.tokenize_secondPass(resToken);


   std::vector<token> expextedTokensSecondPass 
   {
      token("LDA", token::tokenType::instruction), 
      token("#$44", token::tokenType::operand),
      token("STA", token::tokenType::instruction),
      token("$2000", token::tokenType::operand),
      token("damnnnn", token::tokenType::labelDefinition),
      token("JMP", token::tokenType::instruction),
      token("$FFFC", token::tokenType::operand),
      token("dwa", token::tokenType::labelInstance),
      token("dwa", token::tokenType::labelDefinition),
      token("dupppa", token::tokenType::labelInstance),
      token("dupppa", token::tokenType::labelDefinition),
   };



   for(int i =0; i <  resToken.size(); ++i)
   {
      EXPECT_EQ(resToken[i].contents, expextedTokensSecondPass[i].contents);
      EXPECT_EQ(resToken[i].type, expextedTokensSecondPass[i].type);

   }

};


TEST(util, utilz)
{
   bool a{false};
   bool b{false};
   bool c{false};
   std::string dupa{"dupaaaa"};

   if(utils::matches_any(dupa, "test", "test2", "dupaaaa"))
   {
      a = true;
   }
   if(utils::matches_any(dupa, "test", "test2", "dupa"))
   {
      b = true;
   }
   if(utils::matches_any(dupa))
   {
      c = true;
   }

   EXPECT_TRUE(a);
   EXPECT_FALSE(b);
   EXPECT_FALSE(c);
}
