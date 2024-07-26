#include "memory.h"

void Mem::initialise()
{
   for(u32 i = 0; i < MAX_MEM; ++i)
   {
      Data[i] = 0;
   }
}

Byte Mem::operator[](const u32 &_addr) const
{
   assert(_addr < MAX_MEM);
   return Data[_addr];
}

Byte &Mem::operator[](const u32 &_addr)
{
   assert(_addr < MAX_MEM);
   return Data[_addr];
}

void Mem::debug_set(const u32 &_addr, const u32 &_val)
{
   assert(_addr < MAX_MEM);
   Data[_addr] = _val;
   HEX_PRINT("location of memory ", _addr, "value of memory ", _val);
}

Byte Mem::debug_get(const u32 &_addr)
{
   assert(_addr < MAX_MEM);
   return Data[_addr];
}

void Mem::debug_dumpMemory(const std::string& _fileName){
   HEX_PRINT("generating memory map in the: ", _fileName);
   std::ofstream _file;
   _file.open(_fileName);
   if(!_file.is_open()){
      HEX_PRINT("unlucky, want able to generate file");
      return;
   } 
   _file<<std::hex;
   for(int i = 0; i < Mem::MAX_MEM; ++i)
   {
      _file << (int)Data[i] << " at the adress: " << i << "\n";   ///this construction flushes at the end of line
   }
   _file.close();
}

// ///so this thing should load progam state from memory. First 4 bytes will be for version and other BS. Then all CPU flags will be added
// ///then PC and SP values. Then rest of the memory will be raw dogged
// void Mem::loadFromFile(std::string_view _path)
// {
//    struct damn
//    {
//       Byte data[1024*64]{};
//       int version{};
//    };
//
//    damn dupa;
//    std::ifstream srcFile(_path, std::ios::binary);
//    if(!srcFile.is_open())
//    {
//       HEX_PRINT("unlucky, doesnt work =c");
//       return;
//    }
//
//    srcFile.read(reinterpret_cast<char*>(&dupa), sizeof(dupa));
//    HEX_PRINT("this is the general size of the file: ", sizeof(dupa));
//
//    HEX_PRINT("version if not casted and bitset_f: ", bitset_f(dupa.version));
//
//
//    for(int i = 0; i < 1024*64; ++i)
//    {
//       Data[i] = (Byte)dupa.data[i];
//    }
//    HEX_PRINT("this is the size of the data: ", sizeof Data);
//    HEX_PRINT("generating memory map...");
//    debug_dumpMemory(std::string(_path.begin(), _path.end()) + "_generated");
// }

void Mem::loadFromFile(std::string_view _path) {
    std::ifstream srcFile(_path.data(), std::ios::binary); // Open file in binary mode
    if (!srcFile.is_open()) {
        std::cerr << "Failed to open file: " << _path << std::endl;
        return;
    }

    // Read the version (first 4 bytes)
    uint32_t version;
    srcFile.read(reinterpret_cast<char*>(&version), sizeof(version));
    if (!srcFile) {
        std::cerr << "Error reading the version from the file." << std::endl;
        return;
    }

    // Output the version in hex to match the byte order in the file
    std::cout << "Version: " << std::hex << version << std::dec << std::endl;

    // Read the data (next 1024 * 64 bytes)
    srcFile.read(reinterpret_cast<char*>(Data), sizeof(Data));
    if (!srcFile) {
        std::cerr << "Error reading data from the file." << std::endl;
        return;
    }

    std::cout << "Data read successfully." << std::endl;

    // Close the file
    srcFile.close();

    std::cout << "Generating memory map..." << std::endl;
    debug_dumpMemory(std::string(_path.begin(), _path.end()) + "_generated");
}
