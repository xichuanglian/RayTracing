#include <cmath>
#include <opencv2/opencv.hpp>
#include <iostream>
#include "Scene.h"
#include "Ball.h"
#include "Plane.h"
#include "Camera.h"
#include "ImageWrapper.h"

using namespace std;

Scene::Scene() : light(200,-100,400){
    GLOBAL_LIGHT = 0.1;
    
    Vector c(200,0,0);
    Ball* ball = new Ball(c,40);
    ball->color.color.r = 0;
    ball->texture = cvLoadImage("texture/wood.jpg");
    objList.push_back(ball);
    
    c = Vector(350,80,0);
    ball = new Ball(c,40);
    ball->REFLECT_FACTOR = 0.9;
    ball->DIFFUSE_FACTOR = 0.4;
    ball->color.color.g = 0;
    objList.push_back(ball);
    
    c = Vector(100,0,0);
    ball = new Ball(c,40);
    ball->REFLECT_FACTOR = 0.04;
    ball->REFRECT_FACTOR = 0.95;
    ball->REFRECT_RATE = 1.4;
    ball->DIFFUSE_FACTOR = 0.01;
    objList.push_back(ball);
    
    Vector fc(0,0,1);
    Plane* floor = new Plane(fc,Vector(0,1,0),-100);
    objList.push_back(floor);
}

Scene::~Scene(){
    vector<Object*>::iterator iter;
    for (iter = objList.begin(); iter != objList.end(); ++iter){
        delete *iter;
    }
}

float Scene::intersect(const Ray& r, Object*& obj) const{
    vector<Object*>::const_iterator iter;
    float min_t = INFINITE_T;
    obj = 0;
    for (iter = objList.begin(); iter != objList.end(); ++iter){
        float t = (*iter)->intersect(r);
        if (t < min_t) {
            min_t = t;
            obj = *iter;
        }
    }
    return min_t;
}

float Scene::shade(const Vector& p) const{
    // soft shadow
    Vector n = (light - p).unit();
    Vector m = n.orthornal();
    Vector l = m.outer_product(n).unit();
    vector<Object*>::const_iterator iter;
    
    float re = 0;
    float fsum = 0;
    for (int i = -2; i < 3; ++i){
        for (int j = -2; j < 3; ++j){
            float f = Camera::gaussDist(i,j);
            fsum += f;
            Vector newLight = light + m * (i * LIGHT_RADIUS) + l * (j * LIGHT_RADIUS);
            Ray r(p,newLight-p);
            r.start = r.start + r.direction * EPSILON;
            for (iter = objList.begin(); iter != objList.end(); ++iter) {
                if ((*iter)->intersect(r) < INFINITE_T) {
                    re += f;
                    break;
                }
            }
        }
    }
    
    return re / fsum;
}

float Scene::lightFactor(const Ray& ray) const{
    Vector l = (light - ray.start).unit();
    float f = l * ray.direction;
    f = pow(f, 50);
    if (f < 0.99) return 0;
    else return f;
}

float Scene::intersect_light(const Ray& ray) const{
    Vector l = light - ray.start;
    float f = l * ray.direction;
    if (f < 0.99) return INFINITE_T;
    else return l.length();
}