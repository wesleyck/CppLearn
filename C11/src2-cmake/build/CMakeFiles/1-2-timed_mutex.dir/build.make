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
include CMakeFiles/1-2-timed_mutex.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/1-2-timed_mutex.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/1-2-timed_mutex.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/1-2-timed_mutex.dir/flags.make

CMakeFiles/1-2-timed_mutex.dir/1-2-timed_mutex.cpp.o: CMakeFiles/1-2-timed_mutex.dir/flags.make
CMakeFiles/1-2-timed_mutex.dir/1-2-timed_mutex.cpp.o: ../1-2-timed_mutex.cpp
CMakeFiles/1-2-timed_mutex.dir/1-2-timed_mutex.cpp.o: CMakeFiles/1-2-timed_mutex.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/hgfs/0voice/vip/cplusplus/src2-cmake/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/1-2-timed_mutex.dir/1-2-timed_mutex.cpp.o"
	/usr/local/gcc-11.2/bin/g++-11.2 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/1-2-timed_mutex.dir/1-2-timed_mutex.cpp.o -MF CMakeFiles/1-2-timed_mutex.dir/1-2-timed_mutex.cpp.o.d -o CMakeFiles/1-2-timed_mutex.dir/1-2-timed_mutex.cpp.o -c /mnt/hgfs/0voice/vip/cplusplus/src2-cmake/1-2-timed_mutex.cpp

CMakeFiles/1-2-timed_mutex.dir/1-2-timed_mutex.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/1-2-timed_mutex.dir/1-2-timed_mutex.cpp.i"
	/usr/local/gcc-11.2/bin/g++-11.2 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/hgfs/0voice/vip/cplusplus/src2-cmake/1-2-timed_mutex.cpp > CMakeFiles/1-2-timed_mutex.dir/1-2-timed_mutex.cpp.i

CMakeFiles/1-2-timed_mutex.dir/1-2-timed_mutex.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/1-2-timed_mutex.dir/1-2-timed_mutex.cpp.s"
	/usr/local/gcc-11.2/bin/g++-11.2 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/hgfs/0voice/vip/cplusplus/src2-cmake/1-2-timed_mutex.cpp -o CMakeFiles/1-2-timed_mutex.dir/1-2-timed_mutex.cpp.s

# Object files for target 1-2-timed_mutex
1__2__timed_mutex_OBJECTS = \
"CMakeFiles/1-2-timed_mutex.dir/1-2-timed_mutex.cpp.o"

# External object files for target 1-2-timed_mutex
1__2__timed_mutex_EXTERNAL_OBJECTS =

1-2-timed_mutex: CMakeFiles/1-2-timed_mutex.dir/1-2-timed_mutex.cpp.o
1-2-timed_mutex: CMakeFiles/1-2-timed_mutex.dir/build.make
1-2-timed_mutex: CMakeFiles/1-2-timed_mutex.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/hgfs/0voice/vip/cplusplus/src2-cmake/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable 1-2-timed_mutex"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/1-2-timed_mutex.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/1-2-timed_mutex.dir/build: 1-2-timed_mutex
.PHONY : CMakeFiles/1-2-timed_mutex.dir/build

CMakeFiles/1-2-timed_mutex.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/1-2-timed_mutex.dir/cmake_clean.cmake
.PHONY : CMakeFiles/1-2-timed_mutex.dir/clean

CMakeFiles/1-2-timed_mutex.dir/depend:
	cd /mnt/hgfs/0voice/vip/cplusplus/src2-cmake/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/hgfs/0voice/vip/cplusplus/src2-cmake /mnt/hgfs/0voice/vip/cplusplus/src2-cmake /mnt/hgfs/0voice/vip/cplusplus/src2-cmake/build /mnt/hgfs/0voice/vip/cplusplus/src2-cmake/build /mnt/hgfs/0voice/vip/cplusplus/src2-cmake/build/CMakeFiles/1-2-timed_mutex.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/1-2-timed_mutex.dir/depend

