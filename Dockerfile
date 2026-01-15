# ================================================
# COMUM: Dependências base Alpine (usado por múltiplos stages)
# ================================================
FROM alpine:3.21 AS base-deps

RUN apk add --no-cache \
    cmake \
    make \
    g++ \
    gcc \
    git \
    linux-headers \
    libstdc++ \
    mesa-dev \
    glfw-dev \
    libx11-dev \
    libxrandr-dev \
    libxinerama-dev \
    libxcursor-dev \
    libxi-dev \
    alsa-lib-dev \
    pulseaudio-dev \
    # Para Raylib (OpenGL + áudio + windowing)
    && rm -rf /var/cache/apk/*


# ================================================
# STAGE 1: Build do Jogo C++ / Raylib (cliente)
# ================================================
FROM base-deps AS game-builder

WORKDIR /app

# Copia tudo (inclui server/ mas não afeta muito)
COPY . .

# Configura e build com CMake (igual teu CMakeLists.txt atual)
RUN mkdir build && cd build \
    && cmake .. -DCMAKE_BUILD_TYPE=Release \
    && cmake --build . --config Release --parallel $(nproc)

# O binário final fica em /app/build/bin/veredins (ou ajuste conforme teu OUTPUT_NAME)


# ================================================
# STAGE 2: Build do Servidor Go (estático)
# ================================================
FROM golang:1.25-alpine AS server-builder

WORKDIR /src

# Cache inteligente de módulos
COPY server/go.mod ./
RUN go mod download || true
RUN go mod download

# Copia só o necessário pro server
COPY server/ ./

# Compila binário estático (CGO off, otimizado)
RUN CGO_ENABLED=0 GOOS=linux GOARCH=amd64 \
    go build -a -installsuffix cgo \
    -ldflags "-s -w" \
    -o /veredins-server server.go   # ajuste se main estiver em outro arquivo


# ================================================
# IMAGEM FINAL PADRÃO: Só o SERVIDOR (scratch, mínima ~5-15MB)
# ================================================
FROM scratch AS server

# Copia o binário Go estático
COPY --from=server-builder /veredins-server /veredins-server

# Documenta a porta UDP
EXPOSE 12345/udp

CMD ["/veredins-server"]


# ================================================
# OPCIONAL: Imagem do Jogo (se quiser rodar em container com display)
# Use --target game-runtime e monte X11 ou use xvfb
# ================================================
FROM alpine:3.21 AS game-runtime

# Runtime libs mínimas pro Raylib
RUN apk add --no-cache \
    libstdc++ \
    mesa-gl \
    glfw \
    libx11 \
    libxrandr \
    libxinerama \
    libxcursor \
    libxi \
    alsa-lib \
    pulseaudio-libs \
    && rm -rf /var/cache/apk/*

WORKDIR /app

# Copia o binário do jogo + assets
COPY --from=game-builder /app/build/bin/veredins /app/veredins
COPY assets/ /app/assets/

# Para rodar com display (precisa de -v /tmp/.X11-unix:/tmp/.X11-unix -e DISPLAY)
CMD ["./veredins"]