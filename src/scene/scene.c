#include <stdlib.h>
#include <stdio.h>

#include "scene.h"
#include "../utils/style.h"

static void scene_add_model(struct scene *s, struct model *m);

void scene_create_model(struct scene *s, struct mesh *m, struct texture *t,
								 vec3 pos, vec3 scale, f32 rotation)
{
	struct model *model;
	model = model_create(m, t, pos, scale, rotation);
	scene_add_model(s, model);
}

void scene_init(struct scene *s)
{
	s->models_count = 0;
}

void scene_destroy(struct scene *s)
{
	for (int i = 0; i < s->models_count; i++) {
		model_destroy(s->models[i]);
	}
}

static void scene_add_model(struct scene *s, struct model *m)
{
	if (s->models_count >= MAX_MODELS) {
		fprintf(stderr, LERR "Ran out of space for models in the scene\n");
		exit(1);
	}
	s->models[s->models_count] = m;
	s->models_count++;
}
