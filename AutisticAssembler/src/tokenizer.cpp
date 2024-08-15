#include "tokenizer.h"
#include <algorithm>
#include <sstream>
#include <regex>
#include <unordered_set>


std::vector<token> Tokenizer::splitTokens(const std::vector<token>& _inputVec)const noexcept
{
   std::vector<token> resVec{};

   for(auto x: _inputVec)  //not need to make it a reference since on average it's cheaper to make copy
   {
      std::string buf{};
      for(const auto ch: x.contents)
      {
         if(!std::isspace(ch))
         {
            buf += ch;
         }
         else if(!buf.empty())
         {
            resVec.push_back(token(buf));
            buf = "";
         }
      }
      if(!buf.empty())
      {
         resVec.push_back(token(buf));
      }
   }

   return resVec;
}


///this method does 2 things - splits lines into proper tokens and then assigns correct type to them
std::vector<token> Tokenizer::tokenize_firstPass(const std::vector<token>& _inputVec) const noexcept
{

   std::vector<token> resVec = this->splitTokens(_inputVec);
   std::vector<token> retVec{};

   
   for(auto tok: resVec)
   {
      std::string str = tok.contents;
      if(str.empty()) continue;

      token temp{};
      ///TODO: check if this mothersucker is not a variable or sth ;v
      if(*(str.end() - 1) == ':' && str.size() >= 2)   //shuold be shifted, cause end returns after the last char?
      {
         temp.type       = token::tokenType::labelDefinition;
         temp.contents   = std::string(str.begin(), str.end() - 1);
         knownLabels.emplace(label(std::string(str.begin(), str.end() - 1), vPC));
      }
      else if(utils::isAddress(str))
      {
         temp.type       = token::tokenType::operand;
         temp.contents   = str;
      }
      else if(utils::isInstruction(str))
      {
         temp.type       = token::tokenType::instruction;
         temp.contents   = str;
         ++vPC;   //make it a safe increment later?
                  //take into consideration that some instruction do +2
      }
      else if(knownLabels.find(label{str, 0}) != knownLabels.end())
      {
         temp.type       = token::tokenType::labelInstance;
         temp.contents   = str;
      }
      else
      {
         ///this still may be just a predefined lable on first pass
         //std::cout<<"unlucky very much bby from file: "<<__FILE__<<" in function: " << __FUNCTION__<<std::endl;
         //exit(-1);
         //std::unreachable();   ///ofc my fucking linter can't recognize this...
         
         temp.type       = token::tokenType::unresolved;
         temp.contents   = str;
      }

      retVec.push_back(temp); 
   }

   return retVec;
}

void Tokenizer::tokenize_secondPass(std::vector<token>& _inputVec)const noexcept
{
   for(auto& [val, type]: _inputVec)
   {
      if(type == token::tokenType::unresolved)  [[unlikely]]
      {
         if(knownLabels.find(label{val, 0}) != knownLabels.end())
         {
            type = token::tokenType::labelInstance;
         }
      }
   }
}
