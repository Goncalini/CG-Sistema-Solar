#include <stdio.h>
#include "../utils/figura.hpp"
#include "../utils/ponto.hpp"


Figura generatePlane(int length, int divisions) {
	Figura plano = Figura();
	
	float half = (float)length / 2;
	float div = (float)length / divisions;
	float texStep = (float)1.0f / divisions;

	//pontos necessário para fazer triangulos do primeiro quadrado do plano
	float x0 = -half, z0 = -half,
		x1 = -half, z1 = -half + div,
		x2 = -half + div, z2 = -half + div,
		x3 = -half + div, z3 = -half;

	for (int line = 0; line < divisions; line++) {
		for (int collums = 0; collums < divisions; collums++) {
			/* Em coordenadas de textura:
			* (s0,t1)------(s1,t1)
			*		|		|
			*		|		|
			*		|		|
			* (s0,t0)------(s1,t0)
			*/
			float s0 = collums * texStep;
			float t1 = 1 - (line * texStep);
			float s1 = (collums + 1) * texStep;
			float t0 = 1 - ((line + 1) * texStep);

			//primeiro triangulo
			addPonto(plano,newPonto(x0 + collums * div, 0, z0));
			addPonto(plano,newPonto(x1 + collums * div, 0, z1));
			addPonto(plano, newPonto(x2 + collums * div, 0, z2));

			addNormal(plano, newPonto(0, 1, 0));
			addNormal(plano, newPonto(0, 1, 0));
			addNormal(plano, newPonto(0, 1, 0));

			addTexture(plano, newPonto(s0, t1, 0));
			addTexture(plano, newPonto(s0, t0, 0));
			addTexture(plano, newPonto(s1, t0, 0));


			//segundo triangulo
			addPonto(plano, newPonto(x2 + collums * div, 0, z2));
			addPonto(plano, newPonto(x3 + collums * div, 0, z3));
			addPonto(plano, newPonto(x0 + collums * div, 0, z0));

			addNormal(plano, newPonto(0, 1, 0));
			addNormal(plano, newPonto(0, 1, 0));
			addNormal(plano, newPonto(0, 1, 0));

			addTexture(plano, newPonto(s1, t0, 0));
			addTexture(plano, newPonto(s1, t1, 0));
			addTexture(plano, newPonto(s0, t1, 0));
		}
		z0 += div; z1 += div; z2 += div; z3 += div;
	}
	//mudar return 
	return plano;
}