#include "ImageWrapper.h"
#include <cmath>
#include "Plane.h"
#include "Ray.h"

Plane::Plane(const Vector& n, const Vector& di, float d) : normal(n.unit()), direction(di.unit())  {
    distance = d;
    BASE_FACTOR = 0.3;
    DIFFUSE_FACTOR = 0.8;
    REFLECT_FACTOR = 0.9;
}

float Plane::intersect(const Ray& r){
    float nr = normal * r.direction;
    if (std::abs(nr) <= 0.05) return INFINITE_T; // nearly parallel
    float np = normal * (r.start + r.direction * EPSILON) - distance;
    float t = - np / nr;
    if (t > 0) {
        return t;
    } else return INFINITE_T;
}

Vector Plane::normalAt(const Vector& pos){
    return normal;
}

Color Plane::baseColorAt(const Vector& p){
    Color c1,c2;
    c1.color.r = 155;
    c1.color.g = 255;
    c1.color.b = 70;
    c2.color.r = 100;
    c2.color.g = 50;
    c2.color.b = 255;
    Color re;
    Vector pos(p);
    if (pos * normal - distance > 0.05) return re;
    Vector original = normal * distance;
    pos = pos - original;
    float x = pos * direction;
    float y = pos * direction.outer_product(normal);
    bool b1 = ((int)std::abs(x)/40) % 2 == ((int)std::abs(y)/40) % 2;
    bool b2 = x * y > 0;
    if (b1 ^ b2){
        c1.setColor(re.color);
    } else {
        c2.setColor(re.color);
    }
    return re;
}

Color Plane::diffuseColorAt(const Vector& pos, const Vector& light){
    float f = normal * (light - pos).unit();
    return baseColorAt(pos) * f;
}

float Plane::highlightAt(const Vector& pos, const Vector& light, const Ray& ray){
    Vector n = normalAt(pos);
    Vector l = pos - light;
    l = l.mirror(n);
    float f = l.unit() * ray.direction;
    if (f > 0) {
        f = pow(f,300);
        //f /= l.unit() * n;
        
        return f;
    } else return 0;
}

std::map<Ray*,float>* Plane::newRaysAt(const Vector& pos, const Ray& ray){
    std::map<Ray*,float>* re = new std::map<Ray*,float>();
    
    Vector n = normalAt(pos);
    Vector l = Vector(0,0,0) - ray.direction.mirror(n);
    re->insert(std::pair<Ray*,float>(new Ray(pos,l), REFLECT_FACTOR));
    
    return re;
}