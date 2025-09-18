#include <cglm/cglm.h>

#include "atlas.h"
#include "../math/math.h"
#include "cglm/vec2.h"

static void atlas_get_uv(struct atlas *atlas, ivec2 pos,
				  vec2 uv_min, vec2 uv_max);

struct atlas atlas_create(struct texture *t, ivec2 sprite_size)
{
	struct atlas atlas;
	atlas.texture_id = t->id;
	glm_ivec2_copy(t->size, atlas.texture_size);
	glm_ivec2_copy(sprite_size, atlas.sprite_size);

	// convert to UV space
	vec2 sprite_unit, pixel_unit;
	glm_vec2_div(IVEC2F(atlas.sprite_size), IVEC2F(atlas.texture_size), sprite_unit);
	glm_vec2_copy(sprite_unit, atlas.sprite_unit);

	glm_vec2_div(GLM_VEC2_ONE, IVEC2F(atlas.texture_size), pixel_unit);
	glm_vec2_copy(pixel_unit, atlas.pixel_unit);

	// row and column size
	vec2 size;
	glm_vec2_div(IVEC2F(atlas.texture_size), IVEC2F(atlas.sprite_size), size);
	glm_vec2_copy(size, IVEC2F(atlas.size));

	return atlas;
}

void atlas_get_tile(struct atlas *atlas, tile_type_enum type, 
					vec2 uv_min, vec2 uv_max)
{
	switch (type) {
		case TILE_GRASS: atlas_get_uv(atlas, (ivec2) {0, 0}, uv_min, uv_max);  break;
		case TILE_DIRT: atlas_get_uv(atlas, (ivec2) {1, 0}, uv_min, uv_max);  break;
		case TILE_STONE: atlas_get_uv(atlas, (ivec2) {2, 0}, uv_min, uv_max);  break;
		default: atlas_get_uv(atlas, (ivec2) {4, 4}, uv_min, uv_max); break;
	}
}

static void atlas_get_uv(struct atlas *atlas, ivec2 pos,
				  vec2 uv_min, vec2 uv_max)
{
	vec2 pos_min;

	glm_vec2_copy(
		(vec2){
			(pos[VEC_X] * atlas->sprite_size[VEC_X]),
			(atlas->size[VEC_Y] - pos[VEC_Y] - 1) * atlas->sprite_size[VEC_Y]
		},
		pos_min
	);

	// min uv
	vec2 min;
	glm_vec2_div(pos_min, IVEC2F(atlas->texture_size), min);
	glm_vec2_copy(min, uv_min);

	// max uv
	vec2 temp;
	vec2 max;
	glm_vec2_add(pos_min, IVEC2F(atlas->sprite_size), temp);
	glm_vec2_div(temp, IVEC2F(atlas->texture_size), max);
	glm_vec2_copy(max, uv_max);
}

