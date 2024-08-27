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


struct label
{
   std::string name{};
   uint32_t    vPC{};
   label() : name(""), vPC(){};
   label(const std::string& _name, const uint32_t& _vPC): name(_name), vPC(_vPC){};
   label(const label& _other)
   {
      name = _other.name;
      vPC  = _other.vPC;
   }

   label& operator=(const label& _other)
   {
       name = _other.name;
      vPC  = _other.vPC;
      return *this;
   }

   bool operator==(const label& _lhs)
   {
      return (_lhs.name == this->name);
   }

   bool operator<(const label& _other)
   {
      if(vPC <= _other.vPC) return true;
      return false;
   }

   struct labelHash 
   {
      std::size_t operator()(const label& _other) const 
      {
        return std::hash<std::string>()(_other.name);
      }
   };

   struct labelEquality
   {
      std::size_t operator()(const label& _lhs, const label& _rhs) const 
      {
         return _lhs.name == _rhs.name;
      }
   };

   using labelSet =  std::unordered_set<label, label::labelHash, label::labelEquality>;

};


#endif //__TOKEN
