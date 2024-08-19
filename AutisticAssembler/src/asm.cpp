#include "asm.h"


void ASM::loadAndPreprocess(std::ifstream& _inputFile)
{
   if(!_inputFile.good()) $panic$

   std::string buf{};

   while(getline(_inputFile, buf))  
   {
      utils::trimString(buf);

      if(buf.empty()) continue;

      fileContents_.push_back(token(buf));
   }
}


void ASM::generateMachineCode(std::vector<token>& _inputVec)
{
   ///I could do two pass 
}


//this is the entry point for this assembly
void ASM::generate(const std::string& _inputFile, const std::string& _outputFile)
{
   std::ifstream inputFile(_inputFile);   //shuold be in binary mode?

   //Step 1
   ///it's better to handle strings here and just pass handles to files so we dont pass them in the mothods and create garbage in memory
   
   ///will call all of the things in here and just handle them      
   loadAndPreprocess(inputFile); //this mutates
   inputFile.close();
   
      
   //Step 2

   
}

