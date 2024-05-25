
add_executable(test
   main.cpp
   test.hpp
   test_LDA.cpp
   test_LDX.cpp
   test_LDY.cpp
   test_INC.cpp
   test_MultipleInstructions.cpp
   )

target_include_directories( test
   PUBLIC
   ${CMAKE_CURRENT_SOURCE_DIR}/../src/
   )

find_package(GTest CONFIG REQUIRED)


target_link_libraries(
   test
   CPU
   GTest::gtest
   )


