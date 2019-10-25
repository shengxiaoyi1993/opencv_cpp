#include <iostream>
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/core.hpp"
#include<vector>
#include<fstream>
#include <stdlib.h>
#include<stdlib.h>
#include"basic.h"

//#define DEBUG
using namespace std;
using namespace cv;

int main()
{
    Mat mat_tmp=imread("../../../resource/thumb.jpg",IMREAD_REDUCED_COLOR_2);
    imshow("mat_tmp",mat_tmp);

    basic::printMatInfo(mat_tmp);
    Mat image_hsv;

//    cvtColor(mat_tmp, image_hsv, CV_RGB2HSV);
//    imshow("image_hsv",image_hsv);

    basic::showMatTransform(mat_tmp);




    waitKey(0);

    return 0;
}


