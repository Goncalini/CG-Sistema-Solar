#include "figura.hpp"
using namespace std;

//figura � constituida por pontos


void addPonto(Figura& f, Ponto p) {
	f.pontos.push_back(p);
}

void addNormal(Figura& f, Ponto n) {
	f.normais.push_back(n);
}

void addTexture(Figura& f, Ponto n) {
	f.texturas.push_back(n);
}

void writeToFile(Figura f, const char* file_path) {
	
	if (f.pontos.empty()) {
		std::cout << "Figure is Empty!\n";
		return;
	}
	
	std::ofstream file(file_path);

	if (!file) {
		std::cout << "Error opening file to write.\n";
		return;
	}

	int tamanho = f.pontos.size();
	file << tamanho << std::endl;

	for (int i = 0; i < tamanho; i++) { //verificar
		Ponto ponto = f.pontos[i];
		Ponto normal = f.normais[i];
		Ponto textura = f.texturas[i];
		file <<getX(ponto) << "," << getY(ponto) << "," << getZ(ponto) << ";" << getX(normal) << "," << getY(normal) << "," << getZ(normal) << ";" << getX(textura) << "," << getY(textura) << "\n";
	}

	file.close();
	std::cout << "Writing to file done!\n";
}