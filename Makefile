#all: main_jeu

#Affichage.o: Affichage.c Affichage.h 
#	gcc -c -Wall Affichage.c

#Canard.o: Canard.c Canard.h Flechette.h
#	gcc -c -Wall Canard.c

 #main_jeu.o: main_jeu.c Affichage.h 
#	gcc -c -Wall main_jeu.c

#main_jeu: main_jeu.o Affichage.o Canon.o 
#	gcc -g -o main_jeu main_jeu.o Affichage.o Canon.o -lncurses

#clean:
#	rm -fr *~ *.o main_jeu


# Compilateur
CC = gcc

# Flags
CFLAGS = -Wall -Wextra -g -fsanitize=address
LDFLAGS = -lncurses -fsanitize=address

# Nom de l'exécutable
TARGET = jeu

# Fichiers sources
SRC = main.c Affichage.c Canon.c Flechette.c

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
	./$(TARGET) 50 25 1
