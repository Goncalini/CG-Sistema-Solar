#include <stdio.h>
#include "../utils/figura.hpp"


void generateXZ(int length, int divisions, float height, int baixo, Figura& figura) {
	float half = (float)length / 2;
	float div = (float)length / divisions;
	float texStep = (float)1.0f / divisions;
	float normals[3] = { 0.0,1.0,0.0 };

	//pontos necessário para fazer triangulos do primeiro quadrado do plano
	float x0 = -half, z0 = -half,
		x1 = -half, z1 = -half + div,
		x2 = -half + div, z2 = -half,
		x3 = -half + div, z3 = -half + div;
	//se for a fase de baixo, precisa de estar virada para baixo!
	if (baixo == 1) {
		float xaux = x0, zaux = z0;
		x0 = x3; 
		z0 = z3;
		x3 = xaux;
		z3 = zaux;

		//inverter as normais
		normals[1] = -normals[1];
	}
	for (int line = 0; line < divisions; line++) {
		for (int collums = 0; collums < divisions; collums++) {
			float s0 = collums * texStep;
			float t1 = 1 - (line * texStep);
			float s1 = (collums + 1) * texStep;
			float t0 = 1 - ((line + 1) * texStep);

			if (baixo == 1) {
				std::swap(t0, t1);
			}

			//primeiro triangulo
			addPonto(figura, newPonto(x0 + collums * div, height, z0));
			addPonto(figura, newPonto(x1 + collums * div, height, z1));
			addPonto(figura, newPonto(x3 + collums * div, height, z3));

			addNormal(figura, newPonto(normals[0], normals[1], normals[2]));
			addNormal(figura, newPonto(normals[0], normals[1], normals[2]));
			addNormal(figura, newPonto(normals[0], normals[1], normals[2]));

			addTexture(figura, newPonto(s0, t1, 0));
			addTexture(figura, newPonto(s0, t0, 0));
			addTexture(figura, newPonto(s1, t0, 0));


			//segundo triangulo
			addPonto(figura, newPonto(x2 + collums * div, height, z2));
			addPonto(figura, newPonto(x0 + collums * div, height, z0));
			addPonto(figura, newPonto(x3 + collums * div, height, z3));

			addNormal(figura, newPonto(normals[0], normals[1], normals[2]));
			addNormal(figura, newPonto(normals[0], normals[1], normals[2]));
			addNormal(figura, newPonto(normals[0], normals[1], normals[2]));

			addTexture(figura, newPonto(s1, t1, 0));
			addTexture(figura, newPonto(s0, t1, 0));
			addTexture(figura, newPonto(s1, t0, 0));
		}
		z0 += div; z1 += div; z2 += div; z3 += div;
	}
}


//padrão é para o negativo do Z
void generateXY(int length, int divisions, float height, int reverse,Figura& figura) {
	float half = (float)length / 2;
	float div = (float)length / divisions;
	float texStep = (float)1.0f / divisions;
	float normals[3] = { 0.0,0.0,-1.0 };
	//pontos necessário para fazer triangulos do primeiro quadrado do plano
	float x0 = -half, y0 = -half,
		x1 = -half, y1 = -half + div,
		x2 = -half + div, y2 = -half,
		x3 = -half + div, y3 = -half + div;

	//se for a fase de trás, precisa de estar virada!
	if (reverse == 1) {
		float xaux = x0, yaux = y0;
		x0 = x3;
		y0 = y3;
		x3 = xaux;
		y3 = yaux;
		//inverter as normais
		normals[2] = -normals[2];
	}
	for (int line = 0; line < divisions; line++) {
		for (int collums = 0; collums < divisions; collums++) {
			float s0, t0, s1, t1;
			if (reverse == 1) {
				t0 = (1 + collums) * texStep;
				t1 = collums * texStep;
				s0 = line * texStep;
				s1 = (line + 1) * texStep;
			}
			else {
				s0 = 1 - (collums + 1) * texStep;
				t1 = line * texStep;
				s1 = 1 - collums * texStep;
				t0 = (line + 1) * texStep;

			}

			//primeiro triangulo
			addPonto(figura, newPonto(x0 + collums * div, y0, height));
			addPonto(figura, newPonto(x1 + collums * div, y1, height));
			addPonto(figura, newPonto(x3 + collums * div, y3, height));

			addNormal(figura, newPonto(normals[0], normals[1], normals[2]));
			addNormal(figura, newPonto(normals[0], normals[1], normals[2]));
			addNormal(figura, newPonto(normals[0], normals[1], normals[2]));

			addTexture(figura, newPonto(s1, t0, 0));
			addTexture(figura, newPonto(s1, t1, 0));
			addTexture(figura, newPonto(s0, t1, 0));

			//segundo triangulo
			addPonto(figura, newPonto(x2 + collums * div, y2, height));
			addPonto(figura, newPonto(x0 + collums * div, y0, height));
			addPonto(figura, newPonto(x3 + collums * div, y3, height));

			addNormal(figura, newPonto(normals[0], normals[1], normals[2]));
			addNormal(figura, newPonto(normals[0], normals[1], normals[2]));
			addNormal(figura, newPonto(normals[0], normals[1], normals[2]));

			addTexture(figura, newPonto(s0, t0, 0));
			addTexture(figura, newPonto(s1, t0, 0));
			addTexture(figura, newPonto(s0, t1, 0));

		}
		y0 += div; y1 += div; y2 += div; y3 += div;
	}
}



//padrão é para o negativo do X (reverse = 0)
void generateYZ(int length, int divisions, float height, int reverse,Figura& figura) {
	float half = (float)length / 2;
	float div = (float)length / divisions;
	float texStep = (float)1.0f / divisions;
	float normals[3] = { -1.0,0.0,0.0 };

	//pontos necessário para fazer triangulos do primeiro quadrado do plano
	float y0 = -half, z0 = -half,
		y1 = -half, z1 = -half + div,
		y2 = -half + div, z2 = -half,
		y3 = -half + div, z3 = -half + div;

	//se for a fase de trás, precisa de estar virada!
	if (reverse == 1) {
		float yaux = y0, zaux = z0;
		y0 = y3;
		z0 = z3;
		y3 = yaux;
		z3 = zaux;
		normals[0] = -normals[0]; //{1,0,0}
	}

	for (int line = 0; line < divisions; line++) {
		for (int collums = 0; collums < divisions; collums++) {
			float s0, t0, s1, t1;
			if (reverse == 1) {
				s0 = (line + 1) * texStep;
				t0 = 1.0f - (collums + 1) * texStep;
				s1 = line * texStep;
				t1 = 1.0f - collums * texStep;
			}
			else {
				s0 = collums * texStep;
				t0 = line * texStep;
				s1 = (collums + 1) * texStep;
				t1 = (line + 1) * texStep;
			}
			//primeiro triangulo
			addPonto(figura, newPonto(height, y0 + collums * div, z0));
			addPonto(figura, newPonto(height, y1 + collums * div, z1));
			addPonto(figura, newPonto(height, y3 + collums * div, z3));

			addNormal(figura, newPonto(normals[0], normals[1], normals[2]));
			addNormal(figura, newPonto(normals[0], normals[1], normals[2]));
			addNormal(figura, newPonto(normals[0], normals[1], normals[2]));

			addTexture(figura, newPonto(s0, t0, 0));
			addTexture(figura, newPonto(s1, t0, 0));
			addTexture(figura, newPonto(s1, t1, 0));

			//segundo triangulo
			addPonto(figura, newPonto(height, y2 + collums * div, z2));
			addPonto(figura, newPonto(height, y0 + collums * div, z0));
			addPonto(figura, newPonto(height, y3 + collums * div, z3));

			addNormal(figura, newPonto(normals[0], normals[1], normals[2]));
			addNormal(figura, newPonto(normals[0], normals[1], normals[2]));
			addNormal(figura, newPonto(normals[0], normals[1], normals[2]));

			addTexture(figura, newPonto(s0, t1, 0));
			addTexture(figura, newPonto(s0, t0, 0));
			addTexture(figura, newPonto(s1, t1, 0));
		}
		z0 += div; z1 += div; z2 += div; z3 += div;
	}
}



//trocar para gerar figura
Figura generateBox(int length, int divisions) {
	Figura box = Figura();
	float half = (float)length / 2;
	generateXZ(length, divisions, half, 0, box);
	generateXZ(length, divisions, -half, 1, box);
	generateXY(length, divisions, -half, 0, box);
	generateXY(length, divisions, half, 1, box);
	generateYZ(length, divisions, -half, 0, box);
	generateYZ(length, divisions, half, 1, box);
	return box;
}