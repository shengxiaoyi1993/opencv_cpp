#include <iostream>
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/core.hpp"
#include<vector>
#include<fstream>
#include <stdlib.h>
#include<stdlib.h>
#include<opencv2/features2d/features2d.hpp>



//#define DEBUG
using namespace std;
using namespace cv;


int main()
{
    Mat img1 = imread("../../../resource/image_match/move.jpg");
    Mat img2 = imread("../../../resource/image_match/source.jpg");

    // 1. 初始化
    vector<KeyPoint> keypoints1, keypoints2;
    Mat descriptors1, descriptors2;
    Ptr<ORB> orb = ORB::create();

    // 2. 提取特征点
    orb->detect(img1, keypoints1);
    orb->detect(img2, keypoints2);

    // 3. 计算特征描述符
    orb->compute(img1, keypoints1, descriptors1);
    orb->compute(img2, keypoints2, descriptors2);

    // 4. 对两幅图像的BRIEF描述符进行匹配，使用BFMatch，Hamming距离作为参考
    vector<DMatch> matches;
    BFMatcher bfMatcher(NORM_HAMMING);
    bfMatcher.match(descriptors1, descriptors2, matches);

    cout<<"descriptors1:"<<descriptors1.size()<<endl;
    cout<<"descriptors2:"<<descriptors2.size()<<endl;


    imshow("descriptors1",descriptors1);
    imshow("descriptors2",descriptors2);

//    for(int i=0;i<matches.size();i++){
//        cout<<"queryIdx:"<<matches[i].queryIdx<<endl;
//        cout<<"trainIdx:"<<matches[i].trainIdx<<endl;
//        cout<<"imgIdx:"<<matches[i].imgIdx<<endl;
//        cout<<"distance:"<<matches[i].distance<<endl;

//    }
    waitKey(0);


    return 0;
}
