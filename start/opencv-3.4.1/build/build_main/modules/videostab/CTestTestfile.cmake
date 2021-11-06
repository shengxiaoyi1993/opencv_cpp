# CMake generated Testfile for 
# Source directory: /home/sxy/Github/opencv_cpp/start/opencv-3.4.1/modules/videostab
# Build directory: /home/sxy/Github/opencv_cpp/start/opencv-3.4.1/build/build_main/modules/videostab
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(opencv_test_videostab "/home/sxy/Github/opencv_cpp/start/opencv-3.4.1/build/build_main/bin/opencv_test_videostab" "--gtest_output=xml:opencv_test_videostab.xml")
set_tests_properties(opencv_test_videostab PROPERTIES  LABELS "Main;opencv_videostab;Accuracy" WORKING_DIRECTORY "/home/sxy/Github/opencv_cpp/start/opencv-3.4.1/build/build_main/test-reports/accuracy" _BACKTRACE_TRIPLES "/home/sxy/Github/opencv_cpp/start/opencv-3.4.1/cmake/OpenCVUtils.cmake;1344;add_test;/home/sxy/Github/opencv_cpp/start/opencv-3.4.1/cmake/OpenCVModule.cmake;1235;ocv_add_test_from_target;/home/sxy/Github/opencv_cpp/start/opencv-3.4.1/cmake/OpenCVModule.cmake;1046;ocv_add_accuracy_tests;/home/sxy/Github/opencv_cpp/start/opencv-3.4.1/modules/videostab/CMakeLists.txt;11;ocv_define_module;/home/sxy/Github/opencv_cpp/start/opencv-3.4.1/modules/videostab/CMakeLists.txt;0;")
