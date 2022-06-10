#include "IconCompare/IconCompare.h"
//#include "uvss_label_distance/uvss_label_distance_interface.hpp"
#include "opencv_basic/opencv_match.h"
#include "macro_glog/macro_glog.h"
#include <math.h>

const double EPS = 1e-6;


IconCompare::IconCompare():
  __g_volatility_cut(10)
{

}

int IconCompare::setBenchMark(const std::map<std::string,std::string> &m_icon,const cv::Size &v_size)
{
  __map_icon=m_icon;
  __size_std=v_size;
  return 0;
}


/// 给定图标，然后与标准图标列表中的图标一一比对，找出最相似的一个
/// 若正常则返回0
/// 输入的是图标的路径
int IconCompare::getIconMeaning(const std::string &v_path,std::string &v_mean)
{
  cv::Mat v_mat=cv::imread(v_path);
  return getIconMeaning(v_mat,v_mean);
}

/// 作用同上
/// 输入的是图标的数据
int IconCompare::getIconMeaning(const cv::Mat &v_mat,std::string &v_mean)
{

  double min_ssd=-1;
  int ret=-1;
  for (auto it:__map_icon) {
    cv::Mat mat_tmp=cv::imread(it.second);
    cv::Mat mat_target=v_mat;
    std::cout<<"mat_tmp.size:"<<mat_tmp.size<<std::endl;
    std::cout<<"mat_target.size:"<<mat_target.size<<std::endl;

    if (!mat_target.empty() && !mat_tmp.empty()) {

//             由于图标内部截取时可能有偏移,因此需要矫正偏移后再计算平均面积方差
//             这里采用的方法是,去除图标边缘,后均方差最大的区域,截取图片的1/4大小,在另一图片上寻找匹配区域(简化版本为获取指定区域)
//             找到匹配区域后,截取重合区域,计算重合区域的平均方差
//             然后用该值进行比较得到最匹配的图标

      if (v_mat.cols<=2*__g_volatility_cut || v_mat.rows<=2*__g_volatility_cut) {

        MACRO_GLOG_WARNING("v_mat.cols<=2*__g_volatility_cut || v_mat.rows<=2*__g_volatility_cut");

        return -1;

      }



      cv::Rect rect_mid(__g_volatility_cut,
                        __g_volatility_cut,
                        mat_target.cols-2*__g_volatility_cut,
                        mat_target.rows-2*__g_volatility_cut
                        );

      if (mat_tmp.cols<rect_mid.width || mat_tmp.rows<rect_mid.height) {
        MACRO_GLOG_WARNING("mat_tmp.cols<rect_mid.width || mat_tmp.rows<rect_mid.height");
        return -1;
      }

      cv::Rect rect=opencv_match::findMostMatchWithNCC(mat_tmp,mat_target(rect_mid));

      /// 获取重复区域
      /// mat_target rect_mid  mat_tmp rect





//      if (mat_target.size() != __size_std) {
//        cv::resize(mat_target,mat_target,__size_std);
//      }

//      if (mat_tmp.size() != __size_std) {
//        cv::resize(mat_tmp,mat_tmp,__size_std);
//      }

//      double tmpssd=opencv_match::calSSD(mat_target,mat_tmp);
//      if (fabs (min_ssd-(-1)) < EPS) {
//        min_ssd=tmpssd;
//        v_mean=it.first;
//      }
//      else{
//        if (tmpssd<min_ssd) {
//          tmpssd=min_ssd;
//          v_mean=it.first;
//        }
//      }
      ret=0;

    }
    else{
      ret=-1;
    }
  }
  return ret;
}

