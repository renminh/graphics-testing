#include "camera.h"
#include "../graphics/renderer.h"
#include "../math/math.h"
#include "cglm/cam.h"

struct camera camera_create(void)
{
	struct camera cam = {0};
	camera_zoom(&cam, CAMERA_DEFAULT_ZOOM);
	return cam;
}

void camera_update(struct camera *cam, vec3 attach_to_pos)
{
	mat4 view;
	glm_mat4_identity(view);

	glm_translate(view, (vec3){
		-(attach_to_pos[VEC_X] - RENDERER_WIDTH/2.0f),
		-(attach_to_pos[VEC_Y] - RENDERER_HEIGHT/2.0f), 
		-(attach_to_pos[VEC_Z]) 
	});

	glm_mat4_copy(view, cam->view);
}

void camera_zoom(struct camera *cam, f32 zoom)
{
	cam->zoom = CLAMP(zoom, CAMERA_MIN_ZOOM, CAMERA_MAX_ZOOM);

	// set the projection scale
	f32 proj_w = RENDERER_WIDTH / cam->zoom;
	f32 proj_h = RENDERER_HEIGHT / cam->zoom;

	// getting the center
	f32 cx = RENDERER_WIDTH / 2.0;
	f32 cy = RENDERER_HEIGHT / 2.0;

	f32 near_z = -1.0;
	f32 far_z = 1.0; 

	glm_ortho(
		cx - proj_w / 2, cx + proj_w / 2,
		cy - proj_h / 2, cy + proj_h / 2,
		near_z, far_z,
		cam->projection
	);
}
