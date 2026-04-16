all: main_jeu

Affichage.o: Affichage.c Affichage.h 
	gcc -c -Wall Affichage.c

Canard.o: Canard.c Canard.h Flechette.h
	gcc -c -Wall Canard.c

main_jeu.o: main_jeu.c Affichage.h 
	gcc -c -Wall main_jeu.c

main_jeu: main_jeu.o Affichage.o Canon.o 
	gcc -o main_jeu main_jeu.o Affichage.o Canon.o -lncurses

clean:
	rm -fr *~ *.o main_jeu
