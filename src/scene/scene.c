#include <stdlib.h>
#include <stdio.h>

#include "scene.h"
#include "../util/style.h"
#include "entity.h"
#include "../graphics/renderer.h"


void scene_create_model(struct scene *s, model_type_enum type, 
						struct mesh *m, struct texture *t)
{
	s->models[type] = model_create(m, t);
}

void scene_create_entity(struct scene *s, model_type_enum type,
						 vec3 position, vec3 scale, f32 rotation)
{
	// TODO, handling creating a unified id 
	// for stable id
	static u32 next_id = 0;
	u32 id = next_id++;

	size_t old_len = array_list_length(s->entities);
	struct entity entity = {0};

	entity.model_type = type;
	entity_set_position(&entity, position);
	entity_set_scale(&entity, scale);
	entity_set_rotation(&entity, rotation);

	if (array_list_append(s->entities, &entity) != old_len) {
		fprintf(stderr, LERR "Failed to add entity to the scene\n");
		exit(1);
	}
}

void scene_create_player(struct scene *s, 
						 vec3 position, vec3 scale, f32 rotation)

{
	s->player.model_type = MODEL_PLAYER;
	s->player.id = PLAYER_ID;
	entity_set_position(&s->player, position);
	entity_set_scale(&s->player, scale);
	entity_set_rotation(&s->player, rotation);
}

void scene_load_level(struct scene *s, struct renderer *r)
{
	scene_create_model(
		s, MODEL_PLAYER, 
		renderer_get_mesh(r, MESH_QUAD), 
		renderer_get_texture(r, TEXTURE_PLAYER)
	);

	scene_create_player(
		s,
		(vec3) {200, 100, 0},
		(vec3) {32, 32, 1},
		0
	);
}

void scene_destroy_entity(struct scene *s, struct entity *e)
{

}

void scene_init(struct scene *s)
{
	s->entities = array_list_create(sizeof(struct entity), INITIAL_ENTITY_COUNT);
}

void scene_destroy(struct scene *s)
{
	array_list_free(s->entities);
}
