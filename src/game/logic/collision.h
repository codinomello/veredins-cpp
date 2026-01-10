#ifndef GAME_LOGIC_COLLISION_H
#define GAME_LOGIC_COLLISION_H

#include "../core/types.h"

static inline bool aabb_intersect(f32 ax, f32 ay, f32 aw, f32 ah, f32 bx, f32 by, f32 bw, f32 bh
) {
    return ax < bx + bw &&
           ax + aw > bx &&
           ay < by + bh &&
           ay + ah > by;
}

#endif // GAME_LOGIC_COLLISION_H