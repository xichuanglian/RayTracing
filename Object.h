/* 
 * File:   Object.h
 * Author: htc
 *
 * Created on 2012年10月30日, 下午8:03
 */

#ifndef OBJECT_H
#define	OBJECT_H

#include "Ray.h"
#include "Color.h"
#include "Vector.h"
#include <map>

class Object {
public:
    float BASE_FACTOR;
    float DIFFUSE_FACTOR;
    float REFLECT_FACTOR;
    float REFRECT_FACTOR;
    float REFRECT_RATE;
    virtual float intersect(const Ray&) = 0;
    virtual Vector normalAt(const Vector&) = 0;
    virtual Color baseColorAt(const Vector& position) = 0;
    virtual Color diffuseColorAt(const Vector& position, const Vector& light) = 0;
    virtual float highlightAt(const Vector& position, const Vector& light, const Ray& i_ray) = 0;
    virtual std::map<Ray*,float>* newRaysAt(const Vector& position, const Ray& ray) = 0;
};

#endif	/* OBJECT_H */

