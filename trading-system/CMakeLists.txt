cmake_minimum_required(VERSION 3.7)

project(tradingsystem)

set(CMAKE_VERBOSE_MAKEFILE ON)

if(MINGW)
    set(CMAKE_EXE_LINKER_FLAGS "-static")
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE "-s")
    add_definitions(-D _WIN32)
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -fPIC -std=c++17")

include_directories(include)
aux_source_directory(src SRC_FILES)

add_library(utf8cxx INTERFACE)
target_include_directories(utf8cxx INTERFACE utf8cxx/)

add_executable(tradingsystem ${SRC_FILES})
target_link_libraries(tradingsystem PUBLIC utf8cxx)