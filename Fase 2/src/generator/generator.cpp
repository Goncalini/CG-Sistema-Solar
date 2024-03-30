#include <stdio.h>
#include "plane.cpp"
#include "box.cpp"
#include "sphere.cpp"
#include "cone.cpp"
#include "ring.cpp"
#include "torus.cpp"
#include "../utils/figura.hpp"
#include "../utils/ponto.hpp"
#include <string>




int main(int argc,char *argv[]) {
	if (argc >= 5) {
		Figura figura;
		const char *file_path;
		
		//generator plane 1 3 plane.3d 
		if (strcmp(argv[1], "plane") == 0) {
			int length = atoi(argv[2]);
			int divisions = atoi(argv[3]);

			file_path = argv[4];

			figura = generatePlane(length, divisions);

		}
		//generator box 2 3 box.3d 
		else if (strcmp(argv[1], "box") == 0) {
			int length = atoi(argv[2]);
			int divisions = atoi(argv[3]);

			file_path = argv[4];

			figura = generateBox(length, divisions);
		}
		//generator sphere 1 10 10 sphere.3d
		else if (strcmp(argv[1], "sphere") == 0) {
			float radius = std::stof(argv[2]);
			int slices = atoi(argv[3]);
			int stacks = atoi(argv[4]);

			file_path = argv[5];

			figura = generateSphere(radius, slices, stacks);
		}
		//generator cone 1 2 4 3 cone.3d 
		else if (strcmp(argv[1], "cone") == 0) {
			float radius = std::stof(argv[2]);
			float height = std::stof(argv[3]);
			int slices = atoi(argv[4]);
			int stacks = atoi(argv[5]);

			file_path = argv[6];

			figura = generateCone(radius, height, slices, stacks);
		}
		//generator ring 2 3 4 ring.3d 
		else if (strcmp(argv[1], "ring") == 0) {
			float ri = std::stof(argv[2]);
			float re = std::stof(argv[3]);
			int slices = atoi(argv[4]);

			file_path = argv[5];

			figura = generateRing(ri, re, slices);
		}
		//generator torus 2 3 10 10 ring.3d 
		else if (strcmp(argv[1], "torus") == 0) {
			float ri = std::stof(argv[2]);
			float re = std::stof(argv[3]);
			int slices = atoi(argv[4]);
			int stacks = atoi(argv[5]);
			if (stacks < 2) {
				std::cout << "Number of stacks invalid!\n";
				return 1;
			}
			else {
				file_path = argv[6];

				figura = generateTorus(ri, re, slices, stacks);
			}
			
		}
		else {
			std::cout << "Invalid graphic primitive\n";
			return 1;
		}
		writeToFile(figura, file_path);
	}
	else {
		std::cout << "Number of arguments invalid!\n";
		return 1;
	}
	return 0;
}