cmake_minimum_required(VERSION 3.5)

set(NAME Demo)
project(${NAME})

set(CMAKE_PREFIX_PATH F:/opencv/build)
#include_directories(F:/opencv/build/include)

#让CMake自动找OpenCV的头文件和库
find_package(OpenCV REQUIRED)

# OpenCV_INCLUDE_DIRS 是预定义变量，代表OpenCV库的头文件路径
include_directories(${OpenCV_INCLUDE_DIRS})



#file(MAKE_DIRECTORY bin)
#SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# #下面是输出信息
message(STATUS "Opnecv ;ibrary status: ")
message(STATUS "> version: ${OpenCV_VERSION} ")
message(STATUS "libraries: ${OpenCV_LIBS} ")
message(STATUS "> include: ${OpenCV_INCLUDE_DIRS}  ")
message("LIBPATH----------:"  ${libs_path} )



add_executable(${NAME} Demo.cpp )

# OpenCV_LIBS 是预定义变量，代表OpenCV库的lib库文件
target_link_libraries(
${NAME}
${OpenCV_LIBS}
)
 