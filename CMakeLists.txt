cmake_minimum_required(VERSION 3.15)
project(dupa CXX)

#this thing is used for different builds so that i cen test new solutinos without destroing old ones...
option(ALTERNATIVE "build project in alternative (debug) mode " OFF)
option(VERBOSE "all the printing macros in code will show what's happening in memory" OFF)

option(ADD_EXEC "this is for creating executables" OFF)

if(ALTERNATIVE)
   # add_definitions(-DALTERNATIVE)
   message(STATUS "Building LEGACY version")
   set(CMAKE_BUILD_TYPE Debug)
else()
   message(STATUS "Building STABLE version")
   set(CMAKE_BUILD_TYPE Debug)  #sometiems usefull...
endif()

if(VERBOSE)
   add_definitions(-DVERBOSE)
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)

set(COMMON_INC ${CMAKE_CURRENT_SOURCE_DIR}/common/inc/)

add_subdirectory(ProcessorModel)
