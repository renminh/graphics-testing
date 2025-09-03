cmake_minimum_required(VERSION 3.16)
project(hello)

# set the output directory for built objects.
# This makes sure that the dynamic library goes into the build directory automatically.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


# This assumes the SDL source is available in vendored/SDL
add_subdirectory(vendored/SDL EXCLUDE_FROM_ALL)
add_library(glad STATIC vendored/glad/src/glad.c)
target_include_directories(glad PUBLIC vendored/glad/include)

find_package(OpenGL REQUIRED)

# Create your game executable target as usual
add_executable(hello src/main.c src/shaders/shader.c)

# Link to the actual SDL3 library.
target_link_libraries(hello
    PRIVATE 
        SDL3::SDL3
        OpenGL::GL
        glad
        m
)
