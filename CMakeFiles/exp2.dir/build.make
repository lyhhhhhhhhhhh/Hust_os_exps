# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/lyhhhhh/study/Operating_System/exp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/lyhhhhh/study/Operating_System/exp

# Include any dependencies generated for this target.
include CMakeFiles/exp2.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/exp2.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/exp2.dir/flags.make

CMakeFiles/exp2.dir/src/exp2.c.o: CMakeFiles/exp2.dir/flags.make
CMakeFiles/exp2.dir/src/exp2.c.o: src/exp2.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lyhhhhh/study/Operating_System/exp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/exp2.dir/src/exp2.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/exp2.dir/src/exp2.c.o   -c /home/lyhhhhh/study/Operating_System/exp/src/exp2.c

CMakeFiles/exp2.dir/src/exp2.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/exp2.dir/src/exp2.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/lyhhhhh/study/Operating_System/exp/src/exp2.c > CMakeFiles/exp2.dir/src/exp2.c.i

CMakeFiles/exp2.dir/src/exp2.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/exp2.dir/src/exp2.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/lyhhhhh/study/Operating_System/exp/src/exp2.c -o CMakeFiles/exp2.dir/src/exp2.c.s

# Object files for target exp2
exp2_OBJECTS = \
"CMakeFiles/exp2.dir/src/exp2.c.o"

# External object files for target exp2
exp2_EXTERNAL_OBJECTS =

bin/exp2: CMakeFiles/exp2.dir/src/exp2.c.o
bin/exp2: CMakeFiles/exp2.dir/build.make
bin/exp2: CMakeFiles/exp2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/lyhhhhh/study/Operating_System/exp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable bin/exp2"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/exp2.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/exp2.dir/build: bin/exp2

.PHONY : CMakeFiles/exp2.dir/build

CMakeFiles/exp2.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/exp2.dir/cmake_clean.cmake
.PHONY : CMakeFiles/exp2.dir/clean

CMakeFiles/exp2.dir/depend:
	cd /home/lyhhhhh/study/Operating_System/exp && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lyhhhhh/study/Operating_System/exp /home/lyhhhhh/study/Operating_System/exp /home/lyhhhhh/study/Operating_System/exp /home/lyhhhhh/study/Operating_System/exp /home/lyhhhhh/study/Operating_System/exp/CMakeFiles/exp2.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/exp2.dir/depend

