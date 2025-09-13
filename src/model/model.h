#ifndef MODEL_H
#define MODEL_H

#include <cglm/cglm.h>

#include "../mesh/mesh.h"
#include "../texture/texture.h"
#include "../types.h"

typedef enum {
	MODEL_PLAYER,
} model_type_enum;

/*
 * Models bundle together the mesh and its specific texture in use
 * as well as the model matrix that is applied to the mesh
 * this model matrix is sent to the shader
 *
 * model matrix -> position, scale, size, rotation
 */
struct model {
	u32 id;
	model_type_enum type;
	struct mesh *mesh;
	struct texture *texture;
	vec3 position;
	vec3 scale;
	f32 rotation;
	mat4 transform;
};


/*
 * Creates a model from a mesh, texture, position vertex, scale vertex
 * and rotation float and returns a pointer to the model struct
 * The returned model must be freed manually with model_destroy()
 *
 * @param m			-> struct mesh
 * @param t			-> struct texture
 * @param position	-> vec3 for the location of the model in worldspace
 * @param scale		-> vec3 for the scale of the model
 * @param rotation	-> float rotation of the model
 * @return pointer to a newly created model struct
 */
struct model *model_create(struct mesh *m, struct texture *t, 
						   vec3 position, vec3 scale, f32 rotation);

/*
 * Destroys and frees memory to a model
 *
 * @param m -> struct model returned by model_create()
 */
void model_destroy(struct model *m);

#endif
