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
std::vector<token> Tokenizer::tokenize_firstPass(const std::vector<token>& _inputVec) noexcept
{
   std::vector<token> resultingVec = this->splitTokens(_inputVec);
   std::vector<token> returnVec{};

   
   for(const auto& [contents, type]: resultingVec)
   {
      if(contents.empty()) continue;

      token temp{};
      if(*(contents.end() - 1) == ':' && contents.size() >= 2)   //shuold be shifted, cause end returns after the last char?
      {
         std::cout<<"adding kown label";
         temp.type       = token::tokenType::labelDefinition;
         temp.contents   = std::string(contents.begin(), contents.end() - 1);
         utils::safevPCIncreament(vPC);
         knownLabels.emplace(label(std::string(contents.begin(), contents.end() - 1), vPC));   //TODO: IMPORTANT - check if vPC +1 or not
         --vPC;   ///safe to decrement here this way since not mutated after last increament
      }
      else if(utils::isAddress(contents))
      {
         temp.type       = token::tokenType::operand;
         temp.contents   = contents;
      }
      else if(utils::isInstruction(contents))
      {
         temp.type       = token::tokenType::instruction;
         temp.contents   = contents;
         if(utils::matches_any(contents, "JSR", "RTS"))   ///those instructions should take more vPC because reasons I guess (im actually not sure if thats even the case)
         {
            utils::safevPCIncreament(vPC);
            utils::safevPCIncreament(vPC);
         }
         else
         {
            utils::safevPCIncreament(vPC);
         }
      }
      else if(knownLabels.find(label{contents, 0}) != knownLabels.end())
      {
         temp.type       = token::tokenType::labelInstance;
         temp.contents   = contents;
      }
      else
      {
         temp.type       = token::tokenType::unresolved;
         temp.contents   = contents;
      }

      returnVec.push_back(temp); 
   }

   return returnVec;
}

void Tokenizer::tokenize_secondPass(std::vector<token>& _inputVec)noexcept
{
   for(auto& [val, type]: _inputVec)
   {
      if(type == token::tokenType::unresolved)  [[unlikely]]
      {
         if(knownLabels.find(label{val, 0}) != knownLabels.end())
         {
            type = token::tokenType::labelInstance;
         }
         else  [[unlikely]]
         {
            exit(-1);
         }
      }
   }
}



std::vector<token> Tokenizer::tokenize(const std::vector<token>& _inputVector) noexcept
{
   auto resVec = tokenize_firstPass(_inputVector);
   tokenize_secondPass(resVec);   
   return resVec;
}
