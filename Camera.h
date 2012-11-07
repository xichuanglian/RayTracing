/* 
 * File:   Camera.h
 * Author: weida
 *
 * Created on 2012年10月30日, 下午10:40
 */

#ifndef CAMERA_H
#define	CAMERA_H

#include <opencv2/opencv.hpp>
#include "Vector.h"
#include "Scene.h"

#define MIN_FACTOR 0.1
#define SHADE_FACTOR 0.8

class Camera{
public:
    Camera();
    Vector position;
    Vector direction;
    Vector top;
    float distance;
    float width;
    float height;
    
    void rayTracing(IplImage* img, const Scene&);
    static float gaussDist(int x, int y);
    
private:
    Color traceRay(const Scene&, const Ray&, float);
    Color traceRayV2(const Scene&, const Ray&, float);
    
    static const float gaussMat[7][7];
};

#endif	/* CAMERA_H */

