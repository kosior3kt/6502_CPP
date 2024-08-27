#ifndef __PARSER
#define __PARSER

#include <complex>
#include <iostream>
#include <vector>
#include <string>
#include "defines.h"
#include "token.hpp"
#include <fstream>


namespace Parser
{
   //3. resolve the labels 
   void resolveTokens(std::vector<token>& _inputVec, const label::labelSet& _labels);
   
};

#endif   //__PARSER
