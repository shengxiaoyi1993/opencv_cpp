#<>cmake不同版本之间的兼容
# 该版本号应为胜任该模块编译的最小版本
cmake_minimum_required(VERSION 3.6)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)  #编译.ui程序相关

#识别当前文件名，将当前文件夹名设置为项目名称
string(REGEX REPLACE ".*/\(.*\)" "\\1" CURDIR_NAME ${CMAKE_CURRENT_SOURCE_DIR})

project(capture VERSION 0.1)

#设置子项目，假设所有库都位于同一层级，且具有相同的文件结构

find_package(OpenCV  REQUIRED
 opencv_core
 opencv_highgui
 )


# 位于<com_repo>/com_lib的库
set(LIST_COM_LIB
  cjsonobject
  glog
  )


# 位于<com_repo>/private_lib的库
set(LIST_PRIVATE_LIB
  )

# 位于<com_repo>/public_lib的库
set(LIST_PUBLIC_LIB
#  cppgc

  )

# 本地的模块
set(LIST_UVDM_LIB
#    def
  #  basic
#    tool
#    QxBroadcastClient
  #  json_explain
  #  http_def
#  sskj_encrypt
  )

set(HEADERS
  ../src/misc.h

  )

set(SOURCES
  ../src/misc.cpp
  ../src/main.cpp
  )

set(RESOURCES
  #    qml.qrc
  )

set(QMLS
  #    main.qml
  )

set(UIS
  )


#sskj_encrypt
# 编译选项
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11" )


#预设<com_repo>路径 使用cmake 时可以通过cmake . -DPATH_COM_REPO=<com_repo>进行自定义设置
SET(PATH_COM_REPO
  "/home/sxy/Work/com_repo/scripts/com_repo_init/../../"
  CACHE
  STRING
  "Some user-specified option")

#将依赖的库添加到当前项目
FOREACH(MYSUBLIB ${LIST_COM_LIB})
if(NOT TARGET ${MYSUBLIB})
  message("add_subdirectory ${MYSUBLIB}")
  add_subdirectory(${PATH_COM_REPO}/com_lib/${MYSUBLIB}/
    ${PATH_COM_REPO}/com_lib_out/${MYSUBLIB}_${COMPILER_SUFFIX}.out/)
endif()
ENDFOREACH(MYSUBLIB)

FOREACH(MYSUBLIB ${LIST_PRIVATE_LIB})
if(NOT TARGET ${MYSUBLIB})
  message("add_subdirectory ${MYSUBLIB}")
  add_subdirectory(${PATH_COM_REPO}/private_lib/${MYSUBLIB}/
    ${PATH_COM_REPO}/private_lib_out/${MYSUBLIB}_${COMPILER_SUFFIX}.out/)
endif()
ENDFOREACH(MYSUBLIB)

FOREACH(MYSUBLIB ${LIST_PUBLIC_LIB})
if(NOT TARGET ${MYSUBLIB})
  message("add_subdirectory ${MYSUBLIB}")
  add_subdirectory(${PATH_COM_REPO}/public_lib/${MYSUBLIB}/
    ${PATH_COM_REPO}/public_lib_out/${MYSUBLIB}_${COMPILER_SUFFIX}.out/)
endif()
ENDFOREACH(MYSUBLIB)

FOREACH(MYSUBLIB ${LIST_UVDM_LIB})
if(NOT TARGET ${MYSUBLIB})
  message("add_subdirectory ${MYSUBLIB}")
  add_subdirectory(${PATH_COM_REPO}/uvdm_lib/${MYSUBLIB}/ ${PATH_COM_REPO}/uvdm_lib_out/${MYSUBLIB}_${COMPILER_SUFFIX}.out/)
endif()
ENDFOREACH(MYSUBLIB)


find_package(Qt5 COMPONENTS
  Core
  Gui
  Network
  Widgets
  Quick
  Qml
  WebSockets
  REQUIRED) #Qml Quick





add_executable(${PROJECT_NAME}
  ${HEADERS}
  ${SOURCES}
  ${RESOURCES}
  ${UIS})

# 本本项目链接相应的库
target_link_libraries(
  ${PROJECT_NAME}
  -lpthread
  Qt5::Core
  Qt5::Gui
  Qt5::Network
  Qt5::Widgets
  Qt5::Quick
  Qt5::Qml
  Qt5::WebSockets
#  Qt5::WebSockets
  ${LIST_COM_LIB}
  ${LIST_PRIVATE_LIB}
  ${LIST_PUBLIC_LIB}
  ${OpenCV_LIBS}
  )

set( CMAKE_BUILD_TYPE Debug )


