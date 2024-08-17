#ifndef __TOKEN
#define __TOKEN


#include <string>
#include <inttypes.h>
#include "defines.hpp"


struct token
{

   std::string contents;

   enum tokenType : int8_t
   {
      EMPTY = -1,
      labelInstance,
      labelDefinition,
      variable,
      instruction,
      operand,
      unresolved,
   }type{EMPTY};

   friend std::ostream& operator<<(std::ostream& os, const token::tokenType& Token) noexcept
   {
      switch(Token)
      {
         case token::EMPTY:            os << "EMPTY";             break;
         case token::labelInstance:    os << "labelInstance";     break;
         case token::labelDefinition:  os << "labelDefinition";   break;
         case token::variable:         os << "variable";          break;
         case token::instruction:      os << "instruction";       break;
         case token::operand:          os << "operand";           break;
         case token::unresolved:       os << "unresolved";        break;
      }
      return os;
   }

   token(const std::string_view _val) : contents(_val), type(EMPTY){};
   token(const std::string_view _val, const tokenType _type) : contents(_val), type(_type){};

   token() = default;
   ~token() = default;
   //TODO: define rest of garbage 

   bool operator==(const token& other) const noexcept
   {
      return contents == other.contents;
   }
};

#endif //__TOKEN
