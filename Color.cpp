#include "Color.h"
#include <iostream>
using namespace std;

Color::Color()
{
    red = 1.0;
    blue = 1.0;
    green = 1.0;
    alpha = 0.0;
}

Color::Color(float pRed, float pGreen, float pBlue, float pAlpha)
{
    red = pRed;
    green = pGreen;
    blue = pBlue;
    alpha = pAlpha;
    clamp();
}

void Color::clamp()
{
    if(red > 1.0)
    {
        red = 1.0;
    }
    if(red < 0)
    {
        red = 0;
    }
    if(blue > 1.0)
    {
        blue = 1.0;
    }
    if(blue < 0)
    {
        blue = 0;
    }
    if(green > 1.0)
    {
        green = 1.0;
    }
    if(green < 0)
    {
        green = 0;
    }
    if(alpha > 1.0)
    {
        alpha = 1.0;
    }
    if(alpha < 0)
    {
        alpha = 0;
    }
}

Color Color::operator+(const Color& c)
{
    Color temp;
    temp.alpha = this->alpha + c.alpha;
    temp.blue = this->blue + c.blue;
    temp.red = this->red + c.red;
    temp.green = this->green + c.green;
    temp.clamp();
    return temp;
}

Color Color::operator-(const Color& c)
{
    Color temp;
    temp.alpha = this->alpha - c.alpha;
    temp.blue = this->blue - c.blue;
    temp.red = this->red - c.red;
    temp.green = this->green - c.green;
    temp.clamp();
    return temp;
}

 Color Color::operator*(const float& c)
 {
    Color temp;
    temp.alpha = this->alpha * c;
    temp.blue = this->blue * c;
    temp.red = this->red * c;
    temp.green = this->green * c;
    temp.clamp();
    return temp;
 }