set (TEST_SOURCES
   main.cpp
   test.hpp
   test_parser.cpp
   )

set (TEST_SOURCES_DEBUG
   main.cpp
   test.hpp
   )


if(ALTERNATIVE)
   add_executable(
      test_asm
      ${TEST_SOURCES_DEBUG}
      )
   #add_compile_definitions(ALTERNATIVE)

else()
   add_executable(
      test_asm
      ${TEST_SOURCES}
      )
endif()

find_package(GTest CONFIG REQUIRED)


target_include_directories(
   test_asm
   PUBLIC
   ${INC}
   ${COMMON_INC}
   )

target_link_libraries(
   test_asm
   SourcesForAssembly
   GTest::gtest
   )


