#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"
#include "../types.h"

#define PLAYER_BASE_VELOCITY 1

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
