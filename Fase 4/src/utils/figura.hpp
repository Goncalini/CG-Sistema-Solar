#ifndef FIGURA
#define FIGURA
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <string.h>
#include <iomanip>
#include "ponto.hpp"
#include "matriz.hpp"

using namespace std;

//typedef struct figura* Figura;

typedef struct figura {
	std::vector<Ponto> pontos;
	std::vector<Ponto> normais;
	std::vector<Ponto> texturas;

	// Construtor padrão
	figura() {}

}Figura;


void addPonto(Figura& f, Ponto p);
void addNormal(Figura& f, Ponto n);
void addTexture(Figura& f, Ponto n);
void writeToFile(Figura f, const char* file_path);

#endif 