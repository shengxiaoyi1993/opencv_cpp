#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include<string>
#include<vector>
#include <opencv2/features2d/features2d.hpp>
// #include <opencv2/nonfree/nonfree.hpp>

using namespace std;
using namespace cv;


int main(int argc, const char * argv[]) {
  string path_image2="/home/sxy/Work/svn/bs2_repo/runway_scan/runway_scan_sw/splitline_detect/build/splitimage/blockcut_0_2_29.jpg";
Mat mat2=imread(path_image2,IMREAD_GRAYSCALE);
std::cout << "/* message */" << mat2.size()<<'\n';



    return 0;
}
