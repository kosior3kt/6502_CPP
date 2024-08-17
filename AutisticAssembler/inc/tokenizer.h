#ifndef __TOKENIZER
#define __TOKENIZER

#include <vector>
#include <string>

#include "token.hpp"

///yeah, I just dont like the keyword class, how did you know?
///this thing will be, you guessed it - tokenizing the heck out of the code it gets


///yeah, thats global unscoped variable, where's the problem?
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

};

struct Tokenizer
{
   private:
   struct labelHash 
   {
      std::size_t operator()(const label& _other) const 
      {
        //return std::hash<std::string>()(_other.name) ^ std::hash<int>()(_other.vPC);
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
   public:


   static auto hash(const label& _label) -> size_t
   {
         size_t localHash{};
         for(const auto ch: _label.name)
         {
            localHash += localHash * (ch * ch) * std::abs(10 - ch);  ///god forgive me for this xD
         }
         return localHash;
   };

   static auto equal(const label& _lhs, const label& _rhs ) -> bool
   {
      return _lhs.name == _rhs.name;   
   };

   uint32_t             vPC{0};

   void safevPCIncreament(uint32_t& _val) const noexcept;

   std::unordered_set<label, labelHash, labelEquality> knownLabels;

 
   std::vector<token> splitTokens(const std::vector<token>& _inputVec)const noexcept;

   //2. tokenize
   std::vector<token> tokenize_firstPass(const std::vector<token>& _inputVec)noexcept;

   void tokenize_secondPass(std::vector<token>& _inputVec)noexcept;

};


#endif //__TOKENIZER
