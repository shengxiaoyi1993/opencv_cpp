#ifndef OPENCV_BASIC_H
#define OPENCV_BASIC_H


#include "opencv2/opencv.hpp"

namespace opencv_basic {

int getDistanceFromPoint(cv::Point point_mid,cv::Point point_edge);

int  calValueWithProportion(int value_start,int value_end,int interval,int pos );

float  calValueWithProportion(float value_start,float value_end,int interval,int pos );

float  calValueWithCurve(float value_start,float value_end,int interval,int pos );
/**
 * @brief getXFromStraightLineAtY 根据两点确定的直线，取某一纵坐标对应的横坐标
 * @param point0
 * @param point1
 * @param y
 * @return
 */
int getXFromStraightLineAtY(cv::Point2i point0,cv::Point2i point1,int y);



/**
 * @brief getOverLap
 * - 已知两图片的部分重叠区域,计算两图片的最大重叠区域
 * @param v_size_0
 * @param v_rect_0
 * @param v_size_1
 * @param v_rect_1
 * @param v_rect_overlap_0
 * @param v_rect_overlap_1
 * @return
 */
int getOverLap(cv::Size v_size_0,
               cv::Rect v_rect_0,
               cv::Size v_size_1,
               cv::Rect v_rect_1,
               cv::Rect v_rect_overlap_0,
               cv::Rect v_rect_overlap_1
               );

///**
// * @brief getRectOffsetVetor
// * - 已知量及
// * @param p0
// * @param p1
// * @return
// */
//int getRectOffsetVetor(const cv::Point &p0,const cv::Point &p1);

/**
 * @brief getOverLap
 * - 根据两距离的偏移计算重合区域
 * - size0 中的点加上vec后得到size1中的对应的点
 * @param size0
 * @param size1
 * @param vec
 * @return
 */
int getOverLap(const cv::Size &size0,
               const cv::Size &size1,
               const cv::Vec<int,2> &vec,
               cv::Rect &overlap0,
               cv::Rect &overlap1
               );


}






#endif
