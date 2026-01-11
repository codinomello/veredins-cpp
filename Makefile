# Configurações básicas
BINARY_NAME := veredins
BUILD_DIR   := build
SOURCE_DIR  := src

# Detecção de sistema operacional
ifeq ($(OS),Windows_NT)
    EXE_EXT     := .exe
    RUN_PREFIX  :=
    RM          := del /Q /F 2>NUL
    RMDIR       := rmdir /S /Q 2>NUL
    MKDIR       := mkdir
    CMAKE_GENERATOR := -G "MinGW Makefiles"
    LDFLAGS     := -lraylib -lopengl32 -lgdi32 -lwinmm -static
else
    EXE_EXT     :=
    RUN_PREFIX  := ./
    RM          := rm -rf
    RMDIR       := rm -rf
    MKDIR       := mkdir -p
    CMAKE_GENERATOR :=
    LDFLAGS     := -lraylib -lm -lpthread -ldl -lrt -lX11
endif

TARGET      := $(BUILD_DIR)/$(BINARY_NAME)$(EXE_EXT)

# Flags para compilação manual (opcional)
CXX         := g++
CXXFLAGS    := -std=c++20 -Wall -Wextra -pedantic -O2
INCLUDES    := -I$(SOURCE_DIR) -Iinclude/raylib/src
DEFINES     := -DVEREDINS_ASSETS_PATH=\"$(CURDIR)/assets/\"

# ================================================
# Targets principais
# ================================================

.PHONY: all build run cmake cmake-build cmake-run clean distclean gcc

# PADRÃO AGORA É CMAKE-RUN
all: cmake-run

# --- Fluxo CMake (o mais recomendado / padrão) ---
cmake: cmake-build

cmake-build: $(BUILD_DIR)/Makefile
	cmake --build $(BUILD_DIR) --config Release

$(BUILD_DIR)/Makefile:
	-$(MKDIR) "$(BUILD_DIR)" 2>NUL
	cmake -S . -B $(BUILD_DIR) $(CMAKE_GENERATOR) -DCMAKE_BUILD_TYPE=Release

cmake-run: cmake-build
	$(RUN_PREFIX)$(BUILD_DIR)/bin/veredins

# --- Compilação manual direta (g++ cru) - alternativa ---
gcc: build

build: $(TARGET)

SOURCES     := $(wildcard $(SOURCE_DIR)/*.cpp) $(wildcard $(SOURCE_DIR)/**/*.cpp)

$(TARGET): $(SOURCES) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(DEFINES) $^ -o $@ $(LDFLAGS)

run: build
	$(RUN_PREFIX)$(TARGET)

# --- Utilitários ---
$(BUILD_DIR):
	$(MKDIR) $(BUILD_DIR)

clean:
	$(RMDIR) $(BUILD_DIR)

distclean: clean