#include <stdio.h>
#include "figura.hpp"
#include "ponto.hpp"


Figura generatePlane(int length, int divisions) {
	Figura plano;
	float half = (float)length / 2;
	float div = (float)length / divisions;
	//pontos necessário para fazer triangulos do primeiro quadrado do plano
	float x0 = -half, z0 = -half,
		x1 = -half, z1 = -half + div,
		x2 = -half + div, z2 = -half + div,
		x3 = -half + div, z3 = -half;

	for (int line = 0; line < divisions; line++) {
		for (int collums = 0; collums < divisions; collums++) {
			//@TODO - meter aqui as funcoes de meter as cenas na figura
			//so estou a meter os pontos

			//primeiro triangulo
			addPonto(plano,newPonto(x0 + collums * div, 0, z0));
			addPonto(plano,newPonto(x1 + collums * div, 0, z1));
			addPonto(plano, newPonto(x2 + collums * div, 0, z2));

			//segundo triangulo
			addPonto(plano, newPonto(x2 + collums * div, 0, z2));
			addPonto(plano, newPonto(x3 + collums * div, 0, z3));
			addPonto(plano, newPonto(x0 + collums * div, 0, z0));
		}
		z0 += div; z1 += div; z2 += div; z3 += div;
	}
	//mudar return 
	return plano;
}