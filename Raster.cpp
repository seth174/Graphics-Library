#include "Raster.h"
#include <iostream>
using namespace std;
#include <fstream>
#include "Vector2.h"
#include "Triangle2D.h"
#include <limits>
Raster::Raster()
{
   width = 0;
   height = 0;
   pixel = NULL;
   depthPixels = NULL;  
}

int Raster::getWidth()
{
    return width;
}

int Raster::getHeight()
{
    return height;
}


Color Raster::getColorPixel(int x, int y)
{
    y = height - y - 1;
    return pixel[y * width + x];
}

float Raster :: getDepthPixel(int x, int y) {
    y = height - y - 1;
    return depthPixels[y * width + x];
}

Raster :: Raster(int pWidth,int pHeight,Color pFillColor) 
{
    width = pWidth;
    height = pHeight;
    pixel = new Color[pWidth*pHeight];
    depthPixels = new float[pWidth * pHeight];
    clear(pFillColor);
}

Raster::~Raster()
{
    delete []pixel;
    delete []depthPixels;
}

void Raster::setColorPixel(int x, int y, Color pFillColor)
{
    y = height - 1 - y;
    pixel[ y * width + x] = pFillColor;
}

void Raster::setDepthPixel(int x, int y, float depth)
{
    y = height - 1 - y;
    depthPixels[ y * width + x] = depth;
}

void Raster::clear(Color pFillColor)
{
    for(int i = 0; i < width * height; i ++ )
    {
        pixel[i] = pFillColor;
        depthPixels[i] = numeric_limits<float>::max();
    }
}

void Raster::clear(float depth)
{
    for(int i = 0; i < width * height; i ++ )
    {
        depthPixels[i] = depth;
    }
}



void Raster::writeToPPM()
{
    ofstream myfile;
    myfile.open("FRAME_BUFFER.ppm");
    myfile << "P3 \n";
    myfile<<width << " " << height<< "\n";
    myfile<< 255 << "\n";
    int counter = 0;
    for(int i = 0; i < height; i++ )
    {
        for(int j = 0; j < width; j++)
        {
            myfile<<static_cast<int>(pixel[counter].red * 255) << " " << static_cast<int>(pixel[counter].green * 255) << " "
             << static_cast<int>(pixel[counter].blue * 255) << " ";
            counter = counter + 1;
        }
        myfile<<"\n";
    }
    myfile.close();
}



void Raster::drawLine_DDA(float x1, float y1, float x2, float y2, Color fillColor)
{
    float temp; //temp variable used later

    float start = 0; //used for x cordinates
    float  end = 0;

    float start2 = 0; //used for y cordinates
    float end2 = 0;

    float slope = 0; //change in y over change in x
    float slope2 = 0; //change in x over change in y(lines with a slope greater than 1)

    //makes sure not to divide by zero to find slope
    if(x1 - x2 != 0 || y1 - y2 != 0)
    {
        slope = (y2 - y1) / (x2 - x1);
        slope2 = (x2 - x1) / (y2 - y1);
    }

    //if both x or if both y are out of bounds nothing will happen in the picture
    if((x1 >= width && x2 >= width) || (y1 >= height && y2 >= height))
    {
        return;
    }

    //checks if it's out of bounds
    if(x1 >= width){
        x1 = width - 1;
    }
    if(x2 >= width){
        x2 = width - 1;
    }
    if(x1 < 0){
        x1 = 0;
    }
    if(x2 < 0){
        x2=0;
    }
    if(y1 >= height) {
        y1 = height - 1;
    }
     if(y2 >= height) {
        y2 = height - 1;
    }
    if(y1 < 0){
        y1 = 0;
    }
    if(y2 < 0){
        y2 = 0;
    }
    //
    
    //checks to see if it is a vertical line
    if(x1 - x2 == 0)
    {
        if(y1 > y2)
        {
            start2 = y2;
            end2 = y1;
        }
        else
        {
            start2 = y1;
            end2 = y2;
        }
        for(int y = start2; y <= end2; y++)
        {
            setColorPixel(x2, y, fillColor);
            
        }
    }
    
    //checks to see if its a horizontal line
    else if(y2 - y1 == 0)
    {
        if(x2 < x1)
        {
            start = x2;
            end = x1;
        }
        else
        {
            start = x1;
            end = x2;
        }
        for(int x = start; x <= end; x++)
        {
            setColorPixel(x, y1, fillColor);
        }
    }

    //Uses this if the slope of the line is not too steep
    else if(-1 <= slope && slope <= 1)
    {
        float startX = x1;
        float endX = x2; 
        float startY = y1;
        float endY = y2;
        
        if(x1 > x2) {
          startX = x2;
          endX = x1; 
          startY = y2;
          endY = y1; 
        }

        float s_y = startY;
        for(int x = startX; x<=endX;x++) {
            setColorPixel(x,round(s_y),fillColor);
            s_y += slope;
        }
        
    }//end non-steep slope

    //for steep lines
    else if(slope > 1 || slope < -1 )
    {

        if(y2 < y1)
        {
            start2 = y1;
            end2 = y2;
            start = x1;
            end = x2;
        }
        else
        {
            start2 = y2;
            end2 = y1;
            start = x2;
            end = x1;
        }
            
        temp = start;
        for(int y = start2; y >= end2 && y<= height; y--)
        {
            start = temp;
            setColorPixel(round(start), y, fillColor);
            temp = temp - slope2;
        }
    
        
    }
    
}


void Raster::drawLine_DDA_Interpolated(float x1, float y1, float x2, float y2, Color color1,Color color2)
{
    float tempX;
    float tempY;

    Vector2 endPointToPoint(0,0); //vector from endpoint to the point being drawn
    float ratio; //color ratio
    Color tempColor;

    if(x2 < x1 ) //always sets x1 to be on the left
    {
        tempX = x2;
        x2 = x1;
        x1 = tempX;
        tempY = y2;
        y2 = y1;
        y1 = tempY;
    }

    Vector2 lenthOfLine(x2 - x1, y2 - y1);

    Vector2 endPoint1(x1, y1);
    Vector2 endPoint2(x2, y2);

    float temp; //temp variable used later

    float start = 0; //used for x cordinates
    float  end = 0;

    float start2 = 0; //used for y cordinates
    float end2 = 0;

    float slope = 0; //change in y over change in x
    float slope2 = 0; //change in x over change in y(lines with a slope greater than 1)

    //makes sure not to divide by zero to find slope
    if(x1 - x2 != 0 || y1 - y2 != 0)
    {
        slope = (y2 - y1) / (x2 - x1);
        slope2 = (x2 - x1) / (y2 - y1);
    }

    //if both x or if both y are out of bounds nothing will happen in the picture
    if((x1 >= width && x2 >= width) || (y1 >= height && y2 >= height))
    {
        return;
    }

    //checks if it's out of bounds
    if(x1 >= width){
        x1 = width - 1;
    }
    if(x2 >= width){
        x2 = width - 1;
    }
    if(x1 < 0){
        x1 = 0;
    }
    if(x2 < 0){
        x2=0;
    }
    if(y1 >= height) {
        y1 = height - 1;
    }
     if(y2 >= height) {
        y2 = height - 1;
    }
    if(y1 < 0){
        y1 = 0;
    }
    if(y2 < 0){
        y2 = 0;
    }
    //
    
    //checks to see if it is a vertical line
    if(x1 - x2 == 0)
    {
        
        if(y1 > y2) //will always start at the bottom of the line and work its way up and always make endpoint1 the bottom point
        {
            start2 = y2;
            end2 = y1;
            endPoint1.yComponent = endPoint2.yComponent; 
        }
        else
        {
            start2 = y1;
            end2 = y2;
        }
        for(int y = start2; y <= end2; y++)
        {
            endPointToPoint.yComponent = y - endPoint1.yComponent;
            ratio = endPointToPoint.magnitude() / lenthOfLine.magnitude();
            tempColor = color2 * ratio + color1 * (1 - ratio);

            setColorPixel(x2, y, tempColor);
        }
    }
    
    //checks to see if its a horizontal line
    else if(y2 - y1 == 0)
    {
        if(x2 < x1) //always starts at the left of the line
        {
            start = x2;
            end = x1;
            endPoint1.xComponent = endPoint2.xComponent; //always make sure endpoint1.xComponent is the left most point
        }
        else
        {
            start = x1;
            end = x2;
        }
        for(int x = start; x <= end; x++)
        {
            endPointToPoint.xComponent = x - endPoint1.xComponent;
            ratio = endPointToPoint.magnitude()/ lenthOfLine.magnitude();
            tempColor = color2 * ratio + color1 * (1 - ratio);
            setColorPixel(x, y1, tempColor);
        }
    }

    //Uses this if the slope of the line is not too steep
    else if(-1 <= slope && slope <= 1)
    {
        float startX = x1;
        float endX = x2; 
        float startY = y1;
        float endY = y2;
        
        if(x1 > x2) { //always starts at the left endpoint
          startX = x2;
          endPoint1 = endPoint2;
          endX = x1; 
          startY = y2;
          endY = y1; 
        }

        //special case of figuring out where to start if the leftmost x component is of the screen
        if(endPoint1.yComponent < 0 || endPoint1.yComponent > height || endPoint1.xComponent < 0)
        {
            int negativeComponent = endPoint1.yComponent;
            int positiveComponent = endPoint1.yComponent;
            int xComponent = endPoint1.xComponent;
            startX = endPoint1.xComponent;
            while(negativeComponent < 0) //if the left most coordinate has a negative y component
            {
                startX = startX + slope2;
                negativeComponent = negativeComponent+1;
            }
            while (positiveComponent > height) // if the left most component has a y greater than the raster
            {
                startX = startX - slope2;
                positiveComponent = positiveComponent - 1;
            }
            while (xComponent < 0) //if the left most x coordinate is negative
            {
                startY = startY + slope;
                xComponent = xComponent + slope2;
                startX = startX + slope;
            }
        }
        //variables
        float s_y = startY;
        Vector2 endpt1ToPoint(0,0);
        float m;
        float p2;
        float ratioLen;
        for(int x = startX; x<=endX;x++) {
            
            endpt1ToPoint.xComponent = x - endPoint1.xComponent;
            endpt1ToPoint.yComponent = s_y-endPoint1.yComponent;
             m = endpt1ToPoint.magnitude();
            ratioLen = m/ lenthOfLine.magnitude(); 
            p2 = 1.0f-ratioLen;

            tempColor = color2 * ratioLen + color1 * p2;

            setColorPixel(x,round(s_y),tempColor);
            s_y += slope;
        }
        
    }//end non-steep slope

    //for steep lines
    else if(slope > 1 || slope < -1 )
    {

        if(y2 < y1)//always starts at the greatest y value
        {
            start2 = y1;
            end2 = y2;
            start = x1;
            end = x2;
        }
        else
        {
            start2 = y2;
            end2 = y1;
            start = x2;
            end = x1;
            endPoint1 = endPoint2;
        }

         float s_y = y1;
        Vector2 endpt1ToPoint(0,0);
        float m;
        float p2;
        float ratioLen;

        //special case where the greatest y point either has a negative x component or a x component greater than the width
        if(endPoint1.xComponent < 0 || endPoint1.xComponent > width) 
        {
            start2 = endPoint1.yComponent;
            float tempXComponent = endPoint1.xComponent;
            
            while(tempXComponent < 0.0) //if x is less than 0
            {
                start2 = start2 + slope;
                tempXComponent = tempXComponent + 1;
            }
            while(tempXComponent > width)
            {
                start2 = start2 - slope;
                tempXComponent = tempXComponent - 1;
            }
        }
            
        temp = start;
        for(int y = start2; y >= end2; y--)
        {
            start = temp;
            temp = temp - slope2;

            endpt1ToPoint.xComponent = start - endPoint1.xComponent;
            endpt1ToPoint.yComponent = y-endPoint1.yComponent;
             m = endpt1ToPoint.magnitude();
            ratioLen = m/ lenthOfLine.magnitude(); 
            p2 = 1.0f-ratioLen;

            tempColor = color2 * ratioLen + color1 * p2;

            setColorPixel(round(start),y,tempColor);
            if(temp < 0.0) //if it goes out of bounds on the -x axis
            {
                return;
            }
    
        }
        
    }
    
}

void Raster::drawTriangle2D_DotProduct(Triangle2D triangle) {
    Vector2 v1ToV2(triangle.v2.xComponent - triangle.v1.xComponent, triangle.v2.yComponent - triangle.v1.yComponent);
    Vector2 v1ToV2Perp(-(v1ToV2.yComponent), v1ToV2.xComponent);

    Vector2 v2ToV3(triangle.v3.xComponent - triangle.v2.xComponent, triangle.v3.yComponent - triangle.v2.yComponent);
    Vector2 v2ToV3Perp(-(v2ToV3.yComponent), v2ToV3.xComponent);

    Vector2 v3ToV1(triangle.v1.xComponent - triangle.v3.xComponent, triangle.v1.yComponent - triangle.v3.yComponent);
    Vector2 v3ToV1Perp(-(v3ToV1.yComponent), v3ToV1.xComponent);

    Vector2 vertexToPoint(0, 0);

    int endHeight = triangle.v1.yComponent;
    int startHeight = triangle.v1.yComponent;
    
    int startWidth = triangle.v1.xComponent;
    int endWidth = triangle.v1.xComponent;

    if(endHeight < triangle.v2.yComponent){
        endHeight = triangle.v2.yComponent;
    }
    if(endHeight < triangle.v3.yComponent)
    {
        endHeight = triangle.v3.yComponent;
    }

    if(startHeight > triangle.v2.yComponent)
    {
        startHeight = triangle.v2.yComponent;
    }
    if(startHeight > triangle.v3.yComponent)
    {
        startHeight = triangle.v3.yComponent;
    }

    if(endWidth < triangle.v2.xComponent)
    {
        endWidth = triangle.v2.xComponent;
    }
    if(endWidth < triangle.v3.xComponent){
        endWidth = triangle.v3.xComponent;
    }

    if(startWidth > triangle.v2.xComponent)
    {
        startWidth = triangle.v2.xComponent;
    }
    if(startWidth > triangle.v3.xComponent)
    {
        startWidth = triangle.v3.xComponent;
    }

    float dotProduct1 = 0;
    float dotProduct2 = 0;
    float dotProduct3 = 0;

//outside of the left side
    if(triangle.v1.xComponent < 0 ) {
        startWidth = 0; 
    }

     if(triangle.v2.xComponent < 0 ) {
        startWidth = 0; 
    }

     if(triangle.v3.xComponent < 0 ) {
        startWidth = 0; 
    }

//outside of the bottom of the raster
    if(triangle.v1.yComponent < 0 ) {
        startHeight = 0; 
    }

     if(triangle.v2.yComponent < 0 ) {
        startHeight = 0; 
    }

     if(triangle.v3.yComponent < 0 ) {
        startHeight = 0; 
    }

//outside of the right side
    if(triangle.v1.xComponent > width ) {
        endWidth = width - 1; 
    }

     if(triangle.v2.xComponent > width ) {
        endWidth = width - 1; 
    }

     if(triangle.v3.xComponent > width ) {
        endWidth = width - 1; 
    }

//outside of the top of the raster
    if(triangle.v1.yComponent > height ) {
        endHeight = height - 1; 
    }

     if(triangle.v2.yComponent > height ) {
        endHeight = height - 1; 
    }

     if(triangle.v3.yComponent > height ) {
        endHeight = height - 1; 
    }

    for(int i = startHeight; i <= endHeight ; i ++)
    {
        for(int j = startWidth; j <= endWidth; j++)
        {

            vertexToPoint.xComponent = j - triangle.v1.xComponent;
            vertexToPoint.yComponent = i - triangle.v1.yComponent;
            dotProduct1 = vertexToPoint.xComponent * v1ToV2Perp.xComponent + vertexToPoint.yComponent * v1ToV2Perp.yComponent;

            vertexToPoint.xComponent = j - triangle.v2.xComponent;
            vertexToPoint.yComponent = i - triangle.v2.yComponent;
            dotProduct2 = vertexToPoint.xComponent * v2ToV3Perp.xComponent + vertexToPoint.yComponent * v2ToV3Perp.yComponent;


            vertexToPoint.xComponent = j - triangle.v3.xComponent;
            vertexToPoint.yComponent = i - triangle.v3.yComponent;
            dotProduct3 = vertexToPoint.xComponent * v3ToV1Perp.xComponent + vertexToPoint.yComponent * v3ToV1Perp.yComponent;

            if(dotProduct1 >= 0 && dotProduct2 >=0 && dotProduct3 >= 0)
            {
                setColorPixel(j, i, triangle.c1);
            }
           

        }
        
    }


}

void Raster::drawTriangle3D_Barycentric(Triangle3D T)
{
    if(!T.shouldDraw)
    {
        return;
    }
    Triangle2D convertedT3(T);
    int endHeight = T.v1.yComponent;
    int startHeight = T.v1.yComponent;
    
    int startWidth = T.v1.xComponent;
    int endWidth = T.v1.xComponent;
    if(endHeight < T.v2.yComponent){
        endHeight = T.v2.yComponent;
    }
    if(endHeight < T.v3.yComponent)
    {
        endHeight = T.v3.yComponent;
    }

    if(startHeight > T.v2.yComponent)
    {
        startHeight = T.v2.yComponent;
    }
    if(startHeight > T.v3.yComponent)
    {
        startHeight = T.v3.yComponent;
    }

    if(endWidth < T.v2.xComponent)
    {
        endWidth = T.v2.xComponent;
    }
    if(endWidth < T.v3.xComponent){
        endWidth = T.v3.xComponent;
    }

    if(startWidth > T.v2.xComponent)
    {
        startWidth = T.v2.xComponent;
    }
    if(startWidth > T.v3.xComponent)
    {
        startWidth = T.v3.xComponent;
    }
    //outside of the left side
    if(T.v1.xComponent < 0 ) {
        startWidth = 0; 
    }

     if(T.v2.xComponent < 0 ) {
        startWidth = 0; 
    }

     if(T.v3.xComponent < 0 ) {
        startWidth = 0; 
    }

//outside of the bottom of the raster
    if(T.v1.yComponent < 0 ) {
        startHeight = 0; 
    }

     if(T.v2.yComponent < 0 ) {
        startHeight = 0; 
    }

     if(T.v3.yComponent < 0 ) {
        startHeight = 0; 
    }

//outside of the right side
    if(T.v1.xComponent > width ) {
        endWidth = width - 1; //for some reason if the width is greater than the raster it will rap around
    }

     if(T.v2.xComponent > width ) {
        endWidth = width - 1; 
    }

     if(T.v3.xComponent > width ) {
        endWidth = width - 1; 
    }

//outside of the top of the raster
    if(T.v1.yComponent > height ) {
        endHeight = height - 1; 
    }

     if(T.v2.yComponent > height ) {
        endHeight = height - 1; 
    }

     if(T.v3.yComponent > height ) {
        endHeight = height - 1; 
    }
    Vector2 pointVector(0.0f, 0.0f);
    float tempLamda1 = 0.0;
    float tempLamda2 = 0.0;
    float tempLamda3 = 0.0;
    

    for(int i = startHeight; i < endHeight + 1; i++)
    {
        for(int j = startWidth; j < endWidth + 1; j++)
        {
            pointVector.yComponent = float(i);
            pointVector.xComponent = float(j);
            convertedT3.calculateBaryCentricCoordinates(pointVector, tempLamda1, tempLamda2, tempLamda3);

            if(tempLamda3 >= 0 && tempLamda2 >= 0 && tempLamda1 >= 0)
            {
                if(T.v1.zComponent * tempLamda1 + T.v2.zComponent * tempLamda2 + T.v3.zComponent * tempLamda3 < getDepthPixel(j, i))
                {
                    setColorPixel(j, i, T.c1 * tempLamda1 + T.c2 * tempLamda2 + T.c3 * tempLamda3);
                    setDepthPixel(j, i, T.v1.zComponent * tempLamda1 + T.v2.zComponent * tempLamda2 + T.v3.zComponent * tempLamda3);
                }
            }
        }
    }
}

void Raster::drawModel(Model m)
{
    for(int i =0; i< m.numTriangles(); i++) {
        drawTriangle3D_Barycentric(m[i]);
    }

        
}




