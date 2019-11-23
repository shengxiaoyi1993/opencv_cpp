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

int calMAD(const Mat mat1,const Mat mat2){
    Size size1=mat1.size();
    Size size2=mat2.size();

    if(size1 != size2){
        return -1;
    }
    else{
        double sum=0;
        for(int r=0;r<size1.height;r++){
            for(int c=0;c<size1.width;c++){
                sum+=abs(int(mat1.at<uchar>(r,c))-int(mat2.at<uchar>(r,c)));
            }
        }
        int mad=sum/(size1.height*size1.width);
        return mad;

    }

}

double calSSD(const Mat mat1,const Mat mat2){
    Size size1=mat1.size();
    Size size2=mat2.size();

    if(size1 != size2){
        return -1;
    }
    else{
        double sum=0;
        for(int r=0;r<size1.height;r++){
            for(int c=0;c<size1.width;c++){
                int div=(int(mat1.at<uchar>(r,c))-int(mat2.at<uchar>(r,c)));
                sum+=div*div;
            }
        }
//        double ssd=sum/(size1.height*size1.width);
        return sum;

    }

}

double calMSD(const Mat mat1,const Mat mat2){
    Size size1=mat1.size();
    Size size2=mat2.size();

    if(size1 != size2){
        return -1;
    }
    else{
        double sum=0;
        for(int r=0;r<size1.height;r++){
            for(int c=0;c<size1.width;c++){
                int div=(int(mat1.at<uchar>(r,c))-int(mat2.at<uchar>(r,c)));
                sum+=div*div;
            }
        }
        double ssd=sum/(size1.height*size1.width);
        return ssd;

    }

}

Rect findMostMatchWithMSD(const Mat mat_src,const Mat mat_part){
    Size size_src=mat_src.size();
    Size size_part=mat_part.size();
    int height_div=size_src.height-size_part.width;
    int width_div=size_src.width-size_part.width;
    double min_msd=65536;
    Rect rect_res=Rect(0,0,0,0);
    for(int r=0;r<height_div;r++){
        for(int c=0;c<width_div;c++){
            Rect rect_tmp=Rect(c,r,size_part.width,size_part.height);
            double tmp=calSSD(mat_src(rect_tmp),mat_part);
            if(min_msd>tmp){
                min_msd=tmp;
                rect_res=rect_tmp;
            }
        }
    }
    return rect_res;
}


//grayimage
Rect findMostMatchWithMAD(const Mat mat_src,const Mat mat_part){
    Size size_src=mat_src.size();
    Size size_part=mat_part.size();
    int height_div=size_src.height-size_part.width;
    int width_div=size_src.width-size_part.width;
    int min_mad=256;
    Rect rect_res=Rect(0,0,0,0);
    for(int r=0;r<height_div;r++){
        for(int c=0;c<width_div;c++){
            Rect rect_tmp=Rect(c,r,size_part.width,size_part.height);
            int tmp=calMAD(mat_src(rect_tmp),mat_part);
            if(min_mad>tmp){
                min_mad=tmp;
                rect_res=rect_tmp;
            }
        }
    }
    return rect_res;
}


Rect findMostMatchWithSSD(const Mat mat_src,const Mat mat_part){
    Size size_src=mat_src.size();
    Size size_part=mat_part.size();
    int height_div=size_src.height-size_part.width;
    int width_div=size_src.width-size_part.width;
    double min_ssd=65536;
    Rect rect_res=Rect(0,0,0,0);
    for(int r=0;r<height_div;r++){
        for(int c=0;c<width_div;c++){
            Rect rect_tmp=Rect(c,r,size_part.width,size_part.height);
            double tmp=calSSD(mat_src(rect_tmp),mat_part);
            if(min_ssd>tmp){
                min_ssd=tmp;
                rect_res=rect_tmp;
            }
        }
    }
    return rect_res;
}



int calMean(const Mat src){
//    cout<<"channels:"<<src.channels()<<endl;
    int value=(int)(mean(src)[0]);
    return value;
}

double calSD(const Mat mat_src){
    int mean=calMean(mat_src);
    int cols=mat_src.cols;
    int rows=mat_src.rows;
    double sum_sd=0;

    for(int r=0;r<rows;r++){
        for(int c=0;c<cols;c++){
            int tmp=(int(mat_src.at<uchar>(r,c))-mean);
            sum_sd+=tmp*tmp;
        }
    }
    return sum_sd;
}


double calCov(const Mat mat1,const Mat mat2){
    int cols=mat1.cols;
    int rows=mat1.rows;
    int mean1=calMean(mat1);
    int mean2=calMean(mat2);
    double sum_cov=0;
    for(int r=0;r<rows;r++){
        for(int c=0;c<cols;c++){
//            int tmp=(int(mat1.at<uchar>(r,c))-mean1);
            sum_cov+=abs(int(mat1.at<uchar>(r,c))-mean1)*abs(int(mat2.at<uchar>(r,c))-mean2);
        }
    }
    return sum_cov;

}

double calNCC(const Mat mat1,const Mat mat2){
    double sum_sd_1=calSD(mat1);
    double sum_sd_2=calSD(mat2);
    double sum_cov=calCov(mat1,mat2);
    return sum_cov/(sqrt(sum_sd_1)*sqrt(sum_sd_2));
}


Rect findMostMatchWithNCC(const Mat mat_src,const Mat mat_part){
    Size size_src=mat_src.size();
    Size size_part=mat_part.size();
    int height_div=size_src.height-size_part.width;
    int width_div=size_src.width-size_part.width;
    double min_ncc=-1;
    Rect rect_res=Rect(0,0,0,0);
    for(int r=0;r<height_div;r++){
        for(int c=0;c<width_div;c++){
            Rect rect_tmp=Rect(c,r,size_part.width,size_part.height);
            double tmp=calNCC(mat_src(rect_tmp),mat_part);
            if(abs(min_ncc-1)>abs(tmp-1)){
                min_ncc=tmp;
                rect_res=rect_tmp;
            }
        }
    }
    return rect_res;
}

void lineDetection(string image_path)
{
	Mat src, src_gray, dst;
	src = imread(image_path);
  imshow("input image", src);
waitKey(0);
	if (!src.data)
	{
		std::cerr << "无法打开图像文件！" << endl;
		return;
	}

	namedWindow("input image", CV_WINDOW_AUTOSIZE);
	namedWindow("hough-line-detection", CV_WINDOW_AUTOSIZE);
	imshow("input image", src);

	//边缘检测
	Canny(src, src_gray, 150, 200);
	//灰度化
	cvtColor(src_gray, dst, CV_GRAY2BGR);

	vector<Vec2f> lines;
	//霍夫曼直线检测
	Point pt1, pt2;
	HoughLines(src_gray, lines, 1, CV_PI / 180, 150, 0, 0);
	for (size_t i = 0; i < lines.size(); i++)
	{
		// 极坐标中的r长度
		float rho = lines[i][0];
		// 极坐标中的角度
		float theta = lines[i][1];
		double a = cos(theta), b = sin(theta);
		double x0 = a*rho, y0 = b*rho;
		// 转换为平面坐标的四个点
		pt1.x = cvRound(x0 + 1000 * (-b));
		pt1.y = cvRound(y0 + 1000 * (a));
		pt2.x = cvRound(x0 - 1000 * (-b));
		pt2.y = cvRound(y0 - 1000 * (a));
		line(dst, pt1, pt2, Scalar(0, 0, 255), 1, CV_AA);
	}

	imshow("matt", src);

	imshow("hough-line-detection", dst);

	waitKey(0);
}


int main()
{

//     Mat src = imread("../../../resource/circle_detect.jpg",IMREAD_GRAYSCALE);
//     Mat src_part = imread("../../../resource/circle_detect_part.jpg",IMREAD_GRAYSCALE);
//
//     cout<<src.size()<<endl;
//     imshow("src",src);
//     imshow("src_part",src_part);
//
//
//     Rect rect=findMostMatchWithNCC(src,src_part);
//     cout<<"x:"<<rect.x
//        <<"y:"<<rect.y
//       <<"width:"<<rect.width
//      <<"height:"<<rect.height<<endl;
//
//     rectangle(src, rect, Scalar(255, 0, 0),-1, LINE_8,0);
//
// //    cout<<"mean:"<<calMean(src)<<endl;
// //    cout<<"mean:"<<calMean(src_part)<<endl;
//
//     imshow("src_draw",src);
//
//
//     waitKey(0);

lineDetection("/home/sxy/Github/opencv_cpp/resource/line_detect.png");

    return 0;
}
