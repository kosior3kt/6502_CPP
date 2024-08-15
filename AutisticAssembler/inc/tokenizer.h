#ifndef __TOKENIZER
#define __TOKENIZER

#include <vector>
#include <string>

#include "token.hpp"

///yeah, I just dont like the keyword class, how did you know?
///this thing will be, you guessed it - tokenizing the heck out of the code it gets


///yeah, thats global unscoped variable, where's the problem?
static long                      vPC{};
static std::vector<std::string>  labels{};

struct Tokenizer
{
          
   std::vector<token> splitTokens(const std::vector<token>& _inputVec)const noexcept;

   //2. tokenize
   std::vector<token> tokenize(const std::vector<token>& _inputVec)const noexcept;

};


#endif //__TOKENIZER
