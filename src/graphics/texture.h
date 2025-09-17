#ifndef TEXTURE_H
#define TEXTURE_H

#include <cglm/cglm.h>
#include <glad/glad.h>

typedef enum {
	TEXTURE_PLAYER,
	TEXTURE_TILES,
	MAX_TEXTURES
} texture_type_enum;

struct texture {
	GLuint id;
	ivec2 size;
};


/*
 * Creates a texture OpenGl object from a specified path relative to the
 * project's root directory, setting its parameters for pixel art.
 *
 * path -> a string specifying the relative path of the texture (stored in
 * res/textures)
 */
struct texture texture_create(const char *path);

/*
 * Delete a texture from the OpenGL pipeline
 *
 * t -> texture structed created from texture_create()
 */
void texture_destroy(struct texture *t);

#endif
