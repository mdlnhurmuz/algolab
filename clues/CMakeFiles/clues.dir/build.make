# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.15.5/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.15.5/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/madalinahurmuz/Documents/GitHub/algolab/clues

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/madalinahurmuz/Documents/GitHub/algolab/clues

# Include any dependencies generated for this target.
include CMakeFiles/clues.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/clues.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/clues.dir/flags.make

CMakeFiles/clues.dir/clues.cpp.o: CMakeFiles/clues.dir/flags.make
CMakeFiles/clues.dir/clues.cpp.o: clues.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/madalinahurmuz/Documents/GitHub/algolab/clues/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/clues.dir/clues.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/clues.dir/clues.cpp.o -c /Users/madalinahurmuz/Documents/GitHub/algolab/clues/clues.cpp

CMakeFiles/clues.dir/clues.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/clues.dir/clues.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/madalinahurmuz/Documents/GitHub/algolab/clues/clues.cpp > CMakeFiles/clues.dir/clues.cpp.i

CMakeFiles/clues.dir/clues.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/clues.dir/clues.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/madalinahurmuz/Documents/GitHub/algolab/clues/clues.cpp -o CMakeFiles/clues.dir/clues.cpp.s

# Object files for target clues
clues_OBJECTS = \
"CMakeFiles/clues.dir/clues.cpp.o"

# External object files for target clues
clues_EXTERNAL_OBJECTS =

clues: CMakeFiles/clues.dir/clues.cpp.o
clues: CMakeFiles/clues.dir/build.make
clues: /usr/local/lib/libCGAL.13.0.3.dylib
clues: /usr/local/lib/libmpfr.dylib
clues: /usr/local/lib/libgmp.dylib
clues: /usr/local/lib/libboost_thread-mt.dylib
clues: /usr/local/lib/libboost_system-mt.dylib
clues: /usr/local/lib/libboost_chrono-mt.dylib
clues: /usr/local/lib/libboost_date_time-mt.dylib
clues: /usr/local/lib/libboost_atomic-mt.dylib
clues: /usr/local/lib/libboost_thread-mt.dylib
clues: CMakeFiles/clues.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/madalinahurmuz/Documents/GitHub/algolab/clues/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable clues"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/clues.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/clues.dir/build: clues

.PHONY : CMakeFiles/clues.dir/build

CMakeFiles/clues.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/clues.dir/cmake_clean.cmake
.PHONY : CMakeFiles/clues.dir/clean

CMakeFiles/clues.dir/depend:
	cd /Users/madalinahurmuz/Documents/GitHub/algolab/clues && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/madalinahurmuz/Documents/GitHub/algolab/clues /Users/madalinahurmuz/Documents/GitHub/algolab/clues /Users/madalinahurmuz/Documents/GitHub/algolab/clues /Users/madalinahurmuz/Documents/GitHub/algolab/clues /Users/madalinahurmuz/Documents/GitHub/algolab/clues/CMakeFiles/clues.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/clues.dir/depend

