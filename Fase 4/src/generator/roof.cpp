#include <stdio.h>
#include "../utils/figura.hpp"

void generateXYZ(int length, int width, float height, Figura& figura) {
	float x = (float)length / 2;
	float z = (float)width / 2;

    //Triangulo frente
    addPonto(figura,newPonto(0,height,z));
    addPonto(figura,newPonto(-x,0,z));
    addPonto(figura,newPonto(x,0,z));
    
    //Triangulo tras
    addPonto(figura,newPonto(x,0,-z));
    addPonto(figura,newPonto(-x,0,-z));
    addPonto(figura,newPonto(0,height,-z));

    //Lado1
    addPonto(figura,newPonto(0,height,z));
    addPonto(figura,newPonto(x,0,z));
    addPonto(figura,newPonto(x,0,-z));

    addPonto(figura,newPonto(0,height,z));
    addPonto(figura,newPonto(x,0,-z));
    addPonto(figura,newPonto(0,height,-z));

    //Lado2
    addPonto(figura,newPonto(0,height,z));
    addPonto(figura,newPonto(-x,0,-z));
    addPonto(figura,newPonto(-x,0,z));

    addPonto(figura,newPonto(0,height,-z));
    addPonto(figura,newPonto(-x,0,-z));
    addPonto(figura,newPonto(0,height,z));

    //Base
    addPonto(figura,newPonto(-x,0,z));
    addPonto(figura,newPonto(x,0,-z));
    addPonto(figura,newPonto(x,0,z));
    
    addPonto(figura,newPonto(-x,0,-z));
    addPonto(figura,newPonto(x,0,-z));
    addPonto(figura,newPonto(-x,0,z));
    
    

}

//trocar para gerar figura
Figura generateRoof(int length, int width, int height) {
	Figura roof = Figura();
    generateXYZ(length, width,height,roof);
	return roof;
}