#ifndef __TEST__
#define __TEST__


#include <gtest/gtest.h>

#include "asm.h"
#include "parser.h"
#include "tokenizer.h"

class ParserTest : public ::testing::Test {
protected:
    void SetUp() override {
        // This function runs before each test
    }

    void TearDown() override {
        // This function runs after each test
    }
};


#endif
