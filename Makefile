# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.2

# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:

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
CMAKE_SOURCE_DIR = /home/dmagaril/bold

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/dmagaril/bold

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/usr/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache
.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/dmagaril/bold/CMakeFiles /home/dmagaril/bold/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/dmagaril/bold/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean
.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named maptest.14.04

# Build rule for target.
maptest.14.04: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 maptest.14.04
.PHONY : maptest.14.04

# fast build rule for target.
maptest.14.04/fast:
	$(MAKE) -f CMakeFiles/maptest.14.04.dir/build.make CMakeFiles/maptest.14.04.dir/build
.PHONY : maptest.14.04/fast

#=============================================================================
# Target rules for targets named maptest.16.04

# Build rule for target.
maptest.16.04: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 maptest.16.04
.PHONY : maptest.16.04

# fast build rule for target.
maptest.16.04/fast:
	$(MAKE) -f CMakeFiles/maptest.16.04.dir/build.make CMakeFiles/maptest.16.04.dir/build
.PHONY : maptest.16.04/fast

src/battleField.o: src/battleField.cpp.o
.PHONY : src/battleField.o

# target to build an object file
src/battleField.cpp.o:
	$(MAKE) -f CMakeFiles/maptest.14.04.dir/build.make CMakeFiles/maptest.14.04.dir/src/battleField.cpp.o
	$(MAKE) -f CMakeFiles/maptest.16.04.dir/build.make CMakeFiles/maptest.16.04.dir/src/battleField.cpp.o
.PHONY : src/battleField.cpp.o

src/battleField.i: src/battleField.cpp.i
.PHONY : src/battleField.i

# target to preprocess a source file
src/battleField.cpp.i:
	$(MAKE) -f CMakeFiles/maptest.14.04.dir/build.make CMakeFiles/maptest.14.04.dir/src/battleField.cpp.i
	$(MAKE) -f CMakeFiles/maptest.16.04.dir/build.make CMakeFiles/maptest.16.04.dir/src/battleField.cpp.i
.PHONY : src/battleField.cpp.i

src/battleField.s: src/battleField.cpp.s
.PHONY : src/battleField.s

# target to generate assembly for a file
src/battleField.cpp.s:
	$(MAKE) -f CMakeFiles/maptest.14.04.dir/build.make CMakeFiles/maptest.14.04.dir/src/battleField.cpp.s
	$(MAKE) -f CMakeFiles/maptest.16.04.dir/build.make CMakeFiles/maptest.16.04.dir/src/battleField.cpp.s
.PHONY : src/battleField.cpp.s

src/map.o: src/map.cpp.o
.PHONY : src/map.o

# target to build an object file
src/map.cpp.o:
	$(MAKE) -f CMakeFiles/maptest.14.04.dir/build.make CMakeFiles/maptest.14.04.dir/src/map.cpp.o
	$(MAKE) -f CMakeFiles/maptest.16.04.dir/build.make CMakeFiles/maptest.16.04.dir/src/map.cpp.o
.PHONY : src/map.cpp.o

src/map.i: src/map.cpp.i
.PHONY : src/map.i

# target to preprocess a source file
src/map.cpp.i:
	$(MAKE) -f CMakeFiles/maptest.14.04.dir/build.make CMakeFiles/maptest.14.04.dir/src/map.cpp.i
	$(MAKE) -f CMakeFiles/maptest.16.04.dir/build.make CMakeFiles/maptest.16.04.dir/src/map.cpp.i
.PHONY : src/map.cpp.i

src/map.s: src/map.cpp.s
.PHONY : src/map.s

# target to generate assembly for a file
src/map.cpp.s:
	$(MAKE) -f CMakeFiles/maptest.14.04.dir/build.make CMakeFiles/maptest.14.04.dir/src/map.cpp.s
	$(MAKE) -f CMakeFiles/maptest.16.04.dir/build.make CMakeFiles/maptest.16.04.dir/src/map.cpp.s
.PHONY : src/map.cpp.s

src/maptest.o: src/maptest.cpp.o
.PHONY : src/maptest.o

# target to build an object file
src/maptest.cpp.o:
	$(MAKE) -f CMakeFiles/maptest.14.04.dir/build.make CMakeFiles/maptest.14.04.dir/src/maptest.cpp.o
	$(MAKE) -f CMakeFiles/maptest.16.04.dir/build.make CMakeFiles/maptest.16.04.dir/src/maptest.cpp.o
.PHONY : src/maptest.cpp.o

src/maptest.i: src/maptest.cpp.i
.PHONY : src/maptest.i

# target to preprocess a source file
src/maptest.cpp.i:
	$(MAKE) -f CMakeFiles/maptest.14.04.dir/build.make CMakeFiles/maptest.14.04.dir/src/maptest.cpp.i
	$(MAKE) -f CMakeFiles/maptest.16.04.dir/build.make CMakeFiles/maptest.16.04.dir/src/maptest.cpp.i
.PHONY : src/maptest.cpp.i

src/maptest.s: src/maptest.cpp.s
.PHONY : src/maptest.s

# target to generate assembly for a file
src/maptest.cpp.s:
	$(MAKE) -f CMakeFiles/maptest.14.04.dir/build.make CMakeFiles/maptest.14.04.dir/src/maptest.cpp.s
	$(MAKE) -f CMakeFiles/maptest.16.04.dir/build.make CMakeFiles/maptest.16.04.dir/src/maptest.cpp.s
.PHONY : src/maptest.cpp.s

src/tile.o: src/tile.cpp.o
.PHONY : src/tile.o

# target to build an object file
src/tile.cpp.o:
	$(MAKE) -f CMakeFiles/maptest.14.04.dir/build.make CMakeFiles/maptest.14.04.dir/src/tile.cpp.o
	$(MAKE) -f CMakeFiles/maptest.16.04.dir/build.make CMakeFiles/maptest.16.04.dir/src/tile.cpp.o
.PHONY : src/tile.cpp.o

src/tile.i: src/tile.cpp.i
.PHONY : src/tile.i

# target to preprocess a source file
src/tile.cpp.i:
	$(MAKE) -f CMakeFiles/maptest.14.04.dir/build.make CMakeFiles/maptest.14.04.dir/src/tile.cpp.i
	$(MAKE) -f CMakeFiles/maptest.16.04.dir/build.make CMakeFiles/maptest.16.04.dir/src/tile.cpp.i
.PHONY : src/tile.cpp.i

src/tile.s: src/tile.cpp.s
.PHONY : src/tile.s

# target to generate assembly for a file
src/tile.cpp.s:
	$(MAKE) -f CMakeFiles/maptest.14.04.dir/build.make CMakeFiles/maptest.14.04.dir/src/tile.cpp.s
	$(MAKE) -f CMakeFiles/maptest.16.04.dir/build.make CMakeFiles/maptest.16.04.dir/src/tile.cpp.s
.PHONY : src/tile.cpp.s

src/toolkit.o: src/toolkit.cpp.o
.PHONY : src/toolkit.o

# target to build an object file
src/toolkit.cpp.o:
	$(MAKE) -f CMakeFiles/maptest.14.04.dir/build.make CMakeFiles/maptest.14.04.dir/src/toolkit.cpp.o
	$(MAKE) -f CMakeFiles/maptest.16.04.dir/build.make CMakeFiles/maptest.16.04.dir/src/toolkit.cpp.o
.PHONY : src/toolkit.cpp.o

src/toolkit.i: src/toolkit.cpp.i
.PHONY : src/toolkit.i

# target to preprocess a source file
src/toolkit.cpp.i:
	$(MAKE) -f CMakeFiles/maptest.14.04.dir/build.make CMakeFiles/maptest.14.04.dir/src/toolkit.cpp.i
	$(MAKE) -f CMakeFiles/maptest.16.04.dir/build.make CMakeFiles/maptest.16.04.dir/src/toolkit.cpp.i
.PHONY : src/toolkit.cpp.i

src/toolkit.s: src/toolkit.cpp.s
.PHONY : src/toolkit.s

# target to generate assembly for a file
src/toolkit.cpp.s:
	$(MAKE) -f CMakeFiles/maptest.14.04.dir/build.make CMakeFiles/maptest.14.04.dir/src/toolkit.cpp.s
	$(MAKE) -f CMakeFiles/maptest.16.04.dir/build.make CMakeFiles/maptest.16.04.dir/src/toolkit.cpp.s
.PHONY : src/toolkit.cpp.s

src/worldMap.o: src/worldMap.cpp.o
.PHONY : src/worldMap.o

# target to build an object file
src/worldMap.cpp.o:
	$(MAKE) -f CMakeFiles/maptest.14.04.dir/build.make CMakeFiles/maptest.14.04.dir/src/worldMap.cpp.o
	$(MAKE) -f CMakeFiles/maptest.16.04.dir/build.make CMakeFiles/maptest.16.04.dir/src/worldMap.cpp.o
.PHONY : src/worldMap.cpp.o

src/worldMap.i: src/worldMap.cpp.i
.PHONY : src/worldMap.i

# target to preprocess a source file
src/worldMap.cpp.i:
	$(MAKE) -f CMakeFiles/maptest.14.04.dir/build.make CMakeFiles/maptest.14.04.dir/src/worldMap.cpp.i
	$(MAKE) -f CMakeFiles/maptest.16.04.dir/build.make CMakeFiles/maptest.16.04.dir/src/worldMap.cpp.i
.PHONY : src/worldMap.cpp.i

src/worldMap.s: src/worldMap.cpp.s
.PHONY : src/worldMap.s

# target to generate assembly for a file
src/worldMap.cpp.s:
	$(MAKE) -f CMakeFiles/maptest.14.04.dir/build.make CMakeFiles/maptest.14.04.dir/src/worldMap.cpp.s
	$(MAKE) -f CMakeFiles/maptest.16.04.dir/build.make CMakeFiles/maptest.16.04.dir/src/worldMap.cpp.s
.PHONY : src/worldMap.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... maptest.14.04"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... maptest.16.04"
	@echo "... src/battleField.o"
	@echo "... src/battleField.i"
	@echo "... src/battleField.s"
	@echo "... src/map.o"
	@echo "... src/map.i"
	@echo "... src/map.s"
	@echo "... src/maptest.o"
	@echo "... src/maptest.i"
	@echo "... src/maptest.s"
	@echo "... src/tile.o"
	@echo "... src/tile.i"
	@echo "... src/tile.s"
	@echo "... src/toolkit.o"
	@echo "... src/toolkit.i"
	@echo "... src/toolkit.s"
	@echo "... src/worldMap.o"
	@echo "... src/worldMap.i"
	@echo "... src/worldMap.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

