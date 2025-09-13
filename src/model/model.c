#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "model.h"
#include "cglm/mat4.h"

struct model *model_create(struct mesh *m, struct texture *t, 
						   vec3 position, vec3 scale, f32 rotation)
{
	struct model *model;

	model = (struct model *) malloc(sizeof(struct model));

	if (model == NULL) {
		perror("malloc");
		exit(1);
	}

	model->mesh = m;
	model->texture = t;

	memcpy(&model->position, position, sizeof(vec3));
	memcpy(&model->scale, scale, sizeof(vec3));
	model->rotation = rotation;
	glm_mat4_identity(model->transform);

	return model;
}

void model_destroy(struct model *m)
{
	free(m);
}
