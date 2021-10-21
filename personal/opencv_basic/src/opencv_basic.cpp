
#include "opencv_basic/opencv_basic.h"


namespace opencv_basic {

int  calValueWithProportion(int value_start, int value_end, int interval, int pos ){
    double value_pos=(value_end-value_start)*1.0*pos/interval+value_start;
    return static_cast<int >(value_pos);
}

float  calValueWithProportion(float value_start,float value_end,int interval,int pos ){
    float value_pos=(value_end-value_start)*pos/interval+value_start;
    return static_cast<float >(value_pos);
}


float  calValueWithCurve(float value_start,float value_end,int interval,int pos ){
    float value=(value_end-value_start)*pos*pos/(interval*interval)+value_start;
    return value;
}

int getDistanceFromPoint(cv::Point point_mid,cv::Point point_edge){
    cv::Point point_div=point_mid-point_edge;
    point_div=cv::Point(abs(point_div.x),abs(point_div.y));
    if(point_div.x>point_div.y){
        return point_div.x;
    }
    else{
        return point_div.y;
    }

}


int getXFromStraightLineAtY(cv::Point2i point0,cv::Point2i point1,int y){
    double res= (point0.x+(point1.x-point0.x)*1.0*(y-point0.y)/(point1.y-point0.y));
    return int(res+0.5);

}






}
