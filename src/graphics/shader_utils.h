#ifndef SHADER_UTILS
#define SHADER_UTILS

#include "shader.h"
#include <glad/glad.h>

/*
 * Loads the compiled shader onto OpenGL returning a handle to the shader.
 * The compiled source code must be freed after.
 *
 * source	-> the compiled source code of a shader
 * type		-> type of shader defined in the GLenum
 *
 * Returns the shader handle id.
 */
GLuint shader_load_source(const char *source, GLenum type);

/*
 * Creates an OpenGL shader object from source
 *
 * shader_id ->  the shader handle id
 */
void shader_compile(GLuint shader_id);

/*
 * Reads from a shader source file and returns it all to a single buffer.
 * The buffer must be freed after its use.
 *
 * file_path -> shader source code relative to the project's root directory
 *
 * Returns a pointer to the buffer containing the source code
 */
char *shader_read_file(const char *file_path);

/*
 * Links the shader program to OpenGL and all shaders that are attached to it.
 *
 * shader_id ->  the shader handle id
 */
void shader_link_program(GLuint shader_id);

/*
 * Retrieves and stores uniform locations in the shader struct according to
 * the uniform_names array and uniform enum.
 *
 * s -> shader struct for storing the uniforms
 */
void shader_get_uniform_locations(struct shader *s);

#endif
