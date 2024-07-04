set(CPU_SOURCES 
   memory.cpp 
   CPU.cpp 
   CPU_Instructions.cpp 
   CPU_Helper.cpp
   Instructions/Load_store.cpp
   Instructions/Increment_decrement.cpp
   Instructions/Jumps_calls.cpp
   Instructions/Stack_operations.cpp
   Instructions/Register_transfers.cpp
   Instructions/Logical.cpp
   Instructions/Branches.cpp
   Instructions/Shifts.cpp
   Instructions/Arithmetics.cpp
   Instructions/Status_flags.cpp
   Instructions/System_functions.cpp
   )

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
