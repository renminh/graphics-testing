#ifndef TEXTURE_H
#define TEXTURE_H

#include <cglm/cglm.h>
#include <glad/glad.h>

typedef enum {
	TEXTURE_PLAYER,
	MAX_TEXTURES
} texture_type_enum;

struct texture {
	GLuint id;
	int width;
	int height;
};

struct texture *texture_create(const char *path);
void texture_destroy(struct texture *t);

#endif
