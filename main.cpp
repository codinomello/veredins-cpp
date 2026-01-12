#include "include/raylib/src/raylib.h"
#include "include/raylib/src/raymath.h"
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

// --- Constantes ---
const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 800;
const float PLAYER_SPEED = 250.0f;
const float THROW_SPEED = 700.0f;
const float RETURN_SPEED = 400.0f;
const float CARRY_SPEED = 100.0f;

// --- Enums ---
enum ElementType { NEUTRAL, GRASS, FIRE, WATER };
enum CreatureState { IDLE, THROWN, RETURNING, CARRYING, ATTACKING };

// --- Cores ---
Color GetColorByType(ElementType t) {
    switch(t) {
        case GRASS: return LIME;
        case FIRE: return RED;
        case WATER: return BLUE;
        default: return GRAY;
    }
}
Color GetElementColor(ElementType t) { return GetColorByType(t); }
// --- Estruturas ---

struct Base {
    Vector2 pos;
    float radius;
};

// Objetos que podem ser carregados (Inimigos mortos ou Frutas)
struct Carryable {
    int id;
    Vector2 pos;
    float radius;
    int weight;       // Peso total necessário
    int carriers;     // Quantos estão carregando agora
    bool isDelivered; // Se chegou na base
    int value;        // Quantas novas criaturas gera
    Color color;
};

struct Creature {
    Vector2 pos;
    Vector2 targetPos;
    Vector2 velocity;
    ElementType type;
    CreatureState state;
    float radius;
    int targetObjID; // ID do objeto que está atacando ou carregando
    
    Creature(Vector2 p, ElementType t) {
        pos = p;
        type = t;
        state = IDLE;
        radius = 6.0f;
        velocity = {0,0};
        targetObjID = -1;
    }
};

struct Enemy {
    int id;
    Vector2 pos;
    float radius;
    float hp;
    float maxHp;
    ElementType type;
    bool isDead;
};

struct HazardZone {
    Rectangle rect;
    ElementType type; // Tipo necessário para sobreviver
};

// --- Globais para simplificar este protótipo ---
Base base = { {100, SCREEN_HEIGHT/2.0f}, 60.0f };
std::vector<Carryable> items;
std::vector<Enemy> enemies;
std::vector<Creature> squad;
std::vector<HazardZone> zones;

// --- Funções Auxiliares ---

// Verifica se a criatura morre na zona
bool CheckHazardDeath(Creature& c) {
    for (auto& z : zones) {
        if (CheckCollisionCircleRec(c.pos, c.radius, z.rect)) {
            // Se entrar na água e não for de água -> Morre
            if (z.type == WATER && c.type != WATER) return true;
            // Se entrar no fogo e não for de fogo -> Morre
            if (z.type == FIRE && c.type != FIRE) return true;
        }
    }
    return false;
}

// Multiplicador de dano Pokémon
float GetDamageMultiplier(ElementType attacker, ElementType defender) {
    if (attacker == WATER && defender == FIRE) return 2.0f;
    if (attacker == FIRE && defender == GRASS) return 2.0f;
    if (attacker == GRASS && defender == WATER) return 2.0f;
    if (attacker == defender) return 0.5f;
    return 1.0f;
}

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "PokeMin: Full Loop");
    SetTargetFPS(60);

    // Inicialização
    Vector2 playerPos = { 200, SCREEN_HEIGHT/2.0f };
    
    // Spawn inicial de criaturas
    for(int i=0; i<5; i++) squad.push_back(Creature(playerPos, GRASS));
    for(int i=0; i<5; i++) squad.push_back(Creature(playerPos, FIRE));
    for(int i=0; i<5; i++) squad.push_back(Creature(playerPos, WATER));

    // Criar Inimigos
    enemies.push_back({0, {800, 200}, 30, 100, 100, FIRE, false});   // Inimigo de Fogo
    enemies.push_back({1, {800, 600}, 30, 100, 100, WATER, false});  // Inimigo de Água
    enemies.push_back({2, {500, 100}, 20, 50, 50, GRASS, false});    // Inimigo de Planta

    // Criar Zonas de Perigo
    zones.push_back({ {350, 0, 100, 300}, WATER }); // Lago no topo
    zones.push_back({ {350, 500, 100, 300}, FIRE }); // Lava embaixo

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        Vector2 mousePos = GetMousePosition();

        // --- 1. CONTROLES DO JOGADOR ---
        Vector2 input = {0,0};
        if (IsKeyDown(KEY_W)) input.y -= 1;
        if (IsKeyDown(KEY_S)) input.y += 1;
        if (IsKeyDown(KEY_A)) input.x -= 1;
        if (IsKeyDown(KEY_D)) input.x += 1;
        
        if (Vector2Length(input) > 0) 
            playerPos = Vector2Add(playerPos, Vector2Scale(Vector2Normalize(input), PLAYER_SPEED * dt));

        // WHISTLE (Chamar de volta) - Espaço
        if (IsKeyDown(KEY_SPACE)) {
            DrawCircleV(playerPos, 100, Fade(YELLOW, 0.3f)); // Visual do apito
            for (auto& c : squad) {
                c.state = IDLE;
                c.targetObjID = -1;
            }
        }

        // ARREMESSAR - Clique Esquerdo
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            for (auto& c : squad) {
                if (c.state == IDLE) { // Só arremessa quem está seguindo
                    c.state = THROWN;
                    c.velocity = Vector2Scale(Vector2Normalize(Vector2Subtract(mousePos, playerPos)), THROW_SPEED);
                    c.pos = playerPos; 
                    break; // Uma por clique
                }
            }
        }

        // --- 2. LÓGICA DE JOGO (Física e IA) ---

        // Limpar itens entregues
        for (int i = 0; i < items.size(); i++) {
            if (items[i].isDelivered) {
                // SPAWN NOVA CRIATURA DO TIPO BASEADO NA COR DO ITEM
                ElementType newType = GRASS;
                if (ColorToInt(items[i].color) == ColorToInt(RED)) newType = FIRE;
                if (ColorToInt(items[i].color) == ColorToInt(BLUE)) newType = WATER;
                
                for(int k=0; k < items[i].value; k++) {
                    squad.push_back(Creature(base.pos, newType));
                }
                
                // Remover item do vetor
                items.erase(items.begin() + i);
                i--;
            }
        }

        // Atualizar Itens (Carga)
        for (auto& item : items) {
            item.carriers = 0; // Reseta contagem, será recalculada pelas criaturas
        }

        // Atualizar Criaturas
        for (int i = 0; i < squad.size(); i++) {
            Creature& c = squad[i];

            // Morte por Zona
            if (CheckHazardDeath(c)) {
                squad.erase(squad.begin() + i);
                i--;
                continue;
            }

            // --- STATE MACHINE ---
            switch (c.state) {
                case IDLE: // Seguir Jogador
                {
                    float angle = i * 0.3f + GetTime();
                    Vector2 offset = { cosf(angle) * 30.0f, sinf(angle) * 30.0f };
                    c.targetPos = Vector2Add(playerPos, offset);
                    c.pos = Vector2Lerp(c.pos, c.targetPos, 5.0f * dt);
                } break;

                case THROWN: // Voando
                {
                    c.pos = Vector2Add(c.pos, Vector2Scale(c.velocity, dt));
                    
                    // Colisão com Inimigos
                    bool hit = false;
                    for (auto& enemy : enemies) {
                        if (!enemy.isDead && CheckCollisionCircles(c.pos, c.radius, enemy.pos, enemy.radius)) {
                            c.state = ATTACKING;
                            c.targetObjID = enemy.id;
                            hit = true;
                            break;
                        }
                    }
                    
                    // Colisão com Itens (para carregar)
                    if (!hit) {
                        for (int k=0; k<items.size(); k++) {
                            if (CheckCollisionCircles(c.pos, c.radius, items[k].pos, items[k].radius)) {
                                c.state = CARRYING;
                                c.targetObjID = k; // Usamos o índice no vetor de itens
                                hit = true;
                                break;
                            }
                        }
                    }

                    // Limites ou Distância Máxima
                    if (!hit && (c.pos.x < 0 || c.pos.x > SCREEN_WIDTH || c.pos.y < 0 || c.pos.y > SCREEN_HEIGHT)) {
                        c.state = RETURNING;
                    }
                } break;

                case ATTACKING:
                {
                    // Encontrar inimigo alvo
                    Enemy* target = nullptr;
                    for(auto& e : enemies) if(e.id == c.targetObjID) target = &e;

                    if (target && !target->isDead) {
                        // "Pula" no inimigo
                        Vector2 dir = Vector2Normalize(Vector2Subtract(target->pos, c.pos));
                        c.pos = Vector2Add(c.pos, Vector2Scale(dir, 100 * dt)); // Fica grudado
                        
                        // Dano contínuo
                        float damage = 20.0f * dt * GetDamageMultiplier(c.type, target->type);
                        target->hp -= damage;
                    } else {
                        c.state = RETURNING; // Inimigo morreu ou sumiu
                    }
                } break;

                case CARRYING:
                {
                    if (c.targetObjID >= items.size()) { c.state = RETURNING; break; } // Item sumiu
                    
                    Carryable& item = items[c.targetObjID];
                    item.carriers++; // Avisa o item que estou carregando

                    // Posição visual: ao redor do item
                    float angle = i * (PI * 2 / 10.0f); // Distribui em circulo
                    Vector2 carryOffset = { cosf(angle) * item.radius, sinf(angle) * item.radius };
                    c.pos = Vector2Lerp(c.pos, Vector2Add(item.pos, carryOffset), 10.0f * dt);
                } break;

                case RETURNING:
                    if (Vector2Distance(c.pos, playerPos) < 30) c.state = IDLE;
                    else {
                        Vector2 dir = Vector2Normalize(Vector2Subtract(playerPos, c.pos));
                        c.pos = Vector2Add(c.pos, Vector2Scale(dir, RETURN_SPEED * dt));
                    }
                    break;
            }
        }

        // Lógica dos Inimigos
        for (auto& e : enemies) {
            if (!e.isDead && e.hp <= 0) {
                e.isDead = true;
                // Transforma em Item Carregável
                Carryable newItem;
                newItem.id = e.id;
                newItem.pos = e.pos;
                newItem.radius = 20;
                newItem.weight = 5; // Precisa de 5 Pikmins
                newItem.carriers = 0;
                newItem.isDelivered = false;
                newItem.value = 3; // Gera 3 novos
                newItem.color = GetColorByType(e.type);
                items.push_back(newItem);
            }
        }

        // Movimento dos Itens (Se tiver carregadores suficientes)
        for (auto& item : items) {
            if (item.carriers >= item.weight) {
                Vector2 dirToBase = Vector2Normalize(Vector2Subtract(base.pos, item.pos));
                item.pos = Vector2Add(item.pos, Vector2Scale(dirToBase, CARRY_SPEED * dt));

                // Chegou na base?
                if (CheckCollisionCircles(item.pos, item.radius, base.pos, base.radius)) {
                    item.isDelivered = true;
                }
            }
        }

        // --- 3. RENDERIZAÇÃO ---
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Zonas
        for(auto& z : zones) {
            DrawRectangleRec(z.rect, Fade(GetElementColor(z.type), 0.3f));
            DrawRectangleLinesEx(z.rect, 2, GetElementColor(z.type));
            DrawText(z.type == FIRE ? "LAVA" : "LAGO", z.rect.x + 10, z.rect.y + 10, 20, BLACK);
        }

        // Base
        DrawCircleV(base.pos, base.radius, DARKGRAY);
        DrawCircleLines(base.pos.x, base.pos.y, base.radius + 5, BLACK);
        DrawText("BASE", base.pos.x - 20, base.pos.y, 20, WHITE);

        // Itens (Carcaças)
        for(auto& item : items) {
            DrawCircleV(item.pos, item.radius, item.color);
            DrawText(TextFormat("%d/%d", item.carriers, item.weight), item.pos.x - 15, item.pos.y - 10, 20, WHITE);
            // Barra de progresso visual (linha até a base)
            if (item.carriers >= item.weight)
                DrawLineV(item.pos, base.pos, Fade(GRAY, 0.5f));
        }

        // Inimigos Vivos
        for(auto& e : enemies) {
            if (!e.isDead) {
                DrawCircleV(e.pos, e.radius, GetColorByType(e.type));
                DrawRing(e.pos, e.radius + 2, e.radius + 5, 0, (e.hp/e.maxHp)*360, 0, Fade(RED, 0.5f));
                DrawText("INIMIGO", e.pos.x - 30, e.pos.y - 40, 10, BLACK);
            }
        }

        // Esquadrão
        for(auto& c : squad) {
            DrawCircleV(c.pos, c.radius, GetColorByType(c.type));
            DrawCircleLines(c.pos.x, c.pos.y, c.radius, BLACK);
        }

        // Jogador
        DrawCircleV(playerPos, 15, BLACK);
        
        // HUD
        DrawText(TextFormat("Esquadrao: %d", squad.size()), 20, 20, 30, DARKGRAY);
        DrawText("Espaco: Reunir | Clique: Atacar/Carregar", 20, 60, 20, GRAY);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}