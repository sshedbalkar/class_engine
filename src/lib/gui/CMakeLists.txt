cmake_minimum_required(VERSION 3.1.0)
project(gui 
    LANGUAGES CXX 
    VERSION 0.0.1
)

add_compile_options(
    $<$<CONFIG:Debug>:-g>
)

set(SourceFiles 
    ${PROJECT_SOURCE_DIR}/cls_graphics.c
    ${PROJECT_SOURCE_DIR}/cls_graphics_terminal_ui.c
    ${PROJECT_SOURCE_DIR}/cls_ui.cpp
    ${PROJECT_SOURCE_DIR}/cls_ui_terminal_ui.c
)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_library(${PROJECT_NAME} ${SourceFiles})

target_include_directories(${PROJECT_NAME} PRIVATE 
${CMAKE_CURRENT_LIST_DIR}/include
${CMAKE_CURRENT_LIST_DIR}/imgui
${CMAKE_CURRENT_LIST_DIR}/imgui/backends
)

target_link_libraries(${PROJECT_NAME} PRIVATE 
core 
console 
SDL2::SDL2
)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/imgui)
target_link_libraries(${PROJECT_NAME} PUBLIC imgui)
