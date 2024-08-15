#include <gtest/gtest.h>
#include "defines.hpp"


TEST(OpcodeTest, ValidInstructions) {
    EXPECT_TRUE(utils::isInstruction("ADC"));
    EXPECT_TRUE(utils::isInstruction("LDA"));
    EXPECT_TRUE(utils::isInstruction("NOP"));
    EXPECT_TRUE(utils::isInstruction("JSR"));
}

TEST(OpcodeTest, InvalidInstructions) {
    EXPECT_FALSE(utils::isInstruction("XYZ"));
    EXPECT_FALSE(utils::isInstruction("SOM"));
    EXPECT_FALSE(utils::isInstruction("INVALID"));
}
