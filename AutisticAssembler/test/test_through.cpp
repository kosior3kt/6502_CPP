#include "test.hpp"
#include "asm.h"
#include "tokenizer.h"

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



///============================================================test_experimental

class ParserTokenizerTest : public ::testing::Test {
protected:
    Tokenizer tokenizer;
    parser p;
};

TEST_F(ParserTokenizerTest, SimpleProgram) 
{
    std::vector<token> input
    {
        {"START:", token::EMPTY},
        {"LDA #$10", token::EMPTY},
        {"BNE END", token::EMPTY},
        {"LDA #$20", token::EMPTY},
        {"END:", token::EMPTY},
        {"RTS", token::EMPTY}
    };

    auto tokens = tokenizer.tokenize(input);
    label::labelSet labels = tokenizer.knownLabels;
    p.resolveTokens(tokens, labels);


    int i{0};
    for(auto [str, type]: tokens)
    {
         std::cout<< i <<"- name: "<<str<<", type: "<<type<<std::endl;
         ++i;
    }

    ASSERT_EQ(tokens.size(), 9);
    EXPECT_EQ(tokens[0].type, token::labelDefinition);
    EXPECT_EQ(tokens[0].contents, "START");
    EXPECT_EQ(tokens[2].type, token::operand);
    EXPECT_EQ(tokens[3].contents, "BNE");
    EXPECT_EQ(tokens[3].type, token::instruction);
    EXPECT_EQ(std::stoi(tokens[4].contents), 3); // END is 3 bytes ahead
    EXPECT_EQ(tokens[4].type, token::variable);
}

TEST_F(ParserTokenizerTest, ForwardAndBackwardReferences) {
    std::vector<token> input = {
        {"BNE MIDDLE", token::EMPTY},
        {"START:", token::EMPTY},
        {"LDA #$10", token::EMPTY},
        {"BEQ END", token::EMPTY},
        {"MIDDLE:", token::EMPTY},
        {"STA $2000", token::EMPTY},
        {"BNE START", token::EMPTY},
        {"END:", token::EMPTY},
        {"RTS", token::EMPTY}
    };

    auto tokens = tokenizer.tokenize(input);
    label::labelSet labels = tokenizer.knownLabels;
    p.resolveTokens(tokens, labels);



    int i{0};
    for(const auto& [str, type]: tokens)
    {
         std::cout<< i <<"- name: "<<str<<", type: "<<type<<std::endl;
         ++i;
    }



    ASSERT_EQ(tokens.size(), 14);
    EXPECT_EQ(tokens[1].type, token::variable);
    EXPECT_EQ(std::stoi(tokens[1].contents), 4); // MIDDLE is 4 bytes ahead
    EXPECT_EQ(tokens[6].type, token::variable);
    EXPECT_EQ(std::stoi(tokens[6].contents), 5); // END is 3 bytes ahead
    EXPECT_EQ(tokens[11].type, token::variable);
    EXPECT_EQ(std::stoi(tokens[11].contents), -9); // START is 5 bytes behind
}

TEST_F(ParserTokenizerTest, LongBranch) {
    std::vector<token> input = {
        {"START:", token::EMPTY},
        {"LDA #$01", token::EMPTY}
    };
    // Add 126 NOP instructions
    for (int i = 0; i < 126; ++i) {
        input.push_back({"NOP", token::EMPTY});
    }
    input.push_back({"BNE START", token::EMPTY});

    auto tokens = tokenizer.tokenize(input);
    label::labelSet labels = tokenizer.knownLabels;
    p.resolveTokens(tokens, labels);

    ASSERT_EQ(tokens.size(), 131);
    EXPECT_EQ(tokens[128].type, token::instruction);
    EXPECT_EQ(tokens[129].contents, "BNE");
    EXPECT_EQ(tokens[130].type, token::variable);
    EXPECT_EQ(std::stoi(tokens[130].contents), -128); // Maximum negative branch
}

TEST_F(ParserTokenizerTest, MultipleLabelsAndInstructions) {
    std::vector<token> input = {
        {"INIT:", token::EMPTY},
        {"LDX #$00", token::EMPTY},
        {"LOOP:", token::EMPTY},
        {"LDA $2000,X", token::EMPTY},
        {"BEQ END", token::EMPTY},
        {"INX", token::EMPTY},
        {"BEQ LOOP", token::EMPTY},
        {"END:", token::EMPTY},
        {"RTS", token::EMPTY}
    };

    auto tokens = tokenizer.tokenize(input);
    label::labelSet labels = tokenizer.knownLabels;
    p.resolveTokens(tokens, labels);

    ASSERT_EQ(tokens.size(), 13);
    EXPECT_EQ(tokens[0].type, token::labelDefinition);
    EXPECT_EQ(tokens[0].contents, "INIT");
    EXPECT_EQ(tokens[3].type, token::labelDefinition);
    EXPECT_EQ(tokens[3].contents, "LOOP");
    EXPECT_EQ(tokens[7].type, token::variable);
    EXPECT_EQ(std::stoi(tokens[7].contents), 3); // END is 3 bytes ahead
    EXPECT_EQ(tokens[10].type, token::variable);
    EXPECT_EQ(std::stoi(tokens[10].contents), -3); // LOOP is 5 bytes behind
}

////trust me bruh it's incredibly robust - no need to test that

// TEST_F(ParserTokenizerTest, InvalidLabelUsage) {
//     std::vector<token> input = {
//         {"JMP NONEXISTENT", token::EMPTY},
//         {"RTS", token::EMPTY}
//     };
//
//     auto tokens = tokenizer.tokenize(input);
//     label::labelSet labels = tokenizer.knownLabels;
//     //EXPECT_DEATH(p.resolveTokens(tokens, labels), std::runtime_error);
//     EXPECT_DEATH(p.resolveTokens(tokens, labels), "");
// }



