#include <stdio.h>
#include <stdlib.h>
#include <stb/stb_image.h>

#include "texture.h"
#include "../utils/style.h"
#include "glad/glad.h"

struct texture *texture_create(const char *path)
{
	struct texture *texture;

	int width, height, channels;

	// OpenGL expects the 0.0 coordinate on the y-axis
	// to be on the bottom side of the image
	stbi_set_flip_vertically_on_load(true);
	unsigned char *data = stbi_load(
		path, &width, &height, &channels, STBI_rgb_alpha
	);

	if (data == NULL) {
		fprintf(stderr, LERR "Failed to load texture\n");
		exit(1);
	}

	texture = (struct texture *) malloc(sizeof(struct texture));

	if (texture == NULL) {
		perror("malloc");
		exit(1);
	}

	texture->width = width;
	texture->height = height;

	glGenTextures(1, &texture->id);
	glBindTexture(GL_TEXTURE_2D, texture->id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// mipmaps
	glTexParameteri(
		GL_TEXTURE_2D,
		GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR
	);
	glTexParameteri(
		GL_TEXTURE_2D,
		GL_TEXTURE_MIN_FILTER, GL_LINEAR
	);

	glTexImage2D(
		GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE,
		data
	);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);

	return texture;
}

void texture_destroy(struct texture *t)
{
	glDeleteTextures(1, &t->id);
	free(t);
}
