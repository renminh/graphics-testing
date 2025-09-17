#ifndef CAMERA_H
#define CAMERA_H

#include <cglm/cglm.h>
#include "../types.h"

#define CAMERA_MIN_ZOOM 0.4
#define CAMERA_DEFAULT_ZOOM 2
#define CAMERA_MAX_ZOOM 4.0

struct camera {
	mat4 view;
	mat4 projection;
	f32 zoom;
};

struct camera camera_create(void);
void camera_zoom(struct camera *cam, f32 zoom);
void camera_update(struct camera *cam, vec3 attach_to_pos);

#endif
