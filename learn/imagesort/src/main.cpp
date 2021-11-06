#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include<string>
#include<vector>
#include <regex>
#include <opencv2/features2d/features2d.hpp>
#include "basic/getsubfile.h"
#include "sortimage.h"
#include "basic/basic.h"
// #include <opencv2/nonfree/nonfree.hpp>

using namespace std;
using namespace cv;




int main(int argc, const char * argv[]) {
//      string path_image2="/home/sxy/Work/svn/bs2_repo/runway_scan/runway_scan_sw/splitline_detect/build/splitimage/blockcut_0_2_29_sm.jpg";
//    //Mat mat2=imread(path_image2,IMREAD_GRAYSCALE);
//    //std::cout << "/* message */" << mat2.size()<<'\n';
////     cout<< getImageName(path_image2);
//      cout<<getBigImagePath(path_image2)<<endl;
//      string path = path_image2.substr(0,path_image2.find_last_of('/') );
//      cout<<"path:"<<path<<endl;




        string path="/run/media/sxy/Extend/Data/uvss_data_before_2020";
        string dir_output="/run/media/sxy/Extend/Data/output";
        string dir_ex="/run/media/sxy/Extend/Data/output_ex";
        string file_record=dir_output+"/record.txt";

        if(!basic::isFileExist(dir_output)){
            mkdir(dir_output);
        }
        if(!basic::isFileExist(dir_ex)){
            mkdir(dir_ex);
        }

        sortImageInInDir(path,dir_output,dir_ex);
//        getRecBufSave(file_record);

//    Record record0("dir0","big0.jpg","small0.jpg");
//    Record record1("dir1","big1.jpg","small1.jpg");
//    RecordBuf recbuf;
//    recbuf.addRecord(record0);
//    recbuf.addRecord(record1);
//    cout<<RecordBuf::jsonString(&recbuf)<<endl;

//    RecordBuf buf_load;
//    bool   flag= RecordBuf::loadFromString(RecordBuf::jsonString(&recbuf),buf_load);
//    cout<<RecordBuf::jsonString(&buf_load)<<endl;
//    cout<<"flag:"<<flag<<endl;

    return 0;
}
