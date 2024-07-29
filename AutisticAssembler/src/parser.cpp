#include "parser.h"
#include <stdio.h>

void parser::parse(std::string _path)
{
   std::ifstream sourceFile(_path);
   std::string buf{};
   while(getline(sourceFile, buf))
   {
      this->lineVec_.push_back(buf);
   }
}

void parser::trimm()
{
   if(this->lineVec_.empty())
   {
      std::cout<<"found empty vector array. did you call parse before?\n";
      exit(-1);
   }
   for(auto iter = this->lineVec_.begin(); iter != this->lineVec_.end(); )
   {
      const auto iterBeg = std::find_if(iter->cbegin(), iter->cend(), 
                                 [](const char ch) -> bool
                                 {
                                    return ch != ' ';
                                 });

      auto iterEnd = std::find_if(iter->crbegin(), iter->crend(), 
                                 [](const char ch) -> bool
                                 {
                                    return ch != ' ';
                                 });

      if(iterBeg == iterEnd.base())
      {
         iter = this->lineVec_.erase(iter);
         continue;
      }

      if (iterEnd.base() != iter->cend())
      {
          --iterEnd;
      }

      *iter = std::string(iterBeg, iterEnd.base());
      std::advance(iter, 1);
   }
}

std::vector<std::string>& parser::getLines() ///returning reference here is terrible idea
{
   return this->lineVec_;
}


