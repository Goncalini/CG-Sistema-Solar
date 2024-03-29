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

// VBOs
int const numFigurasMax = 100;
GLuint buffers[numFigurasMax];
int numFiguras = 0;
int vertices;

//Transformações
std::list<std::string> transformations;

void processGroup_XML(pugi::xml_node groupNode){
    transformations.push_back("push");

    for (pugi::xml_node transformNode = groupNode.child("transform"); transformNode; transformNode = transformNode.next_sibling("transform")) {
        for (pugi::xml_node childNode = transformNode.first_child(); childNode; childNode = childNode.next_sibling()) {
            if (std::string(childNode.name()) == "translate") {
                transformations.push_back("translate");
                transformations.push_back(childNode.attribute("x").as_string());
                transformations.push_back(childNode.attribute("y").as_string());
                transformations.push_back(childNode.attribute("z").as_string());
            }else if (std::string(childNode.name()) == "rotate"){
                transformations.push_back("rotate");
                transformations.push_back(childNode.attribute("angle").as_string());
                transformations.push_back(childNode.attribute("x").as_string());
                transformations.push_back(childNode.attribute("y").as_string());
                transformations.push_back(childNode.attribute("z").as_string());
            }else if(std::string(childNode.name()) == "scale"){
                transformations.push_back("scale");
                transformations.push_back(childNode.attribute("x").as_string());
                transformations.push_back(childNode.attribute("y").as_string());
                transformations.push_back(childNode.attribute("z").as_string());
            }
        }
    }

    pugi::xml_node modelsNode = groupNode.child("models");
    for (pugi::xml_node modelNode = modelsNode.child("model"); modelNode; modelNode = modelNode.next_sibling("model")) {
        transformations.push_back("figure");
        transformations.push_back(modelNode.attribute("file").as_string());
    }

    pugi::xml_node groupsNode = groupNode.child("group");
    for (pugi::xml_node groupNode = groupsNode; groupNode; groupNode = groupNode.next_sibling("group")) {
        processGroup_XML(groupNode); 
    }

    transformations.push_back("pop");
}

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
        processGroup_XML(groupNode);
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

    glBindBuffer(GL_ARRAY_BUFFER, buffers[numFiguras-1]);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    glDrawArrays(GL_TRIANGLES, 0, vertices);
}

void create_objects(void){
    /* while(!transformations.empty()){
        string next_operation = transformations.front();
        transformations.pop_front();
        cout << next_operation << endl;
    } */

    while(!transformations.empty()){
        string next_operation = transformations.front();
        transformations.pop_front();

        if (next_operation=="push"){
            glPushMatrix();
        }else if (next_operation=="pop"){
            glPopMatrix();
        }else if (next_operation=="rotate"){
            float angle = std::stof(transformations.front());
            transformations.pop_front();
            float x = std::stof(transformations.front());
            transformations.pop_front();
            float y = std::stof(transformations.front());
            transformations.pop_front();
            float z = std::stof(transformations.front());
            transformations.pop_front();
            glRotatef(angle,x,y,z);
           
        }else if (next_operation=="translate"){
            float x = std::stof(transformations.front());
            transformations.pop_front();
            float y = std::stof(transformations.front());
            transformations.pop_front();
            float z = std::stof(transformations.front());
            transformations.pop_front();
            glTranslatef(x,y,z);
           
        }else if (next_operation=="scale"){
            float x = std::stof(transformations.front());
            transformations.pop_front();
            float y = std::stof(transformations.front());
            transformations.pop_front();
            float z = std::stof(transformations.front());
            transformations.pop_front();
            glScalef(x,y,z);
        }else if (next_operation=="figure"){
            string fig = transformations.front();
            transformations.pop_front();
            drawFigure(fig);
        }  

    }
    
    
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

    create_objects();
    
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

    // Enter GLUT's main cycle
    glutMainLoop();
    return 1;
}