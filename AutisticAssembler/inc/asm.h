#ifndef __AUTISTIC_ASM 
#define __AUTISTIC_ASM

#include "defines.h"
#include "parser.h"
#include "tokenizer.h"

#include "instructionCodes.h" ///TODO: move it somewhere - for now here

#include "token.hpp"

using line = token;  //TODO: can stay here for now, later move it into a namespace please =3333

namespace Asm
{
   //1. call generate
   void generate(const std::string& _inputFile, const std::string& _outputFile);

   namespace PRIV
   {
      //5. final machine code generation
      void generateMachineCode(const std::vector<token>& _inputVec, const std::string& _outputFile);

      //1.1 preprocess - get rid of redundant stuff, and load program from file into a vector of strings
      void loadAndPreprocess(std::ifstream&);
   }
   namespace DEBUG
   {
      [[maybe_unused]] void streamToFile(std::ofstream& _outputFile, const uint8_t _val);

      [[maybe_unused]] void debug_fillFileContents_(const std::vector<line>& _filler);

      [[maybe_unused]] std::vector<line> debug_getFileContents_();

      [[maybe_unused]] void debug_flush();
   }
};

#endif
