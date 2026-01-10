#ifndef GAME_ENTITIES_OBJECT
#define GAME_ENTITIES_OBJECT

#include "../core/types.h"
#include "raylib.h"

typedef enum ObjectType {
    OBJECT_CORPSE,
    OBJECT_FRUIT,
    OBJECT_RESOURCE
} ObjectType;

typedef struct Object {
    Vector2 position;
    f32 radius;
    u32 id;
    u32 element_mask;
    u16 weight;
    u16 carriers;
    bool id_delivered;
    bool id_active;
    ObjectType type;
} Object;

#endif // GAME_ENTITIES_OBJECT