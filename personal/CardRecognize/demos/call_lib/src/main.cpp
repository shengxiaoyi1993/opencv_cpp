#include<CardRecognize/CardRecognize.h>
#include <opencv_basic/opencv_match.h>


int main(int argc, char *argv[])
{
  std::string path_image="";
  cv::Mat mat_target=cv::imread(path_image);
  cv::Mat mat_target_gray;
  cv::cvtColor(mat_target,mat_target_gray,CV_BGR2GRAY);


  /// 对图片做模板计算
  std::string path_template="";
  cv::Mat mat_template=cv::imread(path_template);

  cv::cvtColor(mat_template,mat_template,CV_BGR2GRAY);
  cv::Mat mat_mask=cv::Mat::zeros(mat_template.rows,mat_template.cols,CV_8U);
  cv::Rect rect_mask(0,0,255,255);
  mat_mask.setTo(255);
  mat_mask(rect_mask).setTo(0);

  double min_ssd=-1;
  /// 求出ssd最小值
  for(int r=0;r<mat_target_gray.rows-mat_template.rows;r++)
  {
    for(int c=0;c<mat_target_gray.cols-mat_template.cols;c++)
    {
      cv::Rect rect_target_block(c,r,mat_template.cols,mat_template.rows);
      double tmpssd= opencv_match::calSSD(mat_target_gray(rect_target_block),mat_template,mat_mask);
      if (min_ssd<0) {
        min_ssd=tmpssd;
      }
      else {
        min_ssd=min_ssd<tmpssd?min_ssd:tmpssd;
      }
    }
  }

  /// 遍历图像求出所有区域,且使得不交叉
  /// ssd值小于该值的认为是目标区域
  double limit_ssd=min_ssd+10;
  /// 保留目标区域
  std::vector<cv::Rect> list_rect_target_card_block;
  for(int r=0;r<mat_target_gray.rows-mat_template.rows;r++)
  {
    bool has_in_row=false;
    for(int c=0;c<mat_target_gray.cols-mat_template.cols;c++)
    {
      cv::Rect rect_target_block(c,r,mat_template.cols,mat_template.rows);
      double tmpssd= opencv_match::calSSD(mat_target_gray(rect_target_block),mat_template,mat_mask);
      if (tmpssd<=limit_ssd) {
        list_rect_target_card_block.push_back(rect_target_block);
        /// 若满足条件,则跳过这篇区域
        c+=mat_template.cols;
        has_in_row=true;
      }
    }
    if (has_in_row == true) {
      r+=mat_template.rows;
    }
  }

  /// draw
  /// 绘图验证
  {
    cv::Mat mat_draw=mat_target_gray.clone();

    for(auto it:list_rect_target_card_block)
    {
      cv::rectangle(mat_draw,it,cv::Scalar(255,0,0));
    }

  }

  /// 在目标块中识别内容
  /// 方法是利用除去边缘的已知块与目标块进行比对,当差异值较小时认为是匹配的
  /// 或者计算特征值,与特征值进行比对
  /// 对于每个模板图片计算Hu矩
  /// 得到目标图片时与所有模板图片的Hu矩相比较,得到差距最小的

  return 0;
}
