#ifndef MATCH_H
#define MATCH_H

#include <vector>
#include <string>
#include "opencv2/core.hpp"


//for gray image
//using namespace cv;
namespace opencv_match{


enum MatchMethod{
    MatchMethod_NCC = 0,
    MatchMethod_MAD = 1,
    MatchMethod_AMAD = 2,
    MatchMethod_MSD = 3

};

double calMSD(const cv::Mat &mat1,const cv::Mat &mat2);

double calSSD(const cv::Mat &mat1,const cv::Mat &mat2);

int calMAD(const cv::Mat &mat1,const cv::Mat &mat2);


 cv::Rect findMostMatchWithMSD(const cv::Mat &mat_src,const cv::Mat &mat_part);

 cv::Rect findMostMatchWithMAD(const cv::Mat &mat_src,const cv::Mat &mat_part);

 cv::Rect findMostMatchWithSSD(const cv::Mat &mat_src,const cv::Mat &mat_part);

int calMean(const cv::Mat &src);

double calSD(const cv::Mat &mat_src);

double calCov(const cv::Mat &mat1,const cv::Mat &mat2);

double calNCC(const cv::Mat& mat1,const cv::Mat& mat2);

 cv::Rect findMostMatchWithNCC(const cv::Mat& mat_src,const cv::Mat &mat_part);

int searchMostMatch(cv::Mat mat_target,cv::Rect2i rect,int range
                    ,cv::Mat mat_block,cv::Rect2i& rect_target,
                    MatchMethod option);

/**
 * @brief calWeightMAD 计算基于加权的平均值算法,越靠近中间的像素，其权重越大
 * @param mat1
 * @param mat2
 * @return
 */
int calMidWeightMAD(const cv::Mat &mat1,const cv::Mat &mat2);

/**
 * @brief calEdgeWeightMAD 计算基于加权的平均值算法,越靠近中间的像素，其权重越小
 * @param mat1
 * @param mat2
 * @return
 */
int calEdgeWeightMAD(const cv::Mat &mat1,const cv::Mat &mat2);

}




#endif // IMAGEMATCH_H
