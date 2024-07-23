cmake_minimum_required(VERSION 3.15)
project(dupa CXX)

#this thing is used for different builds so that i cen test new solutinos without destroing old ones...
option(BUILD_LEGACY "build project in legacy mode for backwards compatibility" OFF)
option(VERBOSE "all the printing macros in code will show what's happening in memory" OFF)


if(BUILD_LEGACY)
   add_definitions(-DALTERNATIVE)
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

set(INC ${CMAKE_CURRENT_SOURCE_DIR}/inc/)
set(SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/)

#add_subdirectory(inc) #not needed for now
add_subdirectory(src)
add_subdirectory(test)

