cmake_minimum_required(VERSION 3.1.0)
project(gui 
    LANGUAGES C 
    VERSION 0.0.1
)

add_compile_options(
    $<$<CONFIG:Debug>:-g>
)

set(SourceFiles 
    ${PROJECT_SOURCE_DIR}/mrc_graphics.c
    ${PROJECT_SOURCE_DIR}/mrc_graphics_terminal_ui.c
    ${PROJECT_SOURCE_DIR}/mrc_ui.c
    ${PROJECT_SOURCE_DIR}/mrc_ui_terminal_ui.c
)

find_package(SDL2 REQUIRED)

add_library(${PROJECT_NAME} ${SourceFiles})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_LIST_DIR}/include)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2)
