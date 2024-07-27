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


void Mem::set(const u32& _addr, const u32& _val)
{
   assert(_addr < MAX_MEM);
   Data[_addr] = _val;
}

Byte Mem::at(const u32& _addr) const
{
   assert(_addr < MAX_MEM);
   return Data[_addr];
}

///TODO: change all of these cout things into a Logger later
void Mem::loadFromFile(std::string_view _path) {
    std::ifstream srcFile(_path.data(), std::ios::binary);

    if (!srcFile.is_open()) 
    {
        std::cerr << "Failed to open file: " << _path << std::endl;
        return;
    }

    // Read the version (first 4 bytes)   ----> format definition
    uint32_t version;
    srcFile.read(reinterpret_cast<char*>(&version), sizeof(version));
    if (!srcFile) 
    {
        std::cerr << "Error reading the version from the file." << std::endl;
        return;
    }

    srcFile.read(reinterpret_cast<char*>(Data), sizeof(Data));

    if (!srcFile) 
    {
        std::cerr << "Error reading data from the file." << std::endl;
        return;
    }

    ///std::cout << "Data read successfully." << std::endl;

    srcFile.close();

    ///std::cout << "Generating memory map..." << std::endl;
    ///debug_dumpMemory(std::string(_path.begin(), _path.end()) + "_generated");
}

void Mem::saveInFile(std::string_view _path)
{
   ///TODO: finish this later    
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
   HEX_PRINT("location of memory ", _addr, "value of memory ", Data[_addr]);
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

