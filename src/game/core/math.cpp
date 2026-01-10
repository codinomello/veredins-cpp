#include <cmath>

#include "math.h"

f32 distance(f32 x1, f32 y1, f32 x2, f32 y2) {
    f32 dx = x2 - x1;
    f32 dy = y2 - y1;

    return std::sqrt(dx * dx + dy * dy);
}

f32 lerp(f32 a, f32 b, f32 t) {
    return a + (b - a) * t;
}

Vector2 vector2_add(Vector2 v1, Vector2 v2) {
    Vector2 result = { v1.x + v2.x, v1.y + v2.y };

    return result;
}

Vector2 vector2_subtract(Vector2 v1, Vector2 v2) {
    Vector2 result = { v1.x - v2.x, v1.y - v2.y };

    return result;
}

Vector2 vector2_lerp(Vector2 v1, Vector2 v2, float amount) {
    Vector2 result = {
        0, 0
    };

    result.x = v1.x + amount * (v2.x - v1.x);
    result.y = v1.y + amount * (v2.y - v1.y);

    return result;
}

Vector2 vector2_scale(Vector2 v, float scale) {
    Vector2 result = { v.x*scale, v.y*scale };

    return result;
}

Vector2 vector2_normalize(Vector2 v) {
    Vector2 result = { 0 };
    float length = sqrtf((v.x*v.x) + (v.y*v.y));

    if (length > 0)
    {
        float ilength = 1.0f/length;
        result.x = v.x*ilength;
        result.y = v.y*ilength;
    }

    return result;
}

float Vector2Distance(Vector2 v1, Vector2 v2) {
    float result = sqrtf((v1.x - v2.x)*(v1.x - v2.x) + (v1.y - v2.y)*(v1.y - v2.y));

    return result;
}