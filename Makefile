# Compilateur
CC = gcc

# Flags
CFLAGS = -Wall -Wextra -g -fsanitize=address `sdl2-config --cflags` -lSDL2_image
LDFLAGS = -lncurses -fsanitize=address `sdl2-config --libs` -lSDL2_image

# Nom de l'exécutable
TARGET = Game

# Fichiers sources
SRC = main.c game.c player.c

# Objets générés automatiquement
OBJ = $(SRC:.c=.o)

# Règle principale
all: $(TARGET)

# Link final
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Compilation des .c en .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Nettoyage
clean:
	rm -f *.o *~ $(TARGET)

# Rebuild complet
re: clean all

# Lancer le programme
run: $(TARGET)
	./$(TARGET)
