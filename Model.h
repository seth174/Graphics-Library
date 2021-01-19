#ifndef Model_H
#define Model_H
#include<vector>
using namespace std;
#include "Triangle2D.h"

class Model
{
    public:
        vector<Triangle3D> triangles;
        Model();
        int numTriangles(); 
        Triangle3D operator[](int i);
        void transform(Matrix4 m);
        void readFromOBJFile(string filepath, Color pFillColor); 
        void homogenize();
        void test();
        void performBackfaceCulling(Vector4 eye, Vector4 spot); 
};


#endif