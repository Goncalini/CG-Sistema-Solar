#include <stdio.h>
#include "../utils/figura.hpp"

void generateP(int length, int width, float height, Figura& figura) {
	float x = (float)length / 2;
	float z = (float)width / 2;

    //Triangulo frente
    addPonto(figura,newPonto(0,height,0));
    addPonto(figura,newPonto(-x,0,z));
    addPonto(figura,newPonto(x,0,z));

    //Triangulo tras
    addPonto(figura,newPonto(x,0,-z));
    addPonto(figura,newPonto(-x,0,-z));
    addPonto(figura,newPonto(0,height,0));

    //Triangulo lateral1
    addPonto(figura,newPonto(0,height,0));
    addPonto(figura,newPonto(x,0,z));
    addPonto(figura,newPonto(x,0,-z));

    //Triangulo lateral2
    addPonto(figura,newPonto(-x,0,-z));
    addPonto(figura,newPonto(-x,0,z));
    addPonto(figura,newPonto(0,height,0));
    

    //Base
    addPonto(figura,newPonto(-x,0,z));
    addPonto(figura,newPonto(x,0,-z));
    addPonto(figura,newPonto(x,0,z));
    
    addPonto(figura,newPonto(-x,0,-z));
    addPonto(figura,newPonto(x,0,-z));
    addPonto(figura,newPonto(-x,0,z));
    
    

}

//trocar para gerar figura
Figura generatePiramid(int length, int width, int height) {
	Figura piramid = Figura();
    generateP(length, width,height,piramid);
	return piramid;
}