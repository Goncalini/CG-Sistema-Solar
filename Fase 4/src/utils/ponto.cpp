#include "ponto.hpp"

struct ponto {
	float x, y, z;
};

Ponto newPonto(float x, float y, float z) {
	Ponto n = (Ponto)malloc(sizeof(struct ponto));
	if (n != NULL) {
		n->x = x; n->y = y; n->z = z;
	}
	//std::cout << getX(n) << ";" << getY(n) << ";" << getZ(n) << "\n";
	return n;
}

Ponto newPontoArray(float* arr) {
	Ponto n = (Ponto)malloc(sizeof(struct ponto));
	if (n != NULL) {
		n->x = arr[0]; n->y = arr[1]; n->z = arr[2];
	}
	return n;
}

Ponto normalize(Ponto ponto) {
	float x = getX(ponto);
	float y = getY(ponto);
	float z = getZ(ponto);
	float length = sqrt(x * x + y * y + z * z);
	return length == 0 ? ponto : newPonto(x / length, y / length, z / length);
}

void vector2Pontos(float* p1, float* p2, float* res) {
	for (int i = 0; i < 3; i++) {
		res[i] = p2[i] - p1[i];
	}
}

Ponto calculateNormal(Ponto p0, Ponto p1,Ponto p2) {
	float v1[3] = { getX(p1) - getX(p0), getY(p1) - getY(p0), getZ(p1) - getZ(p0) };
	float v2[3] = { getX(p2) - getX(p0), getY(p2) - getY(p0), getZ(p2) - getZ(p0) };

	float x = v1[1] * v2[2] - v1[2] * v2[1];
	float y = v1[2] * v2[0] - v1[0] * v2[2];
	float z = v1[0] * v2[1] - v1[1] * v2[0];

	return normalize(newPonto(x, y, z));
}

float getX(Ponto p) {
	if (p) return p->x;
	return 0.0f;
}

float getY(Ponto p) {
	if (p) return p->y;
	return 0.0f;
}

float getZ(Ponto p) {
	if (p) return p->z;
	return 0.0f;
}