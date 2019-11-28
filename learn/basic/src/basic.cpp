#include "basic.h"

namespace basic {
void printMatNum(const Mat image){
    cout<<"size:"<<image.size()<<endl;
    int rows = image.rows;
    //输入图像的行数
    int cols = image.cols;
    //输入图像的列数
    for(int r =0;r<rows;r++) {
      for(int c = 0;c<cols;c++) {
        int index = int(image.at<int>(r,c)); //获取每个点的像素值
        cout<<index<<" ";
      }
      cout<<endl;
     }
    cout<<endl<<endl;
}



std::vector<int> getMaxValueList(const Mat array){
    std::vector<int>  list_value;
    int cols=array.cols;
    int rows=array.rows;
    for(int r=0;r<rows;r++){
        int max=0;
        for(int c=0;c<cols;c++){
            int value=int(array.at<int>(r,c));
            max=max>value?max:value;
        }
        list_value.push_back(max);
    }
    return list_value;
}


void printMatInfo(Mat mat){
    cout<<"depth:"<<mat.depth()<<endl;
    cout<<"channels:"<<mat.channels()<<endl;
    cout<<"dims:"<<mat.dims<<endl;
    cout<<"type:"<<mat.type()<<endl;
    cout<<"total:"<<mat.total()<<endl;
    cout<<"elemSize:"<<mat.elemSize()<<endl;
    cout<<"elemSize1:"<<mat.elemSize1()<<endl;

    cout<<"cols:"<<mat.cols<<endl;
    cout<<"rows:"<<mat.rows<<endl;
    cout<<"isContinuous:"<<mat.isContinuous()<<endl;

}



void showMatTransform(const Mat Image){

        Mat img_h, img_s, img_v, imghsv;

        vector<cv::Mat> hsv_vec;
        cvtColor(Image, imghsv, CV_BGR2HSV);

        // 分割hsv通道
        split(imghsv, hsv_vec);
        img_h = hsv_vec[0];
        img_s = hsv_vec[1];
        img_v = hsv_vec[2];
        img_h.convertTo(img_h, CV_32F);
        img_s.convertTo(img_s, CV_32F);
        img_v.convertTo(img_v, CV_32F);
        double max_s, max_h, max_v;
        minMaxIdx(img_h, 0, &max_h);
        minMaxIdx(img_s, 0, &max_s);
        minMaxIdx(img_v, 0, &max_v);

        //输入RGB图像,转换成YUV并分离
        Mat imageY(Image.rows, Image.cols, 1);
        Mat imageU(Image.rows, Image.cols, 1);
        Mat imageV(Image.rows, Image.cols, 1);

        Mat imageYUV;
        cvtColor(Image, imageYUV, CV_BGR2YUV);
        vector<Mat> mv;
        split(Image, (vector<Mat>&)mv);

        imageY = mv[0].clone();
        imageU = mv[1].clone();
        imageV = mv[2].clone();

        //bgr
        for (int i = 0; i < 3; i++)
        {
            Mat bgr(Image.rows, Image.cols, CV_8UC3, Scalar(0, 0, 0));
            Mat temp(Image.rows, Image.cols, CV_8UC1);
            Mat out[] = { bgr };
            int from_to[] = { i, i };
            mixChannels(&Image, 1, out, 1, from_to, 1);
            //分别显示bgr
            imshow("bgr", bgr);
            waitKey();
        }

        //显示
        imshow("Y", imageY);
        waitKey();
        imshow("U", imageU);
        waitKey();
        imshow("Y_V", imageV);
        waitKey();

        imshow("h", img_h);
        waitKey();
        imshow("s", img_s);
        waitKey();
        imshow("h_v", img_v);
        waitKey();
}


double X(Point2i a,Point2i b){
    return a.x*b.y-b.x*a.y;
}
double distance(Point2i a,Point2i b){
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
double distance(Point2i a){
    return sqrt((a.x)*(a.x)+(a.y)*(a.y));

}


bool cmp(Point2i a,Point2i b)
{
    double value=X(a,b);

    if(value<0){
        return false;
    }
    else if(value >0){
        return true;
    }
    else{
        if(distance(a)>distance(b)){
            return true;
        }
        else{
            return false;
        }
    }

}
double multi(Point2i p1,Point2i p2,Point2i p3)
{
    return X(p2-p1,p3-p1);
}

std::vector<cv::Point2i> calConvexHull(const std::vector<cv::Point2i>& list_point){
    //caculate the left-buttom point
    vector<Point2i> list_referpoint;
    vector<cv::Point2i> list_res(list_point.size());
    if(list_point.size()==0||list_point.size()==1||list_point.size()==2){
        return list_point;
    }
    Point2i point_leftbuttom=list_point[0];
    for(int i=1;i<list_point.size();i++){
        if(point_leftbuttom.y>list_point[i].y){
            point_leftbuttom=list_point[i];
        }
        else if(point_leftbuttom.y == list_point[i].y){
            if(point_leftbuttom.x>list_point[i].x){
                point_leftbuttom=list_point[i];
            }
        }
    }

//sort the point according to the angle of line formed with point_leftbuttom,with x axis
    for(int i=0;i<list_point.size();i++){
        if(list_point[i]!=point_leftbuttom){
            list_referpoint.push_back(list_point[i]-point_leftbuttom);
        }

    }
    sort(list_referpoint.begin(),list_referpoint.end(),cmp);

  list_res[0]=point_leftbuttom;
  list_res[1]=list_referpoint[0];
  int length=2;
  for(int i=1;i<list_referpoint.size();i++){
      while(length>=2&&multi(list_res[length-1],list_res[length],list_referpoint[i])<=0) length--;
      list_res[++length]=list_referpoint[i];
  }

  return list_res;

}

bool isPointInImage(cv::Point2i point,const cv::Mat& image){
    if(point.x<image.cols&&point.y<image.rows){
        return true;
    }
    else{
        return false;
    }
}

void drawPointList(const std::vector<cv::Point2i>& list_point,cv::Mat& image){
    for(int i=0;i<list_point.size();i++){
        if(isPointInImage(list_point[i],image)){
                circle(image, list_point[i], 2,Scalar(255,0,0),-1);
        }
        else{
            cout<<list_point[i]<<" is out of image"<<endl;
        }
    }
}


void displayMatWithSize(cv::Mat mat,std::string name,cv::Size size ){
    if(mat.size()==Size(0,0)){
        return  ;
    }
    Mat mat_resize;
    resize(mat,mat_resize,size);
    imshow(name,mat_resize);
    //    waitKey(0);
    return  ;
}

void drawMultiLineShape(const std::vector<cv::Point2i>& list_point,cv::Mat& image){
    if(list_point.size()==0){
        return;
    }
    Point2i point_former=list_point[list_point.size()-1];
    for(int i=0;i<list_point.size();i++){
        //PERSUME that all points are in image
        line(image, point_former, list_point[i], Scalar(255, 255, 255), 2);
        point_former=list_point[i];
    }
}

cv::Mat rotateAndCutImage(const cv::Mat& mat_src,double angle){
  // vector<Point> contour;
  // Point p1(0,offset_x),
  // p2(mat_src.cols,mat_src.rows-offset_x),
  // p3(2*offset_x,mat_src.rows),
  // p4(mat_src.cols-offset_x*2,0);
  // contour.push_back(p1);
  // contour.push_back(p2);
  // contour.push_back(p3);
  // contour.push_back(p4);
  // RotatedRect rect = minAreaRect(contour);//外接矩形
  // Point2f center = rect.center;//外接矩形中心点坐标
  Point2f center(mat_src.cols/2,mat_src.rows/2);
  Mat rot_mat = getRotationMatrix2D(center, angle, 1.0);//求旋转矩阵
  Mat rot_image;
  Size dst_sz(mat_src.size());
  warpAffine(mat_src, rot_image, rot_mat, dst_sz);//原图像旋转
  int h_tl,w_tl,h_tr,w_tr;

  for(int i=0;i<rot_image.cols;i++){
    if(rot_image.at<uchar>(0,i)==0){

    }
    else{
      w_tl=i;
      break;
    }
  }

  for(int i=rot_image.cols-1;i>=0;i--){
    if(rot_image.at<uchar>(0,i)==0){

    }
    else{
      w_tr=rot_image.cols-1-i;
      break;
    }
  }

  for(int i=0;i<rot_image.rows;i++){
    if(rot_image.at<uchar>(i,0)==0){

    }
    else{
      h_tl=i;
      break;
    }
  }

  for(int i=0;i<rot_image.rows;i++){
    if(rot_image.at<uchar>(i,rot_image.cols-1)==0){

    }
    else{
      h_tr=i;
      break;
    }
  }


  cout<<"w_tl:"<<w_tl<<endl;
  cout<<"w_tr:"<<w_tr<<endl;
  cout<<"h_tl:"<<h_tl<<endl;
  cout<<"h_tr:"<<h_tr<<endl;


Rect2i rect_in;
if(w_tl>h_tl){
  rect_in=Rect2i(w_tr,h_tl,rot_image.cols-2*w_tr,rot_image.rows-2*h_tl);
}
else{
  rect_in=Rect2i(w_tl,h_tr,rot_image.cols-2*w_tl,rot_image.rows-2*h_tr);
}
cout<<"rect_in: "<<rect_in<<endl;

Mat mat_in=rot_image(rect_in);


  return mat_in;

}



int calMeanAndSD(const cv::Mat& mat_src,double &value_mean,double&value_sd){
  if(mat_src.cols==0||mat_src.rows==0){
    return -1;
  }
  Mat tmp_m, tmp_sd;
  meanStdDev(mat_src, tmp_m, tmp_sd);
  value_mean=tmp_m.at<double>(0,0);
  value_sd = tmp_sd.at<double>(0,0);
  return 0;
}







}
