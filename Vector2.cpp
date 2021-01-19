#include "Vector2.h"
#include <cmath>
#include<iostream>
using namespace std;


Vector2::Vector2()
{
    xComponent = 0.0;
    yComponent = 0.0;
}

Vector2::Vector2(float pXComponent, float PYComponent)
{
    xComponent = pXComponent;
    yComponent = PYComponent;
}
Vector2 Vector2::operator+(const Vector2& v)
{
    Vector2 temp;
    temp.xComponent = v.xComponent + this->xComponent;
    temp.yComponent = v.yComponent + this->yComponent;
    return temp;
}

Vector2 Vector2::operator-(const Vector2& v)
{
    Vector2 temp;
    temp.xComponent = this->xComponent - v.xComponent;
    temp.yComponent = this->yComponent - v.yComponent;
    return temp;
}

Vector2 Vector2::operator*(const float& s)
{
    Vector2 temp;
    temp.yComponent = this->yComponent * s;
    temp.xComponent = this->xComponent * s;
    return temp;
}

float Vector2::magnitude()
{
    return (sqrt(yComponent * yComponent + xComponent * xComponent));
}

void Vector2::normalize()
{
    float magnitude = this->magnitude();
    xComponent = (1/magnitude) * xComponent;
    yComponent = (1 / magnitude) * yComponent;
}
Vector2 Vector2::perpendicular() 
{
    Vector2 t;  
    t.xComponent = this->yComponent * -1.0; 
    t.yComponent = this->xComponent; 
    return t; 
}

float Vector2::dot(Vector2 a)
{
    return a.xComponent * this->xComponent + a.yComponent * this->yComponent;
       
}

float determinant(Vector2 a, Vector2 b)
{
    return float(b.xComponent * a.yComponent - a.xComponent * b.yComponent);
}

Vector4:: Vector4()
{
    xComponent = 0;
    yComponent = 0;
    zComponent = 0;
    w = 0;
}

Vector4:: Vector4(float pX, float pY, float pZ, float pW)
{
    xComponent = pX;
    yComponent = pY;
    zComponent = pZ;
    w = pW;
}

Vector4 Vector4::operator*(const float& s)
{
    Vector4 temp;
    temp.xComponent = this->xComponent * s;
    temp.yComponent = this->yComponent * s;
    temp.zComponent = this->zComponent * s;
    temp.w = this->w * s;
    return temp;
}

Vector4 Vector4 :: operator+(const Vector4& v)
{
    Vector4 temp;
    temp.xComponent = this->xComponent + v.xComponent;
    temp.yComponent = this->yComponent + v.yComponent;
    temp.zComponent = this->zComponent + v.zComponent;
    temp.w = this->w + v.w; 
    return temp;
}

Vector4 Vector4 :: operator-(const Vector4& v)
{
    Vector4 temp;
    temp.xComponent = this->xComponent - v.xComponent;
    temp.yComponent = this->yComponent - v.yComponent;
    temp.zComponent = this->zComponent - v.zComponent;
    temp.w = this->w - v.w; 
    return temp;
}

float Vector4::magnitude()
{
    return (sqrt(xComponent * xComponent + yComponent * yComponent + zComponent * zComponent));
}

void Vector4::normalize()
{
    float magnitude = this->magnitude();
    xComponent = (1/magnitude) * xComponent;
    yComponent = (1/magnitude) * yComponent;
    zComponent = (1/magnitude) * zComponent;
}

float Vector4 :: dot(Vector4 v) {
    return xComponent * v.xComponent + yComponent * v.yComponent + zComponent * v.zComponent;
}

Vector4 Vector4::cross(Vector4 b)
{
    Vector4 temp;
    temp.xComponent = this->yComponent * b.zComponent - this->zComponent * b.yComponent;
    temp.yComponent = this->zComponent * b.xComponent - this->xComponent * b.zComponent;
    temp.zComponent = this->xComponent * b.yComponent - this->yComponent * b.xComponent;
    temp.w = 0;
    return temp;
}
