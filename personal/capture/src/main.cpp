
/// 每一天新建一个文件夹用于
/// 隔一段时间进行一次拍摄 （time_interval），保存视频（若能保存的话）


/// 流程
/// 载入配置文件
/// 初始化根目录
/// 启动计时器
/// timeout 获取文件夹
/// > 创建文件夹
/// > 调用usb摄像头截取图片的接口，获取图片
/// > 获取文件名，在临时文件下保存图片
///



#include <iostream>
#include <math.h>
#include "opencv2/opencv.hpp"
#include <QObject>
#include <QApplication>
#include "misc.h"
#include <QTimer>
#include <QDir>

using namespace cv;
using namespace std;                  //千篇一律的开头

int main(int argc, char* argv[])
{
  QApplication a(argc,argv);
  VideoCapture capture(0);    //最最主要的一个调用函数，opencv真的很强大

  if (capture.isOpened()) {
    std::cout<<"capture.isOpened"<<endl;
  }
  else{
    std::cout<<"capture.isNotOpened"<<endl;
    return -1;
  }


  /// load config
  std::string __dir_root="./";
  DBDirectoryDistributor* instance=DBDirectoryDistributor::getInstance();
  instance->setBaseDir(__dir_root);

  QTimer * __timer=new QTimer();
  QObject::connect(__timer,&QTimer::timeout,
                   [&](){
   string dir_tmp= instance->getDir();
   QDir qdir_help;
   if (!qdir_help.exists(QString::fromStdString(dir_tmp))) {
    bool ret_mkph= qdir_help.mkpath(QString::fromStdString(dir_tmp));
    if (ret_mkph) {
      std::cout<<"Succeed to mkpath"<<endl;
      std::string filename=dir_tmp+"/usb_cam_0.jpg";
        Mat frame;
        capture.read(frame);
        if (!frame.empty()) {
         bool ret_wt= imwrite(filename,frame);
         if (ret_wt) {
           std::cout<<"Succeed to imwrite"<<endl;
         }
         else{
           std::cout<<"Fail to imwrite"<<endl;
         }
        }
        else{
          std::cout<<"Fail to capture"<<endl;
        }
    }
    else{
      std::cout<<"Fail to mkpath"<<endl;
    }

   }
  });

  __timer->start(10000);





  return a.exec();
}
