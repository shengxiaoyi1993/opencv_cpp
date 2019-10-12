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

int testFT(){

    string filename="/home/sxy/Documents/20190902/2019_09_02_04_02/2019_09_02_04_02/2_1_53.jpg";
    Mat I = imread(filename, IMREAD_GRAYSCALE);
    if( I.empty())
        return -1;

    Mat padded;                            //expand input image to optimal size
    int m = getOptimalDFTSize( I.rows );
    int n = getOptimalDFTSize( I.cols ); // on the border add zero values
    copyMakeBorder(I, padded, 0, m - I.rows, 0, n - I.cols, BORDER_CONSTANT, Scalar::all(0));

    Mat planes[] = {Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F)};
    Mat complexI;
    merge(planes, 2, complexI);         // Add to the expanded another plane with zeros

    dft(complexI, complexI);            // this way the result may fit in the source matrix

    // compute the magnitude and switch to logarithmic scale
    // => log(1 + sqrt(Re(DFT(I))^2 + Im(DFT(I))^2))
    split(complexI, planes);                   // planes[0] = Re(DFT(I), planes[1] = Im(DFT(I))
    magnitude(planes[0], planes[1], planes[0]);// planes[0] = magnitude
    Mat magI = planes[0];

    magI += Scalar::all(1);                    // switch to logarithmic scale
    log(magI, magI);

    // crop the spectrum, if it has an odd number of rows or columns
    magI = magI(Rect(0, 0, magI.cols & -2, magI.rows & -2));

    // rearrange the quadrants of Fourier image  so that the origin is at the image center
    int cx = magI.cols/2;
    int cy = magI.rows/2;

    Mat q0(magI, Rect(0, 0, cx, cy));   // Top-Left - Create a ROI per quadrant
    Mat q1(magI, Rect(cx, 0, cx, cy));  // Top-Right
    Mat q2(magI, Rect(0, cy, cx, cy));  // Bottom-Left
    Mat q3(magI, Rect(cx, cy, cx, cy)); // Bottom-Right

    Mat tmp;                           // swap quadrants (Top-Left with Bottom-Right)
    q0.copyTo(tmp);
    q3.copyTo(q0);
    tmp.copyTo(q3);

    q1.copyTo(tmp);                    // swap quadrant (Top-Right with Bottom-Left)
    q2.copyTo(q1);
    tmp.copyTo(q2);

    normalize(magI, magI, 0, 1, NORM_MINMAX); // Transform the matrix with float values into a
    // viewable image form (float between values 0 and 1).

    imshow("Input Image"       , I   );    // Show the result
    imshow("spectrum magnitude", magI);

    //*逆向傅里叶变换
    Mat ifft;

    idft(complexI,ifft,DFT_REAL_OUTPUT);
    normalize(ifft,ifft,0,1,CV_MINMAX);
    imshow("ifft",ifft);

    waitKey();
return 0;
}


int testEdgeDetect(){

    Mat src = imread("/home/sxy/Documents/20190902/2019_09_02_04_02/2019_09_02_04_02/2_1_53.jpg");
    Mat src1 = src.clone();

    //显示原始图
    imshow("【原始图】Canny边缘检测", src);
    //转化为灰度图，减噪，然后用canny得到的边缘作为掩码，拷贝原图到效果图，得到彩色的边缘图
    Mat dst, edge, gray;

    //创建与src同类型和大小的矩阵
    dst.create(src1.size(), src1.type());

    //将原图像转换为灰度图像
    cvtColor(src1, gray, COLOR_BGR2GRAY);

    //使用3×3内核降噪
    blur(gray, edge, Size(3, 3));

    //使用canny算子
    Canny(edge, edge, 3, 9, 3);

    imshow("【效果图】Canny边缘检测1", edge);
    //将dstImage内所有元素为0
    dst = Scalar::all(0);

    //使用Canny算子输出的边缘图，g_cannyDetectedEdges作为掩码，来将原图g_srcImage拷贝到目标图g_dstImage中
    src1.copyTo(dst, edge);
    imshow("【效果图】Canny边缘检测2", dst);
    waitKey(0);
    return 0;

}

int testSobel(){

    Mat grad_x, grad_y;
    Mat abs_grad_x, abs_grad_y, dst;
    //载入图像
    Mat src = imread("/home/sxy/Documents/20190902/2019_09_02_04_02/2019_09_02_04_02/2_1_53.jpg");

    //显示原始图
    imshow("【原始图】sobel边缘检测", src);
    //求x方向梯度
    Sobel(src, grad_x, CV_16S, 1, 0, 3, 1, 1, BORDER_DEFAULT);
    convertScaleAbs(grad_x, abs_grad_x);
    imshow("【效果图】X方向Sobel", abs_grad_x);

    //求y方向梯度
    Sobel(src, grad_y, CV_16S, 0, 1, 3, 1, 1, BORDER_DEFAULT);
    convertScaleAbs(grad_y, abs_grad_y);
    imshow("【效果图】Y方向Sobel", abs_grad_y);

    //合并梯度（近似）
    addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, dst);
    imshow("【效果图】整体方向Sobel", dst);
    imwrite("edgedetect_sobel.jpg",dst);

    waitKey(0);
    return 0;

}



int main()
{

    Mat src = imread("/home/sxy/Documents/20190902/2019_09_02_04_02/2019_09_02_04_02/2_1_53.jpg");
    cout<<src.size()<<endl;

    return 0;
}
