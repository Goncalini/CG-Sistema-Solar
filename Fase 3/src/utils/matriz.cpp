#include "matriz.hpp"

void buildRotMatrix(float* x, float* y, float* z, float* m) {

    m[0] = x[0]; m[1] = x[1]; m[2] = x[2]; m[3] = 0;
    m[4] = y[0]; m[5] = y[1]; m[6] = y[2]; m[7] = 0;
    m[8] = z[0]; m[9] = z[1]; m[10] = z[2]; m[11] = 0;
    m[12] = 0; m[13] = 0; m[14] = 0; m[15] = 1;
}


void cross(float* a, float* b, float* res) {

    res[0] = a[1] * b[2] - a[2] * b[1];
    res[1] = a[2] * b[0] - a[0] * b[2];
    res[2] = a[0] * b[1] - a[1] * b[0];
}


void normalize(float* a) {

    float l = sqrt(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]);
    a[0] = a[0] / l;
    a[1] = a[1] / l;
    a[2] = a[2] / l;
}


float length(float* v) {

    float res = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
    return res;

}

void multMatrixVector(float* m, float* v, float* res) {

    for (int j = 0; j < 4; ++j) {
        res[j] = 0;
        for (int k = 0; k < 4; ++k) {
            res[j] += v[k] * m[j * 4 + k];
        }
    }

}


void getCatmullRomPoint(float t, Point p0, Point p1, Point p2, Point p3, float* pos, float* deriv) {

    // catmull-rom matrix
    float m[4][4] = { {-0.5f,  1.5f, -1.5f,  0.5f},
                        { 1.0f, -2.5f,  2.0f, -0.5f},
                        {-0.5f,  0.0f,  0.5f,  0.0f},
                        { 0.0f,  1.0f,  0.0f,  0.0f} };

    float pontos[4][3] = {{p0.x,p0.y,p0.z},
                          {p1.x,p1.y,p1.z},
                          {p2.x,p2.y,p2.z},
                          {p3.x,p3.y,p3.z}};
    for (int i = 0; i < 3; i++) { //i = x,y,z

        // Compute A = M * P
        float p[4] = { pontos[0][i], pontos[1][i], pontos[2][i], pontos[3][i] };
        float a[4];
        multMatrixVector(*m, p, a);
        // Compute pos = T * A
        pos[i] = powf(t, 3.0) * a[0] + powf(t, 2.0) * a[1] + t * a[2] + a[3];
        // compute deriv = T' * A
        deriv[i] = 3 * powf(t, 2.0) * a[0] + 2 * t * a[1] + a[2];
    }
}

// given  global t, returns the point in the curve
void getGlobalCatmullRomPoint(float gt, std::list<Point> points, float* pos , float* deriv) {
    size_t POINT_COUNT = points.size();

    float t = gt * POINT_COUNT; // this is the real global t
    int index = floor(t);  // which segment
    t = t - index; // where within  the segment

    // indices store the points
    int indices[4];
    indices[0] = (index + POINT_COUNT - 1) % POINT_COUNT;
    indices[1] = (indices[0] + 1) % POINT_COUNT;
    indices[2] = (indices[1] + 1) % POINT_COUNT;
    indices[3] = (indices[2] + 1) % POINT_COUNT;

    std::list<Point>::iterator it0 = points.begin();
    std::advance(it0, indices[0]);
    std::list<Point>::iterator it1 = points.begin();
    std::advance(it1, indices[1]);
    std::list<Point>::iterator it2 = points.begin();
    std::advance(it2, indices[2]);
    std::list<Point>::iterator it3 = points.begin();
    std::advance(it3, indices[3]);

    // obtaining points from iterators
    Point p0 = *it0;
    Point p1 = *it1;
    Point p2 = *it2;
    Point p3 = *it3;

    getCatmullRomPoint(t, p0, p1, p2, p3, pos, deriv);
}