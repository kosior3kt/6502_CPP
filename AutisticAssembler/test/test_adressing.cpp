#include <gtest/gtest.h>
#include "defines.hpp"

TEST(AddressingModeTest, ValidAddressingModes) {
    EXPECT_TRUE(utils::isAddress("#$F9"));         // Immediate addressing
    EXPECT_TRUE(utils::isAddress("($A300)"));        // Absolute addressing
    EXPECT_TRUE(utils::isAddress("($A3,X)"));      // Indexed indirect addressing
    EXPECT_TRUE(utils::isAddress("($B2),Y"));      // Indirect indexed addressing
    EXPECT_TRUE(utils::isAddress("$A5,X"));        // Zero page indexed addressing (X)
    EXPECT_TRUE(utils::isAddress("$A500,X"));        // Zero page indexed addressing (X)
    EXPECT_TRUE(utils::isAddress("($8000)"));        // Zero page indexed addressing (X)
}

TEST(AddressingModeTest, InvalidAddressingModes) {
    EXPECT_FALSE(utils::isAddress("XYZ"));
    EXPECT_FALSE(utils::isAddress("(A3,Z)"));
    EXPECT_FALSE(utils::isAddress("A3"));
    EXPECT_FALSE(utils::isAddress("(A3,X,Y)"));
    EXPECT_FALSE(utils::isAddress("#F9,X"));
}
