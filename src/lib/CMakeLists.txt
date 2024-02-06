cmake_minimum_required(VERSION 3.1.0)
project(merci_engine 
    LANGUAGES C 
    VERSION 2.0.1
    DESCRIPTION "Simple, modular 2D Game engine"
    HOMEPAGE_URL "https://ka05.net"
)
set(SubProjects 
    console
    core
    containers
    utils
    gui
)

set(SourceFiles 
    ${PROJECT_SOURCE_DIR}/merci_engine.c
)

include_directories(${MRC_INCLUDE_DIRS})

add_library(${PROJECT_NAME} ${SourceFiles})

foreach(SubProject IN LISTS SubProjects)
    if(NOT TARGET ${SubProject})
        add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/${SubProject})
    endif()

    # Throws error if not set CMP0079 to NEW
    target_link_libraries(${PROJECT_NAME} PRIVATE ${SubProject}) 
endforeach()

