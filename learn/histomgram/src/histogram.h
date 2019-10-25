#ifndef HISTOGRAM_H
#define HISTOGRAM_H
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/core.hpp"

using namespace std;
using namespace cv;
namespace histogram {
/**
 * [printHistogram description]
 * @param  array distribution of pix value between 0~255
 * @param  size  the size of histogram image
 * @return       image of histogram
 */
Mat printHistogram(const Mat array,Size size);


/**
 * caculate the value describution of between 0~255
 * @param  image source image
 * @return       array to save the value-distribution, with size of [1*256],0->255
 */
Mat calcGrayHist(const Mat & image);





}


#endif // HISTOGRAM_H
