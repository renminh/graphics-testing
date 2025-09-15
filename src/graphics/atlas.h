#ifndef ATLAS_H
#define ATLAS_H

#include "texture.h"
#include <cglm/cglm.h>
#include "texture.h"

typedef enum {
	TILE_GRASS,
	TILE_STONE,
	TILE_DIRT,
} tile_type_enum;

struct atlas {
	texture_type_enum texture_id;
	ivec2 texture_size;
	ivec2 sprite_size;
	vec2 sprite_unit;
	vec2 pixel_unit;
	ivec2 size;		// rows and columns
};

struct atlas atlas_create(struct texture t, ivec2 sprite_size);
void atlas_get_uv(struct atlas atlas, ivec2 pos,
				  vec2 uv_min, vec2 uv_max);

#endif
