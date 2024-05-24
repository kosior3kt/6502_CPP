set(CPU_SOURCES 
   memory.cpp 
   CPU.cpp 
   CPU_Instructions.cpp 
   CPU_Helper.cpp)

add_library(CPU
   ${CPU_SOURCES}
   )

add_executable(${PROJECT_NAME} 
   main.cpp
   )

target_include_directories(CPU
   PUBLIC
   ${INC}
   )

target_include_directories(${PROJECT_NAME}
   PUBLIC
   ${INC}
   )

target_link_libraries(${PROJECT_NAME}
   CPU
   )
