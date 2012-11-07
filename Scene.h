/* 
 * File:   Scene.h
 * Author: weida
 *
 * Created on 2012年10月31日, 下午8:54
 */

#ifndef SCENE_H
#define	SCENE_H

#include <vector>
#include "Object.h"

#define LIGHT_RADIUS 10

class Scene{
public:
    float GLOBAL_LIGHT;
    
    Scene();
    ~Scene();
    std::vector<Object*> objList;
    Vector light;
    float intersect(const Ray&, Object*&) const;
    float shade(const Vector&) const;
    float lightFactor(const Ray&) const;
    float intersect_light(const Ray&) const;
};

#endif	/* SCENE_H */

