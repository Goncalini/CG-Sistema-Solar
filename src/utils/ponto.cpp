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