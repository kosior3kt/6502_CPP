set (TEST_SOURCES
   main.cpp
   test.hpp
   )

set (TEST_SOURCES_DEBUG
   main.cpp
   test.hpp
   test_fileLoading.cpp
   )

#first need to create tests I suppose

# if(ALTERNATIVE)
#    add_executable(test
#       ${TEST_SOURCES_DEBUG}
#       )
# else()
#    add_executable(test
#       ${TEST_SOURCES}
#       )
# endif()
#
# find_package(GTest CONFIG REQUIRED)
#
# target_link_libraries( test
#    CPU
#    GTest::gtest
#    )


