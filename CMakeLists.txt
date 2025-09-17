cmake_minimum_required(VERSION 3.16)
project(hello)

# set the output directory for built objects.
# This makes sure that the dynamic library goes into the build directory automatically.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# This assumes the SDL source is available in vendored/SDL
add_subdirectory(vendored/SDL EXCLUDE_FROM_ALL)

# add glad
add_library(glad STATIC vendored/glad/src/glad.c)
target_include_directories(glad PUBLIC vendored/glad/include)

# add cglm
add_library(cglm INTERFACE)
target_include_directories(cglm INTERFACE
    vendored/cglm/include
)

find_package(OpenGL REQUIRED)

add_library(stb INTERFACE)

target_include_directories(stb INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/vendored
)

# Create your game executable target as usual
add_executable(
    hello 
    src/main.c
    src/window/window.c
    src/input/input.c
    src/graphics/shader_utils.c
    src/graphics/shader.c
    src/graphics/renderer.c
    src/graphics/texture.c
    src/graphics/mesh.c
    src/graphics/atlas.c
    src/scene/scene.c
    src/scene/camera.c
    src/util/array_list.c
)

target_compile_options(
    hello PRIVATE -ggdb -Wall -Wextra -Wuninitialized
)

# Link to the actual SDL3 library.
target_link_libraries(hello
    PRIVATE 
        SDL3::SDL3
        OpenGL::GL
        glad
        m
        stb
        cglm
)
