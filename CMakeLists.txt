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
#16.04
add_executable(maptest.16.04 ${SOURCES})
target_link_libraries(maptest.16.04 ${CMAKE_SOURCE_DIR}/libs/16.04/libSDL2_image-2.0.so.0)
target_link_libraries(maptest.16.04 ${CMAKE_SOURCE_DIR}/libs/16.04/libSDL2.so)
#target_link_libraries(maptest.16.04 ${CMAKE_SOURCE_DIR}/libs/16.04/libstdc++.so.6)
#target_link_libraries(maptest.16.04 ${CMAKE_SOURCE_DIR}/libs/16.04/libxkbcommon.so.0)
#target_link_libraries(maptest.16.04 ${CMAKE_SOURCE_DIR}/libs/16.04/libsndio.so.6.1)
#target_link_libraries(maptest.16.04 ${CMAKE_SOURCE_DIR}/libs/16.04/libdl.so.2)
#target_link_libraries(maptest.16.04 ${CMAKE_SOURCE_DIR}/libs/16.04/libpthread.so)
#target_link_libraries(maptest.16.04 ${CMAKE_SOURCE_DIR}/libs/16.04/libpthread.so.0)
#target_link_libraries(maptest.16.04 ${CMAKE_SOURCE_DIR}/libs/16.04/librt.so.1)
#target_link_libraries(maptest.16.04 ${CMAKE_SOURCE_DIR}/libs/16.04/libm.so)
#target_link_libraries(maptest.16.04 ${CMAKE_SOURCE_DIR}/libs/16.04/libm.so.6)
#target_link_libraries(maptest.16.04 ${CMAKE_SOURCE_DIR}/libs/16.04/libmvec_nonshared.a)
#target_link_libraries(maptest.16.04 ${CMAKE_SOURCE_DIR}/libs/16.04/libmvec.so.1)
#target_link_libraries(maptest.16.04 ${CMAKE_SOURCE_DIR}/libs/16.04/libgcc_s.so.1)
#target_link_libraries(maptest.16.04 ${CMAKE_SOURCE_DIR}/libs/16.04/libc.so.6)
#target_link_libraries(maptest.16.04 ${CMAKE_SOURCE_DIR}/libs/16.04/libpng12.so.0)
#target_link_libraries(maptest.16.04 ${CMAKE_SOURCE_DIR}/libs/16.04/libjpeg.so.8)
#target_link_libraries(maptest.16.04 ${CMAKE_SOURCE_DIR}/libs/16.04/libtiff.so.5)
#target_link_libraries(maptest.16.04 ${CMAKE_SOURCE_DIR}/libs/16.04/libwebp.so.5)
#target_link_libraries(maptest.16.04 ${CMAKE_SOURCE_DIR}/libs/16.04/libasound.so.2)
#target_link_libraries(maptest.16.04 ${CMAKE_SOURCE_DIR}/libs/16.04/libpulse.so.0)
#target_link_libraries(maptest.16.04 ${CMAKE_SOURCE_DIR}/libs/16.04/libX11.so.6)
#target_link_libraries(maptest.16.04 ${CMAKE_SOURCE_DIR}/libs/16.04/libXext.so.6)
#target_link_libraries(maptest.16.04 ${CMAKE_SOURCE_DIR}/libs/16.04/libXcursor.so.1)
#target_link_libraries(maptest.16.04 ${CMAKE_SOURCE_DIR}/libs/16.04/libXinerama.so.1)
#target_link_libraries(maptest.16.04 ${CMAKE_SOURCE_DIR}/libs/16.04/libXi.so.6)
#target_link_libraries(maptest.16.04 ${CMAKE_SOURCE_DIR}/libs/16.04/libXrandr.so.2)
#target_link_libraries(maptest.16.04 ${CMAKE_SOURCE_DIR}/libs/16.04/libXss.so.1)
#target_link_libraries(maptest.16.04 ${CMAKE_SOURCE_DIR}/libs/16.04/libXxf86vm.so.1)
#target_link_libraries(maptest.16.04 ${CMAKE_SOURCE_DIR}/libs/16.04/libwayland-client.so.0)
#target_link_libraries(maptest.16.04 ${CMAKE_SOURCE_DIR}/libs/16.04/libwayland-cursor.so.0)
#target_link_libraries(maptest.16.04 ${CMAKE_SOURCE_DIR}/libs/16.04/libwayland-egl.so.1)
#target_link_libraries(maptest.16.04 ${CMAKE_SOURCE_DIR}/libs/16.04/libbsd.so.0)
#target_link_libraries(maptest.16.04 ${CMAKE_SOURCE_DIR}/libs/16.04/libz.so.1)
#target_link_libraries(maptest.16.04 ${CMAKE_SOURCE_DIR}/libs/16.04/liblzma.so.5)
#target_link_libraries(maptest.16.04 ${CMAKE_SOURCE_DIR}/libs/16.04/libjbig.so.0)
#target_link_libraries(maptest.16.04 ${CMAKE_SOURCE_DIR}/libs/16.04/libjson-c.so.2)
#target_link_libraries(maptest.16.04 ${CMAKE_SOURCE_DIR}/libs/16.04/libpulsecommon-8.0.so)
#target_link_libraries(maptest.16.04 ${CMAKE_SOURCE_DIR}/libs/16.04/libdbus-1.so.3)
#target_link_libraries(maptest.16.04 ${CMAKE_SOURCE_DIR}/libs/16.04/libxcb.so.1)
#target_link_libraries(maptest.16.04 ${CMAKE_SOURCE_DIR}/libs/16.04/libXrender.so.1)
#target_link_libraries(maptest.16.04 ${CMAKE_SOURCE_DIR}/libs/16.04/libXfixes.so.3)
#target_link_libraries(maptest.16.04 ${CMAKE_SOURCE_DIR}/libs/16.04/libffi.so.6)
#target_link_libraries(maptest.16.04 ${CMAKE_SOURCE_DIR}/libs/16.04/libsystemd.so.0)
#target_link_libraries(maptest.16.04 ${CMAKE_SOURCE_DIR}/libs/16.04/libwrap.so.0)
#target_link_libraries(maptest.16.04 ${CMAKE_SOURCE_DIR}/libs/16.04/libsndfile.so.1)
#target_link_libraries(maptest.16.04 ${CMAKE_SOURCE_DIR}/libs/16.04/libasyncns.so.0)
#target_link_libraries(maptest.16.04 ${CMAKE_SOURCE_DIR}/libs/16.04/libXau.so.6)
#target_link_libraries(maptest.16.04 ${CMAKE_SOURCE_DIR}/libs/16.04/libXdmcp.so.6)
#target_link_libraries(maptest.16.04 ${CMAKE_SOURCE_DIR}/libs/16.04/libselinux.so.1)
#target_link_libraries(maptest.16.04 ${CMAKE_SOURCE_DIR}/libs/16.04/libgcrypt.so.20)
#target_link_libraries(maptest.16.04 ${CMAKE_SOURCE_DIR}/libs/16.04/libnsl.so.1)
#target_link_libraries(maptest.16.04 ${CMAKE_SOURCE_DIR}/libs/16.04/libFLAC.so.8)
#target_link_libraries(maptest.16.04 ${CMAKE_SOURCE_DIR}/libs/16.04/libvorbisenc.so.2)
#target_link_libraries(maptest.16.04 ${CMAKE_SOURCE_DIR}/libs/16.04/libresolv.so.2)
#target_link_libraries(maptest.16.04 ${CMAKE_SOURCE_DIR}/libs/16.04/libpcre.so.3)
#target_link_libraries(maptest.16.04 ${CMAKE_SOURCE_DIR}/libs/16.04/libgpg-error.so.0)
#target_link_libraries(maptest.16.04 ${CMAKE_SOURCE_DIR}/libs/16.04/libogg.so.0)
#target_link_libraries(maptest.16.04 ${CMAKE_SOURCE_DIR}/libs/16.04/libvorbis.so.0)
#14.04
add_executable(maptest.14.04 ${SOURCES})
target_link_libraries(maptest.14.04 ${CMAKE_SOURCE_DIR}/libs/14.04/libSDL2-2.0.so.0)
target_link_libraries(maptest.14.04 ${CMAKE_SOURCE_DIR}/libs/14.04/libSDL2_image-2.0.so.0)




















