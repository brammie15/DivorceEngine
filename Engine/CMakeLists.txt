# Engine library

set(ENGINE_NAME "Fovy")

set(ENGINE_SOURCES
    "./FrameBuffer.cpp"
    "./Shader.cpp"
    "./Texture.cpp"
    "./Mesh.cpp"
    "./Scene.cpp"
    "./Camera.cpp"

)
set(ENGINE_INCLUDES
    "./FrameBuffer.h"
    "./DataTypes.h"
    "./Shader.h"
    "./Texture.h"
    "./Mesh.h"
    "./Scene.h"
    "./Camera.h"
)

add_library(${ENGINE_NAME} STATIC ${ENGINE_SOURCES} ${ENGINE_INCLUDES})

target_include_directories(${ENGINE_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})



set(GLAD_OUT_DIR        "${CMAKE_CURRENT_BINARY_DIR}" CACHE STRING "Output directory" FORCE)
set(GLAD_PROFILE        "core" CACHE STRING "OpenGL profile" FORCE)
set(GLAD_API            "gl=3.3" CACHE STRING "API type/version pairs, like \"gl=3.2,gles=\", no version means latest" FORCE)
set(GLAD_GENERATOR      "c" CACHE STRING "Language to generate the binding for" FORCE)
set(GLAD_EXTENSIONS     "" CACHE STRING "Path to extensions file or comma separated list of extensions, if missing all extensions are included" FORCE)
set(GLAD_SPEC           "gl" CACHE STRING "Name of the spec" FORCE)
set(GLAD_ALL_EXTENSIONS OFF CACHE BOOL "Include all extensions instead of those specified by GLAD_EXTENSIONS" FORCE)
set(GLAD_NO_LOADER      OFF CACHE BOOL "No loader" FORCE)
set(GLAD_REPRODUCIBLE   OFF CACHE BOOL "Reproducible build" FORCE)

# Perform dependency linkage
include(${CMAKE_DIR}/LinkGLFW.cmake)
LinkGLFW(${ENGINE_NAME} PUBLIC)


include(${CMAKE_DIR}/LinkGLAD.cmake)
LinkGLAD(${ENGINE_NAME} PUBLIC)


include(${CMAKE_DIR}/LinkImGui.cmake)
LinkImGui(${ENGINE_NAME} PUBLIC)

target_link_libraries(imgui PUBLIC glfw)

include(${CMAKE_DIR}/LinkGLM.cmake)
LinkGLM(${ENGINE_NAME} PUBLIC)


find_package(OpenGL REQUIRED)
if (OpenGL_FOUND)
    target_include_directories(${ENGINE_NAME} PUBLIC ${OPENGL_INCLDUE_DIRS})
    target_link_libraries(${ENGINE_NAME} PUBLIC ${OPENGL_LIBRARIES})
else()
    message(FATAL_ERROR "OpenGL was not found on the system")
endif()

add_definitions(-DASSIMP_BUILD_NO_IFC_IMPORTER)
include(${CMAKE_DIR}/LinkASSIMP.cmake)
LinkASSIMP(${ENGINE_NAME} PUBLIC)

