cmake_minimum_required(VERSION 3.13.0)

#[==[ 
Fix Cmake issue with trying to link libraries to a target in 
a CMake list where the target is not defined in the list
]==]
if(POLICY CMP0079)
  cmake_policy(SET CMP0079 NEW)
endif()
set(CMAKE_COLOR_MAKEFILE ON)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_COLOR_DIAGNOSTICS ON)

set (OSBitness 32)
message("OSBitness: ${CMAKE_SIZEOF_VOID_P}")
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(OSBitness 64)
else()
    set(CMAKE_SIZEOF_VOID_P 8)
    set(OSBitness 64)
endif()

set(FullOutputDir "${CMAKE_SOURCE_DIR}/bin/${CMAKE_SYSTEM_NAME}${OSBitness}/${CMAKE_BUILD_TYPE}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${FullOutputDir}/static_libs")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${FullOutputDir}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${FullOutputDir}")

if(MSVC)
    # Fixes the issue of MSVC not exporting symbols and requiring 
    # a funny macro 
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
    set(BUILD_SHARED_LIBS TRUE)
endif()


# Extract version from ./src/include/cls_version.h
set(VERSION_REGEX "#define APP_VERSION[ \t]+\"(.+)\"")
file(STRINGS "${CMAKE_SOURCE_DIR}/src/include/cls_version.h"
    VERSION_STRING REGEX ${VERSION_REGEX})
string(REGEX REPLACE ${VERSION_REGEX} "\\1" VERSION_STRING "${VERSION_STRING}")


project(Test2
    # LANGUAGES CXX
    VERSION ${VERSION_STRING}
)

add_compile_options(
    $<$<CONFIG:Debug>:-Wall>
    $<$<CONFIG:Debug>:-Wextra>
    # To get rid of warning: missing initializer for field ‘x’ of ‘struct y’ [-Wmissing-field-initializers]
    $<$<CONFIG:Debug>:-Wno-missing-field-initializers> 
    
)

include_directories(src/include)
include_directories(src/app)

add_executable(${PROJECT_NAME} main.c)

add_subdirectory(${CMAKE_SOURCE_DIR}/src/lib)
add_subdirectory(${CMAKE_SOURCE_DIR}/src/app)
target_link_libraries(${PROJECT_NAME} PRIVATE class_engine word_scape)

add_custom_command(TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND /bin/sh "${CMAKE_SOURCE_DIR}/scripts/linux/post_build.sh" "${FullOutputDir}"
)