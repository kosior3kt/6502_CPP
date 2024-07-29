#include "test.hpp"


// Test 1: Normal strings with leading and trailing spaces
TEST_F(ParserTest, TrimNormalStrings) {
    p.lineVec_ = {"   hello   ", " world ", "  foo  ", "bar"};
    p.trimm();
    std::vector<std::string> expected = {"hello", "world", "foo", "bar"};
    EXPECT_EQ(p.lineVec_, expected);
}

// Test 2: Strings with only spaces
TEST_F(ParserTest, TrimStringsWithOnlySpaces) {
    p.lineVec_ = {"   ", "      ", "  "};
    p.trimm();
    EXPECT_TRUE(p.lineVec_.empty());
}

// Test 3: Mix of normal strings and strings with only spaces
TEST_F(ParserTest, TrimMixedStrings) {
    p.lineVec_ = {"   hello   ", "   ", " world ", "      ", "  foo  ", "bar", "  "};
    p.trimm();
    std::vector<std::string> expected = {"hello", "world", "foo", "bar"};
    EXPECT_EQ(p.lineVec_, expected);
}

// Test 4: Strings with no spaces
TEST_F(ParserTest, TrimStringsNoSpaces) {
    p.lineVec_ = {"hello", "world", "foo", "bar"};
    p.trimm();
    std::vector<std::string> expected = {"hello", "world", "foo", "bar"};
    EXPECT_EQ(p.lineVec_, expected);
}

// Test 5: Empty vector
TEST_F(ParserTest, TrimEmptyVector) {
    p.lineVec_.clear();
    p.trimm();
    EXPECT_TRUE(p.lineVec_.empty());
}

// Test 6: Strings with only trailing spaces
TEST_F(ParserTest, TrimStringsWithTrailingSpaces) {
    p.lineVec_ = {"hello   ", "world", "  foo", "bar   "};
    p.trimm();
    std::vector<std::string> expected = {"hello", "world", "  foo", "bar"};
    EXPECT_EQ(p.lineVec_, expected);
}

// Test 7: Strings with only leading spaces
TEST_F(ParserTest, TrimStringsWithLeadingSpaces) {
    p.lineVec_ = {"   hello", "world", "foo  ", "   bar"};
    p.trimm();
    std::vector<std::string> expected = {"hello", "world", "foo", "bar"};
    EXPECT_EQ(p.lineVec_, expected);
}

// Test 8: Strings with empty strings
TEST_F(ParserTest, TrimStringsWithEmptyStrings) {
    p.lineVec_ = {"hello", "", " world ", " ", "foo"};
    p.trimm();
    std::vector<std::string> expected = {"hello", "world", "foo"};
    EXPECT_EQ(p.lineVec_, expected);
}
