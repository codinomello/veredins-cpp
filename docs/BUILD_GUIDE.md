# Veredins - Guia de Build

Jogo 2D top-down de exploração com criaturas elementais (Veredins).

**Cliente:** C++20 + Raylib | **Servidor:** Go (multiplayer inicial via UDP).

**Status atual (15/jan/2026):** * Cliente conecta ao servidor local (127.0.0.1:12345)

* Envia mensagem de teste e recebe echo (confirmação de rede)
* Rede *non-blocking* pronta para expansão (protocolo de mensagens em breve)

---

## Estrutura do Projeto

```text
veredins-cpp/
├── src/                  # Código do cliente/jogo
│   ├── client.h          # Rede (UDP client)
│   ├── client.cpp
│   ├── game.cpp          # Lógica principal
│   └── ... (entities, tilemap, input, etc)
├── server/               # Servidor Go
│   ├── server.go
│   ├── go.mod
│   └── go.sum
├── assets/               # Sprites, tiles, sons
├── include/              # raylib como subdir
├── build/                # Gerado pelo build (ignorar no git)
├── Dockerfile            # Para build do servidor
├── Makefile              # Build jogo + servidor
├── CMakeLists.txt
└── README.md             # Você está aqui

```

---

## Pré-requisitos

### Linux (Ubuntu/Debian/Fedora/Arch)

```bash
sudo apt update && sudo apt install -y \
    build-essential cmake g++ make git \
    libgl1-mesa-dev libx11-dev libxrandr-dev libxi-dev \
    libxcursor-dev libxinerama-dev libasound2-dev libpulse-dev

# Go (se não tiver)
sudo apt install golang-go

```

### Windows

* Instale **MinGW-w64** (ou use MSYS2).
* Instale **CMake** e **Go**.
* Certifique-se de que a Raylib esteja configurada na pasta `include/`.

---

## Como Rodar

### 1. Compilar e Rodar o Cliente (Jogo)

```bash
# Limpa tudo (recomendado na primeira vez ou após mudanças estruturais)
make clean

# Compila + roda via CMake (padrão recomendado)
make cmake-run

# Ou build manual direto com g++ (se configurado no Makefile)
make run

```

### 2. Rodar o Servidor (em um terminal separado)

```bash
# Compila o servidor Go
make server-build

# Roda (porta 12345/UDP)
make server-run

```

*Dica: Para rodar em background, use `make server-run &`.*

### 3. Testar Conexão

O que deve acontecer agora:

1. Rode o servidor primeiro.
2. Rode o jogo (cliente).
3. O client tenta conectar automaticamente e envia: `"hello from veredins client!"`.
4. **Saída esperada no terminal do cliente:**

```text
tentando conectar ao servidor em 127.0.0.1:12345...
cliente UDP conectado com sucesso!
UDP client initialized -> 127.0.0.1:12345
mensagem de teste enviada com sucesso!
recebido do servidor: hello from veredins client!

```

### 4. Docker (Somente Servidor)

```bash
# Build da imagem
docker build -t veredins-server:latest --target server .

# Rodar container
docker run --rm -it -p 12345:12345/udp --name veredins-server veredins-server:latest

```

---

## Dicas Rápidas

* **Configurações:** IP e porta estão fixos no `client_init()`. Em breve serão movidos para um arquivo de configuração ou menu.
* **Dependências Go:** Se adicionar novos pacotes ao servidor, rode `cd server && go mod tidy`.
* **Debug:** Para compilar com símbolos de debug:
```bash
make clean && cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug && cmake --build build

```