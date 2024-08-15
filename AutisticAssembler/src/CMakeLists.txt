###local defines
set(NAME 
   AutisticAssembler)

add_library(
   ${LIB_NAME}
   asm.cpp   
   parser.cpp
   tokenizer.cpp
)

add_executable(
   ${NAME}
   main.cpp
)


###yeah, they should both include this
target_include_directories(
   ${LIB_NAME}
   PUBLIC
   ${INC}
   ${COMMON_INC}
)

target_include_directories(
   ${NAME}
   PUBLIC
   ${INC}
   ${COMMON_INC}
)

###linking
target_link_libraries(
   ${NAME}
   PUBLIC
   ${LIB_NAME}
)

