all: main

Affichage.o: Affichage.c Affichage.h 
	gcc -c -Wall Affichage.c

Canard.o: Canard.c Canard.h Flechette.h
	gcc -c -Wall Canard.c

main.o: main.c Affichage.h 
	gcc -c -Wall main.c

main: main.o Affichage.o Canon.o 
	gcc -o main main.o Affichage.o Canon.o -lncurses

clean:
	rm -fr *~ *.o main
