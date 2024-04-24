#include <stdlib.h>
#include <iostream>
#include <cstring>
#include "pugixml.hpp"
#include <stdio.h>
#include <list>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include "..\utils\matriz.hpp"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>

#define SPHERICAL true
#define FIRSTPERSON false

#define tesselation 100.0

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

//Curvas de CatmullRomPoint
float prev_y[3] = { 0,1,0 };

bool cameraMode;

// VBOs
int const numFigurasMax = 100;
GLuint buffers[numFigurasMax];
int numFiguras = 0;
int vertices;

//GroupsParser -> passei para ja  para matriz.hpp!!
//struct Point {
//    float x, y, z;
//};
enum Type{
    TRANSLATE,
    ROTATE,
    SCALE
};
struct Transformation { //nem todas as transformações usam todos os campos
    Type type;
    float x, y, z, angle = 0, time;
    bool align;
    std::list<Point> points;
};
struct Group {
    std::list<std::string> files;
    std::list<Transformation> transformations;
    std::list<Group> children;
};
Group mainGroup;


Group processGroup_XML(pugi::xml_node groupNode){
    Group group;
    for (pugi::xml_node transformNode = groupNode.child("transform"); transformNode; transformNode = transformNode.next_sibling("transform")) {
        Transformation transformation;
        for (pugi::xml_node childNode = transformNode.first_child(); childNode; childNode = childNode.next_sibling()) {
            if (std::strcmp(childNode.name(),"translate") == 0) {
                transformation.type = TRANSLATE;
                transformation.x = childNode.attribute("x").as_float();
                transformation.y = childNode.attribute("y").as_float();
                transformation.z = childNode.attribute("z").as_float();
                transformation.time = childNode.attribute("time").as_float();
                transformation.align = childNode.attribute("align").as_bool();

                Point point;
                for (pugi::xml_node pointNode = childNode.first_child(); pointNode; pointNode = pointNode.next_sibling()) {
                    if (std::strcmp(pointNode.name(),"point") == 0) {
                        point.x = pointNode.attribute("x").as_float();
                        point.y = pointNode.attribute("y").as_float();
                        point.z = pointNode.attribute("z").as_float();
                        transformation.points.push_back(point);
                    }
                }
                group.transformations.push_back(transformation);    
            }
            else if (std::strcmp(childNode.name(),"rotate") == 0){
                transformation.type = ROTATE;
                transformation.angle = childNode.attribute("angle").as_float();
                transformation.x = childNode.attribute("x").as_float();
                transformation.y = childNode.attribute("y").as_float();
                transformation.z = childNode.attribute("z").as_float();
                transformation.time = childNode.attribute("time").as_float();
                group.transformations.push_back(transformation);    
            }
            else if(std::strcmp(childNode.name(),"scale") == 0){
                transformation.type = SCALE;
                transformation.x = childNode.attribute("x").as_float();
                transformation.y = childNode.attribute("y").as_float();
                transformation.z = childNode.attribute("z").as_float();
                group.transformations.push_back(transformation);
            }
        }
    }

    pugi::xml_node modelsNode = groupNode.child("models");
    for (pugi::xml_node modelNode = modelsNode.child("model"); modelNode; modelNode = modelNode.next_sibling("model")) {
        group.files.push_back(modelNode.attribute("file").as_string());
    }

    pugi::xml_node groupsNode = groupNode.child("group");
    for (pugi::xml_node childGroupNode = groupsNode; childGroupNode; childGroupNode = childGroupNode.next_sibling("group")) {
        Group childGroup = processGroup_XML(childGroupNode); 
        group.children.push_back(childGroup);
    }

    return group;
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
        
        // Processar Groups
        pugi::xml_node groupNode = rootNode.child("group");
        mainGroup = processGroup_XML(groupNode);
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

    if (vertices < std::stoi(linha)) vertices = std::stoi(linha);

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

void renderCatmullRomCurve(std::list<Point> points) {
    float pos[3];
    float derivada[3];
    glBegin(GL_LINE_LOOP);
    float gt;
    //vai fazer [0,1[ de 0.01 por 0.01 - obtem uma curva com todos os segmentos
    for (gt = 0; gt < 1; gt += 1.0 / tesselation) {
        getGlobalCatmullRomPoint(gt, points, pos, derivada);
        glVertex3f(pos[0], pos[1], pos[2]);
    }
    glEnd();
}

void processTransformations(Group group, int& index){
    for (Transformation transformation : group.transformations){
        if (transformation.type == TRANSLATE){
            if (transformation.time==0){
                glTranslatef(transformation.x,transformation.y,transformation.z);
            }else{
                
                //alterar e por a fazer uma translacao que demore time segundos a realizar uma volta completa na curva.
                float pos[3], deriv[3];
                float gt = ( glutGet(GLUT_ELAPSED_TIME) / 1000.0) / transformation.time;
        
                getGlobalCatmullRomPoint(gt,transformation.points,pos,deriv);
                renderCatmullRomCurve(transformation.points);

                glTranslatef(pos[0], pos[1], pos[2]);
                normalize(deriv);

                float z[3];
                cross(deriv, prev_y, z);
                normalize(z);

                float y[3];
                cross(z, deriv, y);
                normalize(y);

                prev_y[0] = y[0];
                prev_y[1] = y[1];
                prev_y[2] = y[2];

                float m[16]; //matriz 4*4
                buildRotMatrix(deriv, y, z, m);

                glMultMatrixf(m);

            }
        }
        else if (transformation.type == ROTATE){
            if (transformation.time==0){
                glRotatef(transformation.angle,transformation.x,transformation.y,transformation.z);
            }else{
                //por a fazer uma rotacao de 360º sobre um dos eixos que demore time segundos a ser realizada
                double angle = 360.0 * (glutGet(GLUT_ELAPSED_TIME) / 1000.0) / transformation.time;
                //para que nunca ultrapasse os 360º
                while (angle > 360) angle -= 360;
                glRotatef(angle, transformation.x, transformation.y, transformation.z);
            }
        }
        else if (transformation.type == SCALE){
            glScalef(transformation.x,transformation.y,transformation.z);
        }
    }

    for (std::string file : group.files){
        glBindBuffer(GL_ARRAY_BUFFER, buffers[index++]);
        glVertexPointer(3, GL_FLOAT, 0, 0);
        glDrawArrays(GL_TRIANGLES, 0, vertices);
    }

    for (Group child : group.children){
        glPushMatrix();
        processTransformations(child,index);
        glPopMatrix();
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

    //Transformations
    int index = 0;
    processTransformations(mainGroup, index);

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

void processVBOs(Group group){
    for (const auto& file : group.files) {
        drawFigure(file);
    }

    for (Group child : group.children){
        processVBOs(child);
    }
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
    glutIdleFunc(renderScene);
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
    processVBOs(mainGroup);

    // Enter GLUT's main cycle
    glutMainLoop();
    return 1;
}