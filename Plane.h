/* 
 * File:   Plane.h
 * Author: weida
 *
 * Created on 2012年10月31日, 下午3:37
 */

#ifndef PLANE_H
#define	PLANE_H

#include "Vector.h"
#include "Object.h"
#include "Color.h"

class Plane : public Object{
public:
    Vector normal;
    Vector direction;
    float distance;
    
    Plane(const Vector&, const Vector&, float);
    float intersect(const Ray&);
    Vector normalAt(const Vector&);
    Color baseColorAt(const Vector& pos);
    Color diffuseColorAt(const Vector& pos, const Vector& light);
    float highlightAt(const Vector& pos, const Vector& light, const Ray& ray);
    std::map<Ray*,float>* newRaysAt(const Vector& position, const Ray&);
};

#endif	/* PLANE_H */

