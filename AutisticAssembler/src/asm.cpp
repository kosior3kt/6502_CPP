
#include "asm.h"

/////////////////////jumpping sections
//====================================
//
//1. __local_definitions__
//2.  __implementation__
//3.  __DEBUG_implementation__
//4. __local__implementations__
//
//====================================


//TODO:  rethink if we even want to have this thing inhere (I mean fileContents_) - this seems like it shuold be just a
//       argumet but this way it's easier to test this

///TODO: do these things need to be static?

///////////////////// __local_definitions__
namespace
{
   using Byte = unsigned char;

   static std::vector<line> fileContents_;   //TODO: resize it right away - it is max 2* 

   struct memory 
   {
      int version{};
      Byte data[1024*64]{};
   }static mem_;

   void fillAt(const uint16_t _loc, const uint8_t _val);

   void fill(const uint8_t _ver, const uint8_t _filling);

   void generate(std::string_view _path);

}

///////////////////// __implementation__
namespace Asm
{
   void Asm::PRIV::loadAndPreprocess(std::ifstream& _inputFile) 
   {
      if(!_inputFile.good()) $panic$

      std::string buf{};

      while(getline(_inputFile, buf))  
      {
         utils::trimString(buf);

         if(buf.empty()) continue;

         fileContents_.push_back(token(buf));
      }
   }

///TODO: refactor me daddy (later)
   void Asm::PRIV::generateMachineCode(const std::vector<token>& _inputTokenVec, const std::string& _outputFile)
   {
      std::cout<<"generating machine code now. size of the vector being: " << _inputTokenVec.size() <<"\n";
      
      uint8_t toFile{};
      bool save = true;

      std::string prevIns{};

      int i = 0;

      for(const auto& [contents, type]: _inputTokenVec)
      {

         std::cout<<i<<"\n";
         save = true;
         if(type == token::tokenType::instruction)
         {
            prevIns = contents;
            save = false;
            ///we dont know addressing at this point so we can't save instruction here
         }
         else if(type == token::tokenType::operand)
         {

            ///TODO: declutter this steaming garbage pile
   ///std::map<std::string, std::vector<std::map<AddressingMode, uint8_t>>>
            if(prevIns.empty()) $parsing_panic$
            auto it = legalInstructionOPCodes.find(prevIns)->second;
            prevIns.clear();  ///should it happend here?

   ///std::vector<std::map<AddressingMode, uint8_t>>
            for(const auto& vec: it)
            {

   ///std::map<AddressingMode, uint8_t>
               for(const auto& tok: vec)
               {
   ///{first = AddressingMode, second = uint8_t}
                  auto temp_am = utils::returnAddressingMode(contents);
                  if(tok.first == temp_am)
                  {
                     //toFile = tok.second;

                     fillAt(0x8000 + i, tok.second);
                     ++i;

                     std::string toRet{};
                     auto removeAlphaNum = [&](const char _ch) mutable{
                        if(std::isalnum(_ch))
                        {
                           toRet += _ch;
                        }
                     };

                     std::ranges::for_each(contents.begin(), contents.end(), removeAlphaNum);

                     uint16_t res;


                     std::stringstream ss;
                     ss << std::hex << toRet;
                     ss >> res;
                     //res = 16384;


                     if(res > 255)
                     {
                        uint8_t lowerRes   = (res >> 0) & 0xFF;
                        uint8_t  higherRes = (res >> 8) & 0xFF;

                        std::cout<<"shifting bitts with the operand bigger than 255\n";

                        std::cout<<"this is lower bit: " << (int)lowerRes<< ", and this is higher bit: "<< (int)higherRes<<"\n";
      
                        std::cout<<"this is the res before shifting: "<< res <<"\n";

                        fillAt(0x8000 + i, lowerRes);
                        ++i;
                        fillAt(0x8000 + i, higherRes);
                        ++i;
                     }
                     else
                     {
                        fillAt(0x8000 + i, res);
                        ++i;
                     }

                     save = false;
                     ///what do we do in this case? 
                     ///what if instruction doesn't take operands?

                     break;
                  }
               }
            }
            
            ///should never be able to be here?
            //exit(-1);
            std::cout<<"this would normally crush\n";
         }
         else if(type == token::tokenType::labelDefinition)
         {
               continue; ///????, right???
         }
         else  ///all of the other things should be just a numbers (maybe labelDefinition tho...?) TODO: check this
         {     
               std::cout << "im here =3!";
               toFile = std::stoi(contents);
               ++i;
         }


         if(save)
         {
            std::cout<<"filling memeory location\n";
            fillAt(0x8000 + i, toFile);
            //streamToFile(outputFile, toFile);
         }
      }
      
      if(!prevIns.empty())
      {
         if(prevIns == "TXA")
         {
            fillAt(0x8000 + i, INS_TXA);
            ++i;
         }
         else if(prevIns == "TAX")
         {
            fillAt(0x8000 + i, INS_TAX);
            ++i;
         }
      }
      
      fillAt(0x8000 + i, INS_NOTHING);
      
      std::cout<<"got past this fucker\n";
   }

   //this is the entry point for this assembly
   void generate(const std::string& _inputFile, const std::string& _outputFile)
   {

      std::cout<<"started generating2\n";
      fill(69, 0);

      std::ifstream inputFile(_inputFile);   //shuold be in binary mode?

      //Step 1
      ///it's better to handle strings here and just pass handles to files so we dont pass them 
      ///in the mothods and create garbage in memory
      ///will call all of the things in here and just handle them      

      Asm::PRIV::loadAndPreprocess(inputFile); //this mutates
               
      inputFile.close();
      
      //Step 2
      auto [resVec, knownLabels] = Tokenizer::tokenize(fileContents_);

      Parser::resolveTokens(resVec, knownLabels);

      //p.validateTokens();
      Asm::PRIV::generateMachineCode(resVec, _outputFile);

      ::generate(_outputFile);
      //should be working now
   }
}


///////////////////// __DEBUG_implementation__
namespace Asm::DEBUG
{
   [[maybe_unused]]   
   void streamToFile(std::ofstream& _outputFile, const uint8_t _val)
   {
      std::cout<< std::ios::hex <<_val<<"\n";
      _outputFile<<_val;
   }

   [[maybe_unused]]   
   void debug_fillFileContents_(const std::vector<line>& _filler)
   {
      fileContents_ = _filler;   //does this do shallow copy or deep copy?
   }

   [[maybe_unused]]
   std::vector<line> debug_getFileContents_()
   {
      return fileContents_;
   }

   [[maybe_unused]]
   void debug_flush()
   {
      fileContents_.clear();
   }
}

///////////////////// __local__implementations__
namespace
{
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
      std::ofstream outputFile(_path, std::ios::binary);
      if(!outputFile.is_open()) {
         std::cout<<"unlucky, not working";
         return;
      }

      //fill(69, 0);

      ::fillAt((1024*64 - 4), 0x4C);
      ::fillAt((1024*64 - 3), 0x00);
      ::fillAt((1024*64 - 2), 0x80);

      int i = 0;
      for(const auto ch: mem_.data)
      {
         
         if(ch == 0) 
         {
            ++i;
            continue;
         }

         std::cout<<"this is data: " << (int)ch <<" at the position: " << i << "\n";
         ++i;
      }

      outputFile.write(reinterpret_cast<char*>(&mem_), sizeof(mem_));
      outputFile.close();
   }
}

