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

# Utility rule file for pch_Generate_opencv_perf_calib3d.

# Include the progress variables for this target.
include modules/calib3d/CMakeFiles/pch_Generate_opencv_perf_calib3d.dir/progress.make

modules/calib3d/CMakeFiles/pch_Generate_opencv_perf_calib3d: modules/calib3d/perf_precomp.hpp.gch/opencv_perf_calib3d_Release.gch


modules/calib3d/perf_precomp.hpp.gch/opencv_perf_calib3d_Release.gch: ../../modules/calib3d/perf/perf_precomp.hpp
modules/calib3d/perf_precomp.hpp.gch/opencv_perf_calib3d_Release.gch: modules/calib3d/perf_precomp.hpp
modules/calib3d/perf_precomp.hpp.gch/opencv_perf_calib3d_Release.gch: lib/libopencv_perf_calib3d_pch_dephelp.a
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/sxy/Github/opencv_cpp/start/opencv-3.4.1/build/build_main/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating perf_precomp.hpp.gch/opencv_perf_calib3d_Release.gch"
	cd /home/sxy/Github/opencv_cpp/start/opencv-3.4.1/build/build_main/modules/calib3d && /usr/local/bin/cmake -E make_directory /home/sxy/Github/opencv_cpp/start/opencv-3.4.1/build/build_main/modules/calib3d/perf_precomp.hpp.gch
	cd /home/sxy/Github/opencv_cpp/start/opencv-3.4.1/build/build_main/modules/calib3d && /usr/bin/c++ -O3 -DNDEBUG -DNDEBUG "-D__OPENCV_BUILD=1" "-D_USE_MATH_DEFINES" "-D__STDC_CONSTANT_MACROS" "-D__STDC_LIMIT_MACROS" "-D__STDC_FORMAT_MACROS" -std=c++11 -I"/home/sxy/Github/opencv_cpp/start/opencv-3.4.1/build/build_main" -I"/home/sxy/Github/opencv_cpp/start/opencv-3.4.1/build/build_main" -I"/home/sxy/Github/opencv_cpp/start/opencv-3.4.1/modules/ts/include" -I"/home/sxy/Github/opencv_cpp/start/opencv-3.4.1/modules/calib3d/include" -I"/home/sxy/Github/opencv_cpp/start/opencv-3.4.1/modules/imgcodecs/include" -I"/home/sxy/Github/opencv_cpp/start/opencv-3.4.1/modules/core/include" -I"/home/sxy/Github/opencv_cpp/start/opencv-3.4.1/modules/flann/include" -I"/home/sxy/Github/opencv_cpp/start/opencv-3.4.1/modules/imgproc/include" -I"/home/sxy/Github/opencv_cpp/start/opencv-3.4.1/modules/imgcodecs/include" -I"/home/sxy/Github/opencv_cpp/start/opencv-3.4.1/modules/videoio/include" -I"/home/sxy/Github/opencv_cpp/start/opencv-3.4.1/modules/highgui/include" -I"/home/sxy/Github/opencv_cpp/start/opencv-3.4.1/modules/features2d/include" -I"/home/sxy/Github/opencv_cpp/start/opencv-3.4.1/modules/core/include" -I"/home/sxy/Github/opencv_cpp/start/opencv-3.4.1/modules/imgproc/include" -I"/home/sxy/Github/opencv_cpp/start/opencv-3.4.1/modules/imgcodecs/include" -I"/home/sxy/Github/opencv_cpp/start/opencv-3.4.1/modules/videoio/include" -I"/home/sxy/Github/opencv_cpp/start/opencv-3.4.1/modules/highgui/include" -I"/home/sxy/Github/opencv_cpp/start/opencv-3.4.1/modules/calib3d/perf" -fsigned-char -W -Wall -Werror=return-type -Werror=non-virtual-dtor -Werror=address -Werror=sequence-point -Wformat -Werror=format-security -Wmissing-declarations -Wundef -Winit-self -Wpointer-arith -Wshadow -Wsign-promo -Wuninitialized -Winit-self -Wno-narrowing -Wno-delete-non-virtual-dtor -Wno-comment -fdiagnostics-show-option -Wno-long-long -pthread -fomit-frame-pointer -ffunction-sections -fdata-sections -msse -msse2 -msse3 -fvisibility=hidden -fvisibility-inlines-hidden -fPIE -x c++-header -o /home/sxy/Github/opencv_cpp/start/opencv-3.4.1/build/build_main/modules/calib3d/perf_precomp.hpp.gch/opencv_perf_calib3d_Release.gch /home/sxy/Github/opencv_cpp/start/opencv-3.4.1/build/build_main/modules/calib3d/perf_precomp.hpp

modules/calib3d/perf_precomp.hpp: ../../modules/calib3d/perf/perf_precomp.hpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/sxy/Github/opencv_cpp/start/opencv-3.4.1/build/build_main/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Generating perf_precomp.hpp"
	cd /home/sxy/Github/opencv_cpp/start/opencv-3.4.1/build/build_main/modules/calib3d && /usr/local/bin/cmake -E copy_if_different /home/sxy/Github/opencv_cpp/start/opencv-3.4.1/modules/calib3d/perf/perf_precomp.hpp /home/sxy/Github/opencv_cpp/start/opencv-3.4.1/build/build_main/modules/calib3d/perf_precomp.hpp

pch_Generate_opencv_perf_calib3d: modules/calib3d/CMakeFiles/pch_Generate_opencv_perf_calib3d
pch_Generate_opencv_perf_calib3d: modules/calib3d/perf_precomp.hpp.gch/opencv_perf_calib3d_Release.gch
pch_Generate_opencv_perf_calib3d: modules/calib3d/perf_precomp.hpp
pch_Generate_opencv_perf_calib3d: modules/calib3d/CMakeFiles/pch_Generate_opencv_perf_calib3d.dir/build.make

.PHONY : pch_Generate_opencv_perf_calib3d

# Rule to build all files generated by this target.
modules/calib3d/CMakeFiles/pch_Generate_opencv_perf_calib3d.dir/build: pch_Generate_opencv_perf_calib3d

.PHONY : modules/calib3d/CMakeFiles/pch_Generate_opencv_perf_calib3d.dir/build

modules/calib3d/CMakeFiles/pch_Generate_opencv_perf_calib3d.dir/clean:
	cd /home/sxy/Github/opencv_cpp/start/opencv-3.4.1/build/build_main/modules/calib3d && $(CMAKE_COMMAND) -P CMakeFiles/pch_Generate_opencv_perf_calib3d.dir/cmake_clean.cmake
.PHONY : modules/calib3d/CMakeFiles/pch_Generate_opencv_perf_calib3d.dir/clean

modules/calib3d/CMakeFiles/pch_Generate_opencv_perf_calib3d.dir/depend:
	cd /home/sxy/Github/opencv_cpp/start/opencv-3.4.1/build/build_main && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/sxy/Github/opencv_cpp/start/opencv-3.4.1 /home/sxy/Github/opencv_cpp/start/opencv-3.4.1/modules/calib3d /home/sxy/Github/opencv_cpp/start/opencv-3.4.1/build/build_main /home/sxy/Github/opencv_cpp/start/opencv-3.4.1/build/build_main/modules/calib3d /home/sxy/Github/opencv_cpp/start/opencv-3.4.1/build/build_main/modules/calib3d/CMakeFiles/pch_Generate_opencv_perf_calib3d.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : modules/calib3d/CMakeFiles/pch_Generate_opencv_perf_calib3d.dir/depend

