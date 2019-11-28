#include <iostream>
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/core.hpp"
#include<vector>
#include<fstream>
#include <stdlib.h>
#include<stdlib.h>
#include<bits/stdc++.h>
#include"basic.h"


using namespace std;
using namespace cv;

void meanStdDev_test()
{
    const char* imagename = "/home/sxy/Work/data/runway/dalu_airport/day2/dir_vig/1_1_145.jpg";
    //产生灰度图
    Mat img = imread(imagename,IMREAD_GRAYSCALE);
    Mat gray,color;
    cvtColor(img, gray, CV_RGB2GRAY);
    cout << "Channel: " << gray.channels() << endl;

    Mat tmp_m, tmp_sd;
    double m = 0, sd = 0;

    m = mean(gray)[0];
    cout << "Mean: " << m << endl;

    meanStdDev(gray, tmp_m, tmp_sd);
    m = tmp_m.at<double>(0,0);
    sd = tmp_sd.at<double>(0,0);
    cout << "Mean: " << m << " , StdDev: " << sd << endl;
}



int main(int argc, char *argv[])
{

	meanStdDev_test();

	// waitKey(0);
	return 0;
}
