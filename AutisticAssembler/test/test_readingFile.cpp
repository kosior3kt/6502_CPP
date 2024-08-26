#include <gtest/gtest.h>
#include <fstream>
#include <sstream>
#include "asm.h"

// Test fixture class
class ASMTest : public ::testing::Test {
protected:
    myASM asmObj;

    // Utility function to create a temporary file with given content
    std::string createTempFile(const std::string& content) {
        std::string filename = "temp_test_file.txt";
        std::ofstream tempFile(filename);
        tempFile << content;
        tempFile.close();
        return filename;
    }

    // Utility function to remove the temporary file
    void removeTempFile(const std::string& filename) {
        std::remove(filename.c_str());
    }
};

TEST_F(ASMTest, EmptyFile) {
    std::string tempFilename = createTempFile("");
    std::ifstream inputFile(tempFilename);

    asmObj.loadAndPreprocess(inputFile);

    EXPECT_TRUE(asmObj.fileContents_.empty());

    inputFile.close();
    removeTempFile(tempFilename);
}

TEST_F(ASMTest, FileWithOnlyWhitespace) {
    std::string tempFilename = createTempFile("   \n\t\n   \t\n");
    std::ifstream inputFile(tempFilename);

    asmObj.loadAndPreprocess(inputFile);

    EXPECT_TRUE(asmObj.fileContents_.empty());

    inputFile.close();
    removeTempFile(tempFilename);
}

TEST_F(ASMTest, FileWithLinesWithOnlyWhitespaceAndValidLines) {
    std::string tempFilename = createTempFile("   \nValidLine1\n  \tValidLine2   \n   ");
    std::ifstream inputFile(tempFilename);

    asmObj.loadAndPreprocess(inputFile);

    ASSERT_EQ(asmObj.fileContents_.size(), 2);
    EXPECT_EQ(asmObj.fileContents_[0].contents, "ValidLine1");
    EXPECT_EQ(asmObj.fileContents_[1].contents, "ValidLine2");

    EXPECT_EQ(asmObj.fileContents_[0].type, token::EMPTY);  // Assuming default token type is EMPTY
    EXPECT_EQ(asmObj.fileContents_[1].type, token::EMPTY);  // Assuming default token type is EMPTY

    inputFile.close();
    removeTempFile(tempFilename);
}

TEST_F(ASMTest, FileWithLeadingAndTrailingWhitespace) {
    std::string tempFilename = createTempFile("   LineWithSpaces   ");
    std::ifstream inputFile(tempFilename);

    asmObj.loadAndPreprocess(inputFile);

    ASSERT_EQ(asmObj.fileContents_.size(), 1);
    EXPECT_EQ(asmObj.fileContents_[0].contents, "LineWithSpaces");
    EXPECT_EQ(asmObj.fileContents_[0].type, token::EMPTY);  // Assuming default token type is EMPTY

    inputFile.close();
    removeTempFile(tempFilename);
}

TEST_F(ASMTest, FileWithMultipleLines) {
    std::string tempFilename = createTempFile("Line1\nLine2\nLine3\n");
    std::ifstream inputFile(tempFilename);

    asmObj.loadAndPreprocess(inputFile);

    ASSERT_EQ(asmObj.fileContents_.size(), 3);
    EXPECT_EQ(asmObj.fileContents_[0].contents, "Line1");
    EXPECT_EQ(asmObj.fileContents_[1].contents, "Line2");
    EXPECT_EQ(asmObj.fileContents_[2].contents, "Line3");

    EXPECT_EQ(asmObj.fileContents_[0].type, token::EMPTY);  // Assuming default token type is EMPTY
    EXPECT_EQ(asmObj.fileContents_[1].type, token::EMPTY);  // Assuming default token type is EMPTY
    EXPECT_EQ(asmObj.fileContents_[2].type, token::EMPTY);  // Assuming default token type is EMPTY

    inputFile.close();
    removeTempFile(tempFilename);
}

TEST_F(ASMTest, InvalidFile) {
    std::ifstream inputFile("non_existent_file.txt");
    EXPECT_NO_THROW(asmObj.loadAndPreprocess(inputFile));

    EXPECT_TRUE(asmObj.fileContents_.empty());
}

