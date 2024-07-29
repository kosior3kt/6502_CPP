#ifndef __AUTISTIC_ASM 
#define __AUTISTIC_ASM

#include "defines.h"
#include "parser.h"

//What does this need to do?
//get file contents - this whuold be done in constructor
//
struct ASM
{
   std::string fileContents_;
   Byte Data[MAX_MEM];  ///this thing is tossed around as a reference =3

   ///should probably have insider Parser, Tokenizer and Analyzer
   ASM(std::string_view _fileName);
   
   
};

#endif
