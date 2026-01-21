BINARY_NAME := veredins
BUILD_DIR   := build

.PHONY: all configure build run clean

all: run

configure:
	cmake -S . -B $(BUILD_DIR) -DCMAKE_BUILD_TYPE=Release

build: configure
	cmake --build $(BUILD_DIR)

run: build
	./$(BUILD_DIR)/bin/$(BINARY_NAME)

clean:
	rm -rf $(BUILD_DIR)