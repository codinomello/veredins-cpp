# C++ Style Guide — Projeto Game / Engine (Raylib)

Este guia define o **padrão oficial de código** do projeto.
Objetivo: **clareza, consistência, baixo acoplamento e estilo profissional**.

Baseado em:
- Google C++ Style Guide
- Convenções C/C++ clássicas
- Boas práticas de engines e jogos

---

## 📛 Nomenclatura

### Funções
- **snake_case**
```cpp
void update_player();
void draw_ui();
```

### Variáveis
- **snake_case**
```cpp
int player_health;
float delta_time;
```

### Structs / Classes / Types
- **PascalCase**
```cpp
struct PlayerState {};
class GameWorld {};
using EntityId = uint32_t;
```

### Constantes
- **SCREAMING_SNAKE_CASE**
```cpp
constexpr int MAX_ENEMIES = 128;
constexpr float GRAVITY = 9.8f;
```

---

## 📁 Arquivos

- Headers: `.hpp` ou `.h`
- Implementação: `.cpp`
- Nomes em **snake_case**
```
player_controller.hpp
game_loop.cpp
```

Include guard:
```cpp
#pragma once
```

---

## 🧠 Estilo Geral

- Sem `using namespace std;`
- Preferir:
  - `constexpr` a `#define`
  - `enum class` a `enum`
  - `using` a `typedef`
- Código explícito > código esperto
- Evitar macros sempre que possível

---

## 🎮 Raylib

### Regra principal
❌ Não usar funções raylib diretamente  
✅ Usar **wrappers** em namespace próprio

### Exemplo
```cpp
namespace rl {
    void init_window(int w, int h, const char* title);
    void begin_drawing();
    void end_drawing();
    void draw_text(const char* text, int x, int y, int size, Color color);
}
```

Uso:
```cpp
rl::init_window(800, 600, "Game");
rl::draw_text("Hello", 10, 10, 20, WHITE);
```

---

## 🧱 Arquitetura

- Nenhuma lógica de jogo no `main.cpp`
- Separação clara de responsabilidades

```
src/
 ├─ core/
 ├─ graphics/
 ├─ input/
 ├─ game/
 └─ main.cpp
```

---

## ♻️ Memória

- RAII sempre que possível
- Preferir:
  - `std::unique_ptr`
  - `std::vector`
- Evitar `new` / `delete` diretos

---

## 🚫 Proibido

- `camelCase` para funções
- Funções globais sem namespace
- Macros desnecessárias
- Misturar render com lógica de jogo

---

## ✅ Regra de Ouro

> **Código deve ser legível para um dev cansado às 3 da manhã.**

---

**Este guia é obrigatório para todo o projeto.**
