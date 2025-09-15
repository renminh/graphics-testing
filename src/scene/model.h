#ifndef MODEL_H
#define MODEL_H

#include <cglm/cglm.h>

#include "../graphics/mesh.h"
#include "../graphics/texture.h"

typedef enum {
	MODEL_PLAYER,
	MAX_MODELS
} model_type_enum;

/*
 * Models bundle together the mesh and its specific texture in use
 * as well as the model matrix that is applied to the mesh
 * this model matrix is sent to the shader
 *
 * model matrix -> position, scale, size, rotation
 */
struct model {
	struct mesh *mesh;
	struct texture *texture;
};

static inline struct model model_create(struct mesh *m, struct texture *t)
{
	struct model model = {
		.mesh = m,
		.texture = t,
	};

	return model;
}


#endif
