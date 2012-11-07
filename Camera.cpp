#include <opencv2/opencv.hpp>
#include "Camera.h"
#include "Vector.h"
#include "Ball.h"
#include "Plane.h"
#include <ctime>
#include "Scene.h"
#include "ImageWrapper.h"

const float Camera::gaussMat[7][7] = {{0.00000067, 0.00002292, 0.00019117, 0.00038771, 0.00019117, 0.00002292, 0.00000067},
                                {0.00002292, 0.00078633, 0.00655965, 0.01330373, 0.00655965, 0.00078633, 0.00002292},
                                {0.00019117, 0.00655965, 0.05472157, 0.11098164, 0.05472157, 0.00655965, 0.00019117},
                                {0.00038771, 0.01330373, 0.11098164, 0.22508352, 0.11098164, 0.01330373, 0.00038771},
                                {0.00019117, 0.00655965, 0.05472157, 0.11098164, 0.05472157, 0.00655965, 0.00019117},
                                {0.00002292, 0.00078633, 0.00655965, 0.01330373, 0.00655965, 0.00078633, 0.00002292},
                                {0.00000067, 0.00002292, 0.00019117, 0.00038771, 0.00019117, 0.00002292, 0.00000067}};

Camera::Camera() : position(-48,0,0), direction(1,0,0), top(0,0,1){
    distance = 48;
    width = 64;
    height = 48;
}

void Camera::rayTracing(IplImage* img, const Scene& scene){
    Vector h = top.outer_product(direction);
    RgbImage imgA(img);
    for (int i = 0; i < img->width; ++i)
        for (int j = 0; j < img->height; ++j){
            float hx = img->width / 2.0;
            float hy = img->height / 2.0;
            float li = width * (i - hx)/ img->width;
            float lj = height * (j -  hy)/ img->height;
            Vector p = direction.unit() * distance + h.unit() * li + top.unit() * lj;
            Ray ray(position, p);
            
            traceRay(scene,ray,1).setColor(imgA[img->height - j][i]);
        }
    for (int i = 0; i < img->width; ++i)
        for (int j = 0; j < img->height; ++j){
            float r,g,b;
            r = g = b = 0;
            int m = i - 2 > 0 ? i - 2 : 0;
            int n = i + 3 < img->width ? i + 3 : img->width;
            int x = j - 2 > 0 ? j - 2 : 0;
            int y = j + 3 < img->height ? j + 3 : img->height;
            float fsum = 0;
            for (int ii = m; ii < n; ++ii)
                for (int jj = x; jj < y; ++jj){
                    float f = gaussDist(ii-i, jj-j);
                    fsum += f;
                    r += imgA[img->height - jj][ii].r * f;
                    g += imgA[img->height - jj][ii].g * f;
                    b += imgA[img->height - jj][ii].b * f;
                }
            imgA[img->height - j][i].r = r / fsum;
            imgA[img->height - j][i].g = g / fsum;
            imgA[img->height - j][i].b = b / fsum;
        }
    cvShowImage("test",img);
}

Color Camera::traceRay(const Scene& scene, const Ray& ray, float factor){
    Object* obj;
    float t = scene.intersect(ray,obj);
    Color finalColor = Color::BLACK;
    if (t < INFINITE_T){
        Vector p = ray.pointAt(t);
        Color baseColor = obj->baseColorAt(p);
        Color diffuseColor = obj->diffuseColorAt(p, scene.light) * obj->DIFFUSE_FACTOR;
        
        Color newColor;
        float fsum = 0;
        if (factor > MIN_FACTOR){
            std::map<Ray*,float>* newRays = obj->newRaysAt(p,ray);
            std::map<Ray*,float>::iterator iter = newRays->begin();
            
            while (iter != newRays->end()){
                float f = iter->second;
                fsum += f;
                Ray* r = iter->first;
                r->start = r->start + r->direction * EPSILON;
                newColor = newColor + traceRay(scene, *r, factor * f) * f;
                delete r;
                ++iter;
            }
            delete newRays;
        }
        newColor = baseColor.mixColor(newColor, fsum);
        
        //finalColor = newColor * fsum + diffuseColor * obj->DIFFUSE_FACTOR;
        finalColor = diffuseColor.mixColor(Color::BLACK, SHADE_FACTOR * scene.shade(p));
        finalColor = finalColor.mixColor(baseColor, scene.GLOBAL_LIGHT);
        finalColor = finalColor.mixColor(newColor, 1 - obj->DIFFUSE_FACTOR);
        finalColor = finalColor.mixColor(Color::WHITE, obj->highlightAt(p,scene.light,ray)*obj->REFLECT_FACTOR);
        //finalColor = baseColor;
        
    }
    
    return finalColor;
}

Color Camera::traceRayV2(const Scene& scene, const Ray& ray, float factor){
    if (factor > 0.9) {
        Vector n = ray.direction;
        Vector m = n.orthornal();
        Vector l = m.outer_product(n).unit();
        Color re = Color::BLACK;
        for (int i = 0; i < 5; ++i){
            float a = (random() - 16384) / 327670.0;
            float b = (random() - 16384) / 327670.0;
            Vector nd = ray.pointAt(10000000) + m * a + l * b; 
            Ray r(ray.start, nd - ray.start);
            re = re + traceRay(scene, r, factor) * 0.2;
        }
        return re;
    }
    else return traceRay(scene, ray, factor);
}

float Camera::gaussDist(int x, int y){
    float f = gaussMat[x+3][y+3];
    return f;
}