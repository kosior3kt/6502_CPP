#ifndef __AUTISTIC_ASM 
#define __AUTISTIC_ASM

#include "defines.h"
#include "parser.h"
#include "tokenizer.h"

#include "instructionCodes.h" ///TODO: move it somewhere - for now here

#include "token.hpp"

struct myASM
{
   private:
   using line = token;
   //std::string fileContents_;    ///usefull
   public:
   std::vector<line> fileContents_;   //purely technically this shuold be at max a 2* line count, but this to TODO at this point
   
   Byte Data[MAX_MEM];           ///this thing is tossed around as a reference =3
                                 ///
   void streamToFile(std::ofstream& _outputFile, const uint8_t _val);

   //5. final machine code generation
   void generateMachineCode(const std::vector<token>& _inputVec, const std::string& _outputFile);

   //1.1 preprocess - get rid of redundant stuff, and load program from file into a vector of strings
   void loadAndPreprocess(std::ifstream&);

   //1. call generate
   void generate2(const std::string& _inputFile, const std::string& _outputFile);
};

#endif
