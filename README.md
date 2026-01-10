# 🌿 Veredins

Um jogo 2D experimental escrito **do zero em C++**, usando **raylib**, focado em **simplicidade técnica**, **arquitetura clara** e **gameplay emergente** inspirado em criaturas elementais e interação com o mundo.

> *Veredins* não é apenas um jogo — é também um **laboratório de engenharia de jogos**, onde cada sistema é construído conscientemente, sem engines pesadas ou abstrações mágicas.

---

## 📖 Visão geral

**Veredins** é um jogo 2D top-down onde o jogador explora um mundo natural vivo, interagindo com criaturas chamadas **Veredins** — seres elementais que habitam o mapa, reagem ao ambiente e ao jogador, e possuem comportamentos próprios.

O projeto segue uma filosofia clara:

* Código simples, explícito e previsivel
* Pouca ou nenhuma OOP pesada
* Estruturas de dados claras
* Sistemas desacoplados
* Foco em *game feel* e mecânicas

---

## 🌱 O que são os Veredins?

**Veredim** (singular) / **Veredins** (plural) são criaturas elementais ligadas à natureza e ao território.

Cada Veredim possui:

* Um ou mais **elementos** (planta, fogo, água, etc)
* Comportamento próprio
* Interação com o mapa
* Reações ao jogador e a outros Veredins

Eles não são apenas inimigos ou mascotes — são **entidades do mundo**.

---

## 🌍 História & universo

O mundo de **Veredins** é composto por regiões naturais antigas, onde a energia elemental moldou a terra, a fauna e as criaturas.

O jogador não é um herói clássico, mas um **viajante** que aprende a coexistir, observar e interagir com essas forças vivas.

A narrativa é **ambiental**:

* Contada através do mapa
* Do comportamento das criaturas
* Da interação com o mundo

Nada é explicitamente explicado — o jogador descobre jogando.

---

## 🎮 Gameplay

### Movimento

* Visão **top-down 2D**
* Movimento livre com colisão baseada em tiles
* Câmera suave com *follow* e *smoothing*

### Exploração

* Mapas baseados em **tiles**
* Terrenos sólidos e não sólidos
* Regiões com identidade visual e mecânica

### Interação

* O jogador pode interagir com Veredins
* Veredins reagem ao jogador, ao ambiente e entre si
* Possibilidade de observar, atrair ou evitar criaturas

---

## 🧠 Mecânicas principais

### 🌿 Sistema elemental

Cada Veredim possui uma **máscara de elementos**:

* Planta
* Fogo
* Água
* Terra
* Elétrico
* Gelo

Os elementos influenciam:

* Resistências
* Interações com o mapa
* Comportamento

### 🧱 Tile system

* Mapa em grid
* Tiles sólidos (paredes, água, rochas)
* Base para colisão e interação futura

### 💥 Colisão

* Sistema AABB simples e confiável
* Movimento separado por eixo (X/Y)
* Base sólida para combate e física leve

---

## 🧩 Arquitetura do projeto

O projeto é organizado por **sistemas**, não por classes abstratas:

```
src/
 └── game/
     ├── core/        # Tipos base, defines, utilitários
     ├── camera/      # Sistema de câmera
     ├── input/       # Input do jogador
     ├── world/       # Tiles, mapa, mundo
     ├── entity/      # Player, Veredins, criaturas
     └── game.cpp     # Loop principal
```

### Princípios

* `.h` define a interface
* `.cpp` implementa comportamento
* Sem `#pragma once`
* Comentários apenas de uma linha
* Tipos explícitos (`f32`, `i32`, `b32`, etc)

---

## 🛠️ Tecnologias

* **C++20**
* **raylib** (render, input, window)
* **CMake**
* Build nativo multiplataforma

Futuro:

* WebAssembly (Emscripten)
* Android
* Comunicação com servidor

---

## 🎯 Objetivos do projeto

* Criar um jogo funcional do zero
* Aprender arquitetura real de jogos
* Evitar dependência de engines grandes
* Evoluir o projeto de forma incremental

Este projeto prioriza **clareza e controle**, não velocidade de entrega.

---

## 🚀 Status atual

* [x] Janela e loop principal
* [x] Player funcional
* [x] Tilemap
* [x] Colisão com mapa
* [x] Câmera suave
* [ ] Interação player × Veredim
* [ ] Comportamento de Veredins
* [ ] Sistema elemental completo
* [ ] Combate / interação avançada

---

## 📜 Licença

Este projeto utiliza uma licença **open-source permissiva**, permitindo estudo, modificação e reutilização.

Consulte o arquivo `LICENSE` para mais detalhes.

---

## 🤝 Contribuição

Este é um projeto autoral, mas ideias, discussões e sugestões são bem-vindas.

Se você gosta de:

* Game dev low-level
* C/C++ sem engine
* Sistemas simples e elegantes

Você está no lugar certo 🌱

---

## ✨ Filosofia final

> *Um jogo pequeno, bem feito, vale mais do que um grande que nunca termina.*

**Veredins** é sobre aprender, experimentar e construir algo vivo — linha por linha.