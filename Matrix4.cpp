#include "Matrix4.h"
#include<iostream>
using namespace std;
#include<math.h>

Matrix4:: Matrix4()
{
    ix = 1; 
    jx = 0; 
    kx = 0;
    ox = 0;
    iy = 0;
    jy = 1;
    ky = 0;
    oy = 0;
    iz = 0;
    jz = 0;
    kz = 1;
    oz = 0;
    iw = 0;
    jw = 0;
    kw = 0;
    ow = 1;
} 
Matrix4::Matrix4(float ix, float jx, float kx, float ox, float iy, float jy, float ky, float oy, 
float iz, float jz, float kz, float oz, float iw, float jw, float kw, float ow) 
{
    this->ix = ix;
    this->jx = jx;
    this->kx = kx;
    this->ox = ox;
    this->iy = iy;
    this->jy = jy;
    this->ky = ky;
    this->oy = oy;
    this->iz = iz;
    this->jz = jz;
    this->kz = kz;
    this->oz = oz;
    this->iw = iw;
    this->jw = jw;
    this->kw = kw;
    this->ow = ow;
}

Matrix4 Matrix4 :: operator*(const Matrix4& m)
{
    Matrix4 temp;
    temp.ix = m.ix * this->ix + m.iy * this->jx + m.iz * this->kx + m.iw * this->ox;
    temp.jx = m.jx * this->ix + m.jy * this->jx + m.jz * this->kx + m.jw * this->ox;
    temp.kx = m.kx * this->ix + m.ky * this->jx + m.kz * this->kx + m.kw * this->ox;
    temp.ox = m.ox * this->ix + m.oy * this->jx + m.oz * this->kx + m.ow * this->ox;
    temp.iy = m.ix * this->iy + m.iy * this->jy + m.iz * this->ky + m.iw * this->oy;
    temp.jy = m.jx * this->iy + m.jy * this->jy + m.jz * this->ky + m.jw * this->oy;
    temp.ky = m.kx * this->iy + m.ky * this->jy + m.kz * this->ky + m.kw * this->oy;
    temp.oy = m.ox * this->iy + m.oy * this->jy + m.oz * this->ky + m.ow * this->oy;
    temp.iz = m.ix * this->iz + m.iy * this->jz + m.iz * this->kz + m.iw * this->oz;
    temp.jz = m.jx * this->iz + m.jy * this->jz + m.jz * this->kz + m.jw * this->oz;
    temp.kz = m.kx * this->iz + m.ky * this->jz + m.kz * this->kz + m.kw * this->oz;
    temp.oz = m.ox * this->iz + m.oy * this->jz + m.oz * this->kz + m.ow * this->oz;
    temp.iw = m.ix * this->iw + m.iy * this->jw + m.iz * this->kw + m.iw * this->ow;
    temp.jw = m.jx * this->iw + m.jy * this->jw + m.jz * this->kw + m.jw * this->ow;
    temp.kw = m.kx * this->iw + m.ky * this->jw + m.kz * this->kw + m.kw * this->ow;
    temp.ow = m.ox * this->iw + m.oy * this->jw + m.oz * this->kw + m.ow * this->ow;
    return temp;
}

Vector4 Matrix4::operator*(const Vector4& v)
{
    Vector4 temp;
    temp.xComponent = v.xComponent * this->ix + v.yComponent * this->jx + v.zComponent * this->kx + v.w * this->ox;
    temp.yComponent = v.xComponent * this->iy + v.yComponent * this->jy + v.zComponent * this->ky + v.w * this->oy;
    temp.zComponent = v.xComponent * this->iz + v.yComponent * this->jz + v.zComponent * this->kz + v.w * this->oz;
             temp.w = v.xComponent * this->iw + v.yComponent * this->jw + v.zComponent * this->kw + v.w * this->ow;
    return temp;
}

Matrix4 Translate3D(float tX, float tY, float tZ)
{
    Matrix4 temp;
    temp.ix = 1; 
    temp.jx = 0; 
    temp.kx = 0;
    temp.ox = tX;
    temp.iy = 0;
    temp.jy = 1;
    temp.ky = 0;
    temp.oy = tY;
    temp.iz = 0;
    temp.jz = 0;
    temp.kz = 1;
    temp.oz = tZ;
    temp.iw = 0;
    temp.jw = 0;
    temp.kw = 0;
    temp.ow = 1;
    return temp;
}

Matrix4 Scale3D(float sX, float sY, float sZ)
{
    Matrix4 temp;
    temp.ix = sX; 
    temp.jx = 0; 
    temp.kx = 0;
    temp.ox = 0;
    temp.iy = 0;
    temp.jy = sY;
    temp.ky = 0;
    temp.oy = 0;
    temp.iz = 0;
    temp.jz = 0;
    temp.kz = sZ;
    temp.oz = 0;
    temp.iw = 0;
    temp.jw = 0;
    temp.kw = 0;
    temp.ow = 1;
    return temp;
}

Matrix4 RotateX3D(float degrees)
{
    float radians = degrees * M_PI /180.0;
    Matrix4 temp;
    temp.ix = 1; 
    temp.jx = 0; 
    temp.kx = 0;
    temp.ox = 0;
    temp.iy = 0;
    temp.jy = cos(radians);
    temp.ky = sin(radians);
    temp.oy = 0;
    temp.iz = 0;
    temp.jz = -sin(radians);
    temp.kz = cos(radians);
    temp.oz = 0;
    temp.iw = 0;
    temp.jw = 0;
    temp.kw = 0;
    temp.ow = 1;
    return temp;
}

Matrix4 RotateY3D(float degrees) {
    float radians = degrees * M_PI/180.0; 
    Matrix4 temp; 
    temp.ix = cos(radians); 
    temp.jx = 0; 
    temp.kx = -sin(radians); 
    temp.ox = 0; 
    temp.iy = 0;
    temp.jy = 1;
    temp.ky = 0;
    temp.oy = 0;
    temp.iz = sin(radians);
    temp.jz = 0;
    temp.kz = cos(radians);
    temp.oz = 0;
    temp.iw = 0;
    temp.jw = 0;
    temp.kw = 0;
    temp.ow = 1;
    return temp;
}

Matrix4 RotateZ3D(float degrees)
{
    float radians = degrees * M_PI /180.0;
    Matrix4 temp;
    temp.ix = cos(radians); 
    temp.jx = sin(radians); 
    temp.kx = 0;
    temp.ox = 0;
    temp.iy = -sin(radians);
    temp.jy = cos(radians);
    temp.ky = 0;
    temp.oy = 0;
    temp.iz = 0;
    temp.jz = 0;
    temp.kz = 1;
    temp.oz = 0;
    temp.iw = 0;
    temp.jw = 0;
    temp.kw = 0;
    temp.ow = 1;
    return temp;
}

Matrix4 Rotate3D(float degreesX, float degreesY, float degreesZ)
{
    float radiansX = degreesX * M_PI /180.0;
    float radiansY = degreesY * M_PI /180.0;
    float radiansZ = degreesZ * M_PI /180.0;
    Matrix4 temp = RotateZ3D(radiansZ) * RotateY3D(radiansY) * RotateX3D(radiansX);
    return temp;
}

Matrix4 Rotate3D(float degrees, Vector4 vec) {
    float radians = degrees * M_PI /180.0;
    float alpha = atanh(vec.xComponent/vec.zComponent);
    float beta = acosf(vec.yComponent/vec.magnitude());
    Matrix4 temp = RotateY3D(-alpha) * RotateX3D(-beta) * RotateY3D(radians) * RotateX3D(beta) * RotateY3D(alpha);
    return temp;
}

void Matrix4::print()
{
    cout<< ix<< " "<< jx<< " "<< kx<< " "<< ox<< endl;
    cout<< iy<< " "<< jy<< " "<< ky<< " "<< oy<< endl;
    cout<< iz<< " "<< jz<< " "<< kz<< " "<< oz<< endl;
    cout<< iw<< " "<< jw<< " "<< kw<< " "<< ow<< endl;
}

Matrix4 LookAt(Vector4 eye, Vector4 spot, Vector4 up) { 
    Matrix4 temp = Translate3D(-eye.xComponent,-eye.yComponent, -eye.zComponent);


    Vector4 tmplook = spot-eye; 
    tmplook.normalize();  
    Vector4 right = tmplook.cross(up); 
    right.normalize(); 
    
    
    Vector4 pUp = right.cross(tmplook);
    pUp.normalize();
    
    Matrix4 lookAtMatrix; 
    lookAtMatrix.ix = right.xComponent;
    lookAtMatrix.jx = right.yComponent; 
    lookAtMatrix.kx = right.zComponent;
    lookAtMatrix.ox = 0;
    lookAtMatrix.iy = pUp.xComponent;
    lookAtMatrix.jy = pUp.yComponent;
    lookAtMatrix.ky = pUp.zComponent;
    lookAtMatrix.oy = 0;
    lookAtMatrix.iz = -tmplook.xComponent;
    lookAtMatrix.jz = -tmplook.yComponent;
    lookAtMatrix.kz = -tmplook.zComponent;
    lookAtMatrix.oz = 0;
    lookAtMatrix.iw = 0;
    lookAtMatrix.jw = 0;
    lookAtMatrix.kw = 0;
    lookAtMatrix.ow = 1;

    Matrix4 temp2 = lookAtMatrix*temp;
    return temp2;

 
}

Matrix4 Orthographic(float minX, float maxX, float minY, float maxY, float minZ, float maxZ)
{
    Matrix4 translateOrigin = Translate3D(-(minX + maxX) / 2, -(minY + maxY) / 2, -(minZ + maxZ) / 2);
    Matrix4 scaleTemp = Scale3D(2/(maxX - minX), 2/(maxY - minY), 2/(maxZ - minZ));
    return scaleTemp * translateOrigin;
}

Matrix4 perspective(float fovY, float aspect, float nearZ, float farZ)
{
    float radians = fovY * M_PI /180.0;
    float F = 1/(tan(radians/2));
    Matrix4 persp(F/aspect, 0, 0, 0, 0, F, 0, 0, 0, 0, (farZ + nearZ) / (nearZ - farZ), (2 * nearZ * farZ) / (nearZ - farZ), 
    0, 0, -1, 0);
    return persp;
}

Matrix4 Viewport(float x, float y, float width, float height)
{
    Matrix4 translate = Translate3D(1, 1, -1);
    Matrix4 scale = Scale3D(.5, .5, .5);
    Matrix4 scalePt2 = Scale3D(width, height, 1);
    Matrix4 translatePt2 = Translate3D(x, y, 0);
    return translatePt2 * scalePt2 * scale * translate;
}
