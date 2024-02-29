cmake_minimum_required(VERSION 3.1.0)
project(core 
    LANGUAGES C 
    VERSION 0.0.1
)


add_compile_options(
    $<$<CONFIG:Debug>:-g>
)

set(SourceFiles 
    ${PROJECT_SOURCE_DIR}/cls_memory.c
    ${PROJECT_SOURCE_DIR}/cls_modules.c
    ${PROJECT_SOURCE_DIR}/cls_events.c
    ${PROJECT_SOURCE_DIR}/cls_timer.c
    ${PROJECT_SOURCE_DIR}/cls_data_container.c
)

add_library(${PROJECT_NAME} SHARED ${SourceFiles})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_LIST_DIR}/include)
