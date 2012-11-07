/* 
 * File:   Vector.h
 * Author: weida
 *
 * Created on 2012年10月30日, 下午9:37
 */

#ifndef VECTOR_H
#define	VECTOR_H

class Vector{
public:
    float x;
    float y;
    float z;
    Vector(float,float,float);
    float operator*(const Vector& v) const;
    Vector operator*(const float& f) const;
    Vector operator+(const Vector& v) const;
    Vector operator-(const Vector& v) const;
    Vector outer_product(const Vector& v) const;
    float length() const;
    Vector unit() const;
    Vector orthornal() const;
    Vector mirror(const Vector& n) const;
    Vector refrect(const Vector& n, float r) const;
    static Vector randomVector();
};

#endif	/* VECTOR_H */

