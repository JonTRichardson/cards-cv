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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/pi/proj/opencv/opencv-3.4.1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/pi/proj/opencv/opencv-3.4.1/build

# Utility rule file for opencv_samples_tutorial.

# Include the progress variables for this target.
include samples/cpp/CMakeFiles/opencv_samples_tutorial.dir/progress.make

opencv_samples_tutorial: samples/cpp/CMakeFiles/opencv_samples_tutorial.dir/build.make

.PHONY : opencv_samples_tutorial

# Rule to build all files generated by this target.
samples/cpp/CMakeFiles/opencv_samples_tutorial.dir/build: opencv_samples_tutorial

.PHONY : samples/cpp/CMakeFiles/opencv_samples_tutorial.dir/build

samples/cpp/CMakeFiles/opencv_samples_tutorial.dir/clean:
	cd /home/pi/proj/opencv/opencv-3.4.1/build/samples/cpp && $(CMAKE_COMMAND) -P CMakeFiles/opencv_samples_tutorial.dir/cmake_clean.cmake
.PHONY : samples/cpp/CMakeFiles/opencv_samples_tutorial.dir/clean

samples/cpp/CMakeFiles/opencv_samples_tutorial.dir/depend:
	cd /home/pi/proj/opencv/opencv-3.4.1/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pi/proj/opencv/opencv-3.4.1 /home/pi/proj/opencv/opencv-3.4.1/samples/cpp /home/pi/proj/opencv/opencv-3.4.1/build /home/pi/proj/opencv/opencv-3.4.1/build/samples/cpp /home/pi/proj/opencv/opencv-3.4.1/build/samples/cpp/CMakeFiles/opencv_samples_tutorial.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : samples/cpp/CMakeFiles/opencv_samples_tutorial.dir/depend

