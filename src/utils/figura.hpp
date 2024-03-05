#ifndef FIGURA
#define FIGURA
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "ponto.hpp"

using namespace std;

typedef struct figura* Figura;

void addPonto(Figura f, Ponto p);
void writeToFile(Figura f, const char* file_path);

#endif // !FIGURA