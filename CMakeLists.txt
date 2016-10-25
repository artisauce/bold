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
	set(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS_DEBUG} -g -O0 -g2 -gdwarf-2 -fexceptions")
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

include_directories(include)
include_directories(${CMAKE_SOURCE_DIR}/include/sdl/)
include_directories(${CMAKE_SOURCE_DIR}/include/sdl_image/)

#However, the file(GLOB...) allows for wildcard additions:
file(GLOB SOURCES "src/*.cpp")

add_executable(maptest ${SOURCES})
target_link_libraries(maptest ${CMAKE_SOURCE_DIR}/libs/libstdc++.so.6)
target_link_libraries(maptest ${CMAKE_SOURCE_DIR}/libs/libxkbcommon.so.0)
target_link_libraries(maptest ${CMAKE_SOURCE_DIR}/libs/libSDL2_image-2.0.so)
target_link_libraries(maptest ${CMAKE_SOURCE_DIR}/libs/libSDL2_image-2.0.so.0)
target_link_libraries(maptest ${CMAKE_SOURCE_DIR}/libs/libSDL2_image-2.0.so.0.0.1) #No way the system can do a matrix dodge now.
target_link_libraries(maptest ${CMAKE_SOURCE_DIR}/libs/libSDL2.so)
target_link_libraries(maptest ${CMAKE_SOURCE_DIR}/libs/libsndio.so.6.1)
target_link_libraries(maptest ${CMAKE_SOURCE_DIR}/libs/libdl.so.2)
target_link_libraries(maptest ${CMAKE_SOURCE_DIR}/libs/libpthread.so)
target_link_libraries(maptest ${CMAKE_SOURCE_DIR}/libs/librt.so.1)
target_link_libraries(maptest ${CMAKE_SOURCE_DIR}/libs/libm.so)
target_link_libraries(maptest ${CMAKE_SOURCE_DIR}/libs/libmvec_nonshared.a)
target_link_libraries(maptest ${CMAKE_SOURCE_DIR}/libs/libmvec.so.1)
