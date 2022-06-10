
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

/// 分别计算已知重叠区域边界与图片边界的距离,然后逐一取较小值
int getOverLap(cv::Size v_size_0,
               cv::Rect v_rect_0,
               cv::Size v_size_1,
               cv::Rect v_rect_1 ,
               cv::Rect v_rect_overlap_0,
               cv::Rect v_rect_overlap_1)
{
  int distance_0_left=v_rect_0.x-0;
  int distance_0_right=v_size_0.width-(v_rect_0.x+v_rect_0.width);
  int distance_0_up=v_rect_0.y-0;
  int distance_0_bottom=v_size_0.height-(v_rect_0.y+v_rect_0.height);
  assert(distance_0_left>=0);
  assert(distance_0_right>=0);
  assert(distance_0_up>=0);
  assert(distance_0_bottom>=0);

  int distance_1_left=v_rect_1.x-0;
  int distance_1_right=v_size_1.width-(v_rect_1.x+v_rect_1.width);
  int distance_1_up=v_rect_1.y-0;
  int distance_1_bottom=v_size_1.height-(v_rect_1.y+v_rect_1.height);
  assert(distance_1_left>=0);
  assert(distance_1_right>=0);
  assert(distance_1_up>=0);
  assert(distance_1_bottom>=0);

 int distance_left=distance_1_left<distance_0_left?distance_1_left:distance_0_left;
 int distance_right=distance_1_right<distance_0_right?distance_1_right:distance_0_right;
 int distance_up=distance_1_up<distance_0_up?distance_1_up:distance_0_up;
 int distance_bottom=distance_1_bottom<distance_0_bottom?distance_1_bottom:distance_0_bottom;

  v_rect_overlap_0=cv::Rect(v_rect_0.x-distance_left,
                            v_rect_0.y-distance_up,
                            v_rect_0.width+distance_left+distance_right,
                            v_rect_0.height+distance_bottom+distance_up);
  v_rect_overlap_1=cv::Rect(v_rect_1.x-distance_left,
                            v_rect_1.y-distance_up,
                            v_rect_1.width+distance_left+distance_right,
                            v_rect_1.height+distance_bottom+distance_up);
}

/// 计算上下左右边界
/// <> 待做条件检验
int getOverLap(const cv::Size &size0,
               const cv::Size &size1,
               const cv::Vec<int,2> &vec,
               cv::Rect &overlap0,
               cv::Rect &overlap1
               )
{
  cv::Rect rect0(0,0,size0.width,size0.height);
  cv::Rect rect1(0-vec[0],0-vec[1],size1.width,size1.height);
  int left=rect0.x>rect1.x?rect0.x:rect1.x;
  int bottom=rect0.y>rect1.y?rect0.y:rect1.y;
  int right0=rect0.x+rect0.width;
  int right1=rect1.x+rect1.width;

  int right=right0>right1?right1:right0;
  int up0=rect0.y+rect0.height;
  int up1=rect1.y+rect1.height;
  int up=up0>up1?up1:up0;

  overlap0=cv::Rect(left,bottom,right-left,up-bottom);

  overlap1=cv::Rect(left+vec[0],bottom+vec[0],right-left,up-bottom);
  return 0;

}








}
