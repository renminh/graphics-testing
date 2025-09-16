#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"
#include "../types.h"

#define PLAYER_BASE_VELOCITY	1
#define PLAYER_SCALE			2
#define PLAYER_PIXEL_SIZE_X		(32 * PLAYER_SCALE)
#define PLAYER_PIXEL_SIZE_Y		(32 * PLAYER_SCALE)

static inline void player_move_left(struct entity *e, i32 units)
{
	e->transform.position[VEC_X] -= units;
}

static inline void player_move_right(struct entity *e, i32 units)
{
	e->transform.position[VEC_X] += units;
}

static inline void player_move_up(struct entity *e, i32 units)
{
	e->transform.position[VEC_Y] += units;
}

static inline void player_move_down(struct entity *e, i32 units)
{
	e->transform.position[VEC_Y] -= units;
}

#endif
