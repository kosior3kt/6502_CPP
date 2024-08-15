#ifndef __DEFINES_ASM
#define __DEFINES_ASM

#include <iostream>
#include <string>
#include <regex>
#include <format>
#include <unordered_set>

#define panic { std::cout<<"somthing went horribly wrong in function: "<<__FUNCTION__<<" in line:"<<__LINE__<<std::endl; return; }


static const std::unordered_set<std::string_view> instructions = {
    "ADC", "AND", "ASL", "BCC", "BCS", "BEQ", "BIT", "BMI", "BNE", "BPL",
    "BRK", "BVC", "BVS", "CLC", "CLD", "CLI", "CLV", "CMP", "CPX", "CPY",
    "DEC", "DEX", "DEY", "EOR", "INC", "INX", "INY", "JMP", "JSR", "LDA",
    "LDX", "LDY", "LSR", "NOP", "ORA", "PHA", "PHP", "PLA", "PLP", "ROL",
    "ROR", "RTS", "SBC", "SEC", "SED", "SEI", "STA", "STX", "STY", "TAX",
    "TAY", "TSX", "TXA", "TXS", "TYA", "RESET", "BRK", "NOP", "SLO", "RLA",
    "SRE", "RRA", "SAX", "DCP", "ISC", "RLA", "SLO", "SRE", "RRA", "ASR"
};

///TODO: change this into map with corresponding addressing modes - will be usefull for the next part, which validates
const std::vector<std::regex> address_regex
{
   std::regex(R"(^#\$([a-fA-F0-9]{1,2})$)"),                //immediete
   std::regex(R"(^\$([a-fA-F0-9]{1,2})$)"),                 //ZPA
   std::regex(R"(^\$([a-fA-F0-9]{1,2},X)$)"),               //ZPX
   std::regex(R"(^\$([a-fA-F0-9]{1,2},Y)$)"),               //ZPY
   std::regex(R"(^\$([a-fA-F0-9]{1,2})$)"),                 //ZP rel
   std::regex(R"(^\$([a-fA-F0-9]{3,4})$)"),                 //ABS
   std::regex(R"(^\$([a-fA-F0-9]{3,4},X)$)"),               //ABSX
   std::regex(R"(^\$([a-fA-F0-9]{3,4},Y)$)"),               //ABSY
   std::regex(R"(^\(\$([a-fA-F0-9]{3,4})\)$)"),             //IND ABS
   std::regex(R"(^\(\$([a-fA-F0-9]{1,2})\),X$)"),           //INDX
   std::regex(R"(^\(\$([a-fA-F0-9]{1,2})\),Y$)"),           //INDY
   std::regex(R"(^\(\$([a-fA-F0-9]{1,2}),X\)$)"),           //INDirectX
   std::regex(R"(^\(\$([a-fA-F0-9]{1,2}),Y\)$)"),           //INDirectY
};                                                    


namespace utils
{

   static void trimString(std::string& _str) noexcept
   {
         auto isNotSpace = [](const char ch) { return !std::isspace(static_cast<unsigned char>(ch)); };

         auto iterBeg = std::find_if(_str.cbegin(), _str.cend(), isNotSpace);
         auto iterEnd = std::find_if(_str.crbegin(), _str.crend(), isNotSpace).base();

         _str = (iterBeg <= iterEnd) ? std::string(iterBeg, iterEnd) : ""; //if only white characters return empty string, else return trimmed
   }

   static bool isAddress(const std::string_view str) noexcept
   {
      for(const auto& reg: address_regex)
      {
         if(std::regex_match(str.begin(), str.end(), reg))  return true;
      }
      return false;
   }

   static bool isInstruction(const std::string_view _str) noexcept
   {
      return (instructions.find(_str) != instructions.end());
   }

}


#endif //__DEFINES_ASM
