#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include "../utils/figura.hpp"

Figura generateSphere(float radius, int slices, int stacks) {
	Figura sphere = Figura();
	float sliceStep = (float)(2.0f * M_PI) / slices;
	float stackStep = (float)M_PI / stacks;

	//para texturas
	float s_step = (float)1.0f / slices;
	float t_step = (float)1.0f / stacks;

	for (int i = 0; i < stacks; i++) {
		float betai = M_PI / 2.0f - i * stackStep;
		float betaf = M_PI / 2.0f - (i + 1) * stackStep;

		for (int j = 0; j < slices;j++) {
			float alfai = j * sliceStep;
			float alfaf = (j + 1) * sliceStep;

			Ponto p1 = newPonto(radius * cos(betai) * sin(alfai), radius * sin(betai), radius * cos(betai) * cos(alfai));
			Ponto p2 = newPonto(radius * cos(betaf) * sin(alfai), radius * sin(betaf), radius * cos(betaf) * cos(alfai));
			Ponto p3 = newPonto(radius * cos(betaf) * sin(alfaf), radius * sin(betaf), radius * cos(betaf) * cos(alfaf));
			Ponto p4 = newPonto(radius * cos(betai) * sin(alfaf), radius * sin(betai), radius * cos(betai) * cos(alfaf));

			/*
			* p1 ---- p4
			* | \     |
			* |   \   |
			* |     \ |
			* p2 ---- p3
			*/
			Ponto n1 = normalize(p1);
			Ponto n2 = normalize(p2);
			Ponto n3 = normalize(p3);
			Ponto n4 = normalize(p4);

			Ponto t1 = newPonto(s_step * i, t_step * j, 0);
			Ponto t2 = newPonto(s_step * i, t_step * (j+1), 0);
			Ponto t3 = newPonto(s_step * (i+1), t_step * (j+1), 0);
			Ponto t4 = newPonto(s_step * (i+1), t_step * j, 0);

			//se for a primeira stack de cima só tem o triangulo da direita
			if (i != 0) {
				//p1,p3,p4
				addPonto(sphere, p1);
				addPonto(sphere, p3);
				addPonto(sphere, p4);

				addNormal(sphere, n1);
				addNormal(sphere, n3);
				addNormal(sphere, n4);

				addTexture(sphere, t1);
				addTexture(sphere, t3);
				addTexture(sphere, t4);
			}
			//se for a ultima só desenha o da esquerda 
			if (i != stacks - 1) {
				//p1,p2,p3
				addPonto(sphere,p1);
				addPonto(sphere, p2);
				addPonto(sphere, p3);

				addNormal(sphere, n1);
				addNormal(sphere, n2);
				addNormal(sphere, n3);

				addTexture(sphere, t1);
				addTexture(sphere, t2);
				addTexture(sphere, t3);
			}
		}
	}
	return sphere;
}