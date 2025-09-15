#ifndef MATH_H
#define MATH_H

#include <cglm/cglm.h>
#include "../types.h"


// converts an ivec2 type to a normal vec2
#define IVEC2F(_v) ((vec2) { _v[VEC_X], _v[VEC_Y] })
#define VEC2I(_v) ((ivec2) { _v{VEC_X], _v[VEC_Y] })


#endif
