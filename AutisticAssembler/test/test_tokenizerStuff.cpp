#include "test.hpp"
#include "tokenizer.h"


// Tests

TEST(TokenizerTest, HandlesSingleWord) {
    std::vector<token> input = { token("hello") };
    std::vector<token> expected = { token("hello") };

    auto result = Tokenizer::splitTokens(input);
    for(int i =0; i< result.size() ;++i)
    {
      EXPECT_EQ(result[i].contents, expected[i].contents);
    }
}

TEST(TokenizerTest, HandlesMultipleWordsWithSingleSpaces) {
    std::vector<token> input = { token("hello world test") };
    std::vector<token> expected = { token("hello"), token("world"), token("test") };

    auto result = Tokenizer::splitTokens(input);

    for(int i =0; i< result.size() ;++i)
    {
      EXPECT_EQ(result[i].contents, expected[i].contents);
    }
}

TEST(TokenizerTest, HandlesMultipleWordsWithMultipleSpaces) {
    std::vector<token> input = { token("hello     world  test") };
    std::vector<token> expected = { token("hello"), token("world"), token("test") };

    auto result = Tokenizer::splitTokens(input);
    for(int i =0; i< result.size() ;++i)
    {
      EXPECT_EQ(result[i].contents, expected[i].contents);
    }
}

TEST(TokenizerTest, HandlesEmptyString) {
    std::vector<token> input = { token("") };
    std::vector<token> expected = {};

    auto result = Tokenizer::splitTokens(input);
    for(int i =0; i< result.size() ;++i)
    {
      EXPECT_EQ(result[i].contents, expected[i].contents);
    }
}

TEST(TokenizerTest, HandlesLeadingAndTrailingSpaces) {
    std::vector<token> input = { token("   hello world  ") };
    std::vector<token> expected = { token("hello"), token("world") };

    auto result = Tokenizer::splitTokens(input);

    for(int i =0; i< result.size() ;++i)
    {
      EXPECT_EQ(result[i].contents, expected[i].contents);
    }
}

TEST(TokenizerTest, HandlesMultipleTokensInInput) {
    std::vector<token> input = { token("first token"), token("second token") };
    std::vector<token> expected = { token("first"), token("token"), token("second"), token("token") };

    auto result = Tokenizer::splitTokens(input);

    for(int i =0; i< result.size() ;++i)
    {
      EXPECT_EQ(result[i].contents, expected[i].contents);
    }
}


