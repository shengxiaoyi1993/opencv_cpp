# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

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
CMAKE_SOURCE_DIR = /home/sxy/Github/opencv_cpp/start/opencv-3.4.1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/sxy/Github/opencv_cpp/start/opencv-3.4.1/build/build_main

# Utility rule file for pch_Generate_opencv_videoio.

# Include the progress variables for this target.
include modules/videoio/CMakeFiles/pch_Generate_opencv_videoio.dir/progress.make

modules/videoio/CMakeFiles/pch_Generate_opencv_videoio: modules/videoio/precomp.hpp.gch/opencv_videoio_Release.gch


modules/videoio/precomp.hpp.gch/opencv_videoio_Release.gch: ../../modules/videoio/src/precomp.hpp
modules/videoio/precomp.hpp.gch/opencv_videoio_Release.gch: modules/videoio/precomp.hpp
modules/videoio/precomp.hpp.gch/opencv_videoio_Release.gch: lib/libopencv_videoio_pch_dephelp.a
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/sxy/Github/opencv_cpp/start/opencv-3.4.1/build/build_main/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating precomp.hpp.gch/opencv_videoio_Release.gch"
	cd /home/sxy/Github/opencv_cpp/start/opencv-3.4.1/build/build_main/modules/videoio && /usr/local/bin/cmake -E make_directory /home/sxy/Github/opencv_cpp/start/opencv-3.4.1/build/build_main/modules/videoio/precomp.hpp.gch
	cd /home/sxy/Github/opencv_cpp/start/opencv-3.4.1/build/build_main/modules/videoio && /usr/bin/c++ -O3 -DNDEBUG -DNDEBUG -fPIC "-D__OPENCV_BUILD=1" "-D_USE_MATH_DEFINES" "-D__STDC_CONSTANT_MACROS" "-D__STDC_LIMIT_MACROS" "-D__STDC_FORMAT_MACROS" -std=c++11 -I"/home/sxy/Github/opencv_cpp/start/opencv-3.4.1/build/build_main" -I"/home/sxy/Github/opencv_cpp/start/opencv-3.4.1/build/build_main" -I"/home/sxy/Github/opencv_cpp/start/opencv-3.4.1/modules/videoio/include" -I"/home/sxy/Github/opencv_cpp/start/opencv-3.4.1/modules/videoio/src" -I"/home/sxy/Github/opencv_cpp/start/opencv-3.4.1/build/build_main/modules/videoio" -I"/home/sxy/Github/opencv_cpp/start/opencv-3.4.1/modules/core/include" -I"/home/sxy/Github/opencv_cpp/start/opencv-3.4.1/modules/imgproc/include" -I"/home/sxy/Github/opencv_cpp/start/opencv-3.4.1/modules/imgcodecs/include" -fsigned-char -W -Wall -Werror=return-type -Werror=non-virtual-dtor -Werror=address -Werror=sequence-point -Wformat -Werror=format-security -Wmissing-declarations -Wundef -Winit-self -Wpointer-arith -Wshadow -Wsign-promo -Wuninitialized -Winit-self -Wno-narrowing -Wno-delete-non-virtual-dtor -Wno-comment -fdiagnostics-show-option -Wno-long-long -pthread -fomit-frame-pointer -ffunction-sections -fdata-sections -msse -msse2 -msse3 -fvisibility=hidden -fvisibility-inlines-hidden -DCVAPI_EXPORTS -fPIC -x c++-header -o /home/sxy/Github/opencv_cpp/start/opencv-3.4.1/build/build_main/modules/videoio/precomp.hpp.gch/opencv_videoio_Release.gch /home/sxy/Github/opencv_cpp/start/opencv-3.4.1/build/build_main/modules/videoio/precomp.hpp

modules/videoio/precomp.hpp: ../../modules/videoio/src/precomp.hpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/sxy/Github/opencv_cpp/start/opencv-3.4.1/build/build_main/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Generating precomp.hpp"
	cd /home/sxy/Github/opencv_cpp/start/opencv-3.4.1/build/build_main/modules/videoio && /usr/local/bin/cmake -E copy_if_different /home/sxy/Github/opencv_cpp/start/opencv-3.4.1/modules/videoio/src/precomp.hpp /home/sxy/Github/opencv_cpp/start/opencv-3.4.1/build/build_main/modules/videoio/precomp.hpp

pch_Generate_opencv_videoio: modules/videoio/CMakeFiles/pch_Generate_opencv_videoio
pch_Generate_opencv_videoio: modules/videoio/precomp.hpp.gch/opencv_videoio_Release.gch
pch_Generate_opencv_videoio: modules/videoio/precomp.hpp
pch_Generate_opencv_videoio: modules/videoio/CMakeFiles/pch_Generate_opencv_videoio.dir/build.make

.PHONY : pch_Generate_opencv_videoio

# Rule to build all files generated by this target.
modules/videoio/CMakeFiles/pch_Generate_opencv_videoio.dir/build: pch_Generate_opencv_videoio

.PHONY : modules/videoio/CMakeFiles/pch_Generate_opencv_videoio.dir/build

modules/videoio/CMakeFiles/pch_Generate_opencv_videoio.dir/clean:
	cd /home/sxy/Github/opencv_cpp/start/opencv-3.4.1/build/build_main/modules/videoio && $(CMAKE_COMMAND) -P CMakeFiles/pch_Generate_opencv_videoio.dir/cmake_clean.cmake
.PHONY : modules/videoio/CMakeFiles/pch_Generate_opencv_videoio.dir/clean

modules/videoio/CMakeFiles/pch_Generate_opencv_videoio.dir/depend:
	cd /home/sxy/Github/opencv_cpp/start/opencv-3.4.1/build/build_main && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/sxy/Github/opencv_cpp/start/opencv-3.4.1 /home/sxy/Github/opencv_cpp/start/opencv-3.4.1/modules/videoio /home/sxy/Github/opencv_cpp/start/opencv-3.4.1/build/build_main /home/sxy/Github/opencv_cpp/start/opencv-3.4.1/build/build_main/modules/videoio /home/sxy/Github/opencv_cpp/start/opencv-3.4.1/build/build_main/modules/videoio/CMakeFiles/pch_Generate_opencv_videoio.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : modules/videoio/CMakeFiles/pch_Generate_opencv_videoio.dir/depend
