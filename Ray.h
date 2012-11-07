/* 
 * File:   Ray.h
 * Author: weida
 *
 * Created on 2012年10月30日, 下午8:11
 */

#ifndef RAY_H
#define	RAY_H

#include "Vector.h"

#define INFINITE_T 99999999
#define EPSILON 0.01

class Ray{
public:
    Ray(const Vector&,const Vector&);
    Vector start;
    Vector direction;
    Vector pointAt(float) const;
};

#endif	/* TYPES_H */

