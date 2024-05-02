#include <stdio.h>
#include "../utils/figura.hpp"
#include <string>
#include <sstream>

//A transposta é igual a m
float M[4][4] = {{-1.0f,3.0f,-3.0f,1.0f},
					 {3.0f,-6.0f,3.0f,0.0f},
					 {-3.0f,3.0f,0.0f,0.0f},
					 {1.0f,0.0f,0.0f,0.0f}};

void multMatrixVector(float *m, float *v, float *res) {
	for (int j = 0; j < 4; ++j) {
		res[j] = 0;
		for (int k = 0; k < 4; ++k) {
			res[j] += v[k] * m[j * 4 + k];
		}
	}
}


float multVectorVector(float *v1, float *v2) {
	float soma=0;
    for (int i = 0; i < 4; ++i) {
        soma += v1[i] * v2[i];
    }
	return soma;
}


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

void gerarPontos(float dif, int iTesselation, int jTesselation, float* pontos_base_x,float* pontos_base_y,float* pontos_base_z, float*result){
	float v=dif*iTesselation;
	float u=dif*jTesselation;
				
	float u_array[4] = {u * u * u, u * u, u, 1};
	float v_array[4] = {v * v * v, v * v, v, 1}; //Vertical

	float transpostaM_V[4]={0};
	multMatrixVector(*M, v_array, transpostaM_V);

	float mulX[4];
	float mulY[4];
	float mulZ[4];
	multMatrixVector(pontos_base_x, transpostaM_V, mulX);
	multMatrixVector(pontos_base_y, transpostaM_V, mulY);
	multMatrixVector(pontos_base_z, transpostaM_V, mulZ);

	float M_mulX[4];
	float M_mulY[4];
	float M_mulZ[4];
	multMatrixVector(*M, mulX, M_mulX);
	multMatrixVector(*M, mulY, M_mulY);
	multMatrixVector(*M, mulZ, M_mulZ);

	float result_X=multVectorVector(u_array, M_mulX);
	float result_Y=multVectorVector(u_array, M_mulY);
	float result_Z=multVectorVector(u_array, M_mulZ);

	result[0]=result_X;
	result[1]=result_Y;
	result[2]=result_Z;
				
}


Figura generateSurface(const char* patch_file, int tesselation) {
	
    Figura surface;
    float x = 0.0f, y = 0.0f, dif = 1.0f / tesselation;

	std::vector<std::vector<std::vector<float>>> patches = readPatchFile(patch_file);
	for (std::vector<std::vector<float>> patch : patches) {
		//Matrizes com as componentes, x y e z dos 16 pontos
		float pontos_base_x[4][4] = {
								{patch[0][0], patch[1][0], patch[2][0], patch[3][0]},
								{patch[4][0], patch[5][0], patch[6][0], patch[7][0]},
								{patch[8][0], patch[9][0], patch[10][0], patch[11][0]},
								{patch[12][0], patch[13][0], patch[14][0], patch[15][0]}
								
							};
		float pontos_base_y[4][4] = {
								{patch[0][1], patch[1][1], patch[2][1], patch[3][1]},
								{patch[4][1], patch[5][1], patch[6][1], patch[7][1]},
								{patch[8][1], patch[9][1], patch[10][1], patch[11][1]},
								{patch[12][1], patch[13][1], patch[14][1], patch[15][1]}
								
							};

		float pontos_base_z[4][4] = {
								{patch[0][2], patch[1][2], patch[2][2], patch[3][2]},
								{patch[4][2], patch[5][2], patch[6][2], patch[7][2]},
								{patch[8][2], patch[9][2], patch[10][2], patch[11][2]},
								{patch[12][2], patch[13][2], patch[14][2], patch[15][2]}
								
							};
		for (int iTesselation=0;iTesselation<tesselation;iTesselation++){ 
			for (int jTesselation=0;jTesselation<tesselation;jTesselation++){
				float ponto1[3];
				float ponto2[3];
				float ponto3[3];
				float ponto4[3];
				gerarPontos(dif, iTesselation, jTesselation, *pontos_base_x,*pontos_base_y,*pontos_base_z,ponto1);
				gerarPontos(dif, iTesselation+1, jTesselation, *pontos_base_x,*pontos_base_y,*pontos_base_z,ponto2);
				gerarPontos(dif, iTesselation, jTesselation+1, *pontos_base_x,*pontos_base_y,*pontos_base_z,ponto3);
				gerarPontos(dif, iTesselation, jTesselation+1, *pontos_base_x,*pontos_base_y,*pontos_base_z,ponto4);

				addPonto(surface,newPonto(ponto1[0], ponto1[1], ponto1[2]));
				addPonto(surface,newPonto(ponto2[0], ponto2[1], ponto2[2]));
				addPonto(surface,newPonto(ponto3[0], ponto3[1], ponto3[2]));
				addPonto(surface,newPonto(ponto2[0], ponto2[1], ponto2[2]));
				addPonto(surface,newPonto(ponto4[0], ponto4[1], ponto4[2]));
				addPonto(surface,newPonto(ponto3[0], ponto3[1], ponto3[2]));

			}
		}

	}
    return surface;
}