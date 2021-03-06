project(OpenGLEngine)

# CMake mostly ripped from https://bitbucket.org/doddzy39/openglengine


find_package(FBX)

#Need to find OpenGL link_libraries(
find_package(OpenGL REQUIRED)

# Bring the headers
include_directories(include)


# Gather additional source files/headers
SET(SOURCES
        src/Utils.cpp
        src/Application.cpp
        src/CameraApplication.cpp
        src/Cameras/Camera.cpp
        src/Cameras/FlyCamera.cpp
        src/gl_core_4_4.c
        src/Gizmos.cpp
        src/Assets/Asset.cpp
        src/Assets/AnimatedMeshShader.cpp
        src/Assets/GridMesh.cpp
        src/Assets/Texture.cpp
        src/Assets/MeshShader.cpp
        src/Assets/Material.cpp
        src/Assets/Shader.cpp
        src/Assets/Mesh.cpp
        src/Assets/TextAsset.cpp
        src/MathTypes/Quaternion.cpp
        src/MathTypes/Transform.cpp
        src/MathTypes/BoundingSphere.cpp
        src/imgui_impl_glfw_gl3.cpp)
SET(HEADERS
        include/Utils.h
        include/Application.h
        include/CameraApplication.h
        include/Cameras/Camera.h
        include/Cameras/FlyCamera.h
        include/gl_core_4_4.h
        include/Gizmos.h
        include/Assets/TextAsset.h
        include/Assets/Grid.h
        include/Assets/Shader.h
        include/Assets/MeshShader.h
        include/Assets/AnimatedMeshShader.h
        include/Assets/GridMesh.h
        include/Assets/Asset.h
        include/Assets/Mesh.h
        include/Assets/FBXMesh.h
        include/Assets/Texture.h
        include/Assets/Material.h
        include/Rendering/RenderData.h
        include/MathTypes/Quaternion.h
        include/MathTypes/Transform.h
        include/MathTypes/BoundingSphere.h
        include/imgui_impl_glfw_gl3.h
	)

SET(EXTRA_SOURCES
   	 ${CMAKE_SOURCE_DIR}/deps/imgui/imgui.cpp
  	 ${CMAKE_SOURCE_DIR}/deps/imgui/imgui_draw.cpp
        )

IF(FBX_FOUND)
    SET(EXTRA_SOURCES
            ${CMAKE_SOURCE_DIR}/deps/mesh_loaders/FBXFile.cpp
            )
ENDIF(FBX_FOUND)

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
source_group(Assets .*/Assets/)
source_group(Math .*/MathTypes/)
source_group(Cameras .*/Cameras/)
source_group(Rendering .*/Rendering/)

# And we need to link against GLFW
target_link_libraries(${PROJECT_NAME} glfw ${GLFW_LIBRARIES})

# and link against OpenGL
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES})

#link against utils
target_link_libraries (${PROJECT_NAME} Utils)

# Finally, we want the compiler to know where to find the headers
# for this library when compiling it into other projects
#TODO: Work out why this isn't working...
target_include_directories (${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)



#Include FBX if supported by this PC
IF(FBX_FOUND)
    message(WARNING "FBX Support enabled")

    include_directories(${FBX_INCLUDE_DIR})
    message(${FBX_INCLUDE_DIR})

    target_link_libraries(${PROJECT_NAME} debug ${FBX_LIBRARY_DEBUG})
    target_link_libraries(${PROJECT_NAME} optimized ${FBX_LIBRARY})

    target_compile_definitions(${PROJECT_NAME} PUBLIC FBX_SUPPORTED)

ELSE(FBX_FOUND)
    message(WARNING "No FBX support in this development environment")
ENDIF(FBX_FOUND)
