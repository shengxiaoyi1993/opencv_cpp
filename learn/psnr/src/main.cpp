#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include<string>
#include<vector>
#include <opencv2/features2d/features2d.hpp>
#include<math.h>
#include "dct.h"
// #include <opencv2/nonfree/nonfree.hpp>

using namespace std;
using namespace cv;

double getPSNR(const Mat& I1, const Mat& I2)
{
    Mat s1;
    absdiff(I1, I2, s1);       // |I1 - I2|AbsDiff函数是 OpenCV 中计算两个数组差的绝对值的函数
    s1.convertTo(s1, CV_32F);  // 这里我们使用的CV_32F来计算，因为8位无符号char是不能进行平方计算
    s1 = s1.mul(s1);           // |I1 - I2|^2

    Scalar s = sum(s1);         //对每一个通道进行加和

    double sse = s.val[0] + s.val[1] + s.val[2]; // sum channels

    if( sse <= 1e-10) // 对于非常小的值我们将约等于0
        return 0;
    else
    {
        double  mse =sse /(double)(I1.channels() * I1.total());//计算MSE
        double psnr = 10.0*log10((255*255)/mse);
        return psnr;//返回PSNR
    }
}

void calCoefficent(){
  double Pi=3.1415926;
  double k=1;
  double n=1;
  double a=k*cos(n*Pi/16);
  double b=k*sin(n*Pi/16);
cout<<"k: "<<k<<" n: "<<n<<" a: "<<a<<" b: "<<b<<endl;

k=1;
n=3;
 a=k*cos(n*Pi/16);
 b=k*sin(n*Pi/16);
cout<<"k: "<<k<<" n: "<<n<<" a: "<<a<<" b: "<<b<<endl;

k=sqrt(2);
n=6;
 a=k*cos(n*Pi/16);
 b=k*sin(n*Pi/16);
cout<<"k: "<<k<<" n: "<<n<<" a: "<<a<<" b: "<<b<<endl;

}

//32  f
//30  int

int main(int argc, const char * argv[]) {
 //
  string path_image_src="/home/sxy/Work/jpeg_encoder/edge_black_white.bmp";
  string path_image_compress="/home/sxy/Work/jpeg_encoder/out.jpg";
  Mat image_src=imread(path_image_src,IMREAD_GRAYSCALE);
  Mat image_compress=imread(path_image_compress,IMREAD_GRAYSCALE);

 int psnr=getPSNR(image_src,image_compress);
 cout<<"psnr:"<<psnr<<endl;
 // calCoefficent();
 //
 //
 // // //一维dct变换测试
 // int max_src[8]={67,68,36,73,104,103,107,127};
 // int max_dst[8]={0};
 // init(10);
 // // // dctTransform_8_1(max_src,max_dst);
 // // //
 // // // printf("%s\n","print mat_src: " );
 // // // for(int i=0;i<8;i++){
 // // //   printf("%d ",max_dst[i] );
 // // // }
 // //
 //
 //
 // // // 一维dct变换测试
 // dctTransform_8_1_withfloat(max_src,max_dst);
 // printf("%s\n","print mat_src: " );
 // for(int i=0;i<8;i++){
 //   printf("%d ",max_dst[i] );
 // }
 //
 //
 //
 //
 //

//
// // 二维dct变换测试
//  init(10);
// // int input[64]= {67,68,36,73,104,103,107,127,78,78,78,97,103,103,104,
// //   110,103,103,103,103,103,103,103,103,103,103,103,103,
// //   103,103,103,103,103,103,103,103,103,103,103,103,103,
// //   103,103,103,103,103,103,103,103,103,103,103,103,103,
// //   103,103,103,103,103,103,103,103,103,103};
// int M[64] = {
// // 0x2E, 0x30, 0xF8, 0xCD, 0xC3, 0xBB, 0xB6, 0xAC,
// 0x52, 0x52, 0x53, 0x54, 0x57, 0x57, 0x55, 0x54,
// 0x52, 0x52, 0x53, 0x54, 0x56, 0x56, 0x54, 0x54,
// 0x53, 0x53, 0x53, 0x53, 0x53, 0x53, 0x53, 0x53,
// 0x53, 0x53, 0x53, 0x53, 0x53, 0x53, 0x53, 0x53,
// 0x53, 0x53, 0x53, 0x53, 0x53, 0x53, 0x54, 0x54,
// 0x53, 0x53, 0x53, 0x53, 0x53, 0x53, 0x54, 0x54,
// 0x53, 0x53, 0x53, 0x53, 0x52, 0x52, 0x53, 0x54,
// 0x53, 0x53, 0x53, 0x53, 0x52, 0x52, 0x53, 0x53};
//
//    int max_dst[64]={0};
//    dctTransform_64_2_with_flost(M,max_dst);
//
//     printf("%s\n","print max_dst: " );
//     for(int i=0;i<64;i++){
//       printf("%d ",max_dst[i] );
//     }
//


    return 0;
}


// 0
// f direct 48
// f 47
// i 47


// 2
// f direct
// f 47
//  i 47
// 50
// f direct 48
// f 30
// i 30
