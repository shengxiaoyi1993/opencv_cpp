#include <iostream>
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/core.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include<vector>
#include<fstream>
#include <stdlib.h>
#include<stdlib.h>
#include<bits/stdc++.h>
#include"basic.h"

using namespace std;
using namespace cv;

string face_cascade_name = "haarcascade_frontalface_alt2.xml";
CascadeClassifier face_cascade;
string window_name = "人脸识别";

void detectAndDisplay(Mat frame);

int main(){
//Mat是个多维的密集数据数组，常用于进行计算性较高的矩阵，图像，直方图操作等
    Mat image;
    image = imread("multiface.jpg");

    if (!face_cascade.load(face_cascade_name)){
        printf("[error] 无法加载级联分类器文件！\n");
        return -1;
    }

    detectAndDisplay(image);

    waitKey(0);
}



void detectAndDisplay(Mat frame){
    std::vector<Rect> faces;
    Mat frame_gray;
    //转换成灰度图像
    cvtColor(frame, frame_gray, CV_BGR2GRAY);
    //灰度图像直方图均衡
    equalizeHist(frame_gray, frame_gray);
    //人脸检测，保存检测到的物体矩阵
    face_cascade.detectMultiScale(frame_gray, faces, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, Size(30, 30));

    for (int i = 0; i < faces.size(); i++){
        //检测到人脸中心
        Point center(faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5);
        //绘制人脸
        ellipse(frame, center, Size(faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, Scalar(255, 0, 255), 4, 8, 0);
    }

    imshow(window_name, frame);
}
