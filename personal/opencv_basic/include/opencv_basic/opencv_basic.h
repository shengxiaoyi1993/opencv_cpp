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


}






#endif
