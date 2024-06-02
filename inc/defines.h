#ifndef __DEFINES__
#define __DEFINES__

//glossary
using Byte = unsigned char;
using Word = unsigned short;
using u32 = unsigned int;
using s32 = int;

///flags for setting flags
constexpr int C_f = (1 << 0);
constexpr int Z_f = (1 << 1);
constexpr int I_f = (1 << 2);
constexpr int D_f = (1 << 3);
constexpr int B_f = (1 << 4);
constexpr int V_f = (1 << 5);
constexpr int N_f = (1 << 6);

#endif
