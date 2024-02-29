cmake_minimum_required(VERSION 3.1.0)
project(class_engine 
    LANGUAGES C 
    VERSION 2.0.1
    DESCRIPTION "Simple, modular 2D Game engine"
    HOMEPAGE_URL "https://classngin.com"
)
set(SubProjects 
    console
    core
    containers
    utils
    gui
)

set(CLS_INCLUDE_DIRS 
    "${PROJECT_SOURCE_DIR}/../include"
    "${PROJECT_SOURCE_DIR}/include"
)

set(SourceFiles 
    ${PROJECT_SOURCE_DIR}/cls_engine_main.c
    ${PROJECT_SOURCE_DIR}/cls_engine_terminal_ui.c
)

include_directories(${CLS_INCLUDE_DIRS})

add_library(${PROJECT_NAME} ${SourceFiles})

foreach(SubProject IN LISTS SubProjects)
    if(NOT TARGET ${SubProject})
        add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/${SubProject})
    endif()

    # Throws error if not set CMP0079 to NEW
    target_link_libraries(${PROJECT_NAME} PRIVATE ${SubProject}) 
endforeach()

