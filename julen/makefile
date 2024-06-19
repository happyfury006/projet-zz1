CXX=gcc
CXXFLAGS=-g -Wall -Wextra -Wfloat-equal
LDFLAGS=-lm -lSDL2 -lSDL2_image

SRC_DIR=./src
BUILD_DIR=./build

EXEC=main
SRC=$(wildcard $(SRC_DIR)/*.c)
OBJS=$(SRC:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

# Règle par défaut : exécutable principal
all: $(EXEC)

# Règle pour générer la documentation avec Doxygen
doc:
	doxygen

# Règle pour exécuter avec Valgrind
valgrind: $(EXEC)
	valgrind --leak-check=full $(BUILD_DIR)/$(EXEC)

# Règle générale pour la compilation des objets .o
$(BUILD_DIR)/%.o : $(SRC_DIR)/%.c
	$(CXX) $(CXXFLAGS) -o $@ -c $< $(LDFLAGS)

# Règle pour l'édition de liens de l'exécutable
$(EXEC) : $(OBJS)
	$(CXX) -o $(BUILD_DIR)/$(EXEC) $(OBJS) $(LDFLAGS)

# Règle pour nettoyer les fichiers générés
clean:
	rm -f $(OBJS) $(BUILD_DIR)/$(EXEC)
	rm -rf doc
