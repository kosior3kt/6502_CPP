project(dupa CXX)
cmake_minimum_required(VERSION 3.15)


#this thing is used for different builds so that i cen test new solutinos without destroing old ones...
option(BUILD_TEST "tests future (hopefully) solutions" OFF)


if(BUILD_TEST)
   add_definitions(-DALTERNATIVE)
   message(STATUS "Building TEST version")
   set(CMAKE_BUILD_TYPE Debug)
else()
   message(STATUS "Building STABLE version")
   #set(CMAKE_BUILD_TYPE Debug)  #sometiems usefull...
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)

set(INC ${CMAKE_CURRENT_SOURCE_DIR}/inc/)
set(SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/)

#add_subdirectory(inc) #not needed for now
add_subdirectory(src)
add_subdirectory(test)

