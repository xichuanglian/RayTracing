#include <opencv2/opencv.hpp>
#include <iostream>
#include <ctime>
#include "Object.h"
#include "Ball.h"
#include "ImageWrapper.h"
#include "Camera.h"
#include "Scene.h"
using namespace std;

int main(){
    srand( (unsigned)time( NULL ) );
    
    IplImage* img = cvCreateImage(cvSize(640,480),IPL_DEPTH_8U,3);
    cvSet(img, cv::Scalar(0,0,0));
    
    cvNamedWindow("test", CV_WINDOW_AUTOSIZE);
    Camera camera;
    Scene scene;
    while (true){
        scene.light.x += 10;
        camera.rayTracing(img,scene);
        IplImage* save = cvCreateImage(cvSize(640,480),IPL_DEPTH_8U,3);
        cvCvtColor(img,save,CV_BGR2RGB);
        if (!cvSaveImage("output/preview.jpg",img)){
            cout << "can't save" << endl;
        }
        cvWaitKey(0);
    }
}
