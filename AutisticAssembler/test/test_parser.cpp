#include "test.hpp"

// Test valid label resolution
TEST(ParserTest, ValidLabelResolution) {
    std::vector<token> tokens = {
        {"START", token::labelDefinition},
        {"LDA", token::instruction},
        {"#$10", token::operand},
        {"BNE", token::instruction},
        {"START", token::labelInstance}
    };
    label::labelSet labels = {{"START", 0}};
    parser p;
    p.resolveTokens(tokens, labels);
    EXPECT_EQ(tokens[4].type, token::variable);
    int value = std::stoi(tokens[4].contents);
    EXPECT_EQ(value, -2); // Assuming START is 3 bytes before
}

// Test forward reference
TEST(ParserTest, ForwardReference) {
    std::vector<token> tokens = {
        {"BEQ", token::instruction},
        {"FORWARD", token::labelInstance},
        {"LDA", token::instruction},
        {"#$20", token::operand},
        {"FORWARD", token::labelDefinition}
    };
    label::labelSet labels = {{"FORWARD", 4}};
    parser p;
    p.resolveTokens(tokens, labels);
    EXPECT_EQ(tokens[1].type, token::variable);
    EXPECT_EQ(std::stoi(tokens[1].contents), 3); // Assuming FORWARD is 2 bytes ahead
}

// // Test invalid label usage
// TEST(ParserTest, InvalidLabelUsage) {
//     std::vector<token> tokens = {
//         {"UNDEFINED", token::labelInstance}
//     };
//     label::labelSet labels;
//     parser p;
//     EXPECT_DEATH(p.resolveTokens(tokens, labels), "");
// }

// Test branching instruction with large shift
TEST(ParserTest, LargeBranchShift) {
    std::vector<token> tokens = {
        {"START", token::labelDefinition},
        // ... 126 bytes of instructions ...
        {"BNE", token::instruction},
        {"START", token::labelInstance}
    };
    label::labelSet labels = {{"START", 0}};
    parser p;
    p.resolveTokens(tokens, labels);
    EXPECT_EQ(tokens.back().type, token::variable);
    EXPECT_EQ(std::stoi(tokens.back().contents), -1); // -128 in two's complement
}

