#ifndef ICONCOMPARE_H
#define ICONCOMPARE_H


/// 该类用于从已知的图标列表中找到一个最相似的图标
/// 通过，标准图标与枚举类型的映射，从而确定目标图标的意义
///
/// <> 注意特殊情况：图标不属于标准图标中任何一种
/// - 计算


#include <map>
#include <opencv2/opencv.hpp>


class IconCompare
{
public:
  IconCompare();
  /// 要求输入的图标路径正确且没有相同图标，否则会取最早的图标作为结果
  /// 比对时若比对图片与参考图片会缩放到v_size进行比对
  int setBenchMark(const std::map<std::string,std::string> &m_icon,
                   const cv::Size &v_size);

  /// 给定图标，然后与标准图标列表中的图标一一比对，找出最相似的一个
  /// 若正常则返回0
  /// 输入的是图标的路径
  int getIconMeaning(const std::string &v_path,std::string &v_mean);

  /// 作用同上
  /// 输入的是图标的数据
  int getIconMeaning(const cv::Mat &v_mat, std::string &v_mean);

private:

  /// <含义,路径>列表
  std::map<std::string,std::string> __map_icon;
  cv::Size __size_std;


};





#endif
