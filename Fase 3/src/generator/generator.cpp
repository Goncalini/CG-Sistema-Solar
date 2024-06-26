#include <stdio.h>
#include "plane.cpp"
#include "box.cpp"
#include "sphere.cpp"
#include "cone.cpp"
#include "torus.cpp"
#include "roof.cpp"
#include "piramid.cpp"
#include "parallelepiped.cpp"
#include "bezier.cpp"
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
		//generator torus 2 3 10 10 torus.3d 
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
		//generator roof 2 2 2 roof.3d 
		else if (strcmp(argv[1], "roof") == 0) {
			int length = atoi(argv[2]);
			int height = atoi(argv[3]);
			int width = atoi(argv[4]);

			file_path = argv[5];

			figura = generateRoof(length,width,height);
		}
		//generator piramid 2 2 2 piramid.3d 
		else if (strcmp(argv[1], "piramid") == 0) {
			int length = atoi(argv[2]);
			int height = atoi(argv[3]);
			int width = atoi(argv[4]);

			file_path = argv[5];

			figura = generatePiramid(length,width,height);
		}

		//generator parallelepiped 2 2 2 piramid.3d 
		else if (strcmp(argv[1], "parallelepiped") == 0) {
			int length = atoi(argv[2]);
			int height = atoi(argv[3]);
			int width = atoi(argv[4]);

			file_path = argv[5];

			figura = generateParallelepiped(length,width,height);
		}
		//generator patch teapot.patch 10 bezier_10.3d 
		else if (strcmp(argv[1], "patch") == 0) {
			const char* patch_file = argv[2];
			int tesselation = atoi(argv[3]);

			file_path = argv[4];

			figura = generateSurface(patch_file, tesselation);

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