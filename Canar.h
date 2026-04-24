#if CANAR_H
#define CANAR_H


typedef struct Canar {
  int x, y;
  struct Canar *next;
} Canar;

typedef struct {
  Canar *Head;
}ListeCanar;


#endif // CANAR_H
