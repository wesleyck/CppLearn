# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.21

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /mnt/hgfs/0voice/vip/cplusplus/src2-cmake

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/hgfs/0voice/vip/cplusplus/src2-cmake/build

# Include any dependencies generated for this target.
include CMakeFiles/3-1-variable-parameter3.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/3-1-variable-parameter3.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/3-1-variable-parameter3.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/3-1-variable-parameter3.dir/flags.make

CMakeFiles/3-1-variable-parameter3.dir/3-1-variable-parameter3.cpp.o: CMakeFiles/3-1-variable-parameter3.dir/flags.make
CMakeFiles/3-1-variable-parameter3.dir/3-1-variable-parameter3.cpp.o: ../3-1-variable-parameter3.cpp
CMakeFiles/3-1-variable-parameter3.dir/3-1-variable-parameter3.cpp.o: CMakeFiles/3-1-variable-parameter3.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/hgfs/0voice/vip/cplusplus/src2-cmake/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/3-1-variable-parameter3.dir/3-1-variable-parameter3.cpp.o"
	/usr/local/gcc-11.2/bin/g++-11.2 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/3-1-variable-parameter3.dir/3-1-variable-parameter3.cpp.o -MF CMakeFiles/3-1-variable-parameter3.dir/3-1-variable-parameter3.cpp.o.d -o CMakeFiles/3-1-variable-parameter3.dir/3-1-variable-parameter3.cpp.o -c /mnt/hgfs/0voice/vip/cplusplus/src2-cmake/3-1-variable-parameter3.cpp

CMakeFiles/3-1-variable-parameter3.dir/3-1-variable-parameter3.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/3-1-variable-parameter3.dir/3-1-variable-parameter3.cpp.i"
	/usr/local/gcc-11.2/bin/g++-11.2 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/hgfs/0voice/vip/cplusplus/src2-cmake/3-1-variable-parameter3.cpp > CMakeFiles/3-1-variable-parameter3.dir/3-1-variable-parameter3.cpp.i

CMakeFiles/3-1-variable-parameter3.dir/3-1-variable-parameter3.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/3-1-variable-parameter3.dir/3-1-variable-parameter3.cpp.s"
	/usr/local/gcc-11.2/bin/g++-11.2 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/hgfs/0voice/vip/cplusplus/src2-cmake/3-1-variable-parameter3.cpp -o CMakeFiles/3-1-variable-parameter3.dir/3-1-variable-parameter3.cpp.s

# Object files for target 3-1-variable-parameter3
3__1__variable__parameter3_OBJECTS = \
"CMakeFiles/3-1-variable-parameter3.dir/3-1-variable-parameter3.cpp.o"

# External object files for target 3-1-variable-parameter3
3__1__variable__parameter3_EXTERNAL_OBJECTS =

3-1-variable-parameter3: CMakeFiles/3-1-variable-parameter3.dir/3-1-variable-parameter3.cpp.o
3-1-variable-parameter3: CMakeFiles/3-1-variable-parameter3.dir/build.make
3-1-variable-parameter3: CMakeFiles/3-1-variable-parameter3.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/hgfs/0voice/vip/cplusplus/src2-cmake/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable 3-1-variable-parameter3"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/3-1-variable-parameter3.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/3-1-variable-parameter3.dir/build: 3-1-variable-parameter3
.PHONY : CMakeFiles/3-1-variable-parameter3.dir/build

CMakeFiles/3-1-variable-parameter3.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/3-1-variable-parameter3.dir/cmake_clean.cmake
.PHONY : CMakeFiles/3-1-variable-parameter3.dir/clean

CMakeFiles/3-1-variable-parameter3.dir/depend:
	cd /mnt/hgfs/0voice/vip/cplusplus/src2-cmake/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/hgfs/0voice/vip/cplusplus/src2-cmake /mnt/hgfs/0voice/vip/cplusplus/src2-cmake /mnt/hgfs/0voice/vip/cplusplus/src2-cmake/build /mnt/hgfs/0voice/vip/cplusplus/src2-cmake/build /mnt/hgfs/0voice/vip/cplusplus/src2-cmake/build/CMakeFiles/3-1-variable-parameter3.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/3-1-variable-parameter3.dir/depend

