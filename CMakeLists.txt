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
target_link_libraries(maptest ${CMAKE_SOURCE_DIR}/libs/libpthread.so.0)
target_link_libraries(maptest ${CMAKE_SOURCE_DIR}/libs/librt.so.1)
target_link_libraries(maptest ${CMAKE_SOURCE_DIR}/libs/libm.so)
target_link_libraries(maptest ${CMAKE_SOURCE_DIR}/libs/libm.so.6)
target_link_libraries(maptest ${CMAKE_SOURCE_DIR}/libs/libmvec_nonshared.a)
target_link_libraries(maptest ${CMAKE_SOURCE_DIR}/libs/libmvec.so.1)
target_link_libraries(maptest ${CMAKE_SOURCE_DIR}/libs/libgcc_s.so.1)
target_link_libraries(maptest ${CMAKE_SOURCE_DIR}/libs/libc.so.6)
target_link_libraries(maptest ${CMAKE_SOURCE_DIR}/libs/libpng12.so.0)
target_link_libraries(maptest ${CMAKE_SOURCE_DIR}/libs/libjpeg.so.8)
target_link_libraries(maptest ${CMAKE_SOURCE_DIR}/libs/libtiff.so.5)
target_link_libraries(maptest ${CMAKE_SOURCE_DIR}/libs/libwebp.so.5)
target_link_libraries(maptest ${CMAKE_SOURCE_DIR}/libs/libasound.so.2)
target_link_libraries(maptest ${CMAKE_SOURCE_DIR}/libs/libpulse.so.0)
target_link_libraries(maptest ${CMAKE_SOURCE_DIR}/libs/libX11.so.6)
target_link_libraries(maptest ${CMAKE_SOURCE_DIR}/libs/libXext.so.6)
target_link_libraries(maptest ${CMAKE_SOURCE_DIR}/libs/libXcursor.so.1)
target_link_libraries(maptest ${CMAKE_SOURCE_DIR}/libs/libXinerama.so.1)
target_link_libraries(maptest ${CMAKE_SOURCE_DIR}/libs/libXi.so.6)
target_link_libraries(maptest ${CMAKE_SOURCE_DIR}/libs/libXrandr.so.2)
target_link_libraries(maptest ${CMAKE_SOURCE_DIR}/libs/libXss.so.1)
#target_link_libraries(maptest ${CMAKE_SOURCE_DIR}/libXxf86vm.so.1)
#target_link_libraries(maptest ${CMAKE_SOURCE_DIR}/libwayland-client.so.0)
#target_link_libraries(maptest ${CMAKE_SOURCE_DIR}/libwayland-cursor.so.0)
#target_link_libraries(maptest ${CMAKE_SOURCE_DIR}/libwayland-egl.so.1)
#target_link_libraries(maptest ${CMAKE_SOURCE_DIR}/libbsd.so.0)
#target_link_libraries(maptest ${CMAKE_SOURCE_DIR}/libz.so.1)
#target_link_libraries(maptest ${CMAKE_SOURCE_DIR}/liblzma.so.5)
#target_link_libraries(maptest ${CMAKE_SOURCE_DIR}/libjbig.so.0)
#target_link_libraries(maptest ${CMAKE_SOURCE_DIR}/libjson-c.so.2)
#target_link_libraries(maptest ${CMAKE_SOURCE_DIR}/libpulsecommon-8.0.so)
#target_link_libraries(maptest ${CMAKE_SOURCE_DIR}/libdbus-1.so.3)
#target_link_libraries(maptest ${CMAKE_SOURCE_DIR}/libxcb.so.1)
#target_link_libraries(maptest ${CMAKE_SOURCE_DIR}/libXrender.so.1)
#target_link_libraries(maptest ${CMAKE_SOURCE_DIR}/libXfixes.so.3)
#target_link_libraries(maptest ${CMAKE_SOURCE_DIR}/libffi.so.6)
#target_link_libraries(maptest ${CMAKE_SOURCE_DIR}/libsystemd.so.0)
#target_link_libraries(maptest ${CMAKE_SOURCE_DIR}/libwrap.so.0)
#target_link_libraries(maptest ${CMAKE_SOURCE_DIR}/libsndfile.so.1)
#target_link_libraries(maptest ${CMAKE_SOURCE_DIR}/libasyncns.so.0)
#target_link_libraries(maptest ${CMAKE_SOURCE_DIR}/libXau.so.6)
#target_link_libraries(maptest ${CMAKE_SOURCE_DIR}/libXdmcp.so.6)
#target_link_libraries(maptest ${CMAKE_SOURCE_DIR}/libselinux.so.1)
#target_link_libraries(maptest ${CMAKE_SOURCE_DIR}/libgcrypt.so.20)
#target_link_libraries(maptest ${CMAKE_SOURCE_DIR}/libnsl.so.1)
#target_link_libraries(maptest ${CMAKE_SOURCE_DIR}/libFLAC.so.8)
#target_link_libraries(maptest ${CMAKE_SOURCE_DIR}/libvorbisenc.so.2)
#target_link_libraries(maptest ${CMAKE_SOURCE_DIR}/libresolv.so.2)
#target_link_libraries(maptest ${CMAKE_SOURCE_DIR}/libpcre.so.3)
#target_link_libraries(maptest ${CMAKE_SOURCE_DIR}/libgpg-error.so.0)
#target_link_libraries(maptest ${CMAKE_SOURCE_DIR}/libogg.so.0)
#target_link_libraries(maptest ${CMAKE_SOURCE_DIR}/libvorbis.so.0)
























