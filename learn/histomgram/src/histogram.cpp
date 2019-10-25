#include "histogram.h"
#include<iostream>
#include "../../basic/src/basic.h"

using namespace std;
using namespace cv;
namespace histogram {

Mat printHistogram(const Mat array,Size size){
 Mat table;
    vector<int> list_value=basic::getMaxValueList(array);

    if(list_value.size()!=1){
        return table;

    }
    int max_height=list_value[0]+1;
     table = Mat::zeros(Size(256,max_height),CV_8UC1);
     cout<<"table.size:"<<table.size<<endl;

    for(int c =0;c<256;c++) {
      for(int r = 0;r<array.at<int>(0,c);r++) {
          table.at<uchar>(max_height-r,c)=255;
      }
     }
    Mat mat_resize;
    cv::resize(table,mat_resize,size);

    return mat_resize;
}



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


}
