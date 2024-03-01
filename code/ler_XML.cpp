#include <iostream>
#include "pugixml.hpp"
#include <stdio.h>
#include <list>
#include <string>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>

int width;
int height;
float camPosX;
float camPosY;
float camPosZ;
std::list<std::string>files;


void read_XML(char* file_path){
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(file_path);

    if (result) {
        // Processar o XML
        pugi::xml_node rootNode = doc.child("world");

        // Processar atributos do elemento window
        pugi::xml_node windowNode = rootNode.child("window");
        width = windowNode.attribute("width").as_int();
        height = windowNode.attribute("height").as_int();

        // Processar atributos do elemento camera
        pugi::xml_node cameraNode = rootNode.child("camera");
        camPosX = cameraNode.child("position").attribute("x").as_float();
        camPosY = cameraNode.child("position").attribute("y").as_float();
        camPosZ = cameraNode.child("position").attribute("z").as_float();

        // Processar modelos
        pugi::xml_node modelsNode = rootNode.child("group").child("models");
        for (pugi::xml_node modelNode = modelsNode.child("model"); modelNode; modelNode = modelNode.next_sibling("model")) {
            std::string filename = modelNode.attribute("file").as_string();
            files.push_back(filename);
        }
    }
}

void changeSize(int w, int h) {
    // Prevent a divide by zero, when window is too short
    // (you cant make a window with zero width).
    if (h == 0)
        h = 1;

    // Compute window's aspect ratio
    float ratio = w * 1.0 / h;

    // Set the projection matrix as current
    glMatrixMode(GL_PROJECTION);
    // Load Identity Matrix
    glLoadIdentity();

    // Set the viewport to be the entire window
    glViewport(0, 0, w, h);

    // Set perspective
    gluPerspective(45.0f, ratio, 1.0f, 1000.0f);

    // Return to the model view matrix mode
    glMatrixMode(GL_MODELVIEW);
}

void renderScene(void) {
    // Clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Set the camera
    glLoadIdentity();
    gluLookAt(camPosX, camPosY, camPosZ,
        0.0, 0.0, 0.0,
        0.0f, 1.0f, 0.0f);

    // End of frame
    glutSwapBuffers();
}


int main(int argc, char* argv[]) {
    // Init GLUT and the window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(width, height);
    glutCreateWindow("CG@DI-UM");

    // Required callback registry
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);


    // Init GLEW
#ifndef __APPLE__
    glewInit();
#endif

    // OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glPolygonMode(GL_FRONT, GL_LINE);

    // Enable smooth shading
    glShadeModel(GL_SMOOTH);

    read_XML(argv[1]);

    // Enter GLUT's main cycle
    glutMainLoop();


    
    return 1;
}
