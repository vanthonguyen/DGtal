# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canoncical targets will work.
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
CMAKE_COMMAND = /usr/local/Cellar/cmake/2.8.5/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/2.8.5/bin/cmake -E remove -f

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/local/Cellar/cmake/2.8.5/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/davidcoeurjolly/Sources/DGtal

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/davidcoeurjolly/Sources/DGtal/build

# Include any dependencies generated for this target.
include examples/io/boards/CMakeFiles/dgtalboard-2-sets.dir/depend.make

# Include the progress variables for this target.
include examples/io/boards/CMakeFiles/dgtalboard-2-sets.dir/progress.make

# Include the compile flags for this target's objects.
include examples/io/boards/CMakeFiles/dgtalboard-2-sets.dir/flags.make

examples/io/boards/CMakeFiles/dgtalboard-2-sets.dir/dgtalboard-2-sets.cpp.o: examples/io/boards/CMakeFiles/dgtalboard-2-sets.dir/flags.make
examples/io/boards/CMakeFiles/dgtalboard-2-sets.dir/dgtalboard-2-sets.cpp.o: ../examples/io/boards/dgtalboard-2-sets.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/davidcoeurjolly/Sources/DGtal/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object examples/io/boards/CMakeFiles/dgtalboard-2-sets.dir/dgtalboard-2-sets.cpp.o"
	cd /Users/davidcoeurjolly/Sources/DGtal/build/examples/io/boards && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/dgtalboard-2-sets.dir/dgtalboard-2-sets.cpp.o -c /Users/davidcoeurjolly/Sources/DGtal/examples/io/boards/dgtalboard-2-sets.cpp

examples/io/boards/CMakeFiles/dgtalboard-2-sets.dir/dgtalboard-2-sets.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/dgtalboard-2-sets.dir/dgtalboard-2-sets.cpp.i"
	cd /Users/davidcoeurjolly/Sources/DGtal/build/examples/io/boards && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /Users/davidcoeurjolly/Sources/DGtal/examples/io/boards/dgtalboard-2-sets.cpp > CMakeFiles/dgtalboard-2-sets.dir/dgtalboard-2-sets.cpp.i

examples/io/boards/CMakeFiles/dgtalboard-2-sets.dir/dgtalboard-2-sets.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/dgtalboard-2-sets.dir/dgtalboard-2-sets.cpp.s"
	cd /Users/davidcoeurjolly/Sources/DGtal/build/examples/io/boards && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /Users/davidcoeurjolly/Sources/DGtal/examples/io/boards/dgtalboard-2-sets.cpp -o CMakeFiles/dgtalboard-2-sets.dir/dgtalboard-2-sets.cpp.s

examples/io/boards/CMakeFiles/dgtalboard-2-sets.dir/dgtalboard-2-sets.cpp.o.requires:
.PHONY : examples/io/boards/CMakeFiles/dgtalboard-2-sets.dir/dgtalboard-2-sets.cpp.o.requires

examples/io/boards/CMakeFiles/dgtalboard-2-sets.dir/dgtalboard-2-sets.cpp.o.provides: examples/io/boards/CMakeFiles/dgtalboard-2-sets.dir/dgtalboard-2-sets.cpp.o.requires
	$(MAKE) -f examples/io/boards/CMakeFiles/dgtalboard-2-sets.dir/build.make examples/io/boards/CMakeFiles/dgtalboard-2-sets.dir/dgtalboard-2-sets.cpp.o.provides.build
.PHONY : examples/io/boards/CMakeFiles/dgtalboard-2-sets.dir/dgtalboard-2-sets.cpp.o.provides

examples/io/boards/CMakeFiles/dgtalboard-2-sets.dir/dgtalboard-2-sets.cpp.o.provides.build: examples/io/boards/CMakeFiles/dgtalboard-2-sets.dir/dgtalboard-2-sets.cpp.o

# Object files for target dgtalboard-2-sets
dgtalboard__2__sets_OBJECTS = \
"CMakeFiles/dgtalboard-2-sets.dir/dgtalboard-2-sets.cpp.o"

# External object files for target dgtalboard-2-sets
dgtalboard__2__sets_EXTERNAL_OBJECTS =

examples/io/boards/dgtalboard-2-sets: examples/io/boards/CMakeFiles/dgtalboard-2-sets.dir/dgtalboard-2-sets.cpp.o
examples/io/boards/dgtalboard-2-sets: src/libDGtal.dylib
examples/io/boards/dgtalboard-2-sets: /usr/local/lib/libboost_program_options-mt.a
examples/io/boards/dgtalboard-2-sets: examples/io/boards/CMakeFiles/dgtalboard-2-sets.dir/build.make
examples/io/boards/dgtalboard-2-sets: examples/io/boards/CMakeFiles/dgtalboard-2-sets.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable dgtalboard-2-sets"
	cd /Users/davidcoeurjolly/Sources/DGtal/build/examples/io/boards && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/dgtalboard-2-sets.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/io/boards/CMakeFiles/dgtalboard-2-sets.dir/build: examples/io/boards/dgtalboard-2-sets
.PHONY : examples/io/boards/CMakeFiles/dgtalboard-2-sets.dir/build

examples/io/boards/CMakeFiles/dgtalboard-2-sets.dir/requires: examples/io/boards/CMakeFiles/dgtalboard-2-sets.dir/dgtalboard-2-sets.cpp.o.requires
.PHONY : examples/io/boards/CMakeFiles/dgtalboard-2-sets.dir/requires

examples/io/boards/CMakeFiles/dgtalboard-2-sets.dir/clean:
	cd /Users/davidcoeurjolly/Sources/DGtal/build/examples/io/boards && $(CMAKE_COMMAND) -P CMakeFiles/dgtalboard-2-sets.dir/cmake_clean.cmake
.PHONY : examples/io/boards/CMakeFiles/dgtalboard-2-sets.dir/clean

examples/io/boards/CMakeFiles/dgtalboard-2-sets.dir/depend:
	cd /Users/davidcoeurjolly/Sources/DGtal/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/davidcoeurjolly/Sources/DGtal /Users/davidcoeurjolly/Sources/DGtal/examples/io/boards /Users/davidcoeurjolly/Sources/DGtal/build /Users/davidcoeurjolly/Sources/DGtal/build/examples/io/boards /Users/davidcoeurjolly/Sources/DGtal/build/examples/io/boards/CMakeFiles/dgtalboard-2-sets.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/io/boards/CMakeFiles/dgtalboard-2-sets.dir/depend

