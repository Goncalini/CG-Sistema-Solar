#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include "../utils/figura.hpp"

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


			//a testar com a luz dps!!
			Ponto n1 = normalize(newPonto(cos(betai) * cos(alfai), sin(betai), cos(betai) * sin(alfai)));
			Ponto n2 = normalize(newPonto(cos(betaf) * cos(alfai), sin(betaf), cos(betaf) * sin(alfai)));
			Ponto n3 = normalize(newPonto(cos(betaf) * cos(alfaf), sin(betaf), cos(betaf) * sin(alfaf)));
			Ponto n4 = normalize(newPonto(cos(betai) * cos(alfaf), sin(betai), cos(betai) * sin(alfaf)));

			Ponto t1 = newPonto((float)j / stacks, (float)i / slices, 0);
			Ponto t2 = newPonto((float)(j + 1) / stacks, (float)i / slices, 0);
			Ponto t3 = newPonto((float)(j + 1) / stacks, (float)(i + 1) / slices, 0);
			Ponto t4 = newPonto((float)j / stacks, (float)(i + 1) / slices, 0);
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

			addTexture(ring, t1);
			addTexture(ring, t2);
			addTexture(ring, t3);

			addPonto(ring, p1);
			addPonto(ring, p3);
			addPonto(ring, p4);

			addNormal(ring, n1);
			addNormal(ring, n3);
			addNormal(ring, n4);

			addTexture(ring, t1);
			addTexture(ring, t3);
			addTexture(ring, t4);
		}																							   
		
	}
	return ring;
}