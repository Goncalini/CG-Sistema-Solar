#include <stdio.h>
#include "../utils/figura.hpp"
#include <string>
#include <sstream>


//final = vetor com todos os patches existentes <vetor para um patch <vetor coordenadas pontos controlo float>>
vector<vector<vector<float>>> readPatchFile(const char* patch_file){

	std::ifstream file(patch_file); //abrir ficheiro
	vector<vector<vector<float>>> final;

	if (file.is_open()) {
		//linha auxiliar para leitura do ficheiro
		std::string line; 
		std::getline(file, line);
		//numero de patches
		int numPatches = atoi(line.c_str());

		//vector para vectores de indices para cada patch
		vector<vector<int>> patchesIndices;

		for (int i = 0; i < numPatches; i++) {
			vector<int> indices;

			std::getline(file, line);
			std::istringstream iss(line);
			std::string token;
			while (std::getline(iss,token, ',')){
				int value = atoi(token.c_str());
				indices.push_back(value);
			}

			patchesIndices.push_back(indices);
		}
		// obter o numero de pontos de controlo e esses pontos presentes no ficheiro
		std::getline(file, line);
		int numControlPoint = atoi(line.c_str());

		vector<vector<float>> controlPoints;
		for (int i = 0; i < numControlPoint; i++) {
			vector<float> point;
			std::getline(file, line);
			std::istringstream iss(line);
			std::string token;

			while (std::getline(iss, token, ',')) {
				float value = std::stof(token);
				point.push_back(value);
			}
			controlPoints.push_back(point);
		}

		//construcao de patch
		for (vector<int> indices : patchesIndices) {
			vector<vector<float>> patch;
			for (int indice : indices) {
				vector<float> point;
				point.push_back(controlPoints[indice][0]);
				point.push_back(controlPoints[indice][1]);
				point.push_back(controlPoints[indice][2]);
				patch.push_back(point);
			}
			final.push_back(patch);
		}
		file.close();
	}
	else {
		std::cout << "Erro ao abrir ficheiro patch!\n";
	}
	return final;
}



//COMPLETAR!
Figura generateSurface(const char* patch_file, int tesselation) {
    Figura surface;
    float x = 0.0f, y = 0.0f, dif = 1.0f / tesselation;

    // leitura do ficheiro patch
    std::vector<std::vector<std::vector<float>>> patches = readPatchFile(patch_file);
    for (const auto& patch : patches) {
        for (const auto& row : patch) {
            for (float value : row) {
                std::cout << value << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

	float M[4][4] = {{-1,3,-3,1},
					 {3,-6,3,0},
					 {-3,3,0,0},
					 {1,0,0,0}};
	
	float transposta[4][4];
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			transposta[i][j] = M[j][i];
		}
	}

	//Vamos considerar os seguintes valores para v e u
	float v=0.33;
	float u=0.75;

	float u_array[4] = {u * u * u, u * u, u, 1};
	float v_array[4] = {{u * u * u}, 
				  {u * u}, 
				  {u}, 
				  {1}};
	

	float Transposta_V[4] = {0};
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            Transposta_V[i] += transposta[i][j] * v_array[j];
        }
    }

	float M_U[4] = {0};
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            M_U[i] += M[i][j] * u_array[j];
        }
    }

	float matriz_teste[4][4] = {{},
								{},
								{},
								{}};


    return surface;
}