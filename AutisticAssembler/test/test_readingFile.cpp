#include <gtest/gtest.h>
#include <fstream>
#include <sstream>
#include "asm.h"

// Test fixture class
class ASMTest : public ::testing::Test 
{
protected:
    // Utility function to create a temporary file with given content
    std::string createTempFile(const std::string& content) 
    {
        std::string filename = "temp_test_file.txt";
        std::ofstream tempFile(filename);
        tempFile << content;
        tempFile.close();
        return filename;
    }

    // Utility function to remove the temporary file
    void removeTempFile(const std::string& filename) 
    {
        std::remove(filename.c_str());
    }
};

TEST_F(ASMTest, EmptyFile) 
{
   Asm::DEBUG::debug_flush();
    std::string tempFilename = createTempFile("");
    std::ifstream inputFile(tempFilename);

    Asm::PRIV::loadAndPreprocess(inputFile);

    EXPECT_TRUE(Asm::DEBUG::debug_getFileContents_().empty());

    inputFile.close();
    removeTempFile(tempFilename);
}

TEST_F(ASMTest, FileWithOnlyWhitespace) {
   Asm::DEBUG::debug_flush();
    std::string tempFilename = createTempFile("   \n\t\n   \t\n");
    std::ifstream inputFile(tempFilename);

    Asm::PRIV::loadAndPreprocess(inputFile);

    EXPECT_TRUE(Asm::DEBUG::debug_getFileContents_().empty());

    inputFile.close();
    removeTempFile(tempFilename);
}

TEST_F(ASMTest, FileWithLinesWithOnlyWhitespaceAndValidLines) {
   Asm::DEBUG::debug_flush();
    std::string tempFilename = createTempFile("   \nValidLine1\n  \tValidLine2   \n   ");
    std::ifstream inputFile(tempFilename);

    Asm::PRIV::loadAndPreprocess(inputFile);

    ASSERT_EQ(Asm::DEBUG::debug_getFileContents_().size(), 2);
    EXPECT_EQ(Asm::DEBUG::debug_getFileContents_()[0].contents, "ValidLine1");
    EXPECT_EQ(Asm::DEBUG::debug_getFileContents_()[1].contents, "ValidLine2");

    EXPECT_EQ(Asm::DEBUG::debug_getFileContents_()[0].type, token::EMPTY);  // Assuming default token type is EMPTY
    EXPECT_EQ(Asm::DEBUG::debug_getFileContents_()[1].type, token::EMPTY);  // Assuming default token type is EMPTY

    inputFile.close();
    removeTempFile(tempFilename);
}

TEST_F(ASMTest, FileWithLeadingAndTrailingWhitespace) 
{
   Asm::DEBUG::debug_flush();
    std::string tempFilename = createTempFile("   LineWithSpaces   ");
    std::ifstream inputFile(tempFilename);

    Asm::PRIV::loadAndPreprocess(inputFile);

    auto vec = Asm::DEBUG::debug_getFileContents_();

   for(const auto& tok: vec)
   {
      std::cout<<tok.contents<<"\n";
   }

    ASSERT_EQ(vec.size(), 1);
    EXPECT_EQ(Asm::DEBUG::debug_getFileContents_()[0].contents, "LineWithSpaces");
    EXPECT_EQ(Asm::DEBUG::debug_getFileContents_()[0].type, token::EMPTY);  // Assuming default token type is EMPTY

    inputFile.close();
    removeTempFile(tempFilename);
}

TEST_F(ASMTest, FileWithMultipleLines) {
   Asm::DEBUG::debug_flush();
    std::string tempFilename = createTempFile("Line1\nLine2\nLine3\n");
    std::ifstream inputFile(tempFilename);

    Asm::PRIV::loadAndPreprocess(inputFile);

    ASSERT_EQ(Asm::DEBUG::debug_getFileContents_().size(), 3);
    EXPECT_EQ(Asm::DEBUG::debug_getFileContents_()[0].contents, "Line1");
    EXPECT_EQ(Asm::DEBUG::debug_getFileContents_()[1].contents, "Line2");
    EXPECT_EQ(Asm::DEBUG::debug_getFileContents_()[2].contents, "Line3");

    EXPECT_EQ(Asm::DEBUG::debug_getFileContents_()[0].type, token::EMPTY);  // Assuming default token type is EMPTY
    EXPECT_EQ(Asm::DEBUG::debug_getFileContents_()[1].type, token::EMPTY);  // Assuming default token type is EMPTY
    EXPECT_EQ(Asm::DEBUG::debug_getFileContents_()[2].type, token::EMPTY);  // Assuming default token type is EMPTY

    inputFile.close();
    removeTempFile(tempFilename);
}

TEST_F(ASMTest, InvalidFile) {
   Asm::DEBUG::debug_flush();
    std::ifstream inputFile("non_existent_file.txt");
    EXPECT_NO_THROW(Asm::PRIV::loadAndPreprocess(inputFile));

    EXPECT_TRUE(Asm::DEBUG::debug_getFileContents_().empty());
}

