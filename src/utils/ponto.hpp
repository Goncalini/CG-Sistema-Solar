#ifndef PONTO
#define PONTO
#include <stdio.h>
#include <stdlib.h>


typedef struct ponto* Ponto;

Ponto newPonto(float x, float y, float z);

float getX(Ponto p);

float getY(Ponto p);

float getZ(Ponto p);


#endif //PONTO