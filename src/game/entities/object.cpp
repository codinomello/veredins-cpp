#include "object.h"

void object_init(Object* o, Vector2 pos, ObjectType type) {
    *o = {
        .pos = pos,
        .radius = 8.0f,
        .weight = type == OBJECT_CORPSE ? 5 : (type == OBJECT_TREASURE ? 3 : 1),
        .value = type == OBJECT_TREASURE ? 50 : (type == OBJECT_CRYSTAL ? 20 : 10),
        .carriers = 0,
        .is_delivered = false,
        .is_active = true,
        .type = type
    };
}

void object_draw(const Object* o) {
    if (!o->is_active || o->is_delivered) return;
    
    Color obj_color = GOLD;
    if (o->type == OBJECT_BERRY) obj_color = PINK;
    else if (o->type == OBJECT_CORPSE) obj_color = DARKGRAY;
    else if (o->type == OBJECT_CRYSTAL) obj_color = SKYBLUE;
    
    DrawCircleV(o->pos, o->radius, obj_color);
    
    if (o->carriers > 0) {
        f32 progress = (f32)o->carriers / (f32)o->weight;
        DrawRectangle(o->pos.x - 15, o->pos.y - o->radius - 10, 30, 4, DARKGRAY);
        DrawRectangle(o->pos.x - 15, o->pos.y - o->radius - 10, 
                     (i32)(30 * progress), 4, YELLOW);
    }
}