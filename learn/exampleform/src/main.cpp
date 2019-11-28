#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/core.hpp"
#include"../../basic/src/basic.h"
#include<iostream>
#include<string>

using namespace std;
using namespace cv;

int g_switch_value = 0;
void switch_callback(int position);

void  switch_off_function(){
  std::cout<<"stitch off"<<std::endl;
}

void switch_on_function(){
  std::cout<<"stitch on"<<std::endl;
}

// void callback_add(int state, void* userData){
//   cout<<__func__<<"state:"<<state<<endl;
//
// }
// void callback_sub(int state, void* userData){
//   cout<<__func__<<"state:"<<state<<endl;
//
// }

int main(int argc,char** argv)
{
    cvNamedWindow("Example3_7",CV_WINDOW_NORMAL);
    cvCreateTrackbar("bar","Example3_7",&g_switch_value,360,switch_callback);
    // createButton("Add", callback_add, NULL, QT_PUSH_BUTTON, 0);
    // createButton("Sub", callback_sub, NULL, QT_PUSH_BUTTON, 0);
    cvWaitKey(0);
    return 0;
}


void switch_callback(int position)
{
  std::cout<<"position: "<<position<<std::endl;
  cout<<g_switch_value<<endl;

  string path_testimage="/home/sxy/Github/opencv_cpp/resource/2_3_609.jpg";
  Mat mat_test=imread(path_testimage,IMREAD_GRAYSCALE);
  resize(mat_test,mat_test,Size2i(1024,512));
  cout<<mat_test.cols<<endl;
  cout<<mat_test.rows<<endl;
  int value_threshold=static_cast<int>(1.0*256*position/100);
  cout<<"value_threshold:"<<value_threshold<<endl;
  // threshold(mat_test,mat_test,value_threshold,255,CV_THRESH_BINARY_INV);
  Mat mat_dst=basic::rotateAndCutImage(mat_test,position);

  imshow("Example3_7",mat_dst);


     if(position == 0)
     {
          switch_off_function();
     }
     else
     {
          switch_on_function();
     }
}
