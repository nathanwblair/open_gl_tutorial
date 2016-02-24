# CMake mostly ripped from https://bitbucket.org/doddzy39/openglengine
cmake_minimum_required (VERSION 2.6)
set (CMAKE_CXX_STANDARD 11)
project (ComputerGraphics)


#Tell the compiler that we want to use C++11
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

#if(UNIX OR APPLE)
#	set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11  -Wno-reorder")
#endif(UNIX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_CHAR_IS_UNSIGNED_CHAR} ${STD_C11} -DGLM_SWIZZLE")
set (CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

enable_testing()

set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Builds)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Builds)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_COLOR_MAKEFILE   ON)



# add common include directories for dependencies
include_directories(${CMAKE_SOURCE_DIR}/deps/glfw/include)
include_directories(${CMAKE_SOURCE_DIR}/deps/glm)
include_directories(${CMAKE_SOURCE_DIR}/deps/Utils)
include_directories(${CMAKE_SOURCE_DIR}/deps/mesh_loaders)
include_directories(${CMAKE_SOURCE_DIR}/deps/stb)

#add_subdirectory(deps/glfw)
add_subdirectory(OpenGLEngine)
add_subdirectory(GridTutorial)