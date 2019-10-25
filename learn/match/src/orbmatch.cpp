#include "orbmatch.h"
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

using namespace std;
using namespace cv;


int matchWithBF(string path_img1,string path_img2){
    Mat img1 = imread(path_img1);
    Mat img2 = imread(path_img2);

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

    // 绘制关键点
    Mat keypoint_img1;
    drawKeypoints(img1, keypoints1, keypoint_img1, Scalar::all(-1), DrawMatchesFlags::DEFAULT);
    imshow("KeyPoints Image1", keypoint_img1);

    Mat keypoint_img2;
    drawKeypoints(img2, keypoints2, keypoint_img2, Scalar::all(-1), DrawMatchesFlags::DEFAULT);
    imshow("KeyPoints Image2", keypoint_img2);

    Mat dst;
    drawMatches(img1, keypoints1, img2, keypoints2, matches, dst);
    imshow("output", dst);

    waitKey(0);
    return 0;
}


int matchWithFlann(string img1,string img2){
    double RATIO   =0.4;
        Mat box = imread(img1);
        Mat scene = imread(img2);
        if (scene.empty()) {
            printf("could not load image...\n");
            return -1;
        }
        imshow("input image", scene);
        vector<KeyPoint> keypoints_obj, keypoints_sence;
        Mat descriptors_box, descriptors_sence;
        Ptr<ORB> detector = ORB::create();
        detector->detectAndCompute(scene, Mat(), keypoints_sence, descriptors_sence);
        detector->detectAndCompute(box, Mat(), keypoints_obj, descriptors_box);
        vector<DMatch> matches;
        // 初始化flann匹配
        // Ptr<FlannBasedMatcher> matcher = FlannBasedMatcher::create(); // default is bad, using local sensitive hash(LSH)
        Ptr<DescriptorMatcher> matcher = makePtr<FlannBasedMatcher>(makePtr<flann::LshIndexParams>(12, 20, 2));
        matcher->match(descriptors_box, descriptors_sence, matches);
        // 发现匹配
        vector<DMatch> goodMatches;
        printf("total match points : %d\n", matches.size());
        float maxdist = 0;
        for (unsigned int i = 0; i < matches.size(); ++i) {
            printf("dist : %.2f \n", matches[i].distance);
            maxdist = max(maxdist, matches[i].distance);
        }
        for (unsigned int i = 0; i < matches.size(); ++i) {
            if (matches[i].distance < maxdist*RATIO)
                goodMatches.push_back(matches[i]);
        }
        Mat dst;
        drawMatches(box, keypoints_obj,scene, keypoints_sence,goodMatches, dst);
        imshow("output", dst);
        waitKey(0);
        return 0;
}
