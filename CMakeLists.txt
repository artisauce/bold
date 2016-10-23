cmake_minimum_required(VERSION 2.8.9)
project(maptest)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY build)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY build)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY build)
SET (CMAKE_CXX_FLAGS "-std=c++11")
#ADD_LIBRARY(SDL2 STATIC IMPORTED)
#SET_TARGET_PROPERTIES(SDL2 PROPERTIES
#    IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/libSDL2.a)
#-lm -lstdc++ incase those errors pop up again


if (${CMAKE_CXX_COMPILER_ID} STREQUAL Clang)
        set(FIPS_CLANG 1)
        message("---------- GOOD: C++ Compiler: Clang (FIPS_CLANG)")
    elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL GNU)
        set(FIPS_GCC 1)
        message("---------- BAD: C++ Compiler: GCC (FIPS_GCC)")
    elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
        set(FIPS_MSVC 1)
        message("---------- BAD: C++ Compiler: VStudio (FIPS_MSVC)")
    else()
        message("---------- BAD: C++ Compiler: Unknown")
    endif()

#Bring the headers, such as Student.h into the project
include_directories(include)
include_directories(${CMAKE_SOURCE_DIR}/include/sdl/)
include_directories(${CMAKE_SOURCE_DIR}/include/sdl_image/)

#Can manually add the sources using the set command as follows:
#set(SOURCES src/mainapp.cpp src/Student.cpp)

#However, the file(GLOB...) allows for wildcard additions:
file(GLOB SOURCES "src/*.cpp")

add_executable(maptest ${SOURCES})
#target_link_libraries(maptest ${CMAKE_SOURCE_DIR}/libSDL2_image.a)
target_link_libraries(maptest ${CMAKE_SOURCE_DIR}/libSDL2_image-2.0.so.0.0.1)
target_link_libraries(maptest ${CMAKE_SOURCE_DIR}/libSDL2.a)
target_link_libraries(maptest ${CMAKE_SOURCE_DIR}/libsndio.so.6.1)
target_link_libraries(maptest ${CMAKE_SOURCE_DIR}/libdl.so)
target_link_libraries(maptest ${CMAKE_SOURCE_DIR}/libpthread.so)

