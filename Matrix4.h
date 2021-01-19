#ifndef Matrix4_H
#define Matrix4_H
#include "Vector2.h"
struct Matrix4
{
    public:
        float ix; 
        float jx; 
        float kx;
        float ox;
        float iy;
        float jy;
        float ky;
        float oy;
        float iz;
        float jz;
        float kz;
        float oz;
        float iw;
        float jw;
        float kw;
        float ow;

        void print();

        Matrix4();
        Matrix4(float ix, float jx, float kx, float ox, float iy, float jy, float ky, float oy, float iz, float jz,
        float kz, float oz, float iw, float jw, float kw, float ow);
        Vector4 operator*(const Vector4& v);
        Matrix4 operator*(const Matrix4& m);
};

Matrix4 Translate3D(float tX, float tY, float tZ);
Matrix4 Scale3D(float sX, float sY, float sZ);
Matrix4 RotateX3D(float degrees); 
Matrix4 RotateY3D(float degrees); 
Matrix4 RotateZ3D(float degrees);
Matrix4 Rotate3D(float degreesX, float degreesY, float degreesZ); 
Matrix4 Rotate3D(float degrees, Vector4 vec);
Matrix4 LookAt(Vector4 eye, Vector4 spot, Vector4 up);
Matrix4 Orthographic(float minX, float maxX, float minY, float maxY, float minZ, float maxZ);
Matrix4 perspective(float fovY, float aspect, float nearZ, float farZ);
Matrix4 Viewport(float x, float y, float width, float height);



#endif