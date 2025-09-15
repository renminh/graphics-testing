#ifndef SHADER_H
#define SHADER_H

#include <stdint.h>
#include <glad/glad.h>
#include <cglm/cglm.h>
#include "texture.h"

#include "../types.h"

typedef enum {
	UNIFORM_COLOR,
	UNIFORM_TEXTURE_ID,
	UNIFORM_PROJECTION,
	UNIFORM_MODEL,
	UNIFORM_UV,
	MAX_UNIFORMS
} uniform_enum;

typedef enum {
	SHADER_DEFAULT,
	SHADER_TILE,
	MAX_SHADERS
} shader_type_enum;

struct shader {
	GLuint id;
	GLint *uniforms;
};


/*
 * Creates a shader from a vertex-fragment shader pair.
 * Loads the source codem, compiles, attaches, links, sets up unifomrs, and
 * returns a pointer to a shader struct
 * The returned shader must be freed manually using shader_destroy()
 *
 * @param vs_path -> path to the vertex shader from project root directory
 * @param fs_path -> path to the fragment shader from project root directory
 * @return pointer to a newly created shader struct
 */
struct shader shader_create(const char *vs_path, const char *fs_path);

/*
 * Activates the shader (wrapper around glUseProgram)
 *
 * @param s -> struct shader returned by shader_create()
 */
void shader_use(const struct shader *s);

/*
 * Destroys and frees memory to a shader, its uniforms, and the OpenGL
 * shader program
 *
 * @param s -> struct shader returned by shader_create()
 */
void shader_destroy(struct shader *s);


/*
 * Below are functions that operate... TODO
 */
void shader_uniform_mat4(struct shader *s, uniform_enum type, mat4 m);
void shader_uniform_texture2D(struct shader *s, struct texture *t, GLuint n);
void shader_uniform_float(struct shader *s, uniform_enum type, f32 f);
void shader_uniform_vec2(struct shader *s, uniform_enum type, vec2 v);
void shader_uniform_vec3(struct shader *s, uniform_enum type, vec3 v);
void shader_uniform_vec4(struct shader *s, uniform_enum type, vec4 v);
void shader_uniform_int(struct shader *s, uniform_enum type, i32 v);
void shader_uniform_uint(struct shader *s, uniform_enum type, u32 v);

#endif
