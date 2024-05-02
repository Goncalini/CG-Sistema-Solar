#ifndef FIGURA
#define FIGURA
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <string.h>
#include "ponto.hpp"

using namespace std;

//typedef struct figura* Figura;

typedef struct figura {
	std::vector<Ponto> pontos;

	// Construtor padrão
	figura() {}

}Figura;


void addPonto(Figura& f, Ponto p);
void writeToFile(Figura f, const char* file_path);

#endif // !FIGURA