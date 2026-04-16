all: main

Affichage.o: Affichage.c Affichage.h 
	gcc -c -Wall Affichage.c

Canard.o: Canard.c Canard.h Flechette.h
	gcc -c -Wall Canard.c

main_jeu.o: main.c Affichage.h 
	gcc -c -Wall main.c

main_jeu: main_jeu.o Affichage.o Canon.o 
	gcc -o main main_jeu.o Affichage.o Canon.o -lncurses

clean:
	rm -fr *~ *.o game
