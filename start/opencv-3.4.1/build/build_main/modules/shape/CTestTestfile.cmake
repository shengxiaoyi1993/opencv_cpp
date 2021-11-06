# CMake generated Testfile for 
# Source directory: /home/sxy/Github/opencv_cpp/start/opencv-3.4.1/modules/shape
# Build directory: /home/sxy/Github/opencv_cpp/start/opencv-3.4.1/build/build_main/modules/shape
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(opencv_test_shape "/home/sxy/Github/opencv_cpp/start/opencv-3.4.1/build/build_main/bin/opencv_test_shape" "--gtest_output=xml:opencv_test_shape.xml")
set_tests_properties(opencv_test_shape PROPERTIES  LABELS "Main;opencv_shape;Accuracy" WORKING_DIRECTORY "/home/sxy/Github/opencv_cpp/start/opencv-3.4.1/build/build_main/test-reports/accuracy" _BACKTRACE_TRIPLES "/home/sxy/Github/opencv_cpp/start/opencv-3.4.1/cmake/OpenCVUtils.cmake;1344;add_test;/home/sxy/Github/opencv_cpp/start/opencv-3.4.1/cmake/OpenCVModule.cmake;1235;ocv_add_test_from_target;/home/sxy/Github/opencv_cpp/start/opencv-3.4.1/cmake/OpenCVModule.cmake;1046;ocv_add_accuracy_tests;/home/sxy/Github/opencv_cpp/start/opencv-3.4.1/modules/shape/CMakeLists.txt;2;ocv_define_module;/home/sxy/Github/opencv_cpp/start/opencv-3.4.1/modules/shape/CMakeLists.txt;0;")
