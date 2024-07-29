#include "test.hpp"

int main(){

   testing::InitGoogleTest();
   //printf("running main() from %s, from line number %d \n\n\n", __FILE__, __LINE__); ///whoah...
   return RUN_ALL_TESTS();
};


