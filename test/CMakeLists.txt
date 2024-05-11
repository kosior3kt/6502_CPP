
add_executable(test
   test.cpp
   )

target_include_directories( test
   PUBLIC
   ${CMAKE_CURRENT_SOURCE_DIR}/../src/
   )

target_link_libraries(
   test
   CPU
   )


