# Configurações
OS          := LINUX
SOURCE_DIR  := src
BUILD_DIR   := build
BINARY_NAME := veredins

# Caminho completo do executável
TARGET      := $(BUILD_DIR)/$(BINARY_NAME)

# Compilador e flags (usados apenas no target manual, se precisar)
CXX         := g++
CXXFLAGS    := -std=c++17 -Wextra -Wpedantic -Wconversion -Wsign-conversion -Wshadow
LDFLAGS     := -lraylib -lm -lpthread -ldl -lrt -lX11

# Targets
.PHONY: all build run cmake cmake-build cmake-run clean

# Target padrão (compila e executa com CMake)

all: cmake-run

# Configura e compila usando CMake (cria a pasta build e gera o binário lá dentro)
cmake: cmake-build

cmake-build: $(BUILD_DIR)/Makefile
	cmake --build $(BUILD_DIR)

# Força a configuração do CMake (útil na primeira vez ou após mudar CMakeLists.txt)
$(BUILD_DIR)/Makefile: 
	cmake -S . -B $(BUILD_DIR) -DCMAKE_BUILD_TYPE=Release

# Compila e executa usando CMake
cmake-run: cmake-build
	./$(TARGET)

# Targets manuais (g++ nu e cru)

build: $(TARGET)

$(TARGET): $(SOURCE_DIR)/main.cpp | $(BUILD_DIR)
	$(CXX) $< -o $@ $(CXXFLAGS) $(LDFLAGS)

run: build
	./$(TARGET)

# Utilitários

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)

# Limpeza mais agressiva (remove tudo dentro de build)
distclean: clean