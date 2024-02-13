cmake_minimum_required(VERSION 3.1.0)
project(word_scape 
    LANGUAGES C 
    VERSION 0.0.1
    DESCRIPTION "WordScape2"
    HOMEPAGE_URL "https://ka05.net"
)

set(SourceFiles 
    ${PROJECT_SOURCE_DIR}/ws_main.c
    ${PROJECT_SOURCE_DIR}/ws_terminal_ui.c
)

include_directories(${CMAKE_CURRENT_LIST_DIR}/../include)

add_library(${PROJECT_NAME} ${SourceFiles})

target_link_libraries(${PROJECT_NAME} PRIVATE merci_engine) 


