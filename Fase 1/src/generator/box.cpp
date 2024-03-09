#include <stdio.h>
#include "../utils/figura.hpp"


void generateXZ(int length, int divisions, float height, int baixo, Figura& figura) {
	float half = (float)length / 2;
	float div = (float)length / divisions;
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
	}

	for (int line = 0; line < divisions; line++) {
		for (int collums = 0; collums < divisions; collums++) {
			//@TODO - meter aqui as funcoes de meter as cenas na figura
			//primeiro triangulo
			addPonto(figura, newPonto(x0 + collums * div, height, z0));
			addPonto(figura, newPonto(x1 + collums * div, height, z1));
			addPonto(figura, newPonto(x3 + collums * div, height, z3));


			//segundo triangulo
			addPonto(figura, newPonto(x2 + collums * div, height, z2));
			addPonto(figura, newPonto(x0 + collums * div, height, z0));
			addPonto(figura, newPonto(x3 + collums * div, height, z3));
			
		}
		z0 += div; z1 += div; z2 += div; z3 += div;
	}
	//writeToFile(figura, "box.ex");
	//mudar return 
}


void generateXY(int length, int divisions, float height, int reverse,Figura& figura) {
	float half = (float)length / 2;
	float div = (float)length / divisions;
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
	}
	for (int line = 0; line < divisions; line++) {
		for (int collums = 0; collums < divisions; collums++) {
			//primeiro triangulo
			addPonto(figura, newPonto(x0 + collums * div, y0, height));
			addPonto(figura, newPonto(x1 + collums * div, y1, height));
			addPonto(figura, newPonto(x3 + collums * div, y3, height));

			//segundo triangulo
			addPonto(figura, newPonto(x2 + collums * div, y2, height));
			addPonto(figura, newPonto(x0 + collums * div, y0, height));
			addPonto(figura, newPonto(x3 + collums * div, y3, height));
		}
		y0 += div; y1 += div; y2 += div; y3 += div;
	}
	//mudar return 
	//writeToFile(figura, "box.ex");
}



//padrão é para o negativo do X
void generateYZ(int length, int divisions, float height, int reverse,Figura& figura) {
	float half = (float)length / 2;
	float div = (float)length / divisions;

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
	}

	for (int line = 0; line < divisions; line++) {
		for (int collums = 0; collums < divisions; collums++) {
			//primeiro triangulo
			addPonto(figura, newPonto(height, y0 + collums * div, z0));
			addPonto(figura, newPonto(height, y1 + collums * div, z1));
			addPonto(figura, newPonto(height, y3 + collums * div, z3));

			//segundo triangulo
			addPonto(figura, newPonto(height, y2 + collums * div, z2));
			addPonto(figura, newPonto(height, y0 + collums * div, z0));
			addPonto(figura, newPonto(height, y3 + collums * div, z3));
		}
		z0 += div; z1 += div; z2 += div; z3 += div;
	}
	//mudar return 
	//writeToFile(figura, "box.ex");
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