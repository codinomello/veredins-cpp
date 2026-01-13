# Estágio de Build
FROM ubuntu:22.04 AS builder

# Evita prompts interativos durante a instalação
ENV DEBIAN_FRONTEND=noninteractive

# Instala dependências de compilação e bibliotecas da Raylib
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    libasound2-dev \
    libx11-dev \
    libxrandr-dev \
    libxi-dev \
    libgl1-mesa-dev \
    libglu1-mesa-dev \
    libxcursor-dev \
    libxinerama-dev \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

# Copia o código fonte
COPY . .

# Cria pasta de build e compila
RUN mkdir build && cd build && \
    cmake .. -DCMAKE_BUILD_TYPE=Release && \
    make

# O binário final estará em /app/build/veredins (ajuste o nome se for outro no CMake)
CMD ["./build/veredins"]