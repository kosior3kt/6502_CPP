#ifndef __TEST__
#define __TEST__

#include "CPU.h"
#include <gtest/gtest.h>


class TEST_6502 : public testing::Test
{
public:
   CPU cpu_;
   Mem mem_;
   CPU copyCPU;

protected:

   virtual void SetUp(){
      cpu_.Reset(mem_);
      copyCPU = cpu_;
   }

   virtual void TearDown(){
   }
};

namespace testHelper{
   static bool flagsUnchanged(const CPU& _original, const CPU& _copy){
      return (_original.C == _copy.C &&
      _original.B == _copy.B &&
      _original.I == _copy.I &&
      _original.D == _copy.D &&
      _original.V == _copy.V);
   };
}

#endif
