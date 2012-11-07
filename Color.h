/* 
 * File:   Color.h
 * Author: htc
 *
 * Created on 2012年10月31日, 下午4:17
 */

#ifndef COLOR_H
#define	COLOR_H

#include "ImageWrapper.h"

class Color{
public:
    Color();
    Color(float,float,float);
    void setColor(RgbPixel& p);
    void setColor(RgbPixel& p, float f);
    Color mixColor(const Color&, float f) const;
    Color operator*(float f) const;
    Color operator+(const Color&) const;
    RgbPixel color;
    const static Color BLACK;
    const static Color WHITE;
};

#endif	/* COLOR_H */

