#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include "../utils/figura.hpp"

Figura generateRing(float ri, float re, int slices) {
	Figura ring = Figura();

	float n = 0, alfa = (float)(2.0f * M_PI) / slices;

	for (int i = 0; i < slices; i++, n += alfa) {
		Ponto p1 = newPonto(ri * sin(n), 0, ri * cos(n));
		Ponto p2 = newPonto(re * sin(n), 0, re * cos(n));
		Ponto p3 = newPonto(re * sin(n + alfa), 0, re * cos(n + alfa));
		Ponto p4 = newPonto(ri * sin(n + alfa), 0, ri * cos(n + alfa));

		/*
		* p1 ---- p4
		* | \     |
		* |   \   |
		* |     \ |
		* p2 ---- p3
		*/

		//vista superior
		addPonto(ring, p1);
		addPonto(ring, p2);
		addPonto(ring, p3);

		addPonto(ring, p1);
		addPonto(ring, p3);
		addPonto(ring, p4);

		//vista inferior
		addPonto(ring, p1);
		addPonto(ring, p3);
		addPonto(ring, p2);

		addPonto(ring, p1);
		addPonto(ring, p4);
		addPonto(ring, p3);
		
	}
	return ring;
}