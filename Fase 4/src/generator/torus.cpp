#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include "../utils/figura.hpp"

Ponto calculateTorusNormal(float theta, float phi, float R, float r) {
	float nx = cos(theta) * cos(phi);
	float ny = cos(theta) * sin(phi);
	float nz = sin(theta);

	// Normalizar o vetor
	float length = sqrt(nx * nx + ny * ny + nz * nz);
	nx /= length;
	ny /= length;
	nz /= length;

	return newPonto(nx, ny, nz);
}

Figura generateTorus(float ri, float re, int slices, int stacks) {
	Figura ring = Figura();

	float n = 0;
	float sliceStep = (float)(2.0f * M_PI) / slices;
	float stackStep = (float)(2.0f * M_PI) / stacks;

	float radius = (ri + re) / 2;
	float dist = radius - ri;

	for (int i = 0; i < slices; i++) {
		float alfai = i * sliceStep;
		float alfaf = (i + 1) * sliceStep;

		for (int j = 0; j < stacks;j++) {
			float betai = j * stackStep;
			float betaf = (j + 1) * stackStep;
			
			Ponto p1 = newPonto((radius + dist * cos(betai)) * cos(alfai), dist * sin(betai),(radius + dist * cos(betai)) * sin(alfai));
			Ponto p2 = newPonto((radius + dist * cos(betaf)) * cos(alfai), dist * sin(betaf), (radius + dist * cos(betaf)) * sin(alfai));
			Ponto p3 = newPonto((radius + dist * cos(betaf)) * cos(alfaf), dist * sin(betaf), (radius + dist * cos(betaf)) * sin(alfaf));
			Ponto p4 = newPonto((radius + dist * cos(betai)) * cos(alfaf), dist * sin(betai), (radius + dist * cos(betai)) * sin(alfaf));



			//a testar com a luz dps
			Ponto n1 = normalize(newPonto(cos(betai) * cos(alfai), sin(betai), cos(betai) * sin(alfai)));
			Ponto n2 = normalize(newPonto(cos(betaf) * cos(alfai), sin(betaf), cos(betaf) * sin(alfai)));
			Ponto n3 = normalize(newPonto(cos(betaf) * cos(alfaf), sin(betaf), cos(betaf) * sin(alfaf)));
			Ponto n4 = normalize(newPonto(cos(betai) * cos(alfaf), sin(betai), cos(betai) * sin(alfaf)));

			//Ponto n1 = calculateTorusNormal(alfai, betai, radius, dist);
			//Ponto n2 = calculateTorusNormal(alfai, betaf, radius, dist);
			//Ponto n3 = calculateTorusNormal(alfaf, betaf, radius, dist);
			//Ponto n4 = calculateTorusNormal(alfaf, betai, radius, dist);

			/*
			* p1 ---- p4
			* | \     |
			* |   \   |
			* |     \ |
			* p2 ---- p3
			*/

			addPonto(ring, p1);
			addPonto(ring, p2);
			addPonto(ring, p3);

			addNormal(ring, n1);
			addNormal(ring, n2);
			addNormal(ring, n3);

			addPonto(ring, p1);
			addPonto(ring, p3);
			addPonto(ring, p4);

			addNormal(ring, n1);
			addNormal(ring, n3);
			addNormal(ring, n4);
		}																							   
		
	}
	return ring;
}