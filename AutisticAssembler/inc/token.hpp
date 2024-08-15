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
