#ifndef MATH_H
#define MATH_H

#include <cglm/cglm.h>
#include "../types.h"

#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#define MAX(x, y) (((x) > (y)) ? (x) : (t)))
#define CLAMP(value, min, max) ((min < max) \
	? (value < min) ? min : ((value > max) ? max : value) \
	: (value < max) ? max : ((value > min) ? min : value))

#define IVEC2F(_v) ((vec2) { _v[VEC_X], _v[VEC_Y] })
#define VEC2I(_v) ((ivec2) { _v{VEC_X], _v[VEC_Y] })

#endif
