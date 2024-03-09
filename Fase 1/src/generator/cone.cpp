#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include "../utils/figura.hpp"

Figura generateCone(float radius, float height, int slices, int stacks) {
	Figura cone = Figura();
	float alfa = (float)(2.0f * M_PI) / slices;
	//altura das stacks
	float div_height = height / stacks;

	//base
	for (int i = 0; i < slices; i++) {
		float alfa_1 = i * alfa;
		float alfa_2 = (i + 1) * alfa;

		addPonto(cone, newPonto(radius * sin(alfa_1), 0, radius * cos(alfa_1)));
		addPonto(cone, newPonto(0, 0, 0));
		addPonto(cone, newPonto(radius * sin(alfa_2), 0, radius * cos(alfa_2)));
	}

	float atual_radius;
	float next_radius = radius;
	int n = 0;

	//laterais
	for (int i = 0; i < slices; i++) {
		atual_radius = radius;
		for (int j = 0; j < stacks - 1;j++) {
			//o raio de cada stack vai ser (1 - ("stack atual" / "numero stacks totais")) * raio da base
			n = j + 1;
			//atual_radius = (1.0 - ((float) j / stacks)) * radius;
			next_radius = (float)(1.0 - ((float) n / stacks)) * radius;

			//primeiro triangulo
			addPonto(cone, newPonto(atual_radius * sin(i * alfa), div_height * j, atual_radius * cos(i * alfa)));
			addPonto(cone, newPonto(atual_radius * sin((i + 1) * alfa), div_height * j, atual_radius * cos((i + 1) * alfa)));
			addPonto(cone, newPonto(next_radius * sin(i * alfa), div_height * n, next_radius * cos(i * alfa)));

			//segundo triangulo
			addPonto(cone, newPonto(next_radius * sin(i * alfa), div_height * n, next_radius * cos(i * alfa)));
			addPonto(cone, newPonto(atual_radius * sin((i + 1) * alfa), div_height * j, atual_radius * cos((i + 1) * alfa)));
			addPonto(cone, newPonto(next_radius * sin((i + 1) * alfa), div_height * n, next_radius * cos((i + 1) * alfa)));

			atual_radius = next_radius; //necessario verificar!!!
		}

		//@TODO - rever!!!
		//triangulos do topo do cone (ultima stack) - aproveita os ultimos pontos calculados
		addPonto(cone, newPonto(next_radius * sin(i * alfa), div_height * n, next_radius * cos(i * alfa)));
		addPonto(cone, newPonto(next_radius * sin((i + 1) * alfa), div_height * n, next_radius * cos((i + 1) * alfa)));
		addPonto(cone, newPonto(0, height, 0));		
	}
	return cone;
}