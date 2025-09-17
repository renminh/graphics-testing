#include <string.h>
#include <stdlib.h>
#include <stb/stb_image.h>
#include <glad/glad.h>

#include "texture.h"
#include "../types.h"
#include "../logging/log.h"

#define CHECK_GL_ERROR(_s) ({ \
	while (glGetError() != GL_NO_ERROR) {}\
	GLenum err=glGetError(); \
	if (err != GL_NO_ERROR) LOG_ERR("%s (GL error: 0x%x)", _s, err);})

struct texture texture_create(const char *path)
{
	LOG_INFO("Creating texture for %s", path);
	struct texture texture = {0};
	i32 width, height, channels;
	width = height = channels = 0;

	// OpenGL expects the 0.0 coordinate on the y-axis
	// to be on the bottom side of the image
	stbi_set_flip_vertically_on_load(true);
	unsigned char *data = stbi_load(
		path, &width, &height, &channels, STBI_rgb_alpha
	);

	if (data == NULL) {
		LOG_ERR("Failed to load texture png");
		exit(1);
	}


	memcpy(&texture.size, (ivec2) {width, height}, sizeof(ivec2));

	glGenTextures(1, &texture.id);
	CHECK_GL_ERROR("Failed to generate texture ID");

	glBindTexture(GL_TEXTURE_2D, texture.id);
	CHECK_GL_ERROR("Failed to bind texture");

	// setting texture attributes best suited for pixel art games
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// generting texture
	glTexImage2D(
		GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE,
		data
	);
	CHECK_GL_ERROR("Failed to generate texture");

	glGenerateMipmap(GL_TEXTURE_2D);
	CHECK_GL_ERROR("Failed to generate mipmaps for the texture");

	// clean up and unbind
	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(data);

	return texture;
}

void texture_destroy(struct texture *t)
{
	glDeleteTextures(1, &t->id);
	CHECK_GL_ERROR("Failed to delete shader");
}
