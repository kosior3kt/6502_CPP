#include <iostream>
#include <fstream>

using Byte = unsigned char;

struct memory 
{
   int version{};
   Byte data[1024*64]{};
}static mem_;

void fill(const uint8_t _ver, const uint8_t _filling)
{
   mem_.version = _ver;

   for(int i = 0; i < 1024 * 64; ++i)
   {
      mem_.data[i] = _filling;
   }
}

void fillAt(const uint16_t _loc, const uint8_t _val)
{
   mem_.data[_loc] = _val;
}

void generate(std::string_view _path)
{
   std::ofstream outputFile(_path);
   if(!outputFile.is_open()) {
      std::cout<<"unlucky, not working";
      return;
   }

   fill(69, 0);

   ///those two things should load 69 into A register - nice
   //FFFF   1
   //FFFE   2
   //FFFD   3
   //FFFC   4
   fillAt((1024*64 - 4), 0xA9);
   fillAt((1024*64 - 3), 0x69);
   fillAt((1024*64 - 2), 0xFF);

   outputFile.write(reinterpret_cast<char*>(&mem_), sizeof(mem_));
   outputFile.close();
}

/*
 * How it should work 
 *    1) we take a path to file as input
 *    2) we trim it from garbage 
 *    3) we parse it into memory of cpu
 *    4) we spit out a file that our processor can consume 
 */

///just an entry point here, go to asm.cpp for meat and juice UwU

int main(int argc, char** argv)
{
   ///TODO: change it into filesystem::path later on
   std::string fileName{"testFile"};

   if(argc != 2)
   {
      return 0;
   }

   fileName = argv[1];
   fileName += ".aa";
   generate(fileName);

   return 0;
}
