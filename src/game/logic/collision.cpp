#include "collision.h"
#include "../world/tile.h"

static inline bool aabb_intersect(f32 ax, f32 ay, f32 aw, f32 ah, f32 bx, f32 by, f32 bw, f32 bh);