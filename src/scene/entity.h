#ifndef ENTITY_H
#define ENTITY_H

#include <cglm/cglm.h>
#include "../types.h"
#include "model.h"

struct transform {
	vec3 position;
	vec3 scale;
	f32 rotation;
};

struct entity {
	u32 id;
	model_type_enum model_type;
	struct transform transform;
};

static inline vec3 *entity_get_position(struct entity *e)
{
	return &e->transform.position;
}

static inline void entity_set_position(struct entity *e, vec3 pos)
{
	glm_vec3_copy(pos, e->transform.position);
}

static inline vec3 *entity_get_scale(struct entity *e)
{
	return &e->transform.scale;

}

static inline void entity_set_scale(struct entity *e, vec3 scale)
{
	glm_vec3_copy(scale, e->transform.scale);
}

static inline f32 entity_get_rotation(struct entity *e)
{
	return e->transform.rotation;
}

static inline void entity_set_rotation(struct entity *e, f32 rotation)
{
	e->transform.rotation = rotation;
}

#endif
