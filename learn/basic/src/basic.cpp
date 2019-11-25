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

bool cmp(Point2i a,Point2i b,Point2i base)
{
    double value=X(a-base,b-base);

    if(value<0){
        return false;
    }
    else if(value >0){
        return true;
    }
    else{
        if(distance(a,base)>distance(b,base)){
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
            list_referpoint.push_back(list_point[i]);
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


}
