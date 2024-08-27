#include <iostream>
#include <fstream>
#include "asm.h"


/*
 * How it should work 
 *    1) we take a path to file as input
 *    2) we trim it from garbage 
 *    3) we parse it into memory of cpu
 *    4) we spit out a file that our processor can consume 
 */



bool isExtensionValid(const std::string& _name)
{
   auto extensionBeg = std::find(_name.crbegin(), _name.crend(), '.');
   std::string extension{};

   if(extensionBeg == _name.crend())
   {
      ///TODO: change it into an error later
      std::cout<<"file doesn't seem to have any extension really\n";
      return false;
   }

   extension = std::string(extensionBeg.base() - 1, _name.end());

   if(extension != ".aa")
   {
      printf("we dont support this extension: %s, use \".aa\"\n", extension.c_str());
      return false;
   }

   return true;
}

std::string changeOrAddExtension_mut(const std::string& _name)
{
   auto extensionBeg = std::find(_name.rbegin(), _name.rend(), '.');
   std::string baseName{};

   if(extensionBeg == _name.crend())
   {
      baseName = _name;
   }
   else
   {
      baseName = std::string(_name. begin(), extensionBeg.base() - 1);  ///is this correct?
   }

   baseName += ".ab";
   
   std::cout<< baseName <<"\n";
   return baseName;
}


int main(int argc, char** argv)
{

   ///TODO: change it into filesystem::path later on
   std::string fileName{};

   if(argc != 2)
   {
      return 0;
   }

   //ASM my_asm;

   fileName = argv[1];
   
   std::string inputFile  = fileName;
   std::string outputFile = changeOrAddExtension_mut(fileName);

   if(!isExtensionValid(fileName))
   {
      ///idk do somthign here - maybe just return?
      return -1;
   }

   Asm::generate(inputFile, outputFile);

   return 0;
}
