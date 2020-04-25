#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include<string>
#include<vector>
#include <opencv2/features2d/features2d.hpp>
// #include <opencv2/nonfree/nonfree.hpp>
#include "../../basic/src/basic.h"
using namespace std;
using namespace cv;





int main(int argc, const char * argv[]) {
    string path_image2="../../resources/image.jpg";
    Mat mat2=imread(path_image2,IMREAD_GRAYSCALE);
    std::cout << "/* message */" << mat2.size()<<'\n';

    vector<Mat> list_mat=basic::cutImage(mat2,4,basic::DIRECTION_W);
    cout<<"list_mat.size:"<<list_mat.size()<<endl;
    for(uint i=0;i<list_mat.size();i++){
        cout<<"i:"<<i<<" size:"<<list_mat[i].size()<<endl;
        string str_name=basic::integerToString(static_cast<int>(i))+".jpg";
        if(!list_mat[i].empty()){
            imwrite(str_name,list_mat[i]);
        }
    }


    return 0;
}
