#ifndef __TEST__
#define __TEST__

#include "CPU.h"

#include <gtest/gtest.h>

namespace testHelper
{
   static bool basicFlagsUnused(const CPU &_original, const CPU &_copy)
   {
      return (
          _original.C == _copy.C && _original.B == _copy.B
          && _original.I == _copy.I && _original.D == _copy.D
          && _original.V == _copy.V
      );
   };
   static bool allFlagsUnchanged(const CPU &_original, const CPU &_copy)
   {
      return (
          _original.C == _copy.C && _original.B == _copy.B
          && _original.I == _copy.I && _original.D == _copy.D
          && _original.V == _copy.V && _original.N == _copy.N && _original.Z == _copy.Z
      );
   };
}

class TEST_6502 : public testing::Test
{
   public:
      CPU cpu_;
      Mem mem_;
      CPU copyCPU_;

      enum class Register
      {
         A,
         X,
         Y
      };

   protected:
      virtual void SetUp()
      {
         cpu_.Reset(mem_);
         copyCPU_ = cpu_;
      }

      virtual void TearDown() {}

   public:
      void test_LD(Byte _oper, Register _reg)
      {
         constexpr uint8_t ASSIGNED_CYCLES = 2;
         mem_.debug_set(0xFFFC, _oper);
         mem_.debug_set(0xFFFD, 0x69);
         auto cyclesLeft = cpu_.execute(ASSIGNED_CYCLES, mem_);

         switch(_reg)
         {
         case Register::A:
         {
            EXPECT_EQ((int)cpu_.A, 0x69);
            break;
         }
         case Register::X:
         {
            EXPECT_EQ((int)cpu_.X, 0x69);
            break;
         }
         case Register::Y:
         {
            EXPECT_EQ((int)cpu_.Y, 0x69);
            break;
         }
         default:
            break;
         }
         EXPECT_EQ(cyclesLeft, 0);
         EXPECT_FALSE((int)cpu_.Z);
         EXPECT_FALSE((int)cpu_.N);
         EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
      };

#ifdef __ALTERNATIVE__
      void test_LD_alternative(Byte _oper, Register _reg)
      {
         constexpr uint8_t ASSIGNED_CYCLES = 2;
         mem_.debug_set(0xFFFC, _oper);
         mem_.debug_set(0xFFFD, 0x69);
         auto cyclesLeft = cpu_.execute_alternative(ASSIGNED_CYCLES, mem_);

         switch(_reg)
         {
         case Register::A:
         {
            EXPECT_EQ((int)cpu_.A, 0x69);
            break;
         }
         case Register::X:
         {
            EXPECT_EQ((int)cpu_.X, 0x69);
            break;
         }
         case Register::Y:
         {
            EXPECT_EQ((int)cpu_.Y, 0x69);
            break;
         }
         default:
            break;
         }
         EXPECT_EQ(cyclesLeft, 0);
         EXPECT_FALSE((int)cpu_.Z);
         EXPECT_FALSE((int)cpu_.N);
         EXPECT_TRUE(testHelper::basicFlagsUnused(cpu_, copyCPU_));
      };
#endif

};


struct test{
   int va;
   test() = default;
   bool operator=(const test& _a){return va == _a.va;};
};

#endif
