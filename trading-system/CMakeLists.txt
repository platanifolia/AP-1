cmake_minimum_required(VERSION 3.0)

project(tradingsystem LANGUAGES CXX)

set(CMAKE_VERBOSE_MAKEFILE ON)

# list(APPEND flags "-fPIC" "-Wall" "-static")
# message("C++ compiler flags: ${CMAKE_CXX_FLAGS}")
# if(NOT WIN32)
#   list(APPEND flags "-Wextra" "-Wpedantic")
# endif()

if(MINGW)
    set(CMAKE_EXE_LINKER_FLAGS "-static")
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE "-s")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -fPIC -std=c++17")

include_directories(include)
aux_source_directory(src SRC_FILES)



add_executable(tradingsystem ${SRC_FILES})