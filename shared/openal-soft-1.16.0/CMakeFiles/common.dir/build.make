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
CMAKE_SOURCE_DIR = /home/rickysimon/Desktop/cs488/A5/shared/openal-soft-1.16.0

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/rickysimon/Desktop/cs488/A5/shared/openal-soft-1.16.0

# Include any dependencies generated for this target.
include CMakeFiles/common.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/common.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/common.dir/flags.make

CMakeFiles/common.dir/common/atomic.c.o: CMakeFiles/common.dir/flags.make
CMakeFiles/common.dir/common/atomic.c.o: common/atomic.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/rickysimon/Desktop/cs488/A5/shared/openal-soft-1.16.0/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/common.dir/common/atomic.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/common.dir/common/atomic.c.o   -c /home/rickysimon/Desktop/cs488/A5/shared/openal-soft-1.16.0/common/atomic.c

CMakeFiles/common.dir/common/atomic.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/common.dir/common/atomic.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/rickysimon/Desktop/cs488/A5/shared/openal-soft-1.16.0/common/atomic.c > CMakeFiles/common.dir/common/atomic.c.i

CMakeFiles/common.dir/common/atomic.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/common.dir/common/atomic.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/rickysimon/Desktop/cs488/A5/shared/openal-soft-1.16.0/common/atomic.c -o CMakeFiles/common.dir/common/atomic.c.s

CMakeFiles/common.dir/common/atomic.c.o.requires:
.PHONY : CMakeFiles/common.dir/common/atomic.c.o.requires

CMakeFiles/common.dir/common/atomic.c.o.provides: CMakeFiles/common.dir/common/atomic.c.o.requires
	$(MAKE) -f CMakeFiles/common.dir/build.make CMakeFiles/common.dir/common/atomic.c.o.provides.build
.PHONY : CMakeFiles/common.dir/common/atomic.c.o.provides

CMakeFiles/common.dir/common/atomic.c.o.provides.build: CMakeFiles/common.dir/common/atomic.c.o

CMakeFiles/common.dir/common/rwlock.c.o: CMakeFiles/common.dir/flags.make
CMakeFiles/common.dir/common/rwlock.c.o: common/rwlock.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/rickysimon/Desktop/cs488/A5/shared/openal-soft-1.16.0/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/common.dir/common/rwlock.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/common.dir/common/rwlock.c.o   -c /home/rickysimon/Desktop/cs488/A5/shared/openal-soft-1.16.0/common/rwlock.c

CMakeFiles/common.dir/common/rwlock.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/common.dir/common/rwlock.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/rickysimon/Desktop/cs488/A5/shared/openal-soft-1.16.0/common/rwlock.c > CMakeFiles/common.dir/common/rwlock.c.i

CMakeFiles/common.dir/common/rwlock.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/common.dir/common/rwlock.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/rickysimon/Desktop/cs488/A5/shared/openal-soft-1.16.0/common/rwlock.c -o CMakeFiles/common.dir/common/rwlock.c.s

CMakeFiles/common.dir/common/rwlock.c.o.requires:
.PHONY : CMakeFiles/common.dir/common/rwlock.c.o.requires

CMakeFiles/common.dir/common/rwlock.c.o.provides: CMakeFiles/common.dir/common/rwlock.c.o.requires
	$(MAKE) -f CMakeFiles/common.dir/build.make CMakeFiles/common.dir/common/rwlock.c.o.provides.build
.PHONY : CMakeFiles/common.dir/common/rwlock.c.o.provides

CMakeFiles/common.dir/common/rwlock.c.o.provides.build: CMakeFiles/common.dir/common/rwlock.c.o

CMakeFiles/common.dir/common/threads.c.o: CMakeFiles/common.dir/flags.make
CMakeFiles/common.dir/common/threads.c.o: common/threads.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/rickysimon/Desktop/cs488/A5/shared/openal-soft-1.16.0/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/common.dir/common/threads.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/common.dir/common/threads.c.o   -c /home/rickysimon/Desktop/cs488/A5/shared/openal-soft-1.16.0/common/threads.c

CMakeFiles/common.dir/common/threads.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/common.dir/common/threads.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/rickysimon/Desktop/cs488/A5/shared/openal-soft-1.16.0/common/threads.c > CMakeFiles/common.dir/common/threads.c.i

CMakeFiles/common.dir/common/threads.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/common.dir/common/threads.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/rickysimon/Desktop/cs488/A5/shared/openal-soft-1.16.0/common/threads.c -o CMakeFiles/common.dir/common/threads.c.s

CMakeFiles/common.dir/common/threads.c.o.requires:
.PHONY : CMakeFiles/common.dir/common/threads.c.o.requires

CMakeFiles/common.dir/common/threads.c.o.provides: CMakeFiles/common.dir/common/threads.c.o.requires
	$(MAKE) -f CMakeFiles/common.dir/build.make CMakeFiles/common.dir/common/threads.c.o.provides.build
.PHONY : CMakeFiles/common.dir/common/threads.c.o.provides

CMakeFiles/common.dir/common/threads.c.o.provides.build: CMakeFiles/common.dir/common/threads.c.o

CMakeFiles/common.dir/common/uintmap.c.o: CMakeFiles/common.dir/flags.make
CMakeFiles/common.dir/common/uintmap.c.o: common/uintmap.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/rickysimon/Desktop/cs488/A5/shared/openal-soft-1.16.0/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/common.dir/common/uintmap.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/common.dir/common/uintmap.c.o   -c /home/rickysimon/Desktop/cs488/A5/shared/openal-soft-1.16.0/common/uintmap.c

CMakeFiles/common.dir/common/uintmap.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/common.dir/common/uintmap.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/rickysimon/Desktop/cs488/A5/shared/openal-soft-1.16.0/common/uintmap.c > CMakeFiles/common.dir/common/uintmap.c.i

CMakeFiles/common.dir/common/uintmap.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/common.dir/common/uintmap.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/rickysimon/Desktop/cs488/A5/shared/openal-soft-1.16.0/common/uintmap.c -o CMakeFiles/common.dir/common/uintmap.c.s

CMakeFiles/common.dir/common/uintmap.c.o.requires:
.PHONY : CMakeFiles/common.dir/common/uintmap.c.o.requires

CMakeFiles/common.dir/common/uintmap.c.o.provides: CMakeFiles/common.dir/common/uintmap.c.o.requires
	$(MAKE) -f CMakeFiles/common.dir/build.make CMakeFiles/common.dir/common/uintmap.c.o.provides.build
.PHONY : CMakeFiles/common.dir/common/uintmap.c.o.provides

CMakeFiles/common.dir/common/uintmap.c.o.provides.build: CMakeFiles/common.dir/common/uintmap.c.o

# Object files for target common
common_OBJECTS = \
"CMakeFiles/common.dir/common/atomic.c.o" \
"CMakeFiles/common.dir/common/rwlock.c.o" \
"CMakeFiles/common.dir/common/threads.c.o" \
"CMakeFiles/common.dir/common/uintmap.c.o"

# External object files for target common
common_EXTERNAL_OBJECTS =

libcommon.a: CMakeFiles/common.dir/common/atomic.c.o
libcommon.a: CMakeFiles/common.dir/common/rwlock.c.o
libcommon.a: CMakeFiles/common.dir/common/threads.c.o
libcommon.a: CMakeFiles/common.dir/common/uintmap.c.o
libcommon.a: CMakeFiles/common.dir/build.make
libcommon.a: CMakeFiles/common.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C static library libcommon.a"
	$(CMAKE_COMMAND) -P CMakeFiles/common.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/common.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/common.dir/build: libcommon.a
.PHONY : CMakeFiles/common.dir/build

CMakeFiles/common.dir/requires: CMakeFiles/common.dir/common/atomic.c.o.requires
CMakeFiles/common.dir/requires: CMakeFiles/common.dir/common/rwlock.c.o.requires
CMakeFiles/common.dir/requires: CMakeFiles/common.dir/common/threads.c.o.requires
CMakeFiles/common.dir/requires: CMakeFiles/common.dir/common/uintmap.c.o.requires
.PHONY : CMakeFiles/common.dir/requires

CMakeFiles/common.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/common.dir/cmake_clean.cmake
.PHONY : CMakeFiles/common.dir/clean

CMakeFiles/common.dir/depend:
	cd /home/rickysimon/Desktop/cs488/A5/shared/openal-soft-1.16.0 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/rickysimon/Desktop/cs488/A5/shared/openal-soft-1.16.0 /home/rickysimon/Desktop/cs488/A5/shared/openal-soft-1.16.0 /home/rickysimon/Desktop/cs488/A5/shared/openal-soft-1.16.0 /home/rickysimon/Desktop/cs488/A5/shared/openal-soft-1.16.0 /home/rickysimon/Desktop/cs488/A5/shared/openal-soft-1.16.0/CMakeFiles/common.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/common.dir/depend
