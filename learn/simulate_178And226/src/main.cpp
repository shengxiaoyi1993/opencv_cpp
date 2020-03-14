
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include<string>
#include<vector>
#include <opencv2/features2d/features2d.hpp>
#include <iostream>

using namespace std;
using namespace cv;

 int main(void) {


     //input image

     string path_image="/home/sxy/Github/opencv_cpp/learn/"
                       "simulate_178And226/resources/0_110.jpg";

     Mat mat=imread(path_image,IMREAD_GRAYSCALE);


  return 0;
}
