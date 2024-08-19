#ifndef __PARSER
#define __PARSER


#include <complex>
#include <iostream>
#include <vector>
#include <string>
#include "defines.h"
#include "token.hpp"
#include <fstream>



struct parser
{
   //std::vector<std::string> lineVec_;

   // void parse(std::string);   
   //void trim();
   // std::vector<std::string>& getLines();

   //3. resolve the labels 
   void resolveTokens(std::vector<token>& _inputVec, const label::labelSet& _labels);

   //4. validate, that such configuration is actually possible in the 6502 - adressing modes and branching range mostly
   void validateTokens();

};


#endif   //__PARSER
