#include "collision.h"

bool aabb_intersect(f32 ax, f32 ay, f32 aw, f32 ah, f32 bx, f32 by, f32 bw, f32 bh) {
    return ax < bx + bw &&
           ax + aw > bx &&
           ay < by + bh &&
           ay + ah > by;
}

bool circles_overlap(Vector2 a, f32 ra, Vector2 b, f32 rb) {
    f32 dx = a.x - b.x;
    f32 dy = a.y - b.y;
    return (dx*dx + dy*dy) <= (ra + rb) * (ra + rb);
}