#include "Triangle2D.h"
#include "Vector2.h"
#include "Color.h"
#include<iostream>
using namespace std;


Triangle2D:: Triangle2D()
{
    Vector2 v1(0,0);
    Vector2 v2(0,0);
    Vector2 v3(0,0);
}

Triangle2D:: Triangle2D(Vector2 pV1, Vector2 pV2, Vector2 pV3, Color pC1, Color pC2, Color pC3)
{
  v1 = pV1; 
  v2 = pV2;
  v3 = pV3;
  c1 = pC1;
  c2 = pC2;
  c3 = pC3;

}

Triangle2D::Triangle2D(Triangle3D t)
{
  this->v1.xComponent = t.v1.xComponent;
  this->v1.yComponent = t.v1.yComponent;
  this->v2.xComponent = t.v2.xComponent;
  this->v2.yComponent = t.v2.yComponent;
  this->v3.xComponent = t.v3.xComponent;
  this->v3.yComponent = t.v3.yComponent;
  c1 = t.c1;
  c2 = t.c2;
  c3 = t.c3;
 
}

 void Triangle2D :: calculateBaryCentricCoordinates(Vector2 p, float &lamda1, float &lamda2, float &lambda3) {
   Vector2 a1 = this->v2 - this->v3; 
   Vector2 b1 = this->v1 - this->v3;

   float fullArea = determinant(a1, b1) / 2.0f;
   
   Vector2 b2 = p - this->v3;
   float A1 = determinant(this->v2 - this->v3,b2) / 2.0f;

   lamda1 = A1 / fullArea;

   Vector2 a2 = this->v1 - this->v3;
  float A2 = determinant(b2,a2) / 2.0f;
  
  lamda2 = A2/fullArea;

  lambda3 = 1.0 - lamda1;
  lambda3 = lambda3 - lamda2;
 }

  
Triangle3D::Triangle3D()
 {
  Vector4 v1(0,0,0,1);
  Vector4 v2(0,0,0,1);
  Vector4 v3(0,0,0,1); 
  shouldDraw = true;
 }

Triangle3D:: Triangle3D(Vector4 pV1, Vector4 pV2, Vector4 pV3, Color pC1, Color pC2, Color pC3)
{
  v1 = pV1; 
  v2 = pV2;
  v3 = pV3;
  c1 = pC1;
  c2 = pC2;
  c3 = pC3;
  shouldDraw = true;

}

void Triangle3D :: transform(Matrix4 matrix) 
{
  this->v1 = matrix * v1;
  this->v2 = matrix * v2;
  this->v3 = matrix * v3;
}

