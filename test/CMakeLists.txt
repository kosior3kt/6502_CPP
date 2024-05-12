
add_executable(test
   main.cpp
   test.hpp
   test.cpp
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


