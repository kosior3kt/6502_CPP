
add_library(Memory
   memory.cpp
   memory.h
   )
target_include_directories(Memory
   PUBLIC
   ${CMAKE_CURRENT_SOURCE_DIR}/../inc/
   )

add_library(CPU
   CPU.cpp
   CPU.h
   )

target_link_libraries(CPU
   Memory
   )

add_executable(${PROJECT_NAME} 
   main.cpp
   )

target_link_libraries(${PROJECT_NAME}
   CPU
   )
