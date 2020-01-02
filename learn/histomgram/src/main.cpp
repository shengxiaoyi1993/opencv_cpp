#include <iostream>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include<vector>
#include<fstream>
#include <stdlib.h>
#include<stdlib.h>
#include"histogram.h"
#include"../../basic/src/basic.h"




//#define DEBUG
using namespace std;
using namespace cv;



int main()
{


    Mat src = imread("../../../resource/circle_detect.jpg",IMREAD_GRAYSCALE);
    cout<<src.size()<<endl;
    imshow("src",src);


    Mat mat_histogram=histogram::calcGrayHist(src);
    basic::printMatNum(mat_histogram);

    Mat mat_histogram_resize=histogram::printHistogram(mat_histogram,Size(512,1024));
    imshow("mat_histogram_resize",mat_histogram_resize);


    waitKey(0);

    return 0;
}
