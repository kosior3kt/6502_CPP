#include "test.hpp"
#include "tokenizer.h"


// Tests

TEST(TokenizerTest, HandlesSingleWord) {
    Tokenizer tokenizer;
    std::vector<token> input = { token("hello") };
    std::vector<token> expected = { token("hello") };

    auto result = tokenizer.splitTokens(input);
    for(int i =0; i< result.size() ;++i)
    {
      EXPECT_EQ(result[i].contents, expected[i].contents);
    }
}

TEST(TokenizerTest, HandlesMultipleWordsWithSingleSpaces) {
    Tokenizer tokenizer;
    std::vector<token> input = { token("hello world test") };
    std::vector<token> expected = { token("hello"), token("world"), token("test") };

    auto result = tokenizer.splitTokens(input);

    for(int i =0; i< result.size() ;++i)
    {
      EXPECT_EQ(result[i].contents, expected[i].contents);
    }
}

TEST(TokenizerTest, HandlesMultipleWordsWithMultipleSpaces) {
    Tokenizer tokenizer;
    std::vector<token> input = { token("hello     world  test") };
    std::vector<token> expected = { token("hello"), token("world"), token("test") };

    auto result = tokenizer.splitTokens(input);
    for(int i =0; i< result.size() ;++i)
    {
      EXPECT_EQ(result[i].contents, expected[i].contents);
    }
}

TEST(TokenizerTest, HandlesEmptyString) {
    Tokenizer tokenizer;
    std::vector<token> input = { token("") };
    std::vector<token> expected = {};

    auto result = tokenizer.splitTokens(input);
    for(int i =0; i< result.size() ;++i)
    {
      EXPECT_EQ(result[i].contents, expected[i].contents);
    }
}

TEST(TokenizerTest, HandlesLeadingAndTrailingSpaces) {
    Tokenizer tokenizer;
    std::vector<token> input = { token("   hello world  ") };
    std::vector<token> expected = { token("hello"), token("world") };

    auto result = tokenizer.splitTokens(input);

    for(int i =0; i< result.size() ;++i)
    {
      EXPECT_EQ(result[i].contents, expected[i].contents);
    }
}

TEST(TokenizerTest, HandlesMultipleTokensInInput) {
    Tokenizer tokenizer;
    std::vector<token> input = { token("first token"), token("second token") };
    std::vector<token> expected = { token("first"), token("token"), token("second"), token("token") };

    auto result = tokenizer.splitTokens(input);

    for(int i =0; i< result.size() ;++i)
    {
      EXPECT_EQ(result[i].contents, expected[i].contents);
    }
}


