CXX=gcc
CXXFLAGS=-g -Wall -Wextra -Wfloat-equal # -Wshadow -Werror
LDFLAGS=-lm -lSDL2 -lSDL2_image

SRC_DIR=./src
BUILD_DIR=./build

EXEC=main
SRC=$(wildcard $(SRC_DIR)/*.c)
OBJS=$(SRC:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

all: $(EXEC)
	$(BUILD_DIR)/$(EXEC)

doc:
	doxygen

valgrind: $(EXEC)
	valgrind --leak-check=full $(BUILD_DIR)/$(EXEC)

$(BUILD_DIR)/%.o : $(SRC_DIR)/%.c
	$(CXX) $(CXXFLAGS) -o $@ -c $< $(LDFLAGS)

$(EXEC) : $(OBJS)
	$(CXX) -o $(BUILD_DIR)/$(EXEC) $(OBJS) $(LDFLAGS)

clean:
	rm -f $(OBJS) $(EXEC)
	rm -rf doc