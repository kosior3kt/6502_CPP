set(INC ${CMAKE_CURRENT_SOURCE_DIR}/inc/)
set(SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/)

###NAMES FOR SOURCE
set(LIB_NAME 
   SourcesForAssembly)

add_subdirectory(src)

add_subdirectory(test)

