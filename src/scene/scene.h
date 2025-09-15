#ifndef SCENE_H
#define SCENE_H

#include "model.h"
#include "../util/array_list.h"
#include "entity.h"

#define INITIAL_ENTITY_COUNT 100
#define PLAYER_ID 0

// forward declaration
struct renderer;

struct scene {
	struct model models[MAX_MODELS];
	array_list *entities;
	struct entity player;
};

void scene_create_player(struct scene *s, 
						 vec3 position, vec3 scale, f32 rotation);
void scene_create_model(struct scene *s, model_type_enum type, 
						struct mesh *m, struct texture *t);
void scene_create_entity(struct scene *s, u32 model_id, 
						 vec3 position, vec3 scale, f32 rotation);
void scene_init(struct scene *s);
void scene_load_level(struct scene *s, struct renderer *r);
void scene_destroy(struct scene *s);

#endif
