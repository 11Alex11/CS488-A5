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
include examples/CMakeFiles/playfile.dir/depend.make

# Include the progress variables for this target.
include examples/CMakeFiles/playfile.dir/progress.make

# Include the compile flags for this target's objects.
include examples/CMakeFiles/playfile.dir/flags.make

examples/CMakeFiles/playfile.dir/playfile.c.o: examples/CMakeFiles/playfile.dir/flags.make
examples/CMakeFiles/playfile.dir/playfile.c.o: examples/playfile.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/rickysimon/Desktop/cs488/A5/shared/freealut-master/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object examples/CMakeFiles/playfile.dir/playfile.c.o"
	cd /home/rickysimon/Desktop/cs488/A5/shared/freealut-master/examples && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/playfile.dir/playfile.c.o   -c /home/rickysimon/Desktop/cs488/A5/shared/freealut-master/examples/playfile.c

examples/CMakeFiles/playfile.dir/playfile.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/playfile.dir/playfile.c.i"
	cd /home/rickysimon/Desktop/cs488/A5/shared/freealut-master/examples && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/rickysimon/Desktop/cs488/A5/shared/freealut-master/examples/playfile.c > CMakeFiles/playfile.dir/playfile.c.i

examples/CMakeFiles/playfile.dir/playfile.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/playfile.dir/playfile.c.s"
	cd /home/rickysimon/Desktop/cs488/A5/shared/freealut-master/examples && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/rickysimon/Desktop/cs488/A5/shared/freealut-master/examples/playfile.c -o CMakeFiles/playfile.dir/playfile.c.s

examples/CMakeFiles/playfile.dir/playfile.c.o.requires:
.PHONY : examples/CMakeFiles/playfile.dir/playfile.c.o.requires

examples/CMakeFiles/playfile.dir/playfile.c.o.provides: examples/CMakeFiles/playfile.dir/playfile.c.o.requires
	$(MAKE) -f examples/CMakeFiles/playfile.dir/build.make examples/CMakeFiles/playfile.dir/playfile.c.o.provides.build
.PHONY : examples/CMakeFiles/playfile.dir/playfile.c.o.provides

examples/CMakeFiles/playfile.dir/playfile.c.o.provides.build: examples/CMakeFiles/playfile.dir/playfile.c.o

# Object files for target playfile
playfile_OBJECTS = \
"CMakeFiles/playfile.dir/playfile.c.o"

# External object files for target playfile
playfile_EXTERNAL_OBJECTS =

examples/playfile: examples/CMakeFiles/playfile.dir/playfile.c.o
examples/playfile: examples/CMakeFiles/playfile.dir/build.make
examples/playfile: src/libalut.so.0
examples/playfile: /usr/lib/x86_64-linux-gnu/libopenal.so
examples/playfile: examples/CMakeFiles/playfile.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable playfile"
	cd /home/rickysimon/Desktop/cs488/A5/shared/freealut-master/examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/playfile.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/CMakeFiles/playfile.dir/build: examples/playfile
.PHONY : examples/CMakeFiles/playfile.dir/build

examples/CMakeFiles/playfile.dir/requires: examples/CMakeFiles/playfile.dir/playfile.c.o.requires
.PHONY : examples/CMakeFiles/playfile.dir/requires

examples/CMakeFiles/playfile.dir/clean:
	cd /home/rickysimon/Desktop/cs488/A5/shared/freealut-master/examples && $(CMAKE_COMMAND) -P CMakeFiles/playfile.dir/cmake_clean.cmake
.PHONY : examples/CMakeFiles/playfile.dir/clean

examples/CMakeFiles/playfile.dir/depend:
	cd /home/rickysimon/Desktop/cs488/A5/shared/freealut-master && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/rickysimon/Desktop/cs488/A5/shared/freealut-master /home/rickysimon/Desktop/cs488/A5/shared/freealut-master/examples /home/rickysimon/Desktop/cs488/A5/shared/freealut-master /home/rickysimon/Desktop/cs488/A5/shared/freealut-master/examples /home/rickysimon/Desktop/cs488/A5/shared/freealut-master/examples/CMakeFiles/playfile.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/CMakeFiles/playfile.dir/depend

