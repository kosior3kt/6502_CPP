#ifndef __PARSER
#define __PARSER


#include <complex>
#include <iostream>
#include <vector>
#include <string>
#include "defines.h"
#include <fstream>

///this thing is just taking contents of the file, then trimming it and packing into vector.

////no need to make it a struct. can be just namespace
///

class parser
{
   public:
   std::vector<std::string> lineVec_;

   void parse(std::string);   
   void trimm();
   std::vector<std::string>& getLines();

};


#endif
