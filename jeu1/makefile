CXX=gcc
CXXFLAGS=-O2 -g -Wall -Wextra -Wfloat-equal $(shell pkg-config --cflags sdl2 SDL2_image)
LDFLAGS=-lm $(shell pkg-config --libs sdl2 SDL2_image)

SRC_DIR=./src
BUILD_DIR=./build

EXEC=main
SRC=$(wildcard $(SRC_DIR)/*.c)
OBJS=$(SRC:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

all: $(BUILD_DIR)/$(EXEC)
	$(BUILD_DIR)/$(EXEC)

console: $(BUILD_DIR)/$(EXEC)
	$(BUILD_DIR)/$(EXEC) --console

# Règles, puis 220 parties de l'IA contre un joueur aléatoire et contre elle-même
test: $(BUILD_DIR)/test
	$(BUILD_DIR)/test

doc:
	doxygen

valgrind: $(BUILD_DIR)/$(EXEC)
	valgrind --leak-check=full $(BUILD_DIR)/$(EXEC)

$(BUILD_DIR)/%.o : $(SRC_DIR)/%.c $(wildcard $(SRC_DIR)/*.h) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $@ -c $<

$(BUILD_DIR)/$(EXEC) : $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LDFLAGS)

$(BUILD_DIR)/test : tests/test_quantik.c $(BUILD_DIR)/jeu.o $(BUILD_DIR)/IA.o
	$(CXX) -O2 -Wall -Wextra -o $@ $^

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR) doc

.PHONY: all console test doc valgrind clean
