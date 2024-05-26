#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include "../utils/figura.hpp"

Figura generateCone(float radius, float height, int slices, int stacks) {
	Figura cone = Figura();
	float alfa = (float)(2.0f * M_PI) / slices;
	//altura das stacks
	float div_height = height / stacks;

	//normais
	std::vector<Ponto> normals;
	//float origem[3] = { 0.0,0.0,0.0 };
	//float topo[3] = { 0.0,height,0.0};
	

	//base
	for (int i = 0; i < slices; i++) {
		float alfa_1 = i * alfa;
		float alfa_2 = (i + 1) * alfa;

		addPonto(cone, newPonto(radius * sin(alfa_1), 0, radius * cos(alfa_1)));
		addPonto(cone, newPonto(0, 0, 0));
		addPonto(cone, newPonto(radius * sin(alfa_2), 0, radius * cos(alfa_2)));

		addNormal(cone, newPonto(0, -1, 0));
		addNormal(cone, newPonto(0, -1, 0));
		addNormal(cone, newPonto(0, -1, 0));

		addTexture(cone, newPonto(0.5 + 0.5 * sin(alfa_1), 0.5 + 0.5 * cos(alfa_1), 0));
		addTexture(cone, newPonto(0.5, 0.5, 0));//ponto do centro
		addTexture(cone, newPonto(0.5 + 0.5 * sin(alfa_2), 0.5 + 0.5 * cos(alfa_2), 0));
	}

	float atual_radius;
	float next_radius = radius;
	int n = 0;
	float nY = (float)(sin(M_PI - atan(height/radius)));

	//laterais
	for (int i = 0; i < slices; i++) {
		atual_radius = radius;
		for (int j = 0; j < stacks - 1;j++) {
			//o raio de cada stack vai ser (1 - ("stack atual" / "numero stacks totais")) * raio da base
			n = j + 1;
			next_radius = (float)(1.0 - ((float) n / stacks)) * radius;

			Ponto p0 = newPonto(atual_radius * sin(i * alfa), div_height * j, atual_radius * cos(i * alfa));
			Ponto p1 = newPonto(atual_radius * sin((i + 1) * alfa), div_height * j, atual_radius * cos((i + 1) * alfa));
			Ponto p2 = newPonto(next_radius * sin(i * alfa), div_height * n, next_radius * cos(i * alfa));
			Ponto p3 = newPonto(next_radius * sin((i + 1) * alfa), div_height * n, next_radius * cos((i + 1) * alfa));

			Ponto n1 = normalize(newPonto(cos(i*alfa),sin(nY),sin(i*alfa)));
			Ponto n2 = normalize(newPonto(cos((i+1)*alfa),sin(nY),sin((i+1)*alfa)));

			//texturas
			float s0 = (float)i / slices;
			float s1 = (float)(i + 1) / slices;
			float t0 = (float)j / stacks;
			float t1 = (float)n / stacks; //(j+1)/stacks

			//primeiro triangulo
			addPonto(cone, p0);
			addPonto(cone, p1);
			addPonto(cone, p2);

			addNormal(cone, n1);
			addNormal(cone, n2);
			addNormal(cone, n1);

			addTexture(cone, newPonto(s0, t0, 0));
			addTexture(cone, newPonto(s1, t0, 0));
			addTexture(cone, newPonto(s0, t1, 0));

			//segundo triangulo
			addPonto(cone, p2);
			addPonto(cone, p1);
			addPonto(cone, p3);

			addNormal(cone, n1);
			addNormal(cone, n2);
			addNormal(cone, n2);

			addTexture(cone, newPonto(s0, t1, 0));
			addTexture(cone, newPonto(s1, t0, 0));
			addTexture(cone, newPonto(s1, t1, 0));
		
			atual_radius = next_radius;
		}
		//triangulos do topo do cone (ultima stack) 

		//nao sei se usar aqui o n � v�lido - trocar para stacks - 1?!!!
		Ponto px = newPonto(next_radius * sin(i * alfa), div_height * n, next_radius * cos(i * alfa));
		Ponto py = newPonto(next_radius * sin((i + 1) * alfa), div_height * n, next_radius * cos((i + 1) * alfa));
		Ponto pt = newPonto(0, height, 0);

		Ponto nx = normalize(newPonto(cos(i*alfa),sin(nY),sin(i*alfa)));
		Ponto ny = normalize(newPonto(cos((i+1)*alfa),sin(nY),sin((i+1)*alfa)));

		float u0 = (float)i / slices;
		float u1 = (float)(i + 1) / slices;
		float t = (float)n / stacks;

		addPonto(cone, px);
		addPonto(cone, py);
		addPonto(cone, pt);

		addNormal(cone, nx);
		addNormal(cone, ny);
		addNormal(cone, nx);

		addTexture(cone, newPonto(u0, t, 0));
		addTexture(cone, newPonto(u1, t, 0));
		addTexture(cone, newPonto((u0 + u1) / 2, 1.0, 0)); //v�rias duvidas sobre isto!!!!

	}
	return cone;
}