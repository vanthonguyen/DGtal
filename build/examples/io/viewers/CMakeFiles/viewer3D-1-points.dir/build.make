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
include examples/io/viewers/CMakeFiles/viewer3D-1-points.dir/depend.make

# Include the progress variables for this target.
include examples/io/viewers/CMakeFiles/viewer3D-1-points.dir/progress.make

# Include the compile flags for this target's objects.
include examples/io/viewers/CMakeFiles/viewer3D-1-points.dir/flags.make

examples/io/viewers/CMakeFiles/viewer3D-1-points.dir/viewer3D-1-points.cpp.o: examples/io/viewers/CMakeFiles/viewer3D-1-points.dir/flags.make
examples/io/viewers/CMakeFiles/viewer3D-1-points.dir/viewer3D-1-points.cpp.o: ../examples/io/viewers/viewer3D-1-points.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/davidcoeurjolly/Sources/DGtal/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object examples/io/viewers/CMakeFiles/viewer3D-1-points.dir/viewer3D-1-points.cpp.o"
	cd /Users/davidcoeurjolly/Sources/DGtal/build/examples/io/viewers && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/viewer3D-1-points.dir/viewer3D-1-points.cpp.o -c /Users/davidcoeurjolly/Sources/DGtal/examples/io/viewers/viewer3D-1-points.cpp

examples/io/viewers/CMakeFiles/viewer3D-1-points.dir/viewer3D-1-points.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/viewer3D-1-points.dir/viewer3D-1-points.cpp.i"
	cd /Users/davidcoeurjolly/Sources/DGtal/build/examples/io/viewers && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /Users/davidcoeurjolly/Sources/DGtal/examples/io/viewers/viewer3D-1-points.cpp > CMakeFiles/viewer3D-1-points.dir/viewer3D-1-points.cpp.i

examples/io/viewers/CMakeFiles/viewer3D-1-points.dir/viewer3D-1-points.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/viewer3D-1-points.dir/viewer3D-1-points.cpp.s"
	cd /Users/davidcoeurjolly/Sources/DGtal/build/examples/io/viewers && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /Users/davidcoeurjolly/Sources/DGtal/examples/io/viewers/viewer3D-1-points.cpp -o CMakeFiles/viewer3D-1-points.dir/viewer3D-1-points.cpp.s

examples/io/viewers/CMakeFiles/viewer3D-1-points.dir/viewer3D-1-points.cpp.o.requires:
.PHONY : examples/io/viewers/CMakeFiles/viewer3D-1-points.dir/viewer3D-1-points.cpp.o.requires

examples/io/viewers/CMakeFiles/viewer3D-1-points.dir/viewer3D-1-points.cpp.o.provides: examples/io/viewers/CMakeFiles/viewer3D-1-points.dir/viewer3D-1-points.cpp.o.requires
	$(MAKE) -f examples/io/viewers/CMakeFiles/viewer3D-1-points.dir/build.make examples/io/viewers/CMakeFiles/viewer3D-1-points.dir/viewer3D-1-points.cpp.o.provides.build
.PHONY : examples/io/viewers/CMakeFiles/viewer3D-1-points.dir/viewer3D-1-points.cpp.o.provides

examples/io/viewers/CMakeFiles/viewer3D-1-points.dir/viewer3D-1-points.cpp.o.provides.build: examples/io/viewers/CMakeFiles/viewer3D-1-points.dir/viewer3D-1-points.cpp.o

# Object files for target viewer3D-1-points
viewer3D__1__points_OBJECTS = \
"CMakeFiles/viewer3D-1-points.dir/viewer3D-1-points.cpp.o"

# External object files for target viewer3D-1-points
viewer3D__1__points_EXTERNAL_OBJECTS =

examples/io/viewers/viewer3D-1-points: examples/io/viewers/CMakeFiles/viewer3D-1-points.dir/viewer3D-1-points.cpp.o
examples/io/viewers/viewer3D-1-points: src/libDGtal-visu3d.dylib
examples/io/viewers/viewer3D-1-points: src/libDGtal.dylib
examples/io/viewers/viewer3D-1-points: /usr/local/lib/libboost_program_options-mt.a
examples/io/viewers/viewer3D-1-points: examples/io/viewers/CMakeFiles/viewer3D-1-points.dir/build.make
examples/io/viewers/viewer3D-1-points: examples/io/viewers/CMakeFiles/viewer3D-1-points.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable viewer3D-1-points"
	cd /Users/davidcoeurjolly/Sources/DGtal/build/examples/io/viewers && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/viewer3D-1-points.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/io/viewers/CMakeFiles/viewer3D-1-points.dir/build: examples/io/viewers/viewer3D-1-points
.PHONY : examples/io/viewers/CMakeFiles/viewer3D-1-points.dir/build

examples/io/viewers/CMakeFiles/viewer3D-1-points.dir/requires: examples/io/viewers/CMakeFiles/viewer3D-1-points.dir/viewer3D-1-points.cpp.o.requires
.PHONY : examples/io/viewers/CMakeFiles/viewer3D-1-points.dir/requires

examples/io/viewers/CMakeFiles/viewer3D-1-points.dir/clean:
	cd /Users/davidcoeurjolly/Sources/DGtal/build/examples/io/viewers && $(CMAKE_COMMAND) -P CMakeFiles/viewer3D-1-points.dir/cmake_clean.cmake
.PHONY : examples/io/viewers/CMakeFiles/viewer3D-1-points.dir/clean

examples/io/viewers/CMakeFiles/viewer3D-1-points.dir/depend:
	cd /Users/davidcoeurjolly/Sources/DGtal/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/davidcoeurjolly/Sources/DGtal /Users/davidcoeurjolly/Sources/DGtal/examples/io/viewers /Users/davidcoeurjolly/Sources/DGtal/build /Users/davidcoeurjolly/Sources/DGtal/build/examples/io/viewers /Users/davidcoeurjolly/Sources/DGtal/build/examples/io/viewers/CMakeFiles/viewer3D-1-points.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/io/viewers/CMakeFiles/viewer3D-1-points.dir/depend

