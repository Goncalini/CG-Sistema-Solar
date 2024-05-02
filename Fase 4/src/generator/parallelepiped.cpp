#include <stdio.h>
#include "../utils/figura.hpp"

void generateParalel(int length, int width, float height, Figura& figura) {
	float x = (float)length / 2;
	float z = (float)width / 2;

    //Base
    addPonto(figura,newPonto(-x,0,z));
    addPonto(figura,newPonto(x,0,-z));
    addPonto(figura,newPonto(x,0,z));
    
    addPonto(figura,newPonto(-x,0,-z));
    addPonto(figura,newPonto(x,0,-z));
    addPonto(figura,newPonto(-x,0,z));

    //Cima
    addPonto(figura,newPonto(x,height,z));
    addPonto(figura,newPonto(x,height,-z));
    addPonto(figura,newPonto(-x,height,z));
    
    addPonto(figura,newPonto(-x,height,z));
    addPonto(figura,newPonto(x,height,-z));
    addPonto(figura,newPonto(-x,height,-z));

    //Frente
    addPonto(figura,newPonto(-x,0,z));
    addPonto(figura,newPonto(x,0,z));
    addPonto(figura,newPonto(x,height,z));

    addPonto(figura,newPonto(-x,0,z));
    addPonto(figura,newPonto(x,height,z));
    addPonto(figura,newPonto(-x,height,z));

    //Tras
    addPonto(figura,newPonto(x,height,-z));
    addPonto(figura,newPonto(x,0,-z));
    addPonto(figura,newPonto(-x,0,-z));

    addPonto(figura,newPonto(-x,height,-z));
    addPonto(figura,newPonto(x,height,-z));
    addPonto(figura,newPonto(-x,0,-z));

    //Lateral1
    addPonto(figura,newPonto(x,height,z));
    addPonto(figura,newPonto(x,0,z));
    addPonto(figura,newPonto(x,0,-z));

    addPonto(figura,newPonto(x,height,z));
    addPonto(figura,newPonto(x,0,-z));
    addPonto(figura,newPonto(x,height,-z));

    //Lateral2
    addPonto(figura,newPonto(-x,0,-z));
    addPonto(figura,newPonto(-x,0,z));
    addPonto(figura,newPonto(-x,height,z));

    addPonto(figura,newPonto(-x,height,-z));
    addPonto(figura,newPonto(-x,0,-z));
    addPonto(figura,newPonto(-x,height,z));
   

    

}

Figura generateParallelepiped(int length, int width, int height){
	Figura parallelepiped = Figura();
    generateParalel(length, width,height,parallelepiped);
	return parallelepiped;
}