# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = //home/gefer8/bold

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = //home/gefer8/bold

# Include any dependencies generated for this target.
include CMakeFiles/maptest.16.04.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/maptest.16.04.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/maptest.16.04.dir/flags.make

CMakeFiles/maptest.16.04.dir/src/worldMap.cpp.o: CMakeFiles/maptest.16.04.dir/flags.make
CMakeFiles/maptest.16.04.dir/src/worldMap.cpp.o: src/worldMap.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report //home/gefer8/bold/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/maptest.16.04.dir/src/worldMap.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/maptest.16.04.dir/src/worldMap.cpp.o -c //home/gefer8/bold/src/worldMap.cpp

CMakeFiles/maptest.16.04.dir/src/worldMap.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/maptest.16.04.dir/src/worldMap.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E //home/gefer8/bold/src/worldMap.cpp > CMakeFiles/maptest.16.04.dir/src/worldMap.cpp.i

CMakeFiles/maptest.16.04.dir/src/worldMap.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/maptest.16.04.dir/src/worldMap.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S //home/gefer8/bold/src/worldMap.cpp -o CMakeFiles/maptest.16.04.dir/src/worldMap.cpp.s

CMakeFiles/maptest.16.04.dir/src/worldMap.cpp.o.requires:
.PHONY : CMakeFiles/maptest.16.04.dir/src/worldMap.cpp.o.requires

CMakeFiles/maptest.16.04.dir/src/worldMap.cpp.o.provides: CMakeFiles/maptest.16.04.dir/src/worldMap.cpp.o.requires
	$(MAKE) -f CMakeFiles/maptest.16.04.dir/build.make CMakeFiles/maptest.16.04.dir/src/worldMap.cpp.o.provides.build
.PHONY : CMakeFiles/maptest.16.04.dir/src/worldMap.cpp.o.provides

CMakeFiles/maptest.16.04.dir/src/worldMap.cpp.o.provides.build: CMakeFiles/maptest.16.04.dir/src/worldMap.cpp.o

CMakeFiles/maptest.16.04.dir/src/tile.cpp.o: CMakeFiles/maptest.16.04.dir/flags.make
CMakeFiles/maptest.16.04.dir/src/tile.cpp.o: src/tile.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report //home/gefer8/bold/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/maptest.16.04.dir/src/tile.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/maptest.16.04.dir/src/tile.cpp.o -c //home/gefer8/bold/src/tile.cpp

CMakeFiles/maptest.16.04.dir/src/tile.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/maptest.16.04.dir/src/tile.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E //home/gefer8/bold/src/tile.cpp > CMakeFiles/maptest.16.04.dir/src/tile.cpp.i

CMakeFiles/maptest.16.04.dir/src/tile.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/maptest.16.04.dir/src/tile.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S //home/gefer8/bold/src/tile.cpp -o CMakeFiles/maptest.16.04.dir/src/tile.cpp.s

CMakeFiles/maptest.16.04.dir/src/tile.cpp.o.requires:
.PHONY : CMakeFiles/maptest.16.04.dir/src/tile.cpp.o.requires

CMakeFiles/maptest.16.04.dir/src/tile.cpp.o.provides: CMakeFiles/maptest.16.04.dir/src/tile.cpp.o.requires
	$(MAKE) -f CMakeFiles/maptest.16.04.dir/build.make CMakeFiles/maptest.16.04.dir/src/tile.cpp.o.provides.build
.PHONY : CMakeFiles/maptest.16.04.dir/src/tile.cpp.o.provides

CMakeFiles/maptest.16.04.dir/src/tile.cpp.o.provides.build: CMakeFiles/maptest.16.04.dir/src/tile.cpp.o

CMakeFiles/maptest.16.04.dir/src/battleField.cpp.o: CMakeFiles/maptest.16.04.dir/flags.make
CMakeFiles/maptest.16.04.dir/src/battleField.cpp.o: src/battleField.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report //home/gefer8/bold/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/maptest.16.04.dir/src/battleField.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/maptest.16.04.dir/src/battleField.cpp.o -c //home/gefer8/bold/src/battleField.cpp

CMakeFiles/maptest.16.04.dir/src/battleField.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/maptest.16.04.dir/src/battleField.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E //home/gefer8/bold/src/battleField.cpp > CMakeFiles/maptest.16.04.dir/src/battleField.cpp.i

CMakeFiles/maptest.16.04.dir/src/battleField.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/maptest.16.04.dir/src/battleField.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S //home/gefer8/bold/src/battleField.cpp -o CMakeFiles/maptest.16.04.dir/src/battleField.cpp.s

CMakeFiles/maptest.16.04.dir/src/battleField.cpp.o.requires:
.PHONY : CMakeFiles/maptest.16.04.dir/src/battleField.cpp.o.requires

CMakeFiles/maptest.16.04.dir/src/battleField.cpp.o.provides: CMakeFiles/maptest.16.04.dir/src/battleField.cpp.o.requires
	$(MAKE) -f CMakeFiles/maptest.16.04.dir/build.make CMakeFiles/maptest.16.04.dir/src/battleField.cpp.o.provides.build
.PHONY : CMakeFiles/maptest.16.04.dir/src/battleField.cpp.o.provides

CMakeFiles/maptest.16.04.dir/src/battleField.cpp.o.provides.build: CMakeFiles/maptest.16.04.dir/src/battleField.cpp.o

CMakeFiles/maptest.16.04.dir/src/toolkit.cpp.o: CMakeFiles/maptest.16.04.dir/flags.make
CMakeFiles/maptest.16.04.dir/src/toolkit.cpp.o: src/toolkit.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report //home/gefer8/bold/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/maptest.16.04.dir/src/toolkit.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/maptest.16.04.dir/src/toolkit.cpp.o -c //home/gefer8/bold/src/toolkit.cpp

CMakeFiles/maptest.16.04.dir/src/toolkit.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/maptest.16.04.dir/src/toolkit.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E //home/gefer8/bold/src/toolkit.cpp > CMakeFiles/maptest.16.04.dir/src/toolkit.cpp.i

CMakeFiles/maptest.16.04.dir/src/toolkit.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/maptest.16.04.dir/src/toolkit.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S //home/gefer8/bold/src/toolkit.cpp -o CMakeFiles/maptest.16.04.dir/src/toolkit.cpp.s

CMakeFiles/maptest.16.04.dir/src/toolkit.cpp.o.requires:
.PHONY : CMakeFiles/maptest.16.04.dir/src/toolkit.cpp.o.requires

CMakeFiles/maptest.16.04.dir/src/toolkit.cpp.o.provides: CMakeFiles/maptest.16.04.dir/src/toolkit.cpp.o.requires
	$(MAKE) -f CMakeFiles/maptest.16.04.dir/build.make CMakeFiles/maptest.16.04.dir/src/toolkit.cpp.o.provides.build
.PHONY : CMakeFiles/maptest.16.04.dir/src/toolkit.cpp.o.provides

CMakeFiles/maptest.16.04.dir/src/toolkit.cpp.o.provides.build: CMakeFiles/maptest.16.04.dir/src/toolkit.cpp.o

CMakeFiles/maptest.16.04.dir/src/map.cpp.o: CMakeFiles/maptest.16.04.dir/flags.make
CMakeFiles/maptest.16.04.dir/src/map.cpp.o: src/map.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report //home/gefer8/bold/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/maptest.16.04.dir/src/map.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/maptest.16.04.dir/src/map.cpp.o -c //home/gefer8/bold/src/map.cpp

CMakeFiles/maptest.16.04.dir/src/map.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/maptest.16.04.dir/src/map.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E //home/gefer8/bold/src/map.cpp > CMakeFiles/maptest.16.04.dir/src/map.cpp.i

CMakeFiles/maptest.16.04.dir/src/map.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/maptest.16.04.dir/src/map.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S //home/gefer8/bold/src/map.cpp -o CMakeFiles/maptest.16.04.dir/src/map.cpp.s

CMakeFiles/maptest.16.04.dir/src/map.cpp.o.requires:
.PHONY : CMakeFiles/maptest.16.04.dir/src/map.cpp.o.requires

CMakeFiles/maptest.16.04.dir/src/map.cpp.o.provides: CMakeFiles/maptest.16.04.dir/src/map.cpp.o.requires
	$(MAKE) -f CMakeFiles/maptest.16.04.dir/build.make CMakeFiles/maptest.16.04.dir/src/map.cpp.o.provides.build
.PHONY : CMakeFiles/maptest.16.04.dir/src/map.cpp.o.provides

CMakeFiles/maptest.16.04.dir/src/map.cpp.o.provides.build: CMakeFiles/maptest.16.04.dir/src/map.cpp.o

CMakeFiles/maptest.16.04.dir/src/maptest.cpp.o: CMakeFiles/maptest.16.04.dir/flags.make
CMakeFiles/maptest.16.04.dir/src/maptest.cpp.o: src/maptest.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report //home/gefer8/bold/CMakeFiles $(CMAKE_PROGRESS_6)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/maptest.16.04.dir/src/maptest.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/maptest.16.04.dir/src/maptest.cpp.o -c //home/gefer8/bold/src/maptest.cpp

CMakeFiles/maptest.16.04.dir/src/maptest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/maptest.16.04.dir/src/maptest.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E //home/gefer8/bold/src/maptest.cpp > CMakeFiles/maptest.16.04.dir/src/maptest.cpp.i

CMakeFiles/maptest.16.04.dir/src/maptest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/maptest.16.04.dir/src/maptest.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S //home/gefer8/bold/src/maptest.cpp -o CMakeFiles/maptest.16.04.dir/src/maptest.cpp.s

CMakeFiles/maptest.16.04.dir/src/maptest.cpp.o.requires:
.PHONY : CMakeFiles/maptest.16.04.dir/src/maptest.cpp.o.requires

CMakeFiles/maptest.16.04.dir/src/maptest.cpp.o.provides: CMakeFiles/maptest.16.04.dir/src/maptest.cpp.o.requires
	$(MAKE) -f CMakeFiles/maptest.16.04.dir/build.make CMakeFiles/maptest.16.04.dir/src/maptest.cpp.o.provides.build
.PHONY : CMakeFiles/maptest.16.04.dir/src/maptest.cpp.o.provides

CMakeFiles/maptest.16.04.dir/src/maptest.cpp.o.provides.build: CMakeFiles/maptest.16.04.dir/src/maptest.cpp.o

# Object files for target maptest.16.04
maptest_16_04_OBJECTS = \
"CMakeFiles/maptest.16.04.dir/src/worldMap.cpp.o" \
"CMakeFiles/maptest.16.04.dir/src/tile.cpp.o" \
"CMakeFiles/maptest.16.04.dir/src/battleField.cpp.o" \
"CMakeFiles/maptest.16.04.dir/src/toolkit.cpp.o" \
"CMakeFiles/maptest.16.04.dir/src/map.cpp.o" \
"CMakeFiles/maptest.16.04.dir/src/maptest.cpp.o"

# External object files for target maptest.16.04
maptest_16_04_EXTERNAL_OBJECTS =

build/maptest.16.04: CMakeFiles/maptest.16.04.dir/src/worldMap.cpp.o
build/maptest.16.04: CMakeFiles/maptest.16.04.dir/src/tile.cpp.o
build/maptest.16.04: CMakeFiles/maptest.16.04.dir/src/battleField.cpp.o
build/maptest.16.04: CMakeFiles/maptest.16.04.dir/src/toolkit.cpp.o
build/maptest.16.04: CMakeFiles/maptest.16.04.dir/src/map.cpp.o
build/maptest.16.04: CMakeFiles/maptest.16.04.dir/src/maptest.cpp.o
build/maptest.16.04: CMakeFiles/maptest.16.04.dir/build.make
build/maptest.16.04: libs/16.04/libSDL2_image-2.0.so.0
build/maptest.16.04: libs/16.04/libSDL2.so
build/maptest.16.04: CMakeFiles/maptest.16.04.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable build/maptest.16.04"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/maptest.16.04.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/maptest.16.04.dir/build: build/maptest.16.04
.PHONY : CMakeFiles/maptest.16.04.dir/build

CMakeFiles/maptest.16.04.dir/requires: CMakeFiles/maptest.16.04.dir/src/worldMap.cpp.o.requires
CMakeFiles/maptest.16.04.dir/requires: CMakeFiles/maptest.16.04.dir/src/tile.cpp.o.requires
CMakeFiles/maptest.16.04.dir/requires: CMakeFiles/maptest.16.04.dir/src/battleField.cpp.o.requires
CMakeFiles/maptest.16.04.dir/requires: CMakeFiles/maptest.16.04.dir/src/toolkit.cpp.o.requires
CMakeFiles/maptest.16.04.dir/requires: CMakeFiles/maptest.16.04.dir/src/map.cpp.o.requires
CMakeFiles/maptest.16.04.dir/requires: CMakeFiles/maptest.16.04.dir/src/maptest.cpp.o.requires
.PHONY : CMakeFiles/maptest.16.04.dir/requires

CMakeFiles/maptest.16.04.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/maptest.16.04.dir/cmake_clean.cmake
.PHONY : CMakeFiles/maptest.16.04.dir/clean

CMakeFiles/maptest.16.04.dir/depend:
	cd //home/gefer8/bold && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" //home/gefer8/bold //home/gefer8/bold //home/gefer8/bold //home/gefer8/bold //home/gefer8/bold/CMakeFiles/maptest.16.04.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/maptest.16.04.dir/depend

