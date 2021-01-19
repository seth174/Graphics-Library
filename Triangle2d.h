#ifndef Triangle2D_H
#define Triangle2D_H
#include "Vector2.h"
#include "Color.h"
#include "Matrix4.h"
struct Triangle3D;
struct Triangle2D
{
    public:
        Vector2 v1;
        Vector2 v2;
        Vector2 v3;

        Color c1;
        Color c2;
        Color c3;


        Triangle2D();
        Triangle2D(Vector2 pV1, Vector2 pV2, Vector2 pv3, Color pC1, Color pC2, Color pC3);
        void calculateBaryCentricCoordinates(Vector2 p, float &lamda1, float &lamda2, float &lambda3);

        Triangle2D(Triangle3D t);

};

#endif

#ifndef Triangle3D_H
#define Triangle3D_H
struct Triangle3D
{
    public:
        Vector4 v1;
        Vector4 v2;
        Vector4 v3;

        Color c1;
        Color c2;
        Color c3;

        bool shouldDraw;

        Triangle3D();
    
    
    
    
        Triangle3D(Vector4 pV1, Vector4 pV2, Vector4 pV3, Color pC1, Color pC2, Color pC3); 
        
        void transform(Matrix4 matrix);
};

#endif