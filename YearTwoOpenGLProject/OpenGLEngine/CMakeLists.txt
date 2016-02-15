project(OpenGLEngine)

#Need to find OpenGL link_libraries(
find_package(OpenGL REQUIRED)

# Bring the headers
include_directories(include)


# Gather additional source files/headers
SET(SOURCES
        src/Application.cpp
        src/Cameras/Camera.cpp
        src/Cameras/FlyCamera.cpp
        src/gl_core_4_4.c
        src/Gizmos.cpp
        src/Resources/Asset.cpp)
SET(HEADERS
        include/Application.h
        include/Cameras/Camera.h
        include/Cameras/FlyCamera.h
        include/Resources/Grid.h
        include/Resources/Shader.h
        include/gl_core_4_4.h
        include/Gizmos.h
        include/Resources/TextAsset.h
        include/Resources/Asset.h)


# Need to build GLFW if we haven't already..
option(GLFW_BUILD_EXAMPLES "Build the GLFW example programs" OFF)
option(GLFW_BUILD_TESTS "Build the GLFW test programs" OFF)
option(GLFW_BUILD_DOCS "Build the GLFW documentation" ON)
option(GLFW_INSTALL "Generate installation target" OFF)
option(GLFW_DOCUMENT_INTERNALS "Include internals in documentation" OFF)
add_subdirectory(${CMAKE_SOURCE_DIR}/deps/glfw ${CMAKE_BINARY_DIR}/deps/glfw)
set_property(TARGET glfw APPEND_STRING PROPERTY COMPILE_FLAGS " -w")

# Include tinyobjloader
include_directories(${CMAKE_SOURCE_DIR}/deps/tinyobjloader)


# Tell cmake that this will be a library (and not a exectutable)
add_library(${PROJECT_NAME} ${SOURCES} ${EXTRA_SOURCES} ${HEADERS})


source_group(Base ./)
source_group(ExtraSources FILES ${EXTRA_SOURCES})
source_group(Resources .*/Resources/)
source_group(include/Cameras .*/Cameras/)
source_group(Rendering .*/Rendering/)
source_group(AssetLoading .*/AssetLoading/)

# And we need to link against GLFW
target_link_libraries(${PROJECT_NAME} glfw ${GLFW_LIBRARIES})

# and link against OpenGL
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES})

# Finally, we want the compiler to know where to find the headers
# for this library when compiling it into other projects
#TODO: Work out why this isn't working...
target_include_directories (${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
