#ifndef __TOKENIZER
#define __TOKENIZER

#include <vector>
#include <string>

#include "token.hpp"

///yeah, I just dont like the keyword class, how did you know?
///this thing will be, you guessed it - tokenizing the heck out of the code it gets

struct Tokenizer
{
   public:
   ///TODO: at some point I want to make them const, but I dont want to mess with test yet
   std::vector<token> tokenize_firstPass(const std::vector<token>& _inputVec) noexcept;   
   void tokenize_secondPass(std::vector<token>& _inputVec) noexcept;

   public:

   uint32_t vPC{0};
   label::labelSet knownLabels;
   std::vector<token> splitTokens(const std::vector<token>& _inputVec)const noexcept;

   //2. tokenize
   std::vector<token> tokenize(const std::vector<token>& _inputVector) noexcept;

};


#endif //__TOKENIZER
