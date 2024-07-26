set (TEST_SOURCES
   main.cpp
   test.hpp
   test_LDX.cpp
   test_LDY.cpp
   test_INC.cpp
   test_DEC.cpp
   test_STA.cpp
   test_MISC.cpp
   test_JumpingInstructions.cpp
   test_circularTestCollection.cpp
   test_MultipleInstructions.cpp
   test_transfer.cpp
   test_stackOperations.cpp
   test_statusFlags.cpp
   test_logicalOperations.cpp
   test_branches.cpp
   test_LDA.cpp
   test_shifts.cpp
   test_arithmetics.cpp
   test_compare.cpp
   test_systemInstructions.cpp
   test_loop.cpp
   )

set (TEST_SOURCES_DEBUG
   main.cpp
   test.hpp
   test_loop.cpp
   )


if(ALTERNATIVE)
   add_executable(test
      ${TEST_SOURCES_DEBUG}
      )
   #add_compile_definitions(ALTERNATIVE)

else()
   add_executable(test
      ${TEST_SOURCES}
      )

endif()


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


