
set(NAME 
   AutisticAssembler)

add_executable(${NAME}
   main.cpp
   )

target_include_directories(${NAME}
   PUBLIC
   ${INC}
   ${COMMON_INC}
   )
