cmake_minimum_required(VERSION 3.1.0)
project(core 
    LANGUAGES C 
    VERSION 0.0.1
)


add_compile_options(
    $<$<CONFIG:Debug>:-g>
)

set(SourceFiles 
    ${PROJECT_SOURCE_DIR}/mrc_memory.c
    ${PROJECT_SOURCE_DIR}/mrc_eng_container.c
    ${PROJECT_SOURCE_DIR}/mrc_modules.c
)

add_library(${PROJECT_NAME} ${SourceFiles})