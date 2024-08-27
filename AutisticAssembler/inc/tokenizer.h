#ifndef __TOKENIZER
#define __TOKENIZER

#include <vector>
#include <string>

#include "token.hpp"

///yeah, I just dont like the keyword class, how did you know?
///this thing will be, you guessed it - tokenizing the heck out of the code it gets

namespace Tokenizer
{
   std::vector<token> splitTokens(const std::vector<token>& _inputVec) noexcept;

   //2. tokenize
   std::tuple<std::vector<token>, label::labelSet>  tokenize(const std::vector<token>& _inputVector) noexcept;

   namespace PRIV
   {
      std::vector<token> tokenize_firstPass(const std::vector<token>& _inputVec) noexcept;   
      void tokenize_secondPass(std::vector<token>& _inputVec) noexcept;
   }

   namespace DEBUG
   {
      [[maybe_unused]] void debug_flush();
   }
};


#endif //__TOKENIZER
