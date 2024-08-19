#ifndef __AUTISTIC_ASM 
#define __AUTISTIC_ASM

#include "defines.h"
#include "parser.h"

#include "token.hpp"

struct ASM
{
   using line = token;
   //std::string fileContents_;    ///usefull
   std::vector<line> fileContents_;   //purely technically this shuold be at max a 2* line count, but this to TODO at this point
   
   Byte Data[MAX_MEM];           ///this thing is tossed around as a reference =3

   //5. final machine code generation
   void generateMachineCode(std::vector<token>& _inputVec);

   //1.1 preprocess - get rid of redundant stuff, and load program from file into a vector of strings
   void loadAndPreprocess(std::ifstream&);

   //1. call generate
   void generate(const std::string& _inputFile, const std::string& _outputFile);
};

#endif
