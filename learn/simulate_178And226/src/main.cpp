#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>
#include "imagetransformer.h"

using namespace std;
using namespace cv;

int main(void) {

    //初始化
    int v_channels=10;
    int v_bit_channel=10;
    int v_bit_delivery=4;
    ImageTransformer Transformer(v_channels,v_bit_channel,v_bit_delivery);

    //input image

    string path_image="/home/sxy/Github/opencv_cpp/learn/"
                      "simulate_178And226/resources/circle_detect_part.jpg";
    Mat mat=imread(path_image,IMREAD_GRAYSCALE);

    if(mat.empty()){
        cout<<">>Error: Fail to load image: "<<path_image<<endl;
    }
    else{
        Transformer.transform(mat,"output.txt");
    }

//    void *pdata=malloc(6);
//    memset(pdata,1,6);

//    uchar ch_tmp='b';
//    void *p=&ch_tmp;

//    memcpy(pdata+3,p,1);
//    cout<<"ch_tmp:"<<ch_tmp<<endl;
//    saveBufferToFile(static_cast<uchar*>(pdata),6,"tmp.txt");



    return 0;
}
