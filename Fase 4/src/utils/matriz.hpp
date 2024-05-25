#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <list>

using namespace std;

struct Point {
    float x, y, z;
};

void buildRotMatrix(float* x, float* y, float* z, float* m);
void cross(float* a, float* b, float* res);
void normalize(float* a);
float length(float* v);
void multMatrixVector(float* m, float* v, float* res);
void getCatmullRomPoint(float t, Point p0, Point p1, Point p2, Point p3, float* pos, float* deriv);
void getGlobalCatmullRomPoint(float gt, std::list<Point> points, float* pos, float* deriv);