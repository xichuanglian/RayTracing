/* 
 * File:   Ball.h
 * Author: weida
 *
 * Created on 2012年10月30日, 下午8:17
 */

#ifndef BALL_H
#define	BALL_H

#include "Object.h"
#include "Color.h"
#include <opencv2/opencv.hpp>

#define PI 3.141592653589793

class Ball : public Object {
public:
    float intersect(const Ray&);
    Vector normalAt(const Vector&);
    Color diffuseColorAt(const Vector& pos, const Vector& light);
    Color baseColorAt(const Vector& pos);
    float highlightAt(const Vector& pos, const Vector& light, const Ray& ray);
    std::map<Ray*,float>* newRaysAt(const Vector& pos, const Ray& ray);
    Ball(Vector _c, float _r);
    Vector center;
    float radius;
    Color color;
    IplImage* texture;
};

#endif	/* BALL_H */

