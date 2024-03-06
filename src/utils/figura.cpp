#include "figura.hpp"
using namespace std;

//figura � constituida por pontos


void addPonto(Figura& f, Ponto p) {
	f.pontos.push_back(p);
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

	//Escreve cabecalho dos pontos
	file << "PosX; PosY; PosZ" << std::endl;
	for (const auto& ponto : f.pontos){
		file << getX(ponto) << ";" << getY(ponto) << ";" << getZ(ponto) << "\n";
	}

	file.close();
	std::cout << "Writing to file done!\n";
}