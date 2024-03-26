#include <stdlib.h>
#include <iostream>
#include "pugixml.hpp"
#include <stdio.h>
#include <list>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;

int width;
int height;

float camPosX;
float camPosY;
float camPosZ;
float camLookAtX;
float camLookAtY;
float camLookAtZ;
float camUpX;
float camUpY;
float camUpZ;
float camProjectionFOV;
float camProjectionNear;
float camProjectionFar;

float alfa = M_PI / 4;
float beta2 = M_PI / 4; //beta is anbiguos in std beta
float raio = 5.0f;
GLenum mode = GL_LINE;

std::list<std::string>files;

// VBOs
int const numFigurasMax = 100;
GLuint buffers[numFigurasMax];
int numFiguras = 0;
int vertices;

struct Transform {
    float translateX, translateY, translateZ;
    float rotateAngle, rotateX, rotateY, rotateZ;
    float scaleX, scaleY, scaleZ; 
};

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

        camLookAtX = cameraNode.child("lookAt").attribute("x").as_float();
        camLookAtY = cameraNode.child("lookAt").attribute("y").as_float();
        camLookAtZ = cameraNode.child("lookAt").attribute("z").as_float();

        camUpX = cameraNode.child("up").attribute("x").as_float();
        camUpY = cameraNode.child("up").attribute("y").as_float();
        camUpZ = cameraNode.child("up").attribute("z").as_float();
        
        camProjectionFOV = cameraNode.child("projection").attribute("fov").as_float();
        camProjectionNear = cameraNode.child("projection").attribute("near").as_float();
        camProjectionFar = cameraNode.child("projection").attribute("far").as_float();
        
        // Processar modelos
        pugi::xml_node groupNode = rootNode.child("group");

        for (pugi::xml_node transformNode = groupNode.child("transform"); transformNode; transformNode = transformNode.next_sibling("transform")) {
            Transform transform;

            pugi::xml_node translateNode = transformNode.child("translate");
            if (translateNode) {
                transform.translateX = translateNode.attribute("x").as_float();
                transform.translateY = translateNode.attribute("y").as_float();
                transform.translateZ = translateNode.attribute("z").as_float();
            }

            pugi::xml_node rotateNode = transformNode.child("rotate");
            if (rotateNode) {
                transform.rotateAngle = rotateNode.attribute("angle").as_float();
                transform.rotateX = rotateNode.attribute("x").as_float();
                transform.rotateY = rotateNode.attribute("y").as_float();
                transform.rotateZ = rotateNode.attribute("z").as_float();
            }

            pugi::xml_node scaleNode = transformNode.child("scale");
            if (scaleNode) {
                transform.scaleX = scaleNode.attribute("x").as_float();
                transform.scaleY = scaleNode.attribute("y").as_float();
                transform.scaleZ = scaleNode.attribute("z").as_float();
            }

            pugi::xml_node modelsNode = groupNode.child("models");
            for (pugi::xml_node modelNode = modelsNode.child("model"); modelNode; modelNode = modelNode.next_sibling("model")) {
                std::string filename = modelNode.attribute("file").as_string();
                files.push_back(filename);
            }
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
    gluPerspective(camProjectionFOV, ratio, camProjectionNear, camProjectionFar);

    // Return to the model view matrix mode
    glMatrixMode(GL_MODELVIEW);
}

void drawAxis(){
    glBegin(GL_LINES);
		// X axis in red
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(-100.0f, 0.0f, 0.0f);
		glVertex3f(100.0f, 0.0f, 0.0f);
		// Y Axis in Green
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0.0f, -100.0f, 0.0f);
		glVertex3f(0.0f, 100.0f, 0.0f);
		// Z Axis in Blue
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(0.0f, 0.0f, -100.0f);
		glVertex3f(0.0f, 0.0f, 100.0f);

        //return to white
        glColor3f(1.0f, 1.0f, 1.0f);
    glEnd();
}

void drawFigure(std::string figureFile){
    // Abra o arquivo
    std::ifstream file(figureFile); // Assuming the file name is figureFile.txt
   
    //Guarda o numero de vertices e cria o vetor
    std::string linha;
    std::getline(file, linha);

    vertices = std::stoi(linha);
    //std::cout << vertices << std::endl;

    std::vector<float> vertexB;

    // Leia o file linha por linha
    while (std::getline(file, linha)) {
        std::istringstream iss(linha);
        std::string token;
        while (std::getline(iss, token, ';')) {
            float value = std::stof(token);
            vertexB.push_back(value);
        }
    }

    // Feche o file
    file.close();

    glBindBuffer(GL_ARRAY_BUFFER, buffers[numFiguras++]); 
    glBufferData(GL_ARRAY_BUFFER, vertexB.size() * sizeof(float), vertexB.data(), GL_STATIC_DRAW);
}

void renderScene(void) {
    // Clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Set the camera
    glLoadIdentity();
    gluLookAt(raio * cos(beta2) * sin(alfa), raio * sin(beta2), raio * cos(beta2) * cos(alfa),
        camLookAtX, camLookAtY, camLookAtZ,
        camUpX, camUpY, camUpZ);

    drawAxis();

    glPolygonMode(GL_FRONT_AND_BACK, mode);

    // Enable vertex array
    glEnableClientState(GL_VERTEX_ARRAY);

    // VBOs
    for (int i=0;i<numFiguras;i++){
        glBindBuffer(GL_ARRAY_BUFFER, buffers[i]);
        glVertexPointer(3, GL_FLOAT, 0, 0);
        glDrawArrays(GL_TRIANGLES, 0, vertices);
    }

    // Disable vertex array
    glDisableClientState(GL_VERTEX_ARRAY);

    // End of frame
    glutSwapBuffers();
}


void processSpecialKeys(int key, int xx, int yy) {
    switch (key) {
        case GLUT_KEY_RIGHT:
            alfa += 0.1f;
            break;
        case GLUT_KEY_LEFT:
            alfa -= 0.1f;
            break;
        case GLUT_KEY_UP:
            beta2 += 0.1f;
            break;
        case GLUT_KEY_DOWN:
            beta2 -= 0.1f;
            break;
        case GLUT_KEY_F1: 
            raio -= 0.5f;
            break;
        case GLUT_KEY_F2:
            raio += 0.5f;
            break;
    }
    
    glutPostRedisplay();
}

void processKeys(unsigned char key, int xx, int yy) {
    // put code to process regular keys in here
    switch (key) {
        case 'f':
            mode = GL_FILL;
            break;

        case 'l':
            mode = GL_LINE;
            break;

        case 'p':
            mode = GL_POINT;
            break;
    }
    
    glutPostRedisplay();
}

int main(int argc, char *argv[]) {
    printf("Engine started\n");

    read_XML(argv[1]);

    alfa = acos(camPosZ / sqrt(camPosX * camPosX + camPosZ * camPosZ));
    raio = sqrt((camPosX * camPosX) + (camPosY * camPosY) + (camPosZ * camPosZ));
    beta2 = asin(camPosY / raio);
    
    // Init GLUT and the window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(width, height);
    glutCreateWindow("CG@DI-UM");

    // Required callback registry
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);

    glutKeyboardFunc(processKeys);
    glutSpecialFunc(processSpecialKeys);

    // Init GLEW
    #ifndef __APPLE__
    glewInit();
    #endif
    
    // OpenGL settings
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    // Enable smooth shading
    glShadeModel(GL_SMOOTH);

    // Initialize VBOs
    glGenBuffers(numFigurasMax, buffers);

    for (const auto& file : files) {
        drawFigure(file);
    }
    
    // Enter GLUT's main cycle
    glutMainLoop();
    return 1;
}