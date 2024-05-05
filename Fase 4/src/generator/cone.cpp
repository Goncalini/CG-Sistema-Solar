#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include "../utils/figura.hpp"

Figura generateCone(float radius, float height, int slices, int stacks) {
	Figura cone = Figura();
	float alfa = (float)(2.0f * M_PI) / slices;
	//altura das stacks
	float div_height = height / stacks;

	std::vector<Ponto> normals;
	//float origem[3] = { 0.0,0.0,0.0 };
	//float topo[3] = { 0.0,height,0.0};
	

	//base
	for (int i = 0; i < slices; i++) {
		float alfa_1 = i * alfa;
		float alfa_2 = (i + 1) * alfa;

	
		//float v[3]; //vetor vertical V
		//float h[3]; //vetor horizontal entre origem e ponto
		//float hip[3]; //vetor hipotenusa entre topo e ponto
		//float coords[3] = { radius * sin(alfa_1), 0, radius * cos(alfa_1) }; //coordenadas do ponto
		//
		//vector2Pontos(origem, topo, v);
		//vector2Pontos(origem, coords, h);
		//vector2Pontos(topo, coords, hip);
		//
		//float vh[3];
		//cross(v,h,vh);
		//float res[3];
		//cross(vh, hip, res);
		//normalize(res);
		//normals.push_back(newPontoArray(res));

		addPonto(cone, newPonto(radius * sin(alfa_1), 0, radius * cos(alfa_1)));
		addPonto(cone, newPonto(0, 0, 0));
		addPonto(cone, newPonto(radius * sin(alfa_2), 0, radius * cos(alfa_2)));

		addNormal(cone, newPonto(0, -1, 0));
		addNormal(cone, newPonto(0, -1, 0));
		addNormal(cone, newPonto(0, -1, 0));
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
			next_radius = (float)(1.0 - ((float) n / stacks)) * radius;

			Ponto p0 = newPonto(atual_radius * sin(i * alfa), div_height * j, atual_radius * cos(i * alfa));
			Ponto p1 = newPonto(atual_radius * sin((i + 1) * alfa), div_height * j, atual_radius * cos((i + 1) * alfa));
			Ponto p2 = newPonto(next_radius * sin(i * alfa), div_height * n, next_radius * cos(i * alfa));
			Ponto p3 = newPonto(next_radius * sin((i + 1) * alfa), div_height * n, next_radius * cos((i + 1) * alfa));

			Ponto n1 = calculateNormal(p0, p1, p2);
			Ponto n2 = calculateNormal(p3, p1, p2);

			//primeiro triangulo
			addPonto(cone, p0);
			addPonto(cone, p1);
			addPonto(cone, p2);

			addNormal(cone, n1);
			addNormal(cone, n2);
			addNormal(cone, n1);

			//segundo triangulo
			addPonto(cone, p2);
			addPonto(cone, p1);
			addPonto(cone, p3);

			addNormal(cone, n1);
			addNormal(cone, n2);
			addNormal(cone, n2);
		
			atual_radius = next_radius;
		}
		//triangulos do topo do cone (ultima stack) - aproveita os ultimos pontos calculados
		Ponto px = newPonto(next_radius * sin(i * alfa), div_height * n, next_radius * cos(i * alfa));
		Ponto py = newPonto(next_radius * sin((i + 1) * alfa), div_height * n, next_radius * cos((i + 1) * alfa));
		Ponto pt = newPonto(0, height, 0);

		Ponto nx = calculateNormal(px, py, pt);
		Ponto ny = calculateNormal(py, px, pt);

		addPonto(cone, px);
		addPonto(cone, py);
		addPonto(cone, pt);

		addNormal(cone, nx);
		addNormal(cone, ny);
		addNormal(cone, nx);


	}
	return cone;
}