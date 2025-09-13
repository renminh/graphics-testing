#ifndef SCENE_H
#define SCENE_H

#include "../model/model.h"

#define MAX_MODELS 1024

struct scene {
	struct model *models[MAX_MODELS];
	u32 models_count;
};

void scene_create_model(struct scene *s, struct mesh *m, struct texture *t,
								 vec3 pos, vec3 scale, f32 rotation);
void scene_init(struct scene *s);
void scene_destroy(struct scene *s);

#endif
