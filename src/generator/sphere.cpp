#include <stdio.h>
#include <math.h>

Figura generateSphere(float radius, int slices, int stacks) {
	Figura sphere;
	float sliceStep = 2.0f * M_PI / slices;
	float stackStep = M_PI / stacks;

	for (int i = 0; i < stacks; i++) {
		float betai = i * stackStep; //calculo do beta para cada linha
		float betaf = (i + 1) * stackStep;

		for (int j = 0; j < slices;j++) {
			float alfai = i * sliceStep;
			float alfaf = (i + 1) * sliceStep;

			//DEFINIR AQUI OS PONTOS!!
			Ponto p1 = newPonto(radius * cos(betai) * sin(alfai), radius * sin(betai), radius * cos(betai) * cos(alfai));
			Ponto p2 = newPonto(radius * cos(betaf) * sin(alfai), radius * sin(betaf), radius * cos(betaf) * cos(alfai));
			Ponto p3 = newPonto(radius * cos(betaf) * sin(alfaf), radius * sin(betaf), radius * cos(betaf) * cos(alfaf));
			Ponto p4 = newPonto(radius * cos(betai) * sin(alfaf), radius * sin(betai), radius * cos(betai) * cos(alfaf));


			//se for a primeira stack de cima só tem o triangulo da direita
			if (i != 0) {
				//p1,p3,p4
				addPonto(sphere, p1);
				addPonto(sphere, p3);
				addPonto(sphere, p4);
			}
			//se for a ultima só desenha o da esquerda 
			if (i != stacks - 1) {
				//p1,p2,p3
				addPonto(sphere,p1);
				addPonto(sphere, p2);
				addPonto(sphere, p3);
			}
			//????
			free(p1);
			free(p2);
			free(p3);
			free(p4);
		}
	}
	return sphere;
}