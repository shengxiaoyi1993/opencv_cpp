#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include<string>
#include<vector>
#include <opencv2/features2d/features2d.hpp>
// #include <opencv2/nonfree/nonfree.hpp>

using namespace std;
using namespace cv;


int main(int argc, const char * argv[]) {
  string path_image2="/home/sxy/Work/svn/bs2_repo/runway_scan/runway_scan_sw/splitline_detect/build/splitimage/blockcut_0_2_29.jpg";
Mat mat2=imread(path_image2,IMREAD_GRAYSCALE);
std::cout << "/* message */" << mat2.size()<<'\n';


string path_buffer="/home/sxy/Share/tftp/imagebuffer.txt";
string path_buffer_save="/home/sxy/Share/tftp/imagebuffer.ppm";
string path_buffer_jpg="/home/sxy/Share/tftp/imagebuffer.jpg";


ifstream infile(path_buffer,ios::in);   //输入流
//load all data from file
std::string str((std::istreambuf_iterator<char>(infile)),
                std::istreambuf_iterator<char>());

std::cout << "size_buffer:"<< str.size()<< '\n';
if(str.size()<4096*4096*3){
std::cout << "imagebuffer is broken" << '\n';
}
else{
unsigned short *pdata=new unsigned short[4096*4096*3];
for (size_t i = 0; i < 4096*4096*3; i++) {
  pdata[i]=static_cast<unsigned short>(str[i]);
//  pdata[i]<<=8;
  // pdata[i]=pdata[i]<255?pdata[i]:255;
}

//以16个元素作为一个单元进行反转
for (size_t i = 0; i < 4096*4096*3/16; i++) {
  for (size_t j = 0; j < 16/2; j++) {
    unsigned short tmp=pdata[i*16+16-j-1];
    pdata[i*16+16-j-1]=pdata[i*16+j];
    pdata[i*16+j]=tmp;
  }
  // pdata[i]=pdata[i]<255?pdata[i]:255;
}

Mat mat(4096,4096,CV_8UC3);
for(uint i=0;i<4096;i++){
  for (uint j=0;j<4096;j++) {
    mat.at<Vec3b>(i*4096+j)=Vec3b(static_cast<uchar>(pdata[(i*4096+j)*3]),
        static_cast<uchar>(pdata[(i*4096+j)*3+1]),
        static_cast<uchar>(pdata[(i*4096+j)*3+2])
        );

  }
}
imwrite(path_buffer_jpg,mat);




}



    return 0;
}
