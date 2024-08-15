#include "tokenizer.h"
#include <algorithm>
#include <sstream>
#include <regex>
#include <unordered_set>

static std::unordered_set<std::string_view> knowsLabels {};

// std::vector<token> Tokenizer::splitTokens(const std::vector<token>& _inputVec)const noexcept
// {
//    std::vector<token> resVec{};
//
//    for(auto x: _inputVec)  //not need to make it a reference since on average it's cheaper to make copy
//    {
//       std::istringstream stream(x.contents);
//
//       std::string temp;
//       while(stream >> temp)
//       {
//          utils::trimString(temp);   //is this needed?
//          if(!temp.empty()) [[likely]]
//             resVec.push_back(token(temp)); 
//       }
//    }
//
//    return resVec;
// }

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
std::vector<token> Tokenizer::tokenize(const std::vector<token>& _inputVec) const noexcept
{

   std::vector<token> resVec = this->splitTokens(_inputVec);
   std::vector<token> retVec{};

   
   for(auto tok: resVec)
   {
      std::string str = tok.contents;
      if(str.empty()) continue;

      token temp{};
      if(*(str.end() - 1) == ':' && str.size() >= 2)   //shuold be shifted, cause end returns after the last char?
      {
         ///std::cout<<"got to label\n";
         temp.type       = token::tokenType::label;
         temp.contents   = std::string(str.begin(), str.end() - 1);
         ///TODO: add this to label vec later when I figure out how I want to go about it
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
      }
      else if(knowsLabels.find(str) != knowsLabels.end())
      {
         temp.type       = token::tokenType::label;
         temp.contents   = str;
      }
      else
      {
         std::cout<<"unlucky very much bby from file: "<<__FILE__<<" in function: " << __FUNCTION__<<std::endl;
         exit(-1);
         //std::unreachable();   ///ofc my fucking linter can't recognize this...
      }

      retVec.push_back(temp); 
   }

   return retVec;
}

