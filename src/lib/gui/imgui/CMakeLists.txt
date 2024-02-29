cmake_minimum_required(VERSION 3.1.0)
project(imgui 
    LANGUAGES CXX 
    VERSION 1.90.3
    DESCRIPTION "Dear ImGui"
    HOMEPAGE_URL "https://github.com/ocornut/imgui/tree/docking"
)

add_compile_options(
    $<$<CONFIG:Debug>:-g>
)

set(SourceFiles 
    ${PROJECT_SOURCE_DIR}/imgui.cpp
    ${PROJECT_SOURCE_DIR}/imgui_demo.cpp
    ${PROJECT_SOURCE_DIR}/imgui_draw.cpp
    ${PROJECT_SOURCE_DIR}/imgui_tables.cpp
    ${PROJECT_SOURCE_DIR}/imgui_widgets.cpp
    ${PROJECT_SOURCE_DIR}/backends/imgui_impl_sdl2.cpp
    ${PROJECT_SOURCE_DIR}/backends/imgui_impl_sdlrenderer2.cpp
)

add_library(${PROJECT_NAME} ${SourceFiles})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR})
