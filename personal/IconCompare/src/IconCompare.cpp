#include "IconCompare/IconCompare.h"
#include "uvss_label_distance/uvss_label_distance_interface.hpp"
#include "opencv_basic/opencv_match.h"
#include <math.h>

const double EPS = 1e-6;


IconCompare::IconCompare()
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
      if (mat_target.size() != __size_std) {
        cv::resize(mat_target,mat_target,__size_std);
      }

      if (mat_tmp.size() != __size_std) {
        cv::resize(mat_tmp,mat_tmp,__size_std);
      }

      double tmpssd=opencv_match::calSSD(mat_target,mat_tmp);
      if (fabs (min_ssd-(-1)) < EPS) {
        min_ssd=tmpssd;
        v_mean=it.first;
      }
      else{
        if (tmpssd<min_ssd) {
          tmpssd=min_ssd;
          v_mean=it.first;
        }
      }
      ret=0;

    }
  }
  return ret;
}

