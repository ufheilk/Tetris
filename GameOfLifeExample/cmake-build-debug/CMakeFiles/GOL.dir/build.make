# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.6

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/keaton/Documents/Programming/C++/GOL

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/keaton/Documents/Programming/C++/GOL/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/GOL.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/GOL.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/GOL.dir/flags.make

CMakeFiles/GOL.dir/main.cpp.o: CMakeFiles/GOL.dir/flags.make
CMakeFiles/GOL.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/keaton/Documents/Programming/C++/GOL/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/GOL.dir/main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/GOL.dir/main.cpp.o -c /Users/keaton/Documents/Programming/C++/GOL/main.cpp

CMakeFiles/GOL.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/GOL.dir/main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/keaton/Documents/Programming/C++/GOL/main.cpp > CMakeFiles/GOL.dir/main.cpp.i

CMakeFiles/GOL.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/GOL.dir/main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/keaton/Documents/Programming/C++/GOL/main.cpp -o CMakeFiles/GOL.dir/main.cpp.s

CMakeFiles/GOL.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/GOL.dir/main.cpp.o.requires

CMakeFiles/GOL.dir/main.cpp.o.provides: CMakeFiles/GOL.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/GOL.dir/build.make CMakeFiles/GOL.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/GOL.dir/main.cpp.o.provides

CMakeFiles/GOL.dir/main.cpp.o.provides.build: CMakeFiles/GOL.dir/main.cpp.o


# Object files for target GOL
GOL_OBJECTS = \
"CMakeFiles/GOL.dir/main.cpp.o"

# External object files for target GOL
GOL_EXTERNAL_OBJECTS =

GOL: CMakeFiles/GOL.dir/main.cpp.o
GOL: CMakeFiles/GOL.dir/build.make
GOL: /Users/keaton/Documents/Programming/C++/sfml/lib/libsfml-system.dylib
GOL: /Users/keaton/Documents/Programming/C++/sfml/lib/libsfml-window.dylib
GOL: /Users/keaton/Documents/Programming/C++/sfml/lib/libsfml-graphics.dylib
GOL: CMakeFiles/GOL.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/keaton/Documents/Programming/C++/GOL/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable GOL"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/GOL.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/GOL.dir/build: GOL

.PHONY : CMakeFiles/GOL.dir/build

CMakeFiles/GOL.dir/requires: CMakeFiles/GOL.dir/main.cpp.o.requires

.PHONY : CMakeFiles/GOL.dir/requires

CMakeFiles/GOL.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/GOL.dir/cmake_clean.cmake
.PHONY : CMakeFiles/GOL.dir/clean

CMakeFiles/GOL.dir/depend:
	cd /Users/keaton/Documents/Programming/C++/GOL/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/keaton/Documents/Programming/C++/GOL /Users/keaton/Documents/Programming/C++/GOL /Users/keaton/Documents/Programming/C++/GOL/cmake-build-debug /Users/keaton/Documents/Programming/C++/GOL/cmake-build-debug /Users/keaton/Documents/Programming/C++/GOL/cmake-build-debug/CMakeFiles/GOL.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/GOL.dir/depend

