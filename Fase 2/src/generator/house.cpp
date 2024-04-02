#include <stdio.h>
#include "../utils/figura.hpp"

void generateCube(int length, int width, float height, Figura& figura) {
	float x = (float)length / 2;
	float z = (float)width / 2;
    float y = (float)height / 2;

    //Base é composta por 2 triangulos 
    addPonto(figura,newPonto(x,0,z));
    addPonto(figura,newPonto(x,0,-z));
    addPonto(figura,newPonto(-x,0,z));
}

//trocar para gerar figura
Figura generateHouse(int length, int width, int height) {
	Figura house = Figura();
	generateCube(length, width,height,house);
	return house;
}