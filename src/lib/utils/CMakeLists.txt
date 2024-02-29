cmake_minimum_required(VERSION 3.1.0)
project(utils 
    LANGUAGES C 
    VERSION 0.0.1
)

add_compile_options(
    $<$<CONFIG:Debug>:-g>
)

set(SourceFiles 
    ${PROJECT_SOURCE_DIR}/cls_utils.c
    ${PROJECT_SOURCE_DIR}/cls_enums_to_string.c
    ${PROJECT_SOURCE_DIR}/cls_engine_utils.c
    ${PROJECT_SOURCE_DIR}/json.c
)

add_library(${PROJECT_NAME} ${SourceFiles})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_LIST_DIR}/include)