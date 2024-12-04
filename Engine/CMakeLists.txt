# Engine library

set(ENGINE_NAME "Fovy")


set(ENGINE_FILES
    "core/CoreEngine.cpp"
    "core/Game.cpp"
    "core/InputHandler.cpp"
    "core/RenderingEngine.cpp"
    "core/Window.cpp"

    "scenegraph/Node.cpp"
    "scenegraph/Transform.cpp"

    "shader/Shader.cpp"
    "shader/BasicShader.cpp"

    "texture/Texture.cpp"

    "components/Component.cpp"

    "components/camera/Camera.cpp"

    "components/model/Material.cpp"
    "components/model/Vertex.cpp"
    "components/model/Mesh.cpp"
    "components/model/Model.cpp"

    "components/renderer/Renderer.cpp"

    "utils/ModelUtils.cpp"



)

# includes

include_directories("core")
include_directories("scenegraph")
include_directories("shader")
include_directories("texture")

include_directories("components")
include_directories("components/camera")
include_directories("components/model")
include_directories("components/renderer")

include_directories("utils")



add_library(${ENGINE_NAME} STATIC ${ENGINE_FILES})

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

include(${CMAKE_DIR}/LinkTinyObjLoader.cmake)
LinkTinyObjLoader(${ENGINE_NAME} PUBLIC)


find_package(OpenGL REQUIRED)
if (OpenGL_FOUND)
    target_include_directories(${ENGINE_NAME} PUBLIC ${OPENGL_INCLDUE_DIRS})
    target_link_libraries(${ENGINE_NAME} PUBLIC ${OPENGL_LIBRARIES})
else()
    message(FATAL_ERROR "OpenGL was not found on the system")
endif()

#add_definitions(-DASSIMP_BUILD_NO_IFC_IMPORTER)
#include(${CMAKE_DIR}/LinkASSIMP.cmake)
#LinkASSIMP(${ENGINE_NAME} PUBLIC)

