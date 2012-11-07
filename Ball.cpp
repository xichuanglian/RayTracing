#include <cmath>
#include "Ball.h"

Ball::Ball(Vector _c, float _r) : center(_c), color(255,255,255){
    radius = _r;
    BASE_FACTOR = 0.1;
    DIFFUSE_FACTOR = 0.8;
    REFLECT_FACTOR = 0.3;
    REFRECT_FACTOR = 0;
    texture = 0;
}

float Ball::intersect(const Ray& ray){
    Vector l = center - ray.start;
    float tp = l * ray.direction;
    if (tp <= 0) return INFINITE_T;
    float dd = l * l - tp * tp;
    if (dd >= radius * radius) return INFINITE_T;
    float t = sqrt(radius * radius - dd);
    if (l * l > radius * radius) t = tp - t;
    else t = tp + t;
    return t;
}

Vector Ball::normalAt(const Vector& pos){
    return (pos - center).unit();
}

Color Ball::baseColorAt(const Vector& pos){
    if (texture == 0) {
        return color;
    } else {
        RgbImage img(texture);
        Vector p = (pos - center).unit();
        Vector z(0,0,1);
        Vector x(1,0,0);
        int a = texture->height * acos(p * z) / PI;
        int b = texture->width * acos(p * x) / PI;
        return Color(img[a][b].r, img[a][b].g, img[a][b].b);
    }
}

Color Ball::diffuseColorAt(const Vector& pos, const Vector& light){
    Vector n = pos - center;
    Vector p = light - pos;
    float f = n.unit() * p.unit();
    Color re = Color::BLACK;
    if (f > 0){
        re = baseColorAt(pos) * f;
    }
    /*p = light - center;
    n = Vector(0,0,1);
    f = p.unit() * n.unit();*/
    return re;
}

float Ball::highlightAt(const Vector& pos, const Vector& light, const Ray& ray){
    Vector n = normalAt(pos);
    Vector l = pos - light;
    l = l.mirror(n);
    float f = l.unit() * ray.direction;
    if (f > 0) {
        f = pow(f,15);
        //f /= l.unit() * n;
        
        return f;
    } else return 0;
}

std::map<Ray*,float>* Ball::newRaysAt(const Vector& pos, const Ray& ray){
    std::map<Ray*,float>* re = new std::map<Ray*,float>();
    
    Vector n = normalAt(pos);
    Vector l = Vector(0,0,0) - ray.direction.mirror(n);
    re->insert(std::pair<Ray*,float>(new Ray(pos,l), REFLECT_FACTOR));
    
    if (REFRECT_FACTOR > 0){
        Ray r(ray);
        //r.start = r.start + r.direction * EPSILON;
        Vector l = r.start - center;
        if (l*l < radius * radius){ // the ray is in the ball
            l = r.direction.refrect(n, REFRECT_RATE);   
        }
        else { // the ray is out of the ball
            l = r.direction.refrect(n, 1 / REFRECT_RATE);
        }
        re->insert(std::pair<Ray*,float>(new Ray(pos,l), REFRECT_FACTOR));
    }
    
    return re;
}