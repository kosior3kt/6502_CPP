#include "parser.h"
#include <stdio.h>
#include <algorithm>

void parser::parse(std::string _path)
{
   std::ifstream sourceFile(_path);
   std::string buf{};
   while(getline(sourceFile, buf))
   {
      std::string temp;
      auto it = std::find_if(buf.begin(), buf.end(), 
                     [](const char _ch) -> bool
                     {
                        return _ch == ';';
                     });
      // if (it != buf.cend())   temp = std::string(buf.begin(), it);
      // else                    temp = buf;

      temp = it != buf.end() ? std::string(buf.begin(), it) : buf;
      this->lineVec_.push_back(temp);
   }
}

void parser::trim() 
{
    if (this->lineVec_.empty()) 
    {
        std::cout << "found empty vector array. did you call parse before?\n";
        return;
    }

    auto isNotSpace = [](const char ch) { return !std::isspace(static_cast<unsigned char>(ch)); };

    for (auto iter = this->lineVec_.begin(); iter != this->lineVec_.end(); ) 
    {
        auto iterBeg = std::find_if(iter->cbegin(), iter->cend(), isNotSpace);

        auto iterEnd = std::find_if(iter->crbegin(), iter->crend(), isNotSpace).base();

        if (iterBeg >= iterEnd) 
        {
            iter = this->lineVec_.erase(iter);
        } 
        else 
        {
            *iter = std::string(iterBeg, iterEnd);
            ++iter;
        }
    }
}

std::vector<std::string>& parser::getLines() ///returning reference here is terrible idea
{
   return this->lineVec_;
}


