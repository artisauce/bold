# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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
CMAKE_SOURCE_DIR = /home/gefer8/bold

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/gefer8/bold

# Include any dependencies generated for this target.
include CMakeFiles/maptest.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/maptest.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/maptest.dir/flags.make

CMakeFiles/maptest.dir/src/tile.cpp.o: CMakeFiles/maptest.dir/flags.make
CMakeFiles/maptest.dir/src/tile.cpp.o: src/tile.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gefer8/bold/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/maptest.dir/src/tile.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/maptest.dir/src/tile.cpp.o -c /home/gefer8/bold/src/tile.cpp

CMakeFiles/maptest.dir/src/tile.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/maptest.dir/src/tile.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gefer8/bold/src/tile.cpp > CMakeFiles/maptest.dir/src/tile.cpp.i

CMakeFiles/maptest.dir/src/tile.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/maptest.dir/src/tile.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gefer8/bold/src/tile.cpp -o CMakeFiles/maptest.dir/src/tile.cpp.s

CMakeFiles/maptest.dir/src/tile.cpp.o.requires:

.PHONY : CMakeFiles/maptest.dir/src/tile.cpp.o.requires

CMakeFiles/maptest.dir/src/tile.cpp.o.provides: CMakeFiles/maptest.dir/src/tile.cpp.o.requires
	$(MAKE) -f CMakeFiles/maptest.dir/build.make CMakeFiles/maptest.dir/src/tile.cpp.o.provides.build
.PHONY : CMakeFiles/maptest.dir/src/tile.cpp.o.provides

CMakeFiles/maptest.dir/src/tile.cpp.o.provides.build: CMakeFiles/maptest.dir/src/tile.cpp.o


CMakeFiles/maptest.dir/src/map.cpp.o: CMakeFiles/maptest.dir/flags.make
CMakeFiles/maptest.dir/src/map.cpp.o: src/map.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gefer8/bold/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/maptest.dir/src/map.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/maptest.dir/src/map.cpp.o -c /home/gefer8/bold/src/map.cpp

CMakeFiles/maptest.dir/src/map.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/maptest.dir/src/map.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gefer8/bold/src/map.cpp > CMakeFiles/maptest.dir/src/map.cpp.i

CMakeFiles/maptest.dir/src/map.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/maptest.dir/src/map.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gefer8/bold/src/map.cpp -o CMakeFiles/maptest.dir/src/map.cpp.s

CMakeFiles/maptest.dir/src/map.cpp.o.requires:

.PHONY : CMakeFiles/maptest.dir/src/map.cpp.o.requires

CMakeFiles/maptest.dir/src/map.cpp.o.provides: CMakeFiles/maptest.dir/src/map.cpp.o.requires
	$(MAKE) -f CMakeFiles/maptest.dir/build.make CMakeFiles/maptest.dir/src/map.cpp.o.provides.build
.PHONY : CMakeFiles/maptest.dir/src/map.cpp.o.provides

CMakeFiles/maptest.dir/src/map.cpp.o.provides.build: CMakeFiles/maptest.dir/src/map.cpp.o


CMakeFiles/maptest.dir/src/toolkit.cpp.o: CMakeFiles/maptest.dir/flags.make
CMakeFiles/maptest.dir/src/toolkit.cpp.o: src/toolkit.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gefer8/bold/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/maptest.dir/src/toolkit.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/maptest.dir/src/toolkit.cpp.o -c /home/gefer8/bold/src/toolkit.cpp

CMakeFiles/maptest.dir/src/toolkit.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/maptest.dir/src/toolkit.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gefer8/bold/src/toolkit.cpp > CMakeFiles/maptest.dir/src/toolkit.cpp.i

CMakeFiles/maptest.dir/src/toolkit.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/maptest.dir/src/toolkit.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gefer8/bold/src/toolkit.cpp -o CMakeFiles/maptest.dir/src/toolkit.cpp.s

CMakeFiles/maptest.dir/src/toolkit.cpp.o.requires:

.PHONY : CMakeFiles/maptest.dir/src/toolkit.cpp.o.requires

CMakeFiles/maptest.dir/src/toolkit.cpp.o.provides: CMakeFiles/maptest.dir/src/toolkit.cpp.o.requires
	$(MAKE) -f CMakeFiles/maptest.dir/build.make CMakeFiles/maptest.dir/src/toolkit.cpp.o.provides.build
.PHONY : CMakeFiles/maptest.dir/src/toolkit.cpp.o.provides

CMakeFiles/maptest.dir/src/toolkit.cpp.o.provides.build: CMakeFiles/maptest.dir/src/toolkit.cpp.o


CMakeFiles/maptest.dir/src/maptest.cpp.o: CMakeFiles/maptest.dir/flags.make
CMakeFiles/maptest.dir/src/maptest.cpp.o: src/maptest.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gefer8/bold/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/maptest.dir/src/maptest.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/maptest.dir/src/maptest.cpp.o -c /home/gefer8/bold/src/maptest.cpp

CMakeFiles/maptest.dir/src/maptest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/maptest.dir/src/maptest.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gefer8/bold/src/maptest.cpp > CMakeFiles/maptest.dir/src/maptest.cpp.i

CMakeFiles/maptest.dir/src/maptest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/maptest.dir/src/maptest.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gefer8/bold/src/maptest.cpp -o CMakeFiles/maptest.dir/src/maptest.cpp.s

CMakeFiles/maptest.dir/src/maptest.cpp.o.requires:

.PHONY : CMakeFiles/maptest.dir/src/maptest.cpp.o.requires

CMakeFiles/maptest.dir/src/maptest.cpp.o.provides: CMakeFiles/maptest.dir/src/maptest.cpp.o.requires
	$(MAKE) -f CMakeFiles/maptest.dir/build.make CMakeFiles/maptest.dir/src/maptest.cpp.o.provides.build
.PHONY : CMakeFiles/maptest.dir/src/maptest.cpp.o.provides

CMakeFiles/maptest.dir/src/maptest.cpp.o.provides.build: CMakeFiles/maptest.dir/src/maptest.cpp.o


CMakeFiles/maptest.dir/src/battleField.cpp.o: CMakeFiles/maptest.dir/flags.make
CMakeFiles/maptest.dir/src/battleField.cpp.o: src/battleField.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gefer8/bold/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/maptest.dir/src/battleField.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/maptest.dir/src/battleField.cpp.o -c /home/gefer8/bold/src/battleField.cpp

CMakeFiles/maptest.dir/src/battleField.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/maptest.dir/src/battleField.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gefer8/bold/src/battleField.cpp > CMakeFiles/maptest.dir/src/battleField.cpp.i

CMakeFiles/maptest.dir/src/battleField.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/maptest.dir/src/battleField.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gefer8/bold/src/battleField.cpp -o CMakeFiles/maptest.dir/src/battleField.cpp.s

CMakeFiles/maptest.dir/src/battleField.cpp.o.requires:

.PHONY : CMakeFiles/maptest.dir/src/battleField.cpp.o.requires

CMakeFiles/maptest.dir/src/battleField.cpp.o.provides: CMakeFiles/maptest.dir/src/battleField.cpp.o.requires
	$(MAKE) -f CMakeFiles/maptest.dir/build.make CMakeFiles/maptest.dir/src/battleField.cpp.o.provides.build
.PHONY : CMakeFiles/maptest.dir/src/battleField.cpp.o.provides

CMakeFiles/maptest.dir/src/battleField.cpp.o.provides.build: CMakeFiles/maptest.dir/src/battleField.cpp.o


CMakeFiles/maptest.dir/src/worldMap.cpp.o: CMakeFiles/maptest.dir/flags.make
CMakeFiles/maptest.dir/src/worldMap.cpp.o: src/worldMap.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gefer8/bold/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/maptest.dir/src/worldMap.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/maptest.dir/src/worldMap.cpp.o -c /home/gefer8/bold/src/worldMap.cpp

CMakeFiles/maptest.dir/src/worldMap.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/maptest.dir/src/worldMap.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gefer8/bold/src/worldMap.cpp > CMakeFiles/maptest.dir/src/worldMap.cpp.i

CMakeFiles/maptest.dir/src/worldMap.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/maptest.dir/src/worldMap.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gefer8/bold/src/worldMap.cpp -o CMakeFiles/maptest.dir/src/worldMap.cpp.s

CMakeFiles/maptest.dir/src/worldMap.cpp.o.requires:

.PHONY : CMakeFiles/maptest.dir/src/worldMap.cpp.o.requires

CMakeFiles/maptest.dir/src/worldMap.cpp.o.provides: CMakeFiles/maptest.dir/src/worldMap.cpp.o.requires
	$(MAKE) -f CMakeFiles/maptest.dir/build.make CMakeFiles/maptest.dir/src/worldMap.cpp.o.provides.build
.PHONY : CMakeFiles/maptest.dir/src/worldMap.cpp.o.provides

CMakeFiles/maptest.dir/src/worldMap.cpp.o.provides.build: CMakeFiles/maptest.dir/src/worldMap.cpp.o


# Object files for target maptest
maptest_OBJECTS = \
"CMakeFiles/maptest.dir/src/tile.cpp.o" \
"CMakeFiles/maptest.dir/src/map.cpp.o" \
"CMakeFiles/maptest.dir/src/toolkit.cpp.o" \
"CMakeFiles/maptest.dir/src/maptest.cpp.o" \
"CMakeFiles/maptest.dir/src/battleField.cpp.o" \
"CMakeFiles/maptest.dir/src/worldMap.cpp.o"

# External object files for target maptest
maptest_EXTERNAL_OBJECTS =

build/maptest: CMakeFiles/maptest.dir/src/tile.cpp.o
build/maptest: CMakeFiles/maptest.dir/src/map.cpp.o
build/maptest: CMakeFiles/maptest.dir/src/toolkit.cpp.o
build/maptest: CMakeFiles/maptest.dir/src/maptest.cpp.o
build/maptest: CMakeFiles/maptest.dir/src/battleField.cpp.o
build/maptest: CMakeFiles/maptest.dir/src/worldMap.cpp.o
build/maptest: CMakeFiles/maptest.dir/build.make
build/maptest: libSDL2.a
build/maptest: libsndio.so.6.1
build/maptest: libdl.so
build/maptest: libpthread.so
build/maptest: CMakeFiles/maptest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/gefer8/bold/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX executable build/maptest"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/maptest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/maptest.dir/build: build/maptest

.PHONY : CMakeFiles/maptest.dir/build

CMakeFiles/maptest.dir/requires: CMakeFiles/maptest.dir/src/tile.cpp.o.requires
CMakeFiles/maptest.dir/requires: CMakeFiles/maptest.dir/src/map.cpp.o.requires
CMakeFiles/maptest.dir/requires: CMakeFiles/maptest.dir/src/toolkit.cpp.o.requires
CMakeFiles/maptest.dir/requires: CMakeFiles/maptest.dir/src/maptest.cpp.o.requires
CMakeFiles/maptest.dir/requires: CMakeFiles/maptest.dir/src/battleField.cpp.o.requires
CMakeFiles/maptest.dir/requires: CMakeFiles/maptest.dir/src/worldMap.cpp.o.requires

.PHONY : CMakeFiles/maptest.dir/requires

CMakeFiles/maptest.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/maptest.dir/cmake_clean.cmake
.PHONY : CMakeFiles/maptest.dir/clean

CMakeFiles/maptest.dir/depend:
	cd /home/gefer8/bold && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/gefer8/bold /home/gefer8/bold /home/gefer8/bold /home/gefer8/bold /home/gefer8/bold/CMakeFiles/maptest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/maptest.dir/depend

