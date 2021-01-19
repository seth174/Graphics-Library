#ifndef Vector2_H
#define Vector2_H

struct Vector2
{
    public:
        Vector2();
        Vector2(float pXComponent, float PYComponent);

        
        Vector2 operator+(const Vector2& v);
        Vector2 operator-(const Vector2& v);
        Vector2 operator*(const float& s);
        
        void normalize();
        Vector2 perpendicular();
        float dot(Vector2 a);
        float magnitude();
 
        float xComponent;
        float yComponent;
};

float determinant(Vector2 a, Vector2 b);

#endif

#ifndef Vector4_H
#define Vector4_H

struct Vector4
{
    public:
        Vector4();
        Vector4(float pX, float pY, float pZ, float pW);

        float xComponent;
        float yComponent;
        float zComponent;
        float w;

        Vector4 operator*(const float& s);
        Vector4 operator+(const Vector4& v);
        Vector4 operator-(const Vector4& v);

        float magnitude();
        void normalize();
        float dot(Vector4 v);
        Vector4 cross(Vector4 b);



};
#endif