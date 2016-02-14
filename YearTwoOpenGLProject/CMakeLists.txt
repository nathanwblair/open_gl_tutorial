cmake_minimum_required (VERSION 2.6)
set (CMAKE_CXX_STANDARD 11)
project (ComputerGraphics)


#Tell the compiler that we want to use C++11
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

#if(UNIX OR APPLE)
#	set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11  -Wno-reorder")
#endif(UNIX)

enable_testing()

set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Builds)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Builds)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_COLOR_MAKEFILE   ON)

# add common include directories for dependencies
include_directories(${CMAKE_SOURCE_DIR}/deps/glfw/include)
include_directories(${CMAKE_SOURCE_DIR}/deps/glm)

#add_subdirectory(deps/glfw)
add_subdirectory(OpenGLEngine)
add_subdirectory(GridTutorial)