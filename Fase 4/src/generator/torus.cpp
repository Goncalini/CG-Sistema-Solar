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

			addPonto(ring, p1);
			addPonto(ring, p3);
			addPonto(ring, p4);
		}																							   
		
	}
	return ring;
}