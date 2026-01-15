# Veredins - Guia de Estilo

Este guia define as regras para o projeto do jogo, onde vamos escrever **C++ como se fosse C moderno**: código simples, previsível, eficiente e sem abstrações pesadas.

**Sem OOP**: Nada de classes, herança, polimorfismo, métodos ou encapsulamento. Usamos apenas `struct` como agregados de dados puros (POD-like) e funções livres.

O objetivo é manter o código próximo da filosofia do C (controle total, zero overhead, fácil de debugar), mas aproveitando o que o C++ moderno oferece de bom e seguro sem complicar.

Perfeito para jogos leves, engines simples ou projetos indie onde performance e clareza importam mais que "elegância orientada a objetos".

## Princípios Gerais ✨

- **Simplicidade máxima**: Funções curtas, estruturas de dados transparentes.
- **Zero overhead**: Só usamos features que não adicionam custo em runtime.
- **Sem exceções e sem RTTI**: Nunca use `throw`, `try/catch`, `dynamic_cast`, `typeid`.
- **RAII é permitido e recomendado** para recursos (arquivos, memória dinâmica via `unique_ptr`).
- **Sem classes**: Apenas `struct` para dados + funções livres que operam sobre esses dados.
- Prefira features concretas do C++11/14/17/20 que facilitam a vida sem esconder o que acontece.

## Features Permitidas e Recomendadas ✅

| Feature                | Uso Recomendado                                                                 | Exemplo |
|------------------------|----------------------------------------------------------------------------------|---------|
| `struct` puros         | Apenas dados + inicializadores in-class se necessário. Sem métodos.             | `struct Creature { int id; std::string name; int health; int attack; };` |
| `std::vector<T>`       | Arrays dinâmicos. Prefira `std::array` quando tamanho for fixo em compile-time. | `std::vector<Creature> enemies;` |
| `std::string`          | Strings seguras e dinâmicas (adeus buffer overflow manual).                     | `std::string name = "Dragon";` |
| `std::unique_ptr<T>`   | Memória dinâmica com posse única (substitui `malloc/free` ou `new/delete`).     | `auto level = std::make_unique<LevelData>();` |
| `std::shared_ptr<T>`   | Evite sempre que possível. Use só em casos extremos de compartilhamento.        | Prefira evitar |
| `std::optional<T>`     | Retornar valores que podem não existir (C++17+).                                 | `std::optional<Creature*> find_enemy_by_id(int id);` |
| `std::array<T, N>`     | Arrays de tamanho fixo com interface STL (melhor que C arrays).                 | `std::array<Item, 10> inventory;` |
| `constexpr`            | Constantes e funções em tempo de compilação.                                    | `constexpr int MAX_HEALTH = 100;` |
| `auto`                 | Dedução de tipo em variáveis locais e parâmetros de função quando óbvio.       | `auto it = enemies.begin();` |
| Lambdas                | Capturas simples para callbacks curtos (ex: sort, eventos).                     | `std::sort(enemies.begin(), enemies.end(), [](const auto& a, const auto& b) { return a.health < b.health; });` |
| Range-based for        | Iteração limpa em containers.                                                   | `for (auto& enemy : enemies) { ... }` |
| Structured bindings    | Desempacotar tuples/pairs/retornos múltiplos (C++17+).                          | `auto [x, y] = get_player_position();` |
| `enum class`           | Enums fortemente tipados.                                                       | `enum class Direction { Up, Down, Left, Right };` |

## Features Proibidas 🚫

- **Classes** (com métodos, construtores complexos, destrutores não triviais, membros privados).
- Herança (pública, privada, virtual, múltipla).
- Polimorfismo (ponteiros virtuais, interfaces).
- Sobrecarga de operadores (exceto em casos matemáticos muito claros, como vetores 2D/3D).
- Templates avançados (SFINAE, concepts só se absolutamente essencial).
- `std::any`, `std::variant` (use `union` + enum manual se precisar).
- Exceções e RTTI.
- `friend`.
- `using namespace std;` global.

## Convenções de Nomeação 📛

- **Structs e enums**: `PascalCase` → `Creature`, `GameState`, `ItemType`
- **Funções**: `snake_case` → `creature_attack()`, `update_game_state()`
- **Variáveis locais e parâmetros**: `snake_case` → `int player_health;`
- **Membros de struct**: `trailing_underscore_` → `int health_;` (opcional, mas recomendado para clareza)
- **Constantes/constexpr**: `SCREAMING_SNAKE_CASE` → `constexpr int MAX_ENEMIES = 50;`
- **Namespaces**: `lowercase` → `namespace game { ... }` ou `namespace entities { ... }`

## Exemplo de Código Válido

```cpp
struct Creature {
    int id_;
    std::string name_;
    int health_;
    int attack_power_;
};

// Funções livres que operam sobre Creature
void creature_take_damage(Creature& c, int damage) {
    c.health_ = std::max(0, c.health_ - damage);
}

bool creature_is_alive(const Creature& c) {
    return c.health_ > 0;
}

void creature_attack(Creature& attacker, Creature& target) {
    if (creature_is_alive(attacker)) {
        target.health_ -= attacker.attack_power_;
    }
}