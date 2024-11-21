cmake_minimum_required(VERSION 3.11 FATAL_ERROR)
project(OpenGLTemplate CXX)
add_compile_options(-m64)
add_compile_options(-Wa,-mbig-obj)
add_compile_options(-Wno-dev)


# o3




# C++ 17
set(CMAKE_CXX_STANDARD 20)

#set (CMAKE_CXX_FLAGS "-O3")

# --fuse-linker-plugin






#===========================================================================================
# OPTIONAL LIBRARiES
#
# The following libraries can be pulled down and added to the project by turnning the
# desired options on. Open an issue for additional default support.
# See: https://github.com/Hoshiningen/OpenGL-Template/issues

set(ENABLE_ASSIMP   ON CACHE BOOL "Add Open Asset Import Library (assimp) to the project" FORCE)

#===========================================================================================
# GLAD CONFIGURATION
#
# Configure GLAD loader generation variables (lines below pulled from the GLAD top-level
# LinkImGui.cmake file, with slight modifications.
# Refer to https://github.com/Dav1dde/glad for more information)

set(GLAD_OUT_DIR        "${CMAKE_CURRENT_BINARY_DIR}" CACHE STRING "Output directory" FORCE)
set(GLAD_PROFILE        "core" CACHE STRING "OpenGL profile" FORCE)
set(GLAD_API            "gl=3.3" CACHE STRING "API type/version pairs, like \"gl=3.2,gles=\", no version means latest" FORCE)
set(GLAD_GENERATOR      "c" CACHE STRING "Language to generate the binding for" FORCE)
set(GLAD_EXTENSIONS     "" CACHE STRING "Path to extensions file or comma separated list of extensions, if missing all extensions are included" FORCE)
set(GLAD_SPEC           "gl" CACHE STRING "Name of the spec" FORCE)
set(GLAD_ALL_EXTENSIONS OFF CACHE BOOL "Include all extensions instead of those specified by GLAD_EXTENSIONS" FORCE)
set(GLAD_NO_LOADER      OFF CACHE BOOL "No loader" FORCE)
set(GLAD_REPRODUCIBLE   OFF CACHE BOOL "Reproducible build" FORCE)

#===========================================================================================

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Set directory paths
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/source)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(SHADERS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/shaders)

set(sources
        ${SOURCE_DIR}/main.cpp
        ${SOURCE_DIR}/Timer.cpp
        ${SOURCE_DIR}/Shader.cpp
        ${SOURCE_DIR}/Scene.cpp
        ${SOURCE_DIR}/Scene1/Scene1.cpp
        ${SOURCE_DIR}/Scene2/Scene2.cpp
        ${SOURCE_DIR}/FrameBuffer.cpp
        ${SOURCE_DIR}/Camera.cpp
        ${SOURCE_DIR}/Texture.cpp
        ${SOURCE_DIR}/Mesh.cpp
)

set(includes
        ${SOURCE_DIR}/Timer.h
        ${SOURCE_DIR}/Shader.h
        ${SOURCE_DIR}/stb_image.h
        ${SOURCE_DIR}/Scene.h
        ${SOURCE_DIR}/Scene1/Scene1.h
        ${SOURCE_DIR}/Scene2/Scene2.h
        ${SOURCE_DIR}/Datatypes.h
        ${SOURCE_DIR}/utils.h
        ${SOURCE_DIR}/FrameBuffer.h
        ${SOURCE_DIR}/Camera.h
        ${SOURCE_DIR}/Texture.h
        ${SOURCE_DIR}/Mesh.h
)

add_executable(opengl-template ${sources} ${includes})

# Perform dependency linkage
include(${CMAKE_DIR}/LinkGLFW.cmake)
LinkGLFW(opengl-template PRIVATE)


include(${CMAKE_DIR}/LinkGLAD.cmake)
LinkGLAD(opengl-template PRIVATE)


include(${CMAKE_DIR}/LinkImGui.cmake)
LinkImGui(opengl-template PRIVATE)

target_link_libraries(imgui PUBLIC glfw)

include(${CMAKE_DIR}/LinkGLM.cmake)
LinkGLM(opengl-template PRIVATE)

find_package(OpenGL REQUIRED)
if (OpenGL_FOUND)
    target_include_directories(opengl-template PRIVATE ${OPENGL_INCLDUE_DIRS})
    target_link_libraries(opengl-template PRIVATE ${OPENGL_LIBRARIES})
else()
    message(FATAL_ERROR "OpenGL was not found on the system")
endif()

# Handle the optional libraries
if (${ENABLE_ASSIMP})
    add_definitions(-DASSIMP_BUILD_NO_IFC_IMPORTER)
    include(${CMAKE_DIR}/LinkASSIMP.cmake)
    LinkASSIMP(opengl-template PRIVATE)
endif()

# Enable C++17
set_target_properties(opengl-template PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO)

# Set project folders
set_target_properties(opengl-template PROPERTIES FOLDER ${PROJECT_NAME})

set(SHADER_SOURCE_FOLDER ${CMAKE_CURRENT_SOURCE_DIR}/shaders)
set(SHADER_OUTPUT_FOLDER ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/shaders)

# Copy shaders to the build directory
add_custom_command(TARGET opengl-template POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${SHADER_SOURCE_FOLDER} ${SHADER_OUTPUT_FOLDER}
    COMMENT "Copying shaders to the build directory")

set(RESOURCES_SOURCE_FOLDER ${CMAKE_CURRENT_SOURCE_DIR}/resources)
set(RESOURCES_OUTPUT_FOLDER ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/resources)

# Copy resources to the build directory
add_custom_command(TARGET opengl-template POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${RESOURCES_SOURCE_FOLDER} ${RESOURCES_OUTPUT_FOLDER}
    COMMENT "Copying resources to the build directory")