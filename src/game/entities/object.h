#ifndef GAME_ENTITIES_OBJECT
#define GAME_ENTITIES_OBJECT

#include "game/core/types.h"

#include "raylib.h"

typedef enum ObjectType : u8 {
    OBJECT_APRICORN, // troca de tipo
    OBJECT_BERRY,    // troca de tipo
    OBJECT_CRYSTAL,  // pontos/evolução
    OBJECT_TREASURE, // itens raros
    OBJECT_CORPSE    // corpo de criatura (precisa ser carregado)
} ObjectType;

typedef struct Object {
    Vector2 pos;
    f32 radius;
    i32 weight;
    i32 value;
    i32 carriers;
    bool is_delivered;
    bool is_active;
    ObjectType type;
} Object;

void object_init(Object* o, f32 x, f32 y, ObjectType type);
void object_draw(const Object* o);

#endif // GAME_ENTITIES_OBJECT