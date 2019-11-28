#ifndef BASIC_H
#define BASIC_H

#include <iostream>
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/core.hpp"
using namespace std;
using namespace cv;

namespace basic {
/**
 * print mat as array of number
 * @param image image of source
 */
void printMatNum(const Mat image);

/**
 * get max value of every col of image
 * @param  array source image
 * @return       the value-list of max value of every col
 */
std::vector<int> getMaxValueList(const Mat array);


void printMatInfo(Mat mat);

void showMatTransform(const Mat Image);
/**
 * calConvexHull caculate the convex hull of these points, result saved in list
 * @param list_point [description]
 */
std::vector<cv::Point2i> calConvexHull(const std::vector<cv::Point2i>& list_point);

void drawPointList(const std::vector<cv::Point2i>& list_point,cv::Mat& image);
void drawMultiLineShape(const std::vector<cv::Point2i>& list_point,cv::Mat& image);


void displayMatWithSize(cv::Mat mat,std::string name,cv::Size size );


/**
 * this function is designed to get image after ritating a certain angle,
 * when the angle larger than certain value ,it may not work well
 * @param  mat_src [description]
 * @param  angle   [description]
 * @return         [description]
 */
cv::Mat rotateAndCutImage(const cv::Mat& mat_src,double angle);


}






#endif // BASIbasicC_H
