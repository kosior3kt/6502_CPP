#ifndef __AUTISTIC_ASM 
#define __AUTISTIC_ASM

#include "defines.h"
#include "parser.h"

#include "token.hpp"

//What does this need to do?
//get file contents - this whuold be done in constructor



struct ASM
{
   using line = token;
   //std::string fileContents_;    ///usefull
   std::vector<line> fileContents_;   //purely technically this shuold be at max a 2* line count, but this to TODO at this point
   
   Byte Data[MAX_MEM];           ///this thing is tossed around as a reference =3

   ///should probably have insider Parser, Tokenizer and Analyzer
   //ASM(std::string_view _fileName);
   


   //5. final machine code generation
   void generateMachineCode();


   //1.1 preprocess - get rid of redundant stuff, and load program from file into a vector of strings
   void loadAndPreprocess(std::ifstream&);

   //1. call generate
   void generate(const std::string& _inputFile, const std::string& _outputFile);
};

#endif
