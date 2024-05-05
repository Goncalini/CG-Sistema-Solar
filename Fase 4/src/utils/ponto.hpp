#ifndef PONTO
#define PONTO
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;



typedef struct ponto* Ponto;

Ponto newPonto(float x, float y, float z);

Ponto newPontoArray(float* arr);

Ponto normalize(Ponto ponto);

void vector2Pontos(float* p1, float* p2, float* res);

Ponto calculateNormal(Ponto p0, Ponto p1, Ponto p2);

float getX(Ponto p);

float getY(Ponto p);

float getZ(Ponto p);


#endif //PONTO