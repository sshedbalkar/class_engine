cmake_minimum_required(VERSION 3.1.0)
project(console 
    # LANGUAGES C 
    VERSION 0.0.1
)

include_directories(${CMAKE_SOURCE_DIR}/src/include)

set(SourceFiles 
    ${PROJECT_SOURCE_DIR}/console.c
)

add_library(${PROJECT_NAME} SHARED ${SourceFiles})