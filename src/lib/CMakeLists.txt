set(SubProjects 
    console
    core
    utils
    gui
)

include_directories(${MRC_INCLUDE_DIRS})

foreach(SubProject IN LISTS SubProjects)
    if(NOT TARGET ${SubProject})
        add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/${SubProject})
    endif()

    # Throws error if not set CMP0079 to NEW
    target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE ${SubProject}) 
endforeach()

