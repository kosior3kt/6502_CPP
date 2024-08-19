#ifndef __DEFINES_ASM
#define __DEFINES_ASM

#include <iostream>
#include <string>
#include <regex>
#include <format>
#include <unordered_set>
#include <map>


//////////////////////////////////////////////////////utils
#define $panic$ { std::cout<<"somthing went horribly wrong in function: "<<__FUNCTION__<<" in line:"<<__LINE__<<std::endl; return; };
#define $parsing_panic$ { std::cout<<"somthing went horribly wrong while parsing: "<<__FUNCTION__<<" in line:"<<__LINE__<<std::endl; return; };

//////////////////////////////////////////////////////common data
static const std::unordered_set<std::string_view> instructions = {
    "ADC", "AND", "ASL", "BCC", "BCS", "BEQ", "BIT", "BMI", "BNE", "BPL",
    "BRK", "BVC", "BVS", "CLC", "CLD", "CLI", "CLV", "CMP", "CPX", "CPY",
    "DEC", "DEX", "DEY", "EOR", "INC", "INX", "INY", "JMP", "JSR", "LDA",
    "LDX", "LDY", "LSR", "NOP", "ORA", "PHA", "PHP", "PLA", "PLP", "ROL",
    "ROR", "RTS", "SBC", "SEC", "SED", "SEI", "STA", "STX", "STY", "TAX",
    "TAY", "TSX", "TXA", "TXS", "TYA", "RESET", "BRK", "NOP", "SLO", "RLA",
    "SRE", "RRA", "SAX", "DCP", "ISC", "RLA", "SLO", "SRE", "RRA", "ASR"
};

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


// Define all addressing modes as an enum class
enum class AddressingMode 
{
    Immediate,        // #value
    ZeroPage,         // $00
    ZeroPageX,        // $00,X
    ZeroPageY,        // $00,Y
    Absolute,         // $0000
    AbsoluteX,        // $0000,X
    AbsoluteY,        // $0000,Y
    Indirect,         // ($0000)
    IndirectX,        // ($00,X)
    IndirectY,        // ($00),Y
    Accumulator,      // A
    Implied,          // Implicit
    Relative          // Branching instructions (e.g., BEQ, BNE)
};

//inline
// inline AdressingMode getAddrMode(std::istream& _os, const std::string& _val)
// {
//
//    if(_val == "")
//    {
//       
//    }
//    switch(_val)
//    {
//       case token::EMPTY:            os << "EMPTY";             break;
//       case token::labelInstance:    os << "labelInstance";     break;
//       case token::labelDefinition:  os << "labelDefinition";   break;
//       case token::variable:         os << "variable";          break;
//       case token::instruction:      os << "instruction";       break;
//       case token::operand:          os << "operand";           break;
//       case token::unresolved:       os << "unresolved";        break;
//    }
//    return os;
// }


// Overload the >> operator for AddressingMode
inline std::istream& operator>>(std::istream& is, AddressingMode& mode) {
    static const std::map<std::string, AddressingMode> modeMap = {
        {"Immediate", AddressingMode::Immediate},
        {"ZeroPage", AddressingMode::ZeroPage},
        {"ZeroPageX", AddressingMode::ZeroPageX},
        {"ZeroPageY", AddressingMode::ZeroPageY},
        {"Absolute", AddressingMode::Absolute},
        {"AbsoluteX", AddressingMode::AbsoluteX},
        {"AbsoluteY", AddressingMode::AbsoluteY},
        {"Indirect", AddressingMode::Indirect},
        {"IndirectX", AddressingMode::IndirectX},
        {"IndirectY", AddressingMode::IndirectY},
        {"Accumulator", AddressingMode::Accumulator},
        {"Implied", AddressingMode::Implied},
        {"Relative", AddressingMode::Relative}
    };

    std::string token;
    if (is >> token) {
        auto it = modeMap.find(token);
        if (it != modeMap.end()) {
            mode = it->second;
        } else {
            is.setstate(std::ios::failbit); // Set failbit on failure
        }
    }
    return is;
}

const std::map<AddressingMode, std::regex> address_regex_map = 
{
    {AddressingMode::Immediate, std::regex(R"(^#\$([a-fA-F0-9]{1,2})$)")},       // Immediate
    {AddressingMode::ZeroPage, std::regex(R"(^\$([a-fA-F0-9]{1,2})$)")},         // ZeroPage
    {AddressingMode::ZeroPageX, std::regex(R"(^\$([a-fA-F0-9]{1,2},X)$)")},      // ZeroPageX
    {AddressingMode::ZeroPageY, std::regex(R"(^\$([a-fA-F0-9]{1,2},Y)$)")},      // ZeroPageY
    {AddressingMode::Absolute, std::regex(R"(^\$([a-fA-F0-9]{3,4})$)")},         // Absolute
    {AddressingMode::AbsoluteX, std::regex(R"(^\$([a-fA-F0-9]{3,4},X)$)")},      // AbsoluteX
    {AddressingMode::AbsoluteY, std::regex(R"(^\$([a-fA-F0-9]{3,4},Y)$)")},      // AbsoluteY
    {AddressingMode::Indirect, std::regex(R"(^\(\$([a-fA-F0-9]{3,4})\)$)")},     // Indirect
    {AddressingMode::IndirectX, std::regex(R"(^\(\$([a-fA-F0-9]{1,2}),X\)$)")},  // IndirectX
    {AddressingMode::IndirectY, std::regex(R"(^\(\$([a-fA-F0-9]{1,2})\),Y$)")},  // IndirectY
};



namespace utils
{
   inline void safevPCIncreament(uint32_t& _val) noexcept
   {
      if(_val >= std::numeric_limits<uint32_t>::max())   [[unlikely]]
      {
         std::cerr<<"max number of operations reached - vPC would overflow\n";
         exit(-1);
      }
      ++_val;
   };

   inline void trimString(std::string& _str) noexcept
   {
         auto isNotSpace = [](const char ch) { return !std::isspace(static_cast<unsigned char>(ch)); };

         auto iterBeg = std::find_if(_str.cbegin(), _str.cend(), isNotSpace);
         auto iterEnd = std::find_if(_str.crbegin(), _str.crend(), isNotSpace).base();

         _str = (iterBeg <= iterEnd) ? std::string(iterBeg, iterEnd) : ""; //if only white characters return empty string, else return trimmed
   }

   inline bool isAddress(const std::string_view str) noexcept
   {
      for(const auto& reg: address_regex)
      {
         if(std::regex_match(str.begin(), str.end(), reg))  return true;
      }
      return false;
   }

   inline bool isInstruction(const std::string_view _str) noexcept
   {
      return (instructions.find(_str) != instructions.end());
   }

   inline bool matches_helper(const std::string&) noexcept
   {
       return false;
   }

   inline AddressingMode returnAddressingMode(const std::string_view _val) 
   {
       // Iterate through the map and check for regex matches
       for (const auto& [mode, regex] : address_regex_map) 
       {
           if (std::regex_match(_val.begin(), _val.end(), regex)) 
           {
               return mode;
           }
       }
       
       // If no match is found, throw an exception or handle as needed
       //throw std::invalid_argument("No matching addressing mode found.");
       exit(-1);
   }

   template <typename... Args>
   bool matches_helper(const std::string& original, const std::string& first, const Args&... rest) 
   {
       if (original == first) {
           return true;
       }
       return matches_helper(original, rest...);
   }

   template <typename... Args>
   bool matches_any(const std::string& original, const Args&... args) 
   {
       return matches_helper(original, args...);
   }
}


///////////////////////////(TODO: clean this mess later) some random defines 
// Mapping instruction names to legal addressing modes
const std::map<std::string, std::vector<AddressingMode>> legalAddressings
{
    {"LDA", { // Load Accumulator
        AddressingMode::Immediate, AddressingMode::ZeroPage, AddressingMode::ZeroPageX,
        AddressingMode::Absolute, AddressingMode::AbsoluteX, AddressingMode::AbsoluteY,
        AddressingMode::IndirectX, AddressingMode::IndirectY
    }},
    {"STA", { // Store Accumulator
        AddressingMode::ZeroPage, AddressingMode::ZeroPageX, AddressingMode::Absolute,
        AddressingMode::AbsoluteX, AddressingMode::AbsoluteY, AddressingMode::IndirectX,
        AddressingMode::IndirectY
    }},
    {"LDX", { // Load X Register
        AddressingMode::Immediate, AddressingMode::ZeroPage, AddressingMode::ZeroPageY,
        AddressingMode::Absolute, AddressingMode::AbsoluteY
    }},
    {"STX", { // Store X Register
        AddressingMode::ZeroPage, AddressingMode::ZeroPageY, AddressingMode::Absolute
    }},
    {"LDY", { // Load Y Register
        AddressingMode::Immediate, AddressingMode::ZeroPage, AddressingMode::ZeroPageX,
        AddressingMode::Absolute, AddressingMode::AbsoluteX
    }},
    {"STY", { // Store Y Register
        AddressingMode::ZeroPage, AddressingMode::ZeroPageX, AddressingMode::Absolute
    }},
    {"ADC", { // Add with Carry
        AddressingMode::Immediate, AddressingMode::ZeroPage, AddressingMode::ZeroPageX,
        AddressingMode::Absolute, AddressingMode::AbsoluteX, AddressingMode::AbsoluteY,
        AddressingMode::IndirectX, AddressingMode::IndirectY
    }},
    {"SBC", { // Subtract with Carry
        AddressingMode::Immediate, AddressingMode::ZeroPage, AddressingMode::ZeroPageX,
        AddressingMode::Absolute, AddressingMode::AbsoluteX, AddressingMode::AbsoluteY,
        AddressingMode::IndirectX, AddressingMode::IndirectY
    }},
    {"INC", { // Increment Memory
        AddressingMode::ZeroPage, AddressingMode::ZeroPageX, AddressingMode::Absolute,
        AddressingMode::AbsoluteX
    }},
    {"DEC", { // Decrement Memory
        AddressingMode::ZeroPage, AddressingMode::ZeroPageX, AddressingMode::Absolute,
        AddressingMode::AbsoluteX
    }},
    {"INX", { // Increment X Register
        AddressingMode::Implied
    }},
    {"INY", { // Increment Y Register
        AddressingMode::Implied
    }},
    {"DEX", { // Decrement X Register
        AddressingMode::Implied
    }},
    {"DEY", { // Decrement Y Register
        AddressingMode::Implied
    }},
    {"JMP", { // Jump
        AddressingMode::Absolute, AddressingMode::Indirect
    }},
    {"JSR", { // Jump to Subroutine
        AddressingMode::Absolute
    }},
    {"RTS", { // Return from Subroutine
        AddressingMode::Implied
    }},
    {"BEQ", { // Branch if Equal
        AddressingMode::Relative
    }},
    {"BNE", { // Branch if Not Equal
        AddressingMode::Relative
    }},
    {"BCC", { // Branch if Carry Clear
        AddressingMode::Relative
    }},
    {"BCS", { // Branch if Carry Set
        AddressingMode::Relative
    }},
    {"BPL", { // Branch if Positive
        AddressingMode::Relative
    }},
    {"BMI", { // Branch if Minus
        AddressingMode::Relative
    }},
    {"CLC", { // Clear Carry Flag
        AddressingMode::Implied
    }},
    {"SEC", { // Set Carry Flag
        AddressingMode::Implied
    }},
    {"CLD", { // Clear Decimal Mode
        AddressingMode::Implied
    }},
    {"SED", { // Set Decimal Mode
        AddressingMode::Implied
    }},
    {"PHA", { // Push Accumulator
        AddressingMode::Implied
    }},
    {"PLA", { // Pull Accumulator
        AddressingMode::Implied
    }},
    {"NOP", { // No Operation
        AddressingMode::Implied
    }},
    {"BRK", { // Break
        AddressingMode::Implied
    }},
    {"RTI", { // Return from Interrupt
        AddressingMode::Implied
    }}
};



#endif //__DEFINES_ASM
