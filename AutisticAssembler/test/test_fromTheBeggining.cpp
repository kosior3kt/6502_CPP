#include "test.hpp"


class BasicStart : public ::testing::Test {
     
protected:
    Tokenizer tokenizer;
    parser p;
};

TEST_F(BasicStart, simpleCase)
{
   std::vector<token> inputVec
   {
      {"LDA #$69"},
      {"LDX $7000"},
      {"START:"},
      {"DEX"},
      {"BNE START"},
   };

    auto tokens = tokenizer.tokenize(inputVec);
    label::labelSet labels = tokenizer.knownLabels;
    p.resolveTokens(tokens, labels);


    int i{0};
    for(auto [str, type]: tokens)
    {
         std::cout<< i <<"- name: "<<str<<", type: "<<type<<std::endl;
         ++i;
    }
   
    ASSERT_EQ(tokens.size(), 8);
    EXPECT_EQ(tokens[4].type, token::labelDefinition);
    EXPECT_EQ(tokens[4].contents, "START"); 
    EXPECT_EQ(tokens[7].type, token::variable);
    EXPECT_EQ(std::stoi(tokens[7].contents), -3); 
}


TEST_F(BasicStart, lessSimpleCase)
{
   std::vector<token> inputVec
   {
      {"LDA #$69"},
      {"STA $8000"},
      {"BNE IGNORE"},
      {"INC"},
      {"STX $8069"},
      {"IGNORE:"},
      {"LDX $8000"},
   };

    auto tokens = tokenizer.tokenize(inputVec);
    label::labelSet labels = tokenizer.knownLabels;
    p.resolveTokens(tokens, labels);


    int i{0};
    for(auto [str, type]: tokens)
    {
         std::cout<< i <<"- name: "<<str<<", type: "<<type<<std::endl;
         ++i;
    }
   
    ASSERT_EQ(tokens.size(), 12);
    EXPECT_EQ(tokens[5].type, token::variable);
    EXPECT_EQ(std::stoi(tokens[5].contents), 4); 
    EXPECT_EQ(tokens[9].type, token::labelDefinition);
    EXPECT_EQ(tokens[9].contents, "IGNORE"); 
}


TEST_F(BasicStart, lessSimpleCase2)
{
   std::vector<token> inputVec
   {
      {"LDA #$69"},
      {"START:"},
      {"LDX $7000"},
      {"BNE END"},
      {"STA $8000"},
      {"LDY #$16"},
      {"END:"},
      {"BNE START"},
   };

    auto tokens = tokenizer.tokenize(inputVec);
    label::labelSet labels = tokenizer.knownLabels;
    p.resolveTokens(tokens, labels);

    int i{0};
    for(auto [str, type]: tokens)
    {
         std::cout<< i <<"- name: "<<str<<", type: "<<type<<std::endl;
         ++i;
    }
   
    ASSERT_EQ(tokens.size(), 14);

    EXPECT_EQ(tokens[2].type, token::labelDefinition);
    EXPECT_EQ(tokens[2].contents, "START"); 
    
    EXPECT_EQ(tokens[6].type, token::variable);
    EXPECT_EQ(std::stoi(tokens[6].contents), 5); 

    EXPECT_EQ(tokens[11].type, token::labelDefinition);
    EXPECT_EQ(tokens[11].contents, "END"); 

    EXPECT_EQ(tokens[13].type, token::variable);
    EXPECT_EQ(std::stoi(tokens[13].contents), -12); 
}
