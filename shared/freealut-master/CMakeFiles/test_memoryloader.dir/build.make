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
CMAKE_SOURCE_DIR = /home/rickysimon/Desktop/cs488/A5/shared/freealut-master

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/rickysimon/Desktop/cs488/A5/shared/freealut-master

# Include any dependencies generated for this target.
include CMakeFiles/test_memoryloader.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/test_memoryloader.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/test_memoryloader.dir/flags.make

CMakeFiles/test_memoryloader.dir/test_suite/test_memoryloader.c.o: CMakeFiles/test_memoryloader.dir/flags.make
CMakeFiles/test_memoryloader.dir/test_suite/test_memoryloader.c.o: test_suite/test_memoryloader.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/rickysimon/Desktop/cs488/A5/shared/freealut-master/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/test_memoryloader.dir/test_suite/test_memoryloader.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -Wno-deprecated-declarations -o CMakeFiles/test_memoryloader.dir/test_suite/test_memoryloader.c.o   -c /home/rickysimon/Desktop/cs488/A5/shared/freealut-master/test_suite/test_memoryloader.c

CMakeFiles/test_memoryloader.dir/test_suite/test_memoryloader.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/test_memoryloader.dir/test_suite/test_memoryloader.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -Wno-deprecated-declarations -E /home/rickysimon/Desktop/cs488/A5/shared/freealut-master/test_suite/test_memoryloader.c > CMakeFiles/test_memoryloader.dir/test_suite/test_memoryloader.c.i

CMakeFiles/test_memoryloader.dir/test_suite/test_memoryloader.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/test_memoryloader.dir/test_suite/test_memoryloader.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -Wno-deprecated-declarations -S /home/rickysimon/Desktop/cs488/A5/shared/freealut-master/test_suite/test_memoryloader.c -o CMakeFiles/test_memoryloader.dir/test_suite/test_memoryloader.c.s

CMakeFiles/test_memoryloader.dir/test_suite/test_memoryloader.c.o.requires:
.PHONY : CMakeFiles/test_memoryloader.dir/test_suite/test_memoryloader.c.o.requires

CMakeFiles/test_memoryloader.dir/test_suite/test_memoryloader.c.o.provides: CMakeFiles/test_memoryloader.dir/test_suite/test_memoryloader.c.o.requires
	$(MAKE) -f CMakeFiles/test_memoryloader.dir/build.make CMakeFiles/test_memoryloader.dir/test_suite/test_memoryloader.c.o.provides.build
.PHONY : CMakeFiles/test_memoryloader.dir/test_suite/test_memoryloader.c.o.provides

CMakeFiles/test_memoryloader.dir/test_suite/test_memoryloader.c.o.provides.build: CMakeFiles/test_memoryloader.dir/test_suite/test_memoryloader.c.o

# Object files for target test_memoryloader
test_memoryloader_OBJECTS = \
"CMakeFiles/test_memoryloader.dir/test_suite/test_memoryloader.c.o"

# External object files for target test_memoryloader
test_memoryloader_EXTERNAL_OBJECTS =

test_memoryloader: CMakeFiles/test_memoryloader.dir/test_suite/test_memoryloader.c.o
test_memoryloader: CMakeFiles/test_memoryloader.dir/build.make
test_memoryloader: src/libalut.so.0
test_memoryloader: /usr/lib/x86_64-linux-gnu/libopenal.so
test_memoryloader: CMakeFiles/test_memoryloader.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable test_memoryloader"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_memoryloader.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/test_memoryloader.dir/build: test_memoryloader
.PHONY : CMakeFiles/test_memoryloader.dir/build

CMakeFiles/test_memoryloader.dir/requires: CMakeFiles/test_memoryloader.dir/test_suite/test_memoryloader.c.o.requires
.PHONY : CMakeFiles/test_memoryloader.dir/requires

CMakeFiles/test_memoryloader.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/test_memoryloader.dir/cmake_clean.cmake
.PHONY : CMakeFiles/test_memoryloader.dir/clean

CMakeFiles/test_memoryloader.dir/depend:
	cd /home/rickysimon/Desktop/cs488/A5/shared/freealut-master && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/rickysimon/Desktop/cs488/A5/shared/freealut-master /home/rickysimon/Desktop/cs488/A5/shared/freealut-master /home/rickysimon/Desktop/cs488/A5/shared/freealut-master /home/rickysimon/Desktop/cs488/A5/shared/freealut-master /home/rickysimon/Desktop/cs488/A5/shared/freealut-master/CMakeFiles/test_memoryloader.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/test_memoryloader.dir/depend

