#include "parser.h"
#include <stdio.h>
#include <algorithm>

bool isAMValidForIns(const std::string& _ins, const AddressingMode& _am)
{
   auto legalInsVec = legalAddressings.find(_ins);

   ///shuold panic prolly
   if(legalInsVec == legalAddressings.end()) {exit(-1);}

   for(const auto& instruction: legalInsVec->second)
   {
      if(instruction == _am) return true;
   }

   return false;
}

///soooo... this thing should just look into the token vector for lables, then search what address in memory they should correspond, and then insert this number
//changed my mind - this isn't gonna be this easy, it depends what is the instruction that label works on...
//maybe this thing shuold be just doing virtual programm counter???
void parser::resolveTokens(std::vector<token>& _inputVec, const label::labelSet& _labels)
{
   uint32_t vPC{0};
   std::string previousInstruction{};

   for(auto& tok: _inputVec)
   {
      //if(tok.type != token::labelInstance) continue;

      switch(tok.type)
      {
         case token::EMPTY:
         case token::unresolved:       ///TODO: handle this case
               ///maybe rise error here?
         case token::variable:         ///unused for now, but might use it one day(and shuoldnt be possible here)
         case token::labelDefinition:  ///w.e prolly just break
            break;
         case token::instruction:      ///this is nice, we want to save this one, so that we can see if it has a operand and if it's the corret addressing mode
         {
            ///TODO: some instructions need a value, so I will need to take care of that later
            utils::safevPCIncreament(vPC);
            if(utils::matches_any(tok.contents.c_str(), "JSR", "RTS"))
            {
               utils::safevPCIncreament(vPC);   ///in this case it should be incremented twice
            }
            previousInstruction = tok.contents;
            break;
         }
         case token::labelInstance:    ///this is juicy we want to match against this, resolve it & then change it into operand depending on prev instruction
         {
            ///TODO: take care of relative indirect and indexed addressing that label can signify. for now it's just absolute and relative
            //1. check if previous instruction exists - otherwise we have nothing to do here and there is parsing error   
            if(previousInstruction.empty())  {$parsing_panic$} 

               
            //2. match against branching methods. For now I will only support relative shift in here
            if(!utils::matches_any(previousInstruction, "BNE", "BEQ", "BCC", "BCS", "BNE", "BMI", "BPL", "BVC", "BVS")) {$parsing_panic$}
            
            utils::safevPCIncreament(vPC);   ///i think it has to be after the shift has been counted

            int shift = (*_labels.find(label{tok.contents, 0})).vPC - vPC;

            //if(shift > 0) --shift;  //it iz what it iz

            tok.contents = std::to_string(shift); //TODO: uncomment this later
            //std::cout << shift <<std::endl;
            tok.type = token::variable;

            break;
         }
         case token::operand:          ///TODO: match for the right instruction and save it's type somewhere 
         {
            utils::safevPCIncreament(vPC);
            const auto am = utils::returnAddressingMode(tok.contents);

            if(!isAMValidForIns(previousInstruction, am))  {$parsing_panic$};

            if(am == AddressingMode::Absolute ||
               am == AddressingMode::AbsoluteX ||
               am == AddressingMode::AbsoluteY ||
               am == AddressingMode::Indirect)
            {
               utils::safevPCIncreament(vPC);
            }
            
            break;
         }
      }
   }
}


