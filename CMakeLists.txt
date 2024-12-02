cmake_minimum_required(VERSION 3.11 FATAL_ERROR)
project(SuperEpikGame CXX)
set(PROJECT_NAME SuperEpikGame)

add_compile_options(-m64)
add_compile_options(-Wa,-mbig-obj)
add_compile_options(-Wno-dev)

#TODO: add msvc support
#IFDEF and shi

# C++ 17
set(CMAKE_CXX_STANDARD 20)






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


#===========================================================================================

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Set directory paths
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/source)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(SHADERS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/shaders)

# Include the engine folder cmake project
add_subdirectory(Engine)


set(sources
        ${SOURCE_DIR}/main.cpp
        ${SOURCE_DIR}/TestGame.cpp
#        ${SOURCE_DIR}/Scene1/Scene1.cpp
#        ${SOURCE_DIR}/Scene2/Scene2.cpp
)

set(includes
        ${SOURCE_DIR}/TestGame.h
#        ${SOURCE_DIR}/Scene1/Scene1.h
#        ${SOURCE_DIR}/Scene2/Scene2.h
)

add_executable(${PROJECT_NAME} ${sources} ${includes})

target_link_libraries(${PROJECT_NAME} PUBLIC Fovy)


# Enable C++17
set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO)

# Set project folders
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER ${PROJECT_NAME})

set(SHADER_SOURCE_FOLDER ${CMAKE_CURRENT_SOURCE_DIR}/shaders)
set(SHADER_OUTPUT_FOLDER ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/shaders)

# Copy shaders to the build directory
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${SHADER_SOURCE_FOLDER} ${SHADER_OUTPUT_FOLDER}
    COMMENT "Copying shaders to the build directory")

set(RESOURCES_SOURCE_FOLDER ${CMAKE_CURRENT_SOURCE_DIR}/resources)
set(RESOURCES_OUTPUT_FOLDER ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/resources)

# Copy resources to the build directory
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${RESOURCES_SOURCE_FOLDER} ${RESOURCES_OUTPUT_FOLDER}
    COMMENT "Copying resources to the build directory")