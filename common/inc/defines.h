#ifndef __DEFINES__
#define __DEFINES__

#include <iostream>


///when this is defined all the debug info's take effect
#ifdef VERBOSE
#define DEBUG_PRINT  
#endif


//glossary
using Byte = unsigned char;
using Word = unsigned short;
using u32 = unsigned int;
using s32 = int;

///we can have control of the size of memory, but I wouldn't recommend to touch this, since size of special pages is hardcoded anyways
static constexpr u32 MAX_MEM = 1024 * 64;

///flags for setting flags
constexpr int C_f = (1 << 0);
constexpr int Z_f = (1 << 1);
constexpr int I_f = (1 << 2);
constexpr int D_f = (1 << 3);
constexpr int B_f = (1 << 4);
constexpr int V_f = (1 << 6);
constexpr int N_f = (1 << 7);

/// abomination
template<typename T, typename... Args>
void HEX_PRINT_TO_BE_WRAPPED(T&& _first, Args&&... _rest)
{
   std::cout<<std::hex;
   std::cout<<std::forward<T>(_first)<<" ";

   if constexpr(sizeof...(_rest) > 0)
   {
      HEX_PRINT_TO_BE_WRAPPED(std::forward<Args>(_rest)...);
   }
   else
   {
      std::cout<<std::dec;      
      std::cout<<"\n";
   }
}


template<typename T, typename... Args>
void PRINT_TO_BE_WRAPPED(T&& _first, Args&&... _rest)
{
   std::cout<<std::forward<T>(_first)<<" ";

   if constexpr(sizeof...(_rest) > 0)
   {
      PRINT_TO_BE_WRAPPED(std::forward<Args>(_rest)...);
   }
   else
   {
      std::cout<<"\n";
   }
}

#ifdef DEBUG_PRINT
#define HEX_PRINT(...) HEX_PRINT_TO_BE_WRAPPED(__VA_ARGS__, "|||| from function:", __FUNCTION__);
#define PRINT(...)         PRINT_TO_BE_WRAPPED(__VA_ARGS__, "|||| from function:", __FUNCTION__);
#else 
#define HEX_PRINT(...)
#define PRINT(...)
#endif



///////////////LORD have mercy on my wicked soul

class bitset_f {
public:
    bitset_f(int _value) : value(_value) {}

    friend std::ostream& operator<<(std::ostream& os, const bitset_f& _val);

private:
    int value;

    static std::string formatWithQuotes(int _value);
};

inline std::string bitset_f::formatWithQuotes(int _value) {
    std::string binaryStr;
    
    while (_value > 0) {
        binaryStr.push_back((_value % 2) ? '1' : '0');
        _value /= 2;
    }

    std::reverse(binaryStr.begin(), binaryStr.end());

    for (int i = binaryStr.length() - 4; i > 0; i -= 4) {
        binaryStr.insert(i, "'");
    }
    return binaryStr;
}

// Overload the << operator for CustomInt class
inline std::ostream& operator<<(std::ostream& _os, const bitset_f& _val) {
    _os << bitset_f::formatWithQuotes(_val.value);
    return _os;
}



enum class adressingMode : uint8_t
{
   ACC,
   IMP,
   IM,
   ZP,
   ZPX,
   ZPY,
   REL,
   ABS,
   ABSX,
   ABSY,
   IND,
   INDX,
   INDY, 
};

#endif
