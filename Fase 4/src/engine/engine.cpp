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
#include "../utils/matriz.hpp"
#include <regex>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>

#include <IL/il.h>

#define tesselation 100.0

// Modos da câmera
#define SPHERICAL true
#define FIRSTPERSON false

using namespace std;

GLuint loadTextureVariable;

int width;
int height;

// Variáveis para câmera
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
bool cameraMode;

float alfa = M_PI / 4;
float beta2 = M_PI / 4; //beta is anbiguos in std beta
float raio = 5.0f;
GLenum mode = GL_LINE;

//Iluminação
enum LightType{
    POINT,
    DIRECTIONAL,
    SPOTLIGHT
};
struct Light { 
    LightType type;
    float posX, posY, posZ; //usando em luzes point e spotlight
    float dirX, dirY, dirZ; //usando em luzes directional e spotlight
    float cutoff; //usando em luzes spotlight
};
std::list<Light> lights; //lista com as luzes presentes no cenário

//Curvas de CatmullRomPoint
float prev_y[3] = { 0,1,0 };

//tempo
int timebase;
double frames;


// VBOs
int const numFigurasMax = 100;
GLuint buffers[numFigurasMax];
GLuint buffersN[numFigurasMax];
GLuint buffersT[numFigurasMax];
int numFiguras = 0;
int vertices;

enum TransformationType{
    TRANSLATE,
    ROTATE,
    SCALE
};
struct Transformation { //nem todas as transformações usam todos os campos
    TransformationType type;
    float x, y, z, angle = 0, time;
    bool align;
    std::list<Point> points;
};
struct Color { //cada campo tem um valor default caso o modelo não tenha cor no xml
    float diffuseR = 200, diffuseG = 200, diffuseB = 200;
    float ambientR = 50, ambientG = 50, ambientB = 50;
    float specularR = 0, specularG = 0, specularB = 0;
    float emissiveR = 0, emissiveG = 0, emissiveB = 0;
    float shininessValue = 0;
};
struct Model { 
    std::string modelFile, textureFile;
    Color color;
};
struct Group {
    std::list<Transformation> transformations;
    std::list<Model> models;
    std::list<Group> children;
};
Group mainGroup;


int loadTexture(std::string s) {

	unsigned int t,tw,th;
	unsigned char *texData;
	unsigned int texID;

	ilInit();
	ilEnable(IL_ORIGIN_SET);
	ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
	ilGenImages(1,&t);
	ilBindImage(t);
	ilLoadImage((ILstring)s.c_str());
	tw = ilGetInteger(IL_IMAGE_WIDTH);
	th = ilGetInteger(IL_IMAGE_HEIGHT);
	ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
	texData = ilGetData();

	glGenTextures(1,&texID);
	
	glBindTexture(GL_TEXTURE_2D,texID);
	glTexParameteri(GL_TEXTURE_2D,	GL_TEXTURE_WRAP_S,		GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,	GL_TEXTURE_WRAP_T,		GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D,	GL_TEXTURE_MAG_FILTER,   	GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,	GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tw, th, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);

	return texID;

}

void setupColors(const Color& color) {
    // Convert 0-255 values to 0-1
    float diffuse[4] = { color.diffuseR / 255.0f, color.diffuseG / 255.0f, color.diffuseB / 255.0f, 1.0f };
    float ambient[4] = { color.ambientR / 255.0f, color.ambientG / 255.0f, color.ambientB / 255.0f, 1.0f };
    float specular[4] = { color.specularR / 255.0f, color.specularG / 255.0f, color.specularB / 255.0f, 1.0f };
    float emissive[4] = { color.emissiveR / 255.0f, color.emissiveG / 255.0f, color.emissiveB / 255.0f, 1.0f }; 

    // Define light colors
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT, GL_EMISSION, emissive);
    glMaterialf(GL_FRONT, GL_SHININESS, color.shininessValue);
}


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
        Model model;
        model.modelFile = modelNode.attribute("file").as_string();
        model.textureFile = modelNode.child("texture").attribute("file").as_string();

        model.color.diffuseR = modelNode.child("color").child("diffuse").attribute("R").as_float();
        model.color.diffuseG = modelNode.child("color").child("diffuse").attribute("G").as_float();
        model.color.diffuseB = modelNode.child("color").child("diffuse").attribute("B").as_float();

        model.color.ambientR = modelNode.child("color").child("ambient").attribute("R").as_float();
        model.color.ambientG = modelNode.child("color").child("ambient").attribute("G").as_float();
        model.color.ambientB = modelNode.child("color").child("ambient").attribute("B").as_float();

        model.color.specularR = modelNode.child("color").child("specular").attribute("R").as_float();
        model.color.specularG = modelNode.child("color").child("specular").attribute("G").as_float();
        model.color.specularB = modelNode.child("color").child("specular").attribute("B").as_float();

        model.color.emissiveR = modelNode.child("color").child("emissive").attribute("R").as_float();
        model.color.emissiveG = modelNode.child("color").child("emissive").attribute("G").as_float();
        model.color.emissiveB = modelNode.child("color").child("emissive").attribute("B").as_float();

        model.color.shininessValue = modelNode.child("color").child("shininess").attribute("value").as_float();

        group.models.push_back(model);
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
        pugi::xml_node worldNode = doc.child("world");

        // Processar atributos do elemento window
        pugi::xml_node windowNode = worldNode.child("window");
        width = windowNode.attribute("width").as_int();
        height = windowNode.attribute("height").as_int();

        // Processar atributos do elemento camera
        pugi::xml_node cameraNode = worldNode.child("camera");
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

        // Processar Iluminação
        pugi::xml_node lightsNode = worldNode.child("lights");
        for (pugi::xml_node lightNode = lightsNode.child("light"); lightNode; lightNode = lightNode.next_sibling("light")) {
            Light light;
            if (std::strcmp(lightNode.attribute("type").as_string(),"point") == 0) {
                light.type=POINT;
                light.posX=lightNode.attribute("posx").as_float();
                light.posY=lightNode.attribute("posy").as_float();
                light.posZ=lightNode.attribute("posz").as_float();
            }
            else if (std::strcmp(lightNode.attribute("type").as_string(),"directional") == 0) {
                light.type=DIRECTIONAL;
                light.dirX=lightNode.attribute("dirx").as_float();
                light.dirY=lightNode.attribute("diry").as_float();
                light.dirZ=lightNode.attribute("dirz").as_float();
            }
            else if (std::strcmp(lightNode.attribute("type").as_string(),"spotlight") == 0) {
                light.type=SPOTLIGHT;
                light.posX=lightNode.attribute("posx").as_float();
                light.posY=lightNode.attribute("posy").as_float();
                light.posZ=lightNode.attribute("posz").as_float();
                light.dirX=lightNode.attribute("dirx").as_float();
                light.dirY=lightNode.attribute("diry").as_float();
                light.dirZ=lightNode.attribute("dirz").as_float();
                light.cutoff=lightNode.attribute("cutoff").as_float();
            }
            lights.push_back(light);
        }
        

        // Processar Groups
        pugi::xml_node groupNode = worldNode.child("group");
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

void drawFigure(std::string figureFile, std::string textureFile){
    // Abra o arquivo
    std::ifstream file(figureFile); // Assuming the file name is figureFile.txt
   
    //Guarda o numero de vertices e cria o vetor
    std::string linha;
    std::getline(file, linha);

    if (vertices < std::stoi(linha)) vertices = std::stoi(linha);

    std::vector<float> vertexB;
    std::vector<float> vertexN;
    std::vector<float> vertexT;

    // Leia o arquivo linha por linha
    while (std::getline(file, linha)) {
        std::istringstream iss(linha);
        std::string tokenSemiColon;

        /* As linhas são do estilo: coordenadas;normais;texturas
        Cada um dos componentes tem 3 ou 2 valores, separados por vírgulas */ 
        int tokenCount = 0;
        while (std::getline(iss, tokenSemiColon, ';')) {
            std::istringstream issSemiColon(tokenSemiColon);
            std::string tokenComa;

            // Divide tokenSemiColon por vírgula
            while (std::getline(issSemiColon, tokenComa, ',')) {
                float value = std::stof(tokenComa);

                if (tokenCount % 3 == 0){
                    vertexB.push_back(value);
                }
                else if (tokenCount % 3 == 1){
                    vertexN.push_back(value);
                }
                else if (tokenCount % 3 == 2){
                    vertexT.push_back(value);
                }
            }
            tokenCount++;
        }
    }

    // Feche o file
    file.close();

    loadTextureVariable = loadTexture("../../textures/"+textureFile);

    glBindTexture(GL_TEXTURE_2D,loadTextureVariable);

    glBindBuffer(GL_ARRAY_BUFFER, buffers[numFiguras]); 
    glBufferData(GL_ARRAY_BUFFER, vertexB.size() * sizeof(float), vertexB.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, buffersN[numFiguras]); 
    glBufferData(GL_ARRAY_BUFFER, vertexN.size() * sizeof(float), vertexN.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, buffersT[numFiguras]); 
    glBufferData(GL_ARRAY_BUFFER, vertexT.size() * sizeof(float), vertexT.data(), GL_STATIC_DRAW);
    numFiguras++;
}

void renderCatmullRomCurve(std::list<Point> points) {
    float pos[3];
    float derivada[3];
    glBegin(GL_LINE_LOOP);
    float gt;
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
                float pos[3], deriv[3];
                float gt = ( glutGet(GLUT_ELAPSED_TIME) / 1000.0) / transformation.time;
        
                getGlobalCatmullRomPoint(gt,transformation.points,pos,deriv);
                renderCatmullRomCurve(transformation.points);

                glTranslatef(pos[0], pos[1], pos[2]);
                if (transformation.align) {
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

                    float m[16];
                    buildRotMatrix(deriv, y, z, m);

                    glMultMatrixf(m);
                }

            }
        }
        else if (transformation.type == ROTATE){
            if (transformation.time==0){
                glRotatef(transformation.angle,transformation.x,transformation.y,transformation.z);
            }else{
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

    for (Model model : group.models){
        setupColors(model.color);
        
        glBindBuffer(GL_ARRAY_BUFFER, buffers[index]);
        glVertexPointer(3, GL_FLOAT, 0, 0);

        glBindBuffer(GL_ARRAY_BUFFER,buffersN[index]);
        glNormalPointer(GL_FLOAT,0,0);

        glBindBuffer(GL_ARRAY_BUFFER,buffersT[index]);
        glTexCoordPointer(2,GL_FLOAT,0,0);

        glDrawArrays(GL_TRIANGLES, 0, vertices);
        index++;
    }

    for (Group child : group.children){
        glPushMatrix();
        processTransformations(child,index);
        glPopMatrix();
    }
}



void sphericalCamera() {
    camPosX = raio * cos(beta2) * sin(alfa);
    camPosY = raio * sin(beta2);
    camPosZ = raio * cos(beta2) * cos(alfa);
}


void framerate() {
    char str[100];
    frames++;
    int time = glutGet(GLUT_ELAPSED_TIME);
    if (time - timebase > 1000) {
        float fps = frames * 1000.0 / (time - timebase);
        timebase = time;
        frames = 0;
        sprintf(str, "CG | FPS: %.2f", fps);
        glutSetWindowTitle(str);

    }
}


void renderScene(void) {
    // Clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Set the camera
    glLoadIdentity();
    if (cameraMode == SPHERICAL) {
        sphericalCamera();
    }
    gluLookAt(camPosX, camPosY, camPosZ,
        camLookAtX, camLookAtY, camLookAtZ,
        camUpX, camUpY, camUpZ);

    drawAxis();

    // Light
    glEnable(GL_LIGHTING);
    int lightIndex = 0;
    for (const Light& light : lights) {
        GLenum glLightId = GL_LIGHT0 + lightIndex;
        
        // Definindo a posição ou direção da luz, dependendo do tipo
        if (light.type == LightType::POINT) {
            float pos[4] = {light.posX, light.posY, light.posZ, 1.0f}; // 1.0f para luz pontual
            glLightfv(glLightId, GL_POSITION, pos);
        } else if (light.type == LightType::DIRECTIONAL) {
            float dir[4] = {light.dirX, light.dirY, light.dirZ, 0.0f}; // 0.0f para luz direcional
            glLightfv(glLightId, GL_POSITION, dir);
        } else if (light.type == LightType::SPOTLIGHT) {
            float pos[4] = {light.posX, light.posY, light.posZ, 1.0f}; // 1.0f para luz de spotlight
            glLightfv(glLightId, GL_POSITION, pos);
            float dir[3] = {light.dirX, light.dirY, light.dirZ};
            glLightfv(glLightId, GL_SPOT_DIRECTION, dir); 
            glLightf(glLightId, GL_SPOT_CUTOFF, light.cutoff);
        }

        // Incrementando o índice da luz
        lightIndex++;
    }

    glPolygonMode(GL_FRONT_AND_BACK, mode);

    // Enable vertex array
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    //Transformations
    int index = 0;
    processTransformations(mainGroup, index);

    // Disable vertex array
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);

    framerate();

    // End of frame
    glutSwapBuffers();
}

//------------------ Funções Auxiliares para Camera ------------------

void moveForward() {
    float d[3] = { camLookAtX - camPosX, 0, camLookAtZ - camPosZ };
    normalize(d);
    float k = 0.1f;
    camPosX += k * d[0]; camPosZ += k * d[2];
    camLookAtX += k * d[0]; camLookAtZ += k * d[2];
}


void moveBackward() {
    float d[3] = { camLookAtX - camPosX, 0, camLookAtZ - camPosZ };
    normalize(d);
    float k = -0.1f;
    camPosX += k * d[0]; camPosY += k * d[1]; camPosZ += k * d[2];
    camLookAtX += k * d[0]; camLookAtY += k * d[1];camLookAtZ += k * d[2];
}

void moveRight() {
    float d[3] = { camLookAtX - camPosX, 0, camLookAtZ - camPosZ };
    float up[3] = { camUpX,camUpY,camUpZ };
    float r[3];
    cross(d,up,r);
    normalize(r);
    float k = 0.1f;
    camPosX += k * r[0]; camPosY += k * r[1]; camPosZ += k * r[2];
    camLookAtX += k * r[0]; camLookAtY += k * r[1];camLookAtZ += k * r[2];
}

void moveLeft() {
    float d[3] = { camLookAtX - camPosX, 0, camLookAtZ - camPosZ };
    float up[3] = { camUpX,camUpY,camUpZ };
    float r[3];
    cross(d, up, r);
    normalize(r);
    float k = -0.1f;
    camPosX += k * r[0]; camPosY += k * r[1]; camPosZ += k * r[2];
    camLookAtX += k * r[0]; camLookAtY += k * r[1];camLookAtZ += k * r[2];
}

void rotateHead() {
    camLookAtX = camPosX + raio * cos(beta2) * sin(alfa);
    camLookAtY = camPosY + raio * sin(beta2);
    camLookAtZ = camPosZ + raio * cos(beta2) * cos(alfa);
}


//------------------ Process Keys ------------------

void processSpecialKeys(int key, int xx, int yy) {
    switch (key) {
    case GLUT_KEY_RIGHT: {
        if (cameraMode == SPHERICAL) {
            alfa += 0.1f;
        }
        else {
            //andar para direita
            moveRight();
        }
        break;
    }
    case GLUT_KEY_LEFT: {
        if (cameraMode == SPHERICAL) {
            alfa -= 0.1f;
        }
        else {
            //andar para esquerda
            moveLeft();

        }
        break;
    }
    case GLUT_KEY_UP: {
        if (cameraMode == SPHERICAL) {
            beta2 += 0.1f;
        }
        else {
            //para a frente
            moveForward();
        }
        break;
    }
    case GLUT_KEY_DOWN: {
        if (cameraMode == SPHERICAL) {
            beta2 -= 0.1f;
        }
        else {
            //para tras
            moveBackward();
        }
        break;
    }
    case GLUT_KEY_F1: {
        if (cameraMode == SPHERICAL) {
            raio -= 0.5f;
        }else {
            camPosY += 1.0f;
            camLookAtY += 1.0f;
        }
        break;
    }
    case GLUT_KEY_F2: {
        if (cameraMode == SPHERICAL) {
            raio += 0.5f;
        }
        else {
            camPosY -= 1.0f;
            camLookAtY -= 1.0f;
        }
        break;
    }

    }
    glutPostRedisplay();
}


void processKeys(unsigned char key, int xx, int yy) {
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
               
        //mudar a versao da câmera
        case 'c': {
            if (cameraMode == SPHERICAL) {
                alfa = M_PI + alfa;
                beta2 = -beta2;
                camLookAtX = camPosX + cos(beta2) * sin(alfa);
                camLookAtY = camPosY + sin(beta2); 
                camLookAtZ = camPosZ + cos(beta2) * cos(alfa);
                cameraMode = FIRSTPERSON;
            }
            else {
                raio = sqrt((camPosX * camPosX) + (camPosY * camPosY) + (camPosZ * camPosZ));
                alfa = atan(camPosX / camPosZ);
                beta2 = asin(camPosY / raio);
                camLookAtX = camLookAtY = camLookAtZ = 0.0f;
                cameraMode = SPHERICAL;
            }
            break;
        }
        //rodar câmera para esquerda
        case 'a': {
            if (cameraMode == FIRSTPERSON) {
                alfa += 0.1f;
                rotateHead();
            }
            break;
        }
        //rodar câmera para direita
        case 'd': {
            if (cameraMode == FIRSTPERSON) {
                alfa -= 0.1f;
                rotateHead();
            }
            break;
        }
        //rodar câmera para cima
        case 'w': {
            if (cameraMode == FIRSTPERSON) {
                beta2 += 0.1f;
                rotateHead();
            }
            break;
        }
        case 's': {
            if (cameraMode == FIRSTPERSON) {
                beta2 += 0.1f;
                rotateHead();
            }
            break;
        }             
    }
    glutPostRedisplay();
}


void processVBOs(Group group){
    for (Model model : group.models) {
        drawFigure(model.modelFile,model.textureFile);
    }

    for (Group child : group.children){
        processVBOs(child);
    }
}


int main(int argc, char *argv[]) {
    printf("Engine started\n");

    read_XML(argv[1]);

    cameraMode = SPHERICAL;

    // Calculate Angles for Camera
    alfa = acos(camPosZ / sqrt(camPosX * camPosX + camPosZ * camPosZ));
    raio = sqrt((camPosX * camPosX) + (camPosY * camPosY) + (camPosZ * camPosZ));
    beta2 = asin(camPosY / raio);
    
    // Init GLUT and the window
    glutInit(&argc, argv);
    timebase = glutGet(GLUT_ELAPSED_TIME);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(width, height);
    glutCreateWindow("CG");

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
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_RESCALE_NORMAL);
    glEnable(GL_TEXTURE_2D);
    
    glShadeModel(GL_SMOOTH);

    // Initialize VBOs
    glGenBuffers(numFigurasMax, buffers);
    glGenBuffers(numFigurasMax, buffersN);
    glGenBuffers(numFigurasMax, buffersT);
    processVBOs(mainGroup);

    float amb[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb);
    

    // Enter GLUT's main cycle
    glutMainLoop();
    return 1;
}