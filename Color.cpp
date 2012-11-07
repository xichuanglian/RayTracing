#include "Color.h"
#include "ImageWrapper.h"

const Color Color::BLACK(0,0,0);
const Color Color::WHITE(255,255,255);

Color::Color(){
    color.r = 0;
    color.g = 0;
    color.b = 0;
}

Color::Color(float r, float g, float b){
    color.r = r;
    color.g = g;
    color.b = b;
}

void Color::setColor(RgbPixel& p){
    p.r = color.r;
    p.g = color.g;
    p.b = color.b;
}

void Color::setColor(RgbPixel& p, float f){
    p.r = color.r * f;
    p.g = color.g * f;
    p.b = color.b * f;
}

Color Color::mixColor(const Color& nc, float f) const{
    Color re(*this);
    re.color.r = (1-f) * re.color.r + f * nc.color.r;
    re.color.g = (1-f) * re.color.g + f * nc.color.g; 
    re.color.b = (1-f) * re.color.b + f * nc.color.b; 
    return re;
}

Color Color::operator *(float f) const {
    Color re(*this);
    if (f < 1) {
        re.color.r *= f;
        re.color.g *= f;
        re.color.b *= f;
    }
    return re;
}

Color Color::operator +(const Color& c) const {
    return Color(color.r + c.color.r, color.g + c.color.g, color.b + c.color.b);
}