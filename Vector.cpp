/* 
 * File:   Vector.cpp
 * Author: weida
 * 
 * Created on 2012年10月30日, 下午9:37
 */

#include "Vector.h"
#include <cmath>
#include <cstdlib>

Vector::Vector(float _x, float _y, float _z){
    x = _x;
    y = _y;
    z = _z;
}

float Vector::operator *(const Vector& v) const{
    return x * v.x + y * v.y + z * v.z;
}

Vector Vector::operator *(const float& f) const{
    return Vector(x * f, y * f, z * f);
}

Vector Vector::operator +(const Vector& v) const{
    return Vector(x + v.x, y + v.y, z + v.z);
}

Vector Vector::operator -(const Vector& v) const{
    return Vector(x - v.x, y - v.y, z - v.z);
}

Vector Vector::outer_product(const Vector& v) const{
    float a = y * v.z - z * v.y;
    float b = z * v.x - x * v.z;
    float c = x * v.y - y * v.x;
    return Vector(a,b,c);
}

float Vector::length() const{
    return sqrt(x * x + y * y + z * z);
}

Vector Vector::unit() const{
    float l = length();
    return Vector(x/l, y/l, z/l);
}

Vector Vector::orthornal() const{
    Vector rv = Vector::randomVector();
    return outer_product(rv).unit();
}

Vector Vector::mirror(const Vector& n) const {
    Vector l(*this);
    Vector orthornal = l.outer_product(n);
    Vector parallel = orthornal.outer_product(n).unit();
    float a = n * l;
    float b = l * parallel;
    return n * a - parallel * b;
}

Vector Vector::refrect(const Vector& _n, float r) const {
    Vector i = unit();
    Vector n = _n.unit();
    Vector m = outer_product(n).unit();
    Vector l = n.outer_product(m).unit();
    
    float a = i * l;
    float b = a * r;
    float c = i * n;
    float s = 1;
    if (c < 0) s = -1;
    
    if (b >= 1 && b <= -1) {
        return mirror(_n) * (-1);
    }
    else{
        c = sqrt(1 - b*b) * s;
        return l * b + n * c;
    }
}

Vector Vector::randomVector(){
    float x = (rand() - 16384) / 32767.0;
    float y = (rand() - 16384) / 32767.0;
    float z = (rand() - 16384) / 32767.0;
    return Vector(x,y,z);
}