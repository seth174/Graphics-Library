#ifndef Raster_H
#define Raster_H
#include "Color.h"
#include "Triangle2D.h"
#include "Model.h"

class Raster
{
    private:
        int width; 
        int height;
        Color* pixel;
        float* depthPixels;
    public:
        Raster();
        Raster(int pWidth, int pHeight, Color pFillCollor);
        ~Raster();
        
        int getWidth();
        int getHeight();
        Color getColorPixel(int x, int y);
        float getDepthPixel(int x, int y);
        void setColorPixel(int x, int y, Color pFillColor);
        void setDepthPixel(int x, int y, float depth);
        void clear(Color pFillObject);
        void clear(float depth);
        void writeToPPM();
        

        void drawLine_DDA(float x1, float y1, float x2, float y2, Color fillColor);
        void drawLine_DDA_Interpolated(float x1, float y1, float x2, float y2, Color color1,Color color2);
        
        void drawTriangle2D_DotProduct(Triangle2D triangle);
        void drawTriangle3D_Barycentric(Triangle3D T);

        void drawModel(Model m); 
        

};

#endif 