#include <iostream>
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/core.hpp"
#include<vector>
#include<fstream>
#include <stdlib.h>
#include<stdlib.h>




//#define DEBUG
using namespace std;
using namespace cv;


Mat calcGrayHist(const Mat & image) {
   Mat histogram = Mat::zeros(Size(256,1),CV_32SC1);
   //256对应的是0~255共计256个像素值
   //注意，Size对应的是x和y，也就是第一个元数是矩阵的列数
   int rows = image.rows;
   //输入图像的行数
   int cols = image.cols;
   //输入图像的列数
   for(int r =0;r<rows;r++) {
     for(int c = 0;c<cols;c++) {
       int index = int(image.at<uchar>(r,c)); //获取每个点的像素值
       histogram.at<int>(0,index) +=1; //获取了一个像素值，在相应的位置上加1
     }
    }
  return histogram;
}

void printMatNum(const Mat image){
    cout<<"size:"<<image.size()<<endl;
    int rows = image.rows;
    //输入图像的行数
    int cols = image.cols;
    //输入图像的列数
    for(int r =0;r<rows;r++) {
      for(int c = 0;c<cols;c++) {
        int index = int(image.at<uchar>(r,c)); //获取每个点的像素值
        cout<<index<<" ";
      }
      cout<<endl;
     }
    cout<<endl<<endl;
}

Mat printHistogram(const Mat array){
    int cols=256;
    int rows=1000;

    Mat table = Mat::zeros(Size(cols,rows),CV_8UC1);

    for(int r =0;r<cols;r++) {
      for(int c = 0;c<array.at<int>(0,r);c++) {
          table.at<int>(r,c)=255;
          cout<<"h"<<array.at<int>(0,r)<<endl;
      }
     }


    return table;
}

int main()
{

    Mat src = imread("../../../resource/circle_detect.jpg");
    cout<<src.size()<<endl;
    imshow("src",src);


    Mat mat_histogram=calcGrayHist(src);
    printMatNum(mat_histogram);

    Mat mat_histogram_resize=printHistogram(mat_histogram);
    imshow("mat_histogram_resize",mat_histogram_resize);




    waitKey(0);

    return 0;
}
