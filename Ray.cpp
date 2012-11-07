#include <cmath>
#include "Ray.h"

Ray::Ray(const Vector& s,const Vector& d) : start(s),direction(d.unit()){
    
}

Vector Ray::pointAt(float t) const{
    float x = direction.x;
    float y = direction.y;
    float z = direction.z;
    return Vector(start.x + t * x, start.y + t * y, start.z + t * z);
}