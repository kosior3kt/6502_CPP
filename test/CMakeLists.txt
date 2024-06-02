set (TEST_SOURCES
   main.cpp
   test.hpp
   test_LDA.cpp
   test_LDX.cpp
   test_LDY.cpp
   test_INC.cpp
   test_DEC.cpp
   test_STA.cpp
   test_MultipleInstructions.cpp
   )

set(ALTERNATIVE_SOURCES
   test.hpp
   alternative_solution.cpp
   main.cpp
   )

add_executable(test
   ${TEST_SOURCES}
   #${ALTERNATIVE_SOURCES}
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


