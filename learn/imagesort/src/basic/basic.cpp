#include "basic.h"
#include <iostream>
#include <fstream>
#include <limits>

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



std::vector<int> getMaxValueList(const Mat& array){
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

int getMaxValue(const Mat &array){
    int cols=array.cols;
    int rows=array.rows;
    int max=0;

    for(int r=0;r<rows;r++){
        for(int c=0;c<cols;c++){
            int value=int(array.at<int>(r,c));
            max=max>value?max:value;
        }
    }
    return max;
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
    minMaxIdx(img_h, nullptr, &max_h);
    minMaxIdx(img_s, nullptr, &max_s);
    minMaxIdx(img_v, nullptr, &max_v);

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
    for(unsigned int i=1;i<list_point.size();i++){
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
    for(unsigned int i=0;i<list_point.size();i++){
        if(list_point[i]!=point_leftbuttom){
            list_referpoint.push_back(list_point[i]-point_leftbuttom);
        }

    }
    sort(list_referpoint.begin(),list_referpoint.end(),cmp);

    list_res[0]=point_leftbuttom;
    list_res[1]=list_referpoint[0];
    unsigned int length=2;
    for(unsigned int i=1;i<list_referpoint.size();i++){
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

void drawPointList(const std::vector<cv::Point2i>& list_point, cv::Mat& image){
    for(unsigned int i=0;i<list_point.size();i++){
        if(isPointInImage(list_point[i],image)){
            circle(image, list_point[i], 3,Scalar(255,0,0),-1);
        }
        else{
            cout<<list_point[i]<<" is out of image"<<endl;
        }
    }
}


void drawPointList(const std::vector<cv::Point2i>& list_point,cv::Mat& image,
                   const std::vector<int> list_num){
    for(unsigned int i=0;i<list_point.size();i++){
        if(isPointInImage(list_point[i],image)){
            circle(image, list_point[i], 3,Scalar(255,0,0),-1);
            putText(image, integerToString(list_num[i]),
                    list_point[i], FONT_HERSHEY_SIMPLEX, 1, Scalar(0,0,255), 1, 2);

        }
        else{
            cout<<list_point[i]<<" is out of image"<<endl;
        }
    }
}


void displayMatWithSize(cv::Mat mat,std::string name,cv::Size size ){
    if(mat.cols==0||mat.rows==0){
        cout<<__func__<<name<<"is empty"<<endl;
        return  ;
    }
    Mat mat_resize;
    resize(mat,mat_resize,size);
    imshow(name,mat_resize);
    return  ;
}

void drawMultiLineShape(const std::vector<cv::Point2i>& list_point,cv::Mat& image){
    if(list_point.size()==0){
        return;
    }
    Point2i point_former=list_point[list_point.size()-1];
    for(unsigned int i=0;i<list_point.size();i++){
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
    int h_tl=0,w_tl=0,h_tr=0,w_tr=0;

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

    Rect2i rect_in;
    if(w_tl>h_tl){
        rect_in=Rect2i(w_tr,h_tl,rot_image.cols-2*w_tr,rot_image.rows-2*h_tl);
    }
    else{
        rect_in=Rect2i(w_tl,h_tr,rot_image.cols-2*w_tl,rot_image.rows-2*h_tr);
    }
//    cout<<"rect_in: "<<rect_in<<endl;

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



void drawLineCol( Mat &mat, int c){
    if(c>=mat.cols){
        //        cout<<"drawLineCol:"
        return;
    }
    for(int r=0;r<mat.rows;r++){
        //        mat.at<uchar>(r+1,c)=255;
        mat.at<uchar>(r,c)=255;
        //        mat.at<uchar>(r-1,c)=255;

    }
    return ;
}


void drawLineRow( cv::Mat &mat,int r){
    //    cout<<__func__<<endl;
    for(int c=0;c<mat.cols;c++){
        mat.at<uchar>(r,c)=255;
    }
    return ;
}


void drawLineRow( cv::Mat &mat,int r,int thickness){
    int start=r-(thickness+1)/2;
    int end=r+(thickness+1)/2;
    start=start>0?start:0;
    end=end<mat.rows-1?end:mat.rows-1;
    for(int i=start;i<end;i++){
        drawLineRow(mat,i);
    }

    return ;
}



Mat printHistogram(const Mat & array,Size size){

    Mat table ;
    vector<int> list_value=getMaxValueList(array);

    //    if(list_value.size()!=1){
    //        return table;

    //    }
    //    if(list_value[0]==0){
    //        return table;
    //    }

    int max_height;
    if(list_value.size()<=0){
        max_height=10;
    }
    else{
        if(list_value[0]==0){
            max_height=10;
        }
        else{
            max_height=list_value[0]+1;
        }
    }


    table = Mat::zeros(Size(256,size.height),CV_8UC1);
    //    cout<<"table.size:"<<table.size<<endl;

    for(int c =0;c<256;c++) {

        int height_tmp=array.at<int>(0,c)*size.height/max_height;
        //                cout<<"array.at<int>(0,c):"<<height_tmp<<endl;

        for(int r = 0;r<height_tmp;r++) {
            //            cout<<"r: "<<size.height-r<<endl;
            table.at<uchar>(size.height-r-1,c)=255;
        }
    }
    //    cout<<"before resize:"<<table.size<<endl;
    ////    printMatInfo(array);

    ////    printMatInfo(table);
    Mat mat_resize;
    cv::resize(table,mat_resize,size);

    //    cout<<"after resize:"<<endl;


    return mat_resize;
}

int drawRectToImage(cv::Mat &mat,std::vector<cv::Rect2i> list_rect){
    for(int i=0;i<list_rect.size();i++){
        rectangle(mat, list_rect[i], Scalar(0, 255, 255), 2);
    }
    return 0;
}
int drawRectToImage(cv::Mat &mat, cv::Rect2i rect, Scalar v_scalar){
    rectangle(mat, rect, v_scalar, 2);
    return 0;
}





Mat printGram(const Mat& mat_list){
    Mat table ;
    vector<int> list_value=getMaxValueList(mat_list);
    if(list_value.size()!=1){
        return table;

    }
    if(list_value[0]==0){
        return table;
    }
    table=Mat::zeros(Size(mat_list.cols,list_value[0]),CV_8UC1);
    //    cout<<"table.size:"<<table.size<<endl;
    for(int c=0;c<mat_list.cols;c++){
        for(int r=0;r<=mat_list.at<int>(0,c);r++){
            table.at<uchar>(table.rows-r-1,c)=255;
        }
    }
    return table;

}

Mat printGram(const Mat& mat_list, int height){
    Mat table =Mat::zeros(Size(mat_list.cols,height),CV_8UC1);
    //    cout<<"table.size:"<<table.size<<endl;
    for(int c=0;c<mat_list.cols;c++){
        for(int r=0;r<=mat_list.at<int>(0,c);r++){
            table.at<uchar>(table.rows-r-1,c)=255;
        }
    }
    return table;


}


Mat calcGrayHist(const Mat & image) {
    Mat histogram = Mat::zeros(Size(256,1),CV_32SC1);

    int rows = image.rows;
    int cols = image.cols;
    for(int r =0;r<rows;r++) {
        for(int c = 0;c<cols;c++) {
            int index = int(image.at<uchar>(r,c));
            histogram.at<int>(0,index) +=1;
        }
    }
    return histogram;
}



Mat calcGrayHistWithNormalization(const Mat & mat_src) {
    Mat histogram_percentage = Mat::zeros(Size(256,1),CV_32FC1);

    Mat histogram = Mat::zeros(Size(256,1),CV_32SC1);

    int rows = mat_src.rows;
    int cols = mat_src.cols;
    for(int r =0;r<rows;r++) {
        for(int c = 0;c<cols;c++) {
            int index = int(mat_src.at<uchar>(r,c));
            histogram.at<int>(0,index) +=1;
        }
    }

    int sum_pix=rows*cols;
    int* grayrowptr_value = const_cast<int*>(histogram.ptr<signed int>(0));
    //    float* grayrowptr_percentage = static_cast<float*>(histogram_percentage.ptr<float>(0));
    for(unsigned int c=0;c<256;c++){
        histogram_percentage.at<float>(0,c)=static_cast<float>(grayrowptr_value[c]*1.0/sum_pix);
    }

    return histogram_percentage;
}


cv::Mat calMeanForCol(const cv::Mat &image){

    cv::Mat list_mean = Mat::zeros(Size(image.rows,1),CV_8UC1);

    for(int row=0;row<image.rows;row++){
        uchar* grayrowptr = const_cast<uchar*>(image.ptr<uchar>(row));
        double sum=0;
        for(int col=0;col<image.cols;col++){
            sum+=grayrowptr[col];
        }
        int mean=static_cast<int>(sum/image.cols);
        list_mean.at<uchar>(0,row)=static_cast<uchar>(mean);

    }
    return list_mean;
}

cv::Mat drawDistributionInRow(const cv::Mat& list_mean){

    Mat mat_paint=Mat::zeros(Size(256,list_mean.cols),CV_8UC1);
    for(int row=0;row<mat_paint.rows;row++){
        for(int col=0;col<list_mean.at<uchar>(0,row);col++){
            mat_paint.at<uchar>(row,col)=255;
        }
    }
    return mat_paint;

}

double crossProduct(const cv::Vec2d& vec1,const cv::Vec2d& vec2){
    return (vec1[0]*vec2[1]-vec1[1]*vec2[0]);
}


cv::Point2i getMidPoint(const std::vector<cv::Point2i> & list){
    std::vector<int> list_x;
    std::vector<int> list_y;
    for(unsigned int i=0;i<list.size();i++){
        list_x.push_back(list[i].x);
        list_y.push_back(list[i].y);
    }
    sort(list_x.begin(),list_x.end());
    sort(list_y.begin(),list_y.end());


    if(list.size()>0){
        return Point2i(list_x[list_x.size()/2],list_y[list_y.size()/2]);
    }
    else{
        return Point2i(-1,-1);
    }

}


int getMidValue(std::vector<int> list_value){
    assert(list_value.size()>0);
    sort(list_value.begin(),list_value.end());
    return list_value[list_value.size()/2];
}


cv::Point2d getMidPoint(const std::vector<cv::Point2d> & list){
    std::vector<double> list_x;
    std::vector<double> list_y;
    for(unsigned int i=0;i<list.size();i++){
        list_x.push_back(list[i].x);
        list_y.push_back(list[i].y);
    }
    sort(list_x.begin(),list_x.end());
    sort(list_y.begin(),list_y.end());


    if(list.size()>0){
        return Point2d(list_x[list_x.size()/2],list_y[list_y.size()/2]);
    }
    else{
        return Point(-1,-1);

    }
}



cv::Mat drawLine(const cv::Mat& mat_src,LinePara line){

    Mat mat_clone=mat_src.clone();
    for(int c=0;c<mat_src.cols;c++){
        int r_tmp=static_cast<int>(line.getY(c));
        if(r_tmp>=0&&r_tmp<mat_src.rows){
            mat_clone.at<uchar>(r_tmp,c)=255;
        }
    }
    return mat_clone;
}


int calMean(const Mat &src){
    int value=(int)(mean(src)[0]);
    return value;
}

int insertOrderLy(vector<int> & list_num,int num,int length){
    if(length>0){
        if(list_num.size()>0){
            if(list_num.size()<length){
                int count=list_num.size()-1;
                while(count>=0){
                    if(num<list_num[count]){
                        break;
                    }
                    count--;
                }
                if(count+1<length){
                    list_num.insert(list_num.begin()+count+1,num);
                }
                if(list_num.size()>length){
                    list_num.erase(list_num.end());
                }

            }

        }
        else{
            list_num.push_back(num);
        }

    }
    return 0;
}






std::string integerToString(int num){
    stringstream ss;
    ss.clear();
    ss.str("");
    string tmps;
    ss<<num;
    ss>>tmps;
    return tmps;
}




int calMeanEx(const cv::Mat & mat_src,Rect2i rect_block,int num_rm){

    double sum_gray=0;
    vector<int> list_larger;
    for(int r=rect_block.y;r<rect_block.y+rect_block.height;r++){
        for(int c=rect_block.x;c<rect_block.x+rect_block.width;c++){
            int value_tmp=mat_src.at<uchar>(r,c);
            insertOrderLy(list_larger,value_tmp,num_rm);
            sum_gray+=value_tmp;
        }
    }
    for(unsigned int i=0;i<list_larger.size();i++){
        sum_gray-=list_larger[i];
    }
    int mean_tmp=static_cast<int>(sum_gray/(rect_block.height*rect_block.width-list_larger.size()));
    return mean_tmp;
}

Point2i getBaryCenterOfBinaryMat(const cv::Mat& mat_src){
    double sum_r=0;
    int count_notnone=0;
    double sum_c=0;
    for(int r=0;r<mat_src.rows;r++){
        uchar* grayrowptr = const_cast<uchar*>(mat_src.ptr<uchar>(r));
        for(int c=0;c<mat_src.cols;c++){
            if(grayrowptr[c]!=0){
                sum_r+=r;
                sum_c+=c;
                count_notnone++;
            }

        }
    }

    //        cout<<""
    //              "count_notnone:"<<count_notnone<<endl;


    Point2i point(static_cast<int>(sum_c/count_notnone),
                  static_cast<int>(sum_r/count_notnone));

    return point;

}






int setBrightBlock( cv::Mat & mat_src,Rect2i rect_block){
    for(int r=rect_block.y;r<rect_block.y+rect_block.height;r++){
        for(int c=rect_block.x;c<rect_block.x+rect_block.width;c++){
            mat_src.at<uchar>(r,c)=255;
        }
    }
    return 0;
}





cv::Mat filterSmallBlock(const cv::Mat& mat_src,Size2i size_module ,int thresold){

    Mat mat_res=Mat::zeros(Size(mat_src.cols,mat_src.rows),CV_8UC1);
    for( int r=0;r<mat_src.rows-size_module.height;r++){
        for(int c=0;c<mat_src.cols-size_module.width;c++){
            Rect rect_tmp=Rect(c,r,size_module.width,size_module.height);
            Mat mat_tmp=mat_src(rect_tmp);
            int mean_tmp=calMean(mat_tmp);
            if(mean_tmp<thresold){
                setBrightBlock(mat_res,rect_tmp);
            }
        }
    }

    return mat_res;
}


cv::Mat filterSmallBlockEx(const cv::Mat& mat_src,Size2i size_module ,int thresold,
                           cv::Mat& mat_distribution){
    mat_distribution=Mat::zeros(Size(mat_src.rows,1),CV_32SC1);

    Mat mat_res=Mat::zeros(Size(mat_src.cols,mat_src.rows),CV_8UC1);
    for( int r=0;r<mat_src.rows-size_module.height;r++){
        int r_mid=r+size_module.height/2;
        for(int c=0;c<mat_src.cols-size_module.width;c++){
            Rect rect_tmp=Rect(c,r,size_module.width,size_module.height);
            Mat mat_tmp=mat_src(rect_tmp);
            int mean_tmp=calMean(mat_tmp);
            if(mean_tmp<thresold){
                mat_distribution.at<int>(0,r_mid)=mat_distribution.at<int>(0,r_mid)+1;
                setBrightBlock(mat_res,rect_tmp);
            }
        }
    }

    return mat_res;
}


cv::Mat filterSmallBlockLengthwise(const cv::Mat& mat_src,Size2i size_module ,int thresold,
                                   cv::Mat& mat_distribution){
    mat_distribution=Mat::zeros(Size(mat_src.rows,1),CV_32SC1);

    Mat mat_res=Mat::zeros(Size(mat_src.cols,mat_src.rows),CV_8UC1);
    for( int r=0;r<mat_src.rows-size_module.height;r++){
        int r_mid=r+size_module.height/2;
        for(int c=0;c<mat_src.cols-size_module.width;c++){
            Rect rect_tmp=Rect(c,r,size_module.width,size_module.height);
            Mat mat_tmp=mat_src(rect_tmp);
            int mean_tmp=calMean(mat_tmp);
            if(mean_tmp<thresold){
                mat_distribution.at<int>(0,r_mid)=mat_distribution.at<int>(0,r_mid)+1;
                setBrightBlock(mat_res,rect_tmp);
            }
        }
    }

    return mat_res;
}


cv::Mat filterSmallBlockCrosswise(const cv::Mat& mat_src,Size2i size_module ,int thresold,
                                  cv::Mat& mat_distribution){
    mat_distribution=Mat::zeros(Size(mat_src.cols,1),CV_32SC1);

    Mat mat_res=Mat::zeros(Size(mat_src.cols,mat_src.rows),CV_8UC1);
    for( int r=0;r<mat_src.rows-size_module.height;r++){
        //       int r_mid=r+size_module.height/2;
        for(int c=0;c<mat_src.cols-size_module.width;c++){
            int c_mid=c+size_module.width/2;

            Rect rect_tmp=Rect(c,r,size_module.width,size_module.height);
            Mat mat_tmp=mat_src(rect_tmp);
            int mean_tmp=calMean(mat_tmp);
            if(mean_tmp<thresold){
                mat_distribution.at<int>(0,c_mid)=mat_distribution.at<int>(0,c_mid)+1;
                setBrightBlock(mat_res,rect_tmp);
            }
        }
    }

    return mat_res;
}



cv::Mat getDistributionMatOfBinaryMat(const cv::Mat &mat_binary, Direction type){
//   imwrite("mat_binary.jpg",mat_binary);
//    cout<<__func__<<" type: "<<type<<endl;
    Mat mat_distibution;
    switch (type) {
    case direction_Crosswise:{
        mat_distibution=Mat::zeros(1,mat_binary.cols,CV_32SC1);
        int* distributionrowptr = const_cast<int*>(mat_distibution.ptr<int>(0));
        for(int r=0;r<mat_binary.rows;r++){
            uchar* grayrowptr = const_cast<uchar*>(mat_binary.ptr<uchar>(r));
            for(int c=0;c<mat_binary.cols;c++){
                if(grayrowptr[c]!=0){
                    distributionrowptr[c]+=1;
                }
            }
        }
        break;
    }
    case direction_Lengthwise:{
        mat_distibution=Mat::zeros(1,mat_binary.rows,CV_32SC1);
        int* distributionrowptr = const_cast<int*>(mat_distibution.ptr<int>(0));
        for(int r=0;r<mat_binary.rows;r++){
            uchar* grayrowptr = const_cast<uchar*>(mat_binary.ptr<uchar>(r));
            for(int c=0;c<mat_binary.cols;c++){
                if(grayrowptr[c]!=0){
                    distributionrowptr[r]+=1;
                }
            }
        }
        break;
    }
    }

    return mat_distibution;

}



void copyFile(string file_src, string file_dst)
{
    string command = "cp ";
    command  += file_src;
    command  += " ";
    command  += file_dst;//cp /home/file1 /root/file2
    system(command.c_str());//
}

void mkDir(string dir ){

    string command = "mkdir -p " + dir;
    system(command.c_str());
}


void rmDir(string dir){
    string command_rm = "rm " + dir+" -rf";
    system(command_rm.c_str());
}



int countBrightPix(const cv::Mat & mat_src){
    int  count=0;
    for(int r=0;r<mat_src.rows;r++){
        uchar* grayrowptr = const_cast<uchar*>(mat_src.ptr<uchar>(r));

        for(int c=0;c<mat_src.cols;c++){
            if(grayrowptr[c]==255){
                count++;
            }

        }
    }
    return count;
}

int countBrightPixInConnectDomainIncludePoint(const cv::Mat & mat_src,
                                              cv::Point point,
                                              cv::Point& point_center){

    //    cout<<__func__<<point<<endl;

    //!一点的连通域的位置信息
    vector<Point> list_position_refer;
    list_position_refer.push_back(Point(-1,-1));
    list_position_refer.push_back(Point(-1,0));
    list_position_refer.push_back(Point(-1,1));
    list_position_refer.push_back(Point(0,-1));
    list_position_refer.push_back(Point(0,1));
    list_position_refer.push_back(Point(1,-1));
    list_position_refer.push_back(Point(1,0));
    list_position_refer.push_back(Point(1,1));


    //当某一点被确认在连通域内时，该图片上的相应点被置为1
    Mat mat_connectdemon_refer=Mat::zeros(mat_src.rows,mat_src.cols,CV_8UC1);
    //为避免输入重复的候选点，或者排除重复的候选点时的遍历计算，用该图进行标识已有的候选点
    Mat mat_candidate_refer=Mat::zeros(mat_src.rows,mat_src.cols,CV_8UC1);

    //为避免从将已经计算过的不属于连通域的像素点再次输入候选点，建立此图以标识，不属于连通域的点
    Mat mat_not_refer=Mat::zeros(mat_src.rows,mat_src.cols,CV_8UC1);

    //当某一点确认为连通域上的一点时，他的8领域将被选为连通域的候选点。
    vector<Point> list_candidate;

    //给定点将作为连通域的种子
    if(mat_src.at<uchar>(point.y,point.x)>127){
        list_candidate.push_back(point);
        mat_candidate_refer.at<uchar>(point.y,point.x)=255;
    }
    else{
        cout<<">>error mid point is not bright"<<endl;

        return 0;
    }

    int count_pix_connectdemon=0;
    double sum_connectdemon_y=0;
    double sum_connectdemon_x=0;



    while(list_candidate.size()>0){

        //        //!test
        //        cout<<"list_candidate.size:"<<list_candidate.size()<<endl;
        //        for(uint i=0;i<list_candidate.size();i++){
        //            cout<<"i: "<<i<<" "<<list_candidate[i]<<endl;
        //        }

        //在获选点列表中取一点，判断其是佛i否属于连通域中的一个。由于位置条件以满足，只需判断其像素条件
        Point point_tmp(list_candidate[0]);

        list_candidate.erase(list_candidate.begin());
        if(mat_src.at<uchar>(point_tmp.y,point_tmp.x)>127){
            mat_connectdemon_refer.at<uchar>(point_tmp.y,point_tmp.x)=255;
            count_pix_connectdemon++;
            sum_connectdemon_y+=point_tmp.y;
            sum_connectdemon_x+=point_tmp.x;
            mat_candidate_refer.at<uchar>(point_tmp.y,point_tmp.x)=0;

            //将该点的8领域输入候选点列表，不属于候选点，已验证不属于，已验证属于中的任一个
            for(uint num_pos=0;num_pos<list_position_refer.size();num_pos++){
                Point point_along=list_position_refer[num_pos]+point_tmp;
                if((point_along.x<mat_src.cols&&point_along.y<mat_src.rows
                    &&point_along.x>=0&&point_along.y>=0)){
                    if(mat_candidate_refer.at<uchar>(point_along.y,point_along.x)==0&&
                            mat_not_refer.at<uchar>(point_along.y,point_along.x)==0&&
                            mat_connectdemon_refer.at<uchar>(point_along.y,point_along.x)==0){

                        list_candidate.push_back(point_along);
                        mat_candidate_refer.at<uchar>(point_along.y,point_along.x)=255;
                    }
                }
            }
        }
        else{
            mat_not_refer.at<uchar>(point_tmp.y,point_tmp.x)=255;
        }
    }
    point_center.x=static_cast<int>(sum_connectdemon_x/count_pix_connectdemon);
    point_center.y=static_cast<int>(sum_connectdemon_y/count_pix_connectdemon);

    return count_pix_connectdemon;
}


int separatePositiveAndNegtive(const cv::Mat& mat_src,
                               cv::Mat &mat_positive,
                               cv::Mat &mat_negtive){
    mat_positive=Mat::zeros(mat_src.size(),mat_src.type());
    mat_negtive=Mat::zeros(mat_src.size(),mat_src.type());

    for(int r=0;r<mat_src.rows;r++){
        float* grayrowptr = const_cast<float*>(mat_src.ptr<float>(r));
        for(int c=0;c<mat_src.cols;c++){
            if(grayrowptr[c]>0){
                mat_positive.at<float>(r,c)=grayrowptr[c];
            }
            else{
                mat_negtive.at<float>(r,c)=grayrowptr[c];
            }
        }
    }

    return 0;

}

std::vector<Segment> calSegmentInDistributionMat(const Mat &mat_distribution,
                                                 int v_threshold){
    std::vector<Segment> list_seg;
    //    int* ptr= mat_distribution.ptr(0);
    //若之前的匹配为正
    bool flag=false;
    Point2i point_start;
    Point2i point_end;

    for(int c=0;c<mat_distribution.cols;c++){
        //        cout<<"mat_distribution.at<float>(0,c):"<<mat_distribution.at<int>(0,c)<<endl;

        if(mat_distribution.at<int>(0,c)>v_threshold){
            if(flag==false){
                flag=true;
                point_start=Point2i(c,0);
            }

            if(flag==true&&c==mat_distribution.cols-1){
                flag=false;
                point_end=Point2i(c,0);
                Segment sement_tmp(point_start,point_end);
                list_seg.push_back(sement_tmp);
            }
        }
        else{
            if(flag==true){
                flag=false;
                point_end=Point2i(c,0);
                Segment sement_tmp(point_start,point_end);
                list_seg.push_back(sement_tmp);
            }
        }
    }
    return list_seg;
}

int getMaxXInDistributionMat(const Mat &mat_distribution){
    int* grayrowptr = const_cast<int*>(mat_distribution.ptr<int>(0));
    int value_max=0;
    int c_record=0;
    for(int c=0;c<mat_distribution.cols;c++){
        if(value_max<grayrowptr[c]){
            c_record=c;
            value_max=grayrowptr[c];
        }
    }
    return c_record;
}



int calGraySum(const cv::Mat& mat_src, Rect2i rect_area){
    int sum=0;
    for(int r=rect_area.y;r<rect_area.y+rect_area.height;r++){
        uchar* grayrowptr = const_cast<uchar*>(mat_src.ptr<uchar>(r));
        for(int c=rect_area.x;c<rect_area.x+rect_area.width;c++){
            sum+=grayrowptr[c];
        }
    }
    return sum;

}



int searchMostBright(const cv::Mat&mat_src, Size2i size_block,Rect2i& rect_targrt){
    int max_sum=0;
    int value_mid=0;
    for(int r=0;r<=mat_src.rows-size_block.height;r++){
        for(int c=0;c<=mat_src.cols-size_block.width;c++){
            Rect2i rect_tmp=Rect2i(c,r,size_block.width,size_block.height);
            int sum_tmp=calGraySum(mat_src,rect_tmp);
            if(max_sum<sum_tmp){
                max_sum=sum_tmp;
                rect_targrt=rect_tmp;
                value_mid=mat_src.at<uchar>(r+size_block.width/2,
                                            c+size_block.height/2);
            }
            else if(max_sum==sum_tmp){
                int value_mid_tmp=mat_src.at<uchar>(r+size_block.width/2,
                                                    c+size_block.height/2);
                if(value_mid<value_mid_tmp){
                    max_sum=sum_tmp;
                    rect_targrt=rect_tmp;
                    value_mid=value_mid_tmp;
                }
            }
        }
    }
    return max_sum;
}



int getXFromStraightLineAtY(cv::Point2i point0,cv::Point2i point1,int y){
    double res= (point0.x+(point1.x-point0.x)*1.0*(y-point0.y)/(point1.y-point0.y));
    return int(res+0.5);

}


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



std::vector<Vec2i> getVectorAtDistance(int num){
    std::vector<Vec2i> list_vector;
    assert(num>=0);
    if(num==0){
        list_vector.push_back(Vec2i(0,0));
        return list_vector;
    }
    int start=-num;
    int end=num;
    for(int r=start;r<=end;r++){
        if(r!=start&&r!=end){
            list_vector.push_back(Vec2i(start,r));
            list_vector.push_back(Vec2i(end,r));
        }
        else{
            for(int c=start;c<end;c++){
                list_vector.push_back(Vec2i(c,r));
            }

        }
    }
    return list_vector;
}


bool findNearBrightPoint(const cv::Mat& mat_src,Point2i point_given,Point& point_get){
    int value_distance=0;
    while(1){
        std::vector<Vec2i> list_vec=getVectorAtDistance(value_distance);
        uint cout_error=0;
        for(uint i=0;i<list_vec.size();i++){
            if((list_vec[i][1]+point_given.y)<0
                    ||(list_vec[i][1]+point_given.y)>=mat_src.rows
                    ||(list_vec[i][0]+point_given.x)<0
                    ||(list_vec[i][0]+point_given.x)>=mat_src.cols
                    ){
                cout_error++;
                continue;
                //                return false;
            }
            if(mat_src.at<uchar>(list_vec[i][1]+point_given.y,
                                 list_vec[i][0]+point_given.x)>0){
                point_get=Point(list_vec[i][0]+point_given.x,
                        list_vec[i][1]+point_given.y);
                return true;
            }
        }
        if(cout_error == list_vec.size()){
            return false;
        }
        value_distance++;
    }

}



void saveFile(char* content,std::string file_dst) {

    FILE *fp = NULL;
    fp = fopen(file_dst.c_str(),"w");
    if(fp!=NULL){
        fprintf(fp,content);
        fclose(fp);
    }

    return ;
}

int getStringFromFile(std::string dirpath,char** content){
//    cout<<__func__<<" start"<<dirpath<<endl;
    filebuf *pbuf;
    ifstream filestr;

    long size;
    // 要读入整个文件，必须采用二进制打开
    filestr.open (dirpath.c_str(), ios::binary);
    // 获取filestr对应buffer对象的指针
    pbuf=filestr.rdbuf();

    // 调用buffer对象方法获取文件大小
    size=pbuf->pubseekoff (0,ios::end,ios::in);

    pbuf->pubseekpos (0,ios::in);

    if(size<=0){

        return -1;
    }
//    cout<<size<<endl;
    // 分配内存空间

    *content=new char[size];

    // 获取文件内容
    pbuf->sgetn (*content,size);

    filestr.close();
    // 输出到标准输出
//    cout.write (*content,size);
//    cout<<__func__<<" end"<<endl;

    return 0;
}



int getRectInMat(const Size& size_mat,const Rect & rect_src,Rect & rect_target){

    int start_x=rect_src.x;
    int end_x=rect_src.x+rect_src.width;
    int start_y=rect_src.y;
    int end_y=rect_src.y+rect_src.height;
    cout<<"end_y: "<<end_y<<endl;

    assert(start_x<end_x);
    assert(start_y<end_y);

    start_x=start_x>=0?start_x:0;
    start_y=start_y>=0?start_y:0;

    end_x=end_x<=(size_mat.width-1)?end_x:(size_mat.width-1);
    end_y=end_y<=(size_mat.height-1)?end_y:(size_mat.height-1);
    rect_target.x=start_x;
    rect_target.y=start_y;
    rect_target.width=end_x-start_x;
    rect_target.height=end_y-start_y;

    return 0;
}



bool isRectInMat(const Size size_mat,const Rect& rect_block){
    int start_x=rect_block.x;
    int start_y=rect_block.y;
    int end_x=rect_block.x+rect_block.width;
    int end_y=rect_block.y+rect_block.height;
    if(start_x>=0
            &&start_x<end_x
            &&end_x<size_mat.width
            &&start_y>=0
            &&start_y<end_y
            &&end_y<size_mat.height
            ){
        return true;
    }

    else{
        return false;
    }


}

Rect getRectInMat(const Size size_mat,const Rect& rect_block){
    Rect rect_res;
    assert(rect_block.width>0);
    assert(rect_block.height>0);
    int start_block_y=rect_block.y;
    int start_block_x=rect_block.x;
    int end_block_x=rect_block.x+rect_block.width;
    int end_block_y=rect_block.y+rect_block.height;
    start_block_y=start_block_y>0?start_block_y:0;
    start_block_x=start_block_x>0?start_block_x:0;
    end_block_x=end_block_x<(size_mat.width-1)?
                end_block_x:(size_mat.width-1);
    end_block_y=end_block_y<(size_mat.height-1)?
                end_block_y:(size_mat.height-1);
    rect_res.x=start_block_x;
    rect_res.y=start_block_y;
    rect_res.width=end_block_x-start_block_x;
    rect_res.height=end_block_y-start_block_y;
    return rect_res;
}


LinePara calLineByHough(const std::vector<Point2i> list_point){
    LinePara line_res;
    //! 遍历所有不同的俩点N（N-1）/2，求出所有直线
    std::vector<LinePara> list_line;
    for(uint i=0;i<list_point.size();i++){
        for(uint j=0;j<list_point.size();j++){
            if(i!=j){
                cout<<"list_point[i]:"<<list_point[i]<<endl;
                cout<<"list_point[j]:"<<list_point[j]<<endl;
                list_line.push_back(LinePara::getLine(list_point[i],list_point[j]));
                cout<<"LinePara:"<<LinePara::getLine(list_point[i],list_point[j]).jsonString()<<endl;
            }
        }
    }
    //! 计算截距与斜率的范围
    double k_min=0;
    double k_max=0;
    double b_min=0;
    double b_max=0;
    for(uint i=0;i<list_line.size();i++){
        if(i==0){
            k_min=list_line[i].k;
            k_max=list_line[i].k;
            b_min=list_line[i].b;
            b_max=list_line[i].b;
        }
        else{
            if(k_min>list_line[i].k){
                k_min=list_line[i].k;
            }
            if(k_max<list_line[i].k){
                k_max=list_line[i].k;
            }
            if(b_min>list_line[i].b){
                b_min=list_line[i].b;
            }
            if(b_max<list_line[i].b){
                b_max=list_line[i].b;
            }
        }
    }

    cout<<"k_min:"<<k_min<<endl;
    cout<<"k_max:"<<k_max<<endl;
    cout<<"b_min:"<<b_min<<endl;
    cout<<"b_max:"<<b_max<<endl;

    //!建立映射将斜率和截距转换为正整数
    //! 暂定为100*100像素的图片，根据数据的可区分程度确定不同的辅助矩阵尺度
    Size size_mat_help(100,100);

    double k_per_pix=(size_mat_help.width-1)*1.0/(k_max-k_min);
    //    int k_max_pix=static_cast<int>(k_max*1.0/k_per_pix);
    //    int k_pix_move=size_mat_help.width-k_max_pix;

    double b_per_pix=(size_mat_help.height-1)*1.0/(b_max-b_min);
    //    int b_max_pix=static_cast<int>(b_max*1.0/b_per_pix);
    //    int b_pix_move=size_mat_help.height-b_max_pix;
    vector<vector<vector<LinePara>>> map_line;
    map_line.resize(static_cast<uint>(size_mat_help.height));
    for(uint i=0;i<map_line.size();i++){
        map_line[i].resize(static_cast<uint>(size_mat_help.width));
    }
    for(uint i=0;i<list_line.size();i++){
        int r=static_cast<int>((list_line[i].b-b_min)*1.0*b_per_pix);
        int c=static_cast<int>((list_line[i].k-k_min)*1.0*k_per_pix);
        cout<<"c:"<<c<<endl;
        cout<<"r:"<<r<<endl;
        map_line[static_cast<uint>(r)][static_cast<uint>(c)].push_back(list_line[i]);
    }

    cout<<"k_per_pix:"<<k_per_pix<<endl;
    cout<<"b_per_pix:"<<b_per_pix<<endl;

    Size size_pix(size_mat_help/2);
    //    Size size_pix(static_cast<int>(v_k/k_per_pix),
    //                  static_cast<int>(v_b/b_per_pix));
    cout<<"size_pix:"<<size_pix<<endl;
    //!统计图片中size_pix点最密集的区域
    uint sum_line_max=0;
    uint start_max_c=0;
    uint start_max_r=0;
    for(uint r=0;r<static_cast<uint>(size_mat_help.height-size_pix.height);r++){
        for(uint c=0;c<static_cast<uint>(size_mat_help.width-size_pix.width);c++){
            uint sum_line_tmp=0;
            for(uint r_mv=0;r_mv<static_cast<uint>(size_pix.height);r_mv++){
                for(uint c_mv=0;c_mv<static_cast<uint>(size_pix.height);c_mv++){
                    //                    cout<<"r+r_mv:"<<r+r_mv<<endl;
                    //                    cout<<"c+c_mv:"<<c+c_mv<<endl;
                    sum_line_tmp+=map_line[r+r_mv][c+c_mv].size();
                }
            }
            if(sum_line_max<sum_line_tmp){
                sum_line_max=sum_line_tmp;
                start_max_r=r;
                start_max_c=c;
            }
        }
    }

    std::vector<Point2d> list_point_inarea;
    for(uint r_mv=0;r_mv<static_cast<uint>(size_pix.height);r_mv++){
        for(uint c_mv=0;c_mv<static_cast<uint>(size_pix.width);c_mv++){
            for(uint num=0;num<map_line[start_max_r+r_mv][start_max_c+c_mv].size();
                num++){
                list_point_inarea.push_back(
                            Point2d(map_line[start_max_r+r_mv][start_max_c+c_mv][num].k,
                        map_line[start_max_r+r_mv][start_max_c+c_mv][num].b));
            }
        }
    }

    Point2d point_mid=basic::getMidPoint(list_point_inarea);
    return LinePara(point_mid.x,point_mid.y);
}


LinePara calLineByHoughWithComfirmedPoints(const std::vector<Point2i> list_point){
    //! 遍历所有不同的俩点N（N-1）/2，求出所有直线
    //    std::vector<LinePara> list_line;
    assert(list_point.size()>0);

    double sum_k=0;
    double sum_b=0;
    int count=0;


    for(uint i=0;i<list_point.size();i++){
        for(uint j=0;j<list_point.size();j++){
            if(i!=j){
                LinePara line_tmp=LinePara::getLine(list_point[i],list_point[j]);
                count++;
                sum_k+=line_tmp.k;
                sum_b+=line_tmp.b;
            }
        }
    }
    return LinePara(sum_k/count,sum_b/count);

}

Point calPointInLineGivenY(Point point_0,Point point_1,int point_y){
    if(point_0.x==point_1.x){

        return Point(point_0.x,point_y);
    }
    else{
        return LinePara::getLine(point_0,point_1).getPointGivenY(point_y);
    }
}



int getDistanceFromPoint(Point point_mid,Point point_edge){
    Point point_div=point_mid-point_edge;
    point_div=Point(abs(point_div.x),abs(point_div.y));
    if(point_div.x>point_div.y){
        return point_div.x;
    }
    else{
        return point_div.y;
    }
}



int calMeanOfPointInMat(const Point& point_mid,const Mat &mat_src,int range){
    assert(isPointInMat(point_mid,mat_src)&&range>=0);
    int start_x=point_mid.x-range;
    int end_x=point_mid.x+range;
    int start_y=point_mid.y-range;
    int end_y=point_mid.x+range;
    start_x=start_x>0?start_x:0;
    start_y=start_y>0?start_y:0;
    end_x=end_x<(mat_src.cols-1)?end_x:(mat_src.cols-1);
    end_y=end_y<(mat_src.rows-1)?end_y:(mat_src.rows-1);

    double sum_pix=0;
    int count=(end_x-start_x)*(end_y-start_y);
    for(int r=start_y;r<=end_y;r++){
        uchar* grayrowptr=const_cast<uchar*>(mat_src.ptr<uchar>(r) );
        for(int c=start_x;c<end_x;c++){
            sum_pix+=grayrowptr[c];
        }
    }
    return static_cast<int>(sum_pix/count);
}

bool isPointInMat(const Point& point, const Mat &mat_src){
    if(point.x<mat_src.cols&&point.y<mat_src.rows){
        return true;
    }
    else{
        return false;
    }
}


std::vector<Point> getPaddingListAlongLowGray(const Mat &mat_src,
                                              Point point_start,
                                              int v_range){
    //    for(){}
}


std::vector<Point> smoothPointListWithMedian(const std::vector<Point> & list_point,
                                             int v_offset_x,
                                             int v_offset_y,
                                             int v_length){
    assert(v_length<static_cast<int>(list_point.size()));
    std::vector<Point>  list_correct=list_point;
    uint radius=static_cast<uint>(v_length/2);
    uint length=radius*2+1;
    for(uint i=0;i<list_point.size()-length+1;i++ ){
        std::vector<Point> list_tmp;
        Point point_mid_src=list_point[i+radius];
        for(uint j=i;j<i+static_cast<uint>(length);j++){
            list_tmp.push_back(list_point[j]);
        }
        Point point_mid_cal=getMidPoint(list_tmp);
        if(abs(point_mid_cal.x-point_mid_src.x)>v_offset_x
                ||abs(point_mid_cal.y-point_mid_src.y)>v_offset_y){
            list_correct[i+radius]=point_mid_cal;
        }
    }

    //处理端点的若干点
    //! 假设经过中值矫正的点都是正常的
    //! 先用可靠的值差值法进行该点的估计，对该点的准确性做判断，若超出阈值，则用求出的点作为该点的矫正
    //! 起点部分使用后侧的点对前侧的点进行估计，因为后侧的点经过了中值优化
    for(int i=static_cast<int>(radius-1);i>=0;i--){
        std::vector<Point> list_tmp;
        Point point_src=list_correct[static_cast<uint>(i)];
        for(int j=0;j<i+1+static_cast<int>(radius);j++){
            if(static_cast<uint>(j)<list_point.size()){
                list_tmp.push_back(list_correct[static_cast<uint>(j)]);
            }
        }
        Point point_cal=estimatePointWithComfirmPoints(list_tmp,point_src.y);

        if(abs(point_cal.x-point_src.x)>v_offset_x
                ||abs(point_cal.y-point_src.y)>v_offset_y){
            list_correct[static_cast<uint>(i)]=point_cal;
        }
    }



    //处理后侧的端点
    int listsize=static_cast<int>(list_point.size());
    for(int i=listsize-static_cast<int>(radius);i<listsize;i++){
        std::vector<Point> list_tmp;
        Point point_src=list_correct[static_cast<uint>(i)];
        for(int j=listsize-1;j>i-1-static_cast<int>(radius);j--){
            if(j>=0&&j<listsize){
                list_tmp.push_back(list_correct[static_cast<uint>(j)]);
            }
        }
        Point point_cal=estimatePointWithComfirmPoints(list_tmp,point_src.y);
        if(abs(point_cal.x-point_src.x)>v_offset_x
                ||abs(point_cal.y-point_src.y)>v_offset_y){
            list_correct[static_cast<uint>(i)]=point_cal;
        }
    }

    return list_correct;
}


Point estimatePointWithComfirmPoints(const std::vector<Point> &list_point_comfirm,
                                     int point_y){

    std::vector<Point> list_point;
    for(uint i=0;i<list_point_comfirm.size();i++){
        for(uint j=0;j<list_point_comfirm.size();j++){
            if(i!=j){
                Point point_tmp;
                     point_tmp=calPointInLineGivenY(list_point_comfirm[i],list_point_comfirm[j],point_y);
                list_point.push_back(point_tmp);
            }
        }
    }

    return getMidPoint(list_point);
}


std::vector<Point>  smoothPointListWithMean(const std::vector<Point> & list_point,
                                            int v_length){
    std::vector<Point> list_point_after_correct;
    list_point_after_correct.resize(list_point.size());
    int listsize=static_cast<int>(list_point.size());
    for(uint i=0;i<list_point.size();i++){
        int start_tmp=static_cast<int>(i)-v_length;
        int end_tmp=static_cast<int>(i)+v_length;
        start_tmp=start_tmp>0?start_tmp:0;
        end_tmp=end_tmp<listsize-1?end_tmp:listsize-1;

        int sum_tmp_x=0;
        int sum_tmp_y=0;
        for(int j=start_tmp;j<=end_tmp;j++){
            sum_tmp_x+=list_point[static_cast<uint>(j)].x;
            sum_tmp_y+=list_point[static_cast<uint>(j)].y;
        }
        list_point_after_correct[i]=Point(sum_tmp_x/(end_tmp-start_tmp+1),
                                          sum_tmp_y/(end_tmp-start_tmp+1));
    }

    return list_point_after_correct;
}


bool isPointListInRect(const vector<Point> &v_list_point,const Rect v_rect){
    for(uint i=0;i<v_list_point.size();i++){
        if(v_list_point[i].x>=v_rect.x&&v_list_point[i].x<v_rect.x+v_rect.width
                &&v_list_point[i].y>=v_rect.y&&v_list_point[i].y<v_rect.y+v_rect.height){
        }
        else{
            return false;
        }
    }
    return true;
}


Point predictNextPointInList(const std::vector<Point> v_list_point,
                             int v_count_refer,
                             int v_offset){

    int length_list=static_cast<int>(v_list_point.size());
    int length_cal=length_list<v_count_refer?length_list:v_count_refer;
    Point2d sum(0,0);
    double count=0;
    for(int i=0;i<length_cal;i++){
        if(distance(v_list_point[static_cast<uint>(length_list-1-i)])<=v_offset){
            count+=1.0/(1+i);
            sum=sum+static_cast<Point2d>(v_list_point[static_cast<uint>(length_list-1-i)]*1.0/(1+i));
        }
    }
//    cout<<"count:"<<count<<endl;
    if(count<DBL_MIN&&count>-DBL_MIN){
        return Point(0,0);
    }
    else{
        Point point_res=static_cast<Point>(sum/count);
        return point_res;

    }
}

bool isFileExist(const string &path_file){
    fstream _file;
    _file.open(path_file, ios::in);
    if(!_file)
    {
        return false;
    }
    else
    {
        return true;
    }

}








}
