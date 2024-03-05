#include "figura.hpp"
using namespace std;

//figura é constituida por pontos
struct figura {
	std::vector<Ponto> pontos;
};

void addPonto(Figura f, Ponto p) {
	if (f) {
		f->pontos.push_back(p);
	}
}

void writeToFile(Figura f, const char* file_path) {
	if (!f) {
		printf("Figure is Empty!\n");
		return;
	}
	FILE* file = fopen(file_path, "w");
	if (!file) {
		printf("Error opening file to write.\n");
		return;
	}
	//Escreve o número de pontos no inicio do ficheiro
	fprintf(file, "%lu\n", f->pontos.size());
	for (unsigned long i = 0; i < f->pontos.size(),i++) {
		Ponto p = f->pontos[i];
		fprintf(file, "%f,%f,%f\n", getX(p), getY(p), getZ(p));
	}
	fclose(file);
}