#include "opencv_basic/opencv_match.h"
#include <iostream>
#include "opencv_basic/opencv_basic.h"
using namespace std;
using namespace cv;

namespace opencv_match{




int calMAD(const Mat &mat1,const Mat &mat2){
    Size size1=mat1.size();
    Size size2=mat2.size();

    if(size1 != size2){
        return -1;
    }
    else{
        double sum=0;
        for(int r=0;r<size1.height;r++){
            for(int c=0;c<size1.width;c++){
                sum+=abs(int(mat1.at<uchar>(r,c))-int(mat2.at<uchar>(r,c)));
            }
        }
        int mad=static_cast<int>(sum/(size1.height*size1.width));
        return mad;
    }
}


double calSSD(const Mat &mat1,const Mat &mat2){
    Size size1=mat1.size();
    Size size2=mat2.size();

    if(size1 != size2){
        return -1;
    }
    else{
        double sum=0;
        for(int r=0;r<size1.height;r++){
            for(int c=0;c<size1.width;c++){
                int div=(int(mat1.at<uchar>(r,c))-int(mat2.at<uchar>(r,c)));
                sum+=div*div;
            }
        }
        //        double ssd=sum/(size1.height*size1.width);
        return sum;

    }
}

double calMSD(const Mat &mat1,const Mat &mat2){
    Size size1=mat1.size();
    Size size2=mat2.size();

    if(size1 != size2){
        return -1;
    }
    else{
        double sum=0;
        for(int r=0;r<size1.height;r++){
            for(int c=0;c<size1.width;c++){
                int div=(int(mat1.at<uchar>(r,c))-int(mat2.at<uchar>(r,c)));
                sum+=div*div;
            }
        }
        double ssd=sum/(size1.height*size1.width);
        return ssd;

    }
}

Rect findMostMatchWithMSD(const Mat &mat_src,const Mat &mat_part){
    Size size_src=mat_src.size();
    Size size_part=mat_part.size();
    int height_div=size_src.height-size_part.width;
    int width_div=size_src.width-size_part.width;
    double min_msd=65536;
    Rect rect_res=Rect(0,0,0,0);
    for(int r=0;r<height_div;r++){
        for(int c=0;c<width_div;c++){
            Rect rect_tmp=Rect(c,r,size_part.width,size_part.height);
            double tmp=calSSD(mat_src(rect_tmp),mat_part);
            if(min_msd>tmp){
                min_msd=tmp;
                rect_res=rect_tmp;
            }
        }
    }
    return rect_res;
}


//grayimage
Rect findMostMatchWithMAD(const Mat &mat_src,const Mat &mat_part){
    Size size_src=mat_src.size();
    Size size_part=mat_part.size();
    int height_div=size_src.height-size_part.width;
    int width_div=size_src.width-size_part.width;
    int min_mad=256;
    Rect rect_res=Rect(0,0,0,0);
    for(int r=0;r<height_div;r++){
        for(int c=0;c<width_div;c++){
            Rect rect_tmp=Rect(c,r,size_part.width,size_part.height);
            int tmp=calMAD(mat_src(rect_tmp),mat_part);
            if(min_mad>tmp){
                min_mad=tmp;
                rect_res=rect_tmp;
            }
        }
    }
    return rect_res;
}


Rect findMostMatchWithSSD(const Mat &mat_src,const Mat &mat_part){
    Size size_src=mat_src.size();
    Size size_part=mat_part.size();
    int height_div=size_src.height-size_part.width;
    int width_div=size_src.width-size_part.width;
    double min_ssd=65536;
    Rect rect_res=Rect(0,0,0,0);
    for(int r=0;r<height_div;r++){
        for(int c=0;c<width_div;c++){
            Rect rect_tmp=Rect(c,r,size_part.width,size_part.height);
            double tmp=calSSD(mat_src(rect_tmp),mat_part);
            if(min_ssd>tmp){
                min_ssd=tmp;
                rect_res=rect_tmp;
            }
        }
    }
    return rect_res;
}



int calMean(const Mat &src){
    //    cout<<"channels:"<<src.channels()<<endl;
    int value=static_cast<int>(mean(src)[0]);
    return value;
}

double calSD(const Mat &mat_src){
    int mean=calMean(mat_src);
    int cols=mat_src.cols;
    int rows=mat_src.rows;
    double sum_sd=0;

    for(int r=0;r<rows;r++){
        for(int c=0;c<cols;c++){
            int tmp=(int(mat_src.at<uchar>(r,c))-mean);
            sum_sd+=tmp*tmp;
        }
    }
    return sum_sd;
}


double calCov(const Mat &mat1,const Mat &mat2){
    int cols=mat1.cols;
    int rows=mat1.rows;
    int mean1=calMean(mat1);
    int mean2=calMean(mat2);
    double sum_cov=0;
    for(int r=0;r<rows;r++){
        for(int c=0;c<cols;c++){
            //            int tmp=(int(mat1.at<uchar>(r,c))-mean1);
            sum_cov+=abs(int(mat1.at<uchar>(r,c))-mean1)*abs(int(mat2.at<uchar>(r,c))-mean2);
        }
    }
    return sum_cov;

}

double calNCC(const Mat& mat1,const Mat& mat2){
    double sum_sd_1=calSD(mat1);
    double sum_sd_2=calSD(mat2);
    double sum_cov=calCov(mat1,mat2);
    return sum_cov/(sqrt(sum_sd_1)*sqrt(sum_sd_2));
}


Rect findMostMatchWithNCC(const Mat& mat_src,const Mat &mat_part){
    Size size_src=mat_src.size();
    Size size_part=mat_part.size();
    int height_div=size_src.height-size_part.width;
    int width_div=size_src.width-size_part.width;
    double min_ncc=-1;
    Rect rect_res=Rect(0,0,0,0);
    for(int r=0;r<height_div;r++){
        for(int c=0;c<width_div;c++){
            Rect rect_tmp=Rect(c,r,size_part.width,size_part.height);
            double tmp=calNCC(mat_src(rect_tmp),mat_part);
            if(abs(min_ncc-1)>abs(tmp-1)){
                min_ncc=tmp;
                rect_res=rect_tmp;
            }
        }
    }
    return rect_res;
}


int calAMAD(const cv::Mat & mat0,const cv::Mat & mat1){
    int row=mat0.rows;
    int col=mat0.cols;
    if(mat0.size()!=mat1.size()&&(row==0||col==0)){
        return  -1;
    }

    double sum0=0;
    double sum1=0;

    for(int i=0;i<row;i++){
        uchar* grayrowptr_0 = const_cast<uchar*>(mat0.ptr<uchar>(i));//gray是cv::Mat类型的矩阵，单通道，表示灰度图像
        uchar* grayrowptr_1 = const_cast<uchar*>(mat1.ptr<uchar>(i));//gray是cv::Mat类型的矩阵，单通道，表示灰度图像
        for(int j=0;j<col;j++){
            sum0+=static_cast<int>(grayrowptr_0[j]);
            sum1+=static_cast<int>(grayrowptr_1[j]);

        }
    }
    int average0=static_cast<int>(sum0/(row*col));
    int average1=static_cast<int>(sum1/(row*col));

    double sum=0;
    for(int i=0;i<row;i++){
        uchar* grayrowptr_0 =  const_cast<uchar*>(mat0.ptr<uchar>(i));//gray是cv::Mat类型的矩阵，单通道，表示灰度图像
        uchar* grayrowptr_1 =  const_cast<uchar*>(mat1.ptr<uchar>(i));//gray是cv::Mat类型的矩阵，单通道，表示灰度图像
        for(int j=0;j<col;j++){
            sum+=abs((static_cast<int>(grayrowptr_1[j])-average1)-
                     (static_cast<int>(grayrowptr_0[j])-average0));
        }
    }
    int res=static_cast<int>(sum/(row*col));

    return res;

}


int searchMostMatch(cv::Mat mat_target,cv::Rect2i rect,int range
                    ,cv::Mat mat_block,cv::Rect2i& rect_target,
                    MatchMethod option){
    int blocksize=mat_block.cols;
    int blocksize_range=blocksize+2*range;
    int x=( rect.x-range)>0?(rect.x-range):0;
    int y= (rect.y-range)>0?(rect.y-range):0;

    int height=blocksize_range<=(mat_target.rows-y)?blocksize_range:(mat_target.rows-y);
    int width=blocksize_range<=(mat_target.cols-x)?blocksize_range:(mat_target.cols-x);

    Mat mat_range=mat_target(Rect2i(x,y,width,height));


    int minmad=INT_MAX;

    switch (option){
    case MatchMethod_NCC:
    {
        double min_ncc=-1;
        for(int i=0;i<width-blocksize;i++){
            for(int j=0;j<height-blocksize;j++){
                Mat tmpmat=mat_range(Rect2i(i,j,blocksize,blocksize));
                //match bu ncc
                double tmp=calNCC(mat_block,tmpmat);
                if(abs(min_ncc-1)>abs(tmp-1)){
                    min_ncc=tmp;
                    rect_target=Rect2i(i+x,j+y,blocksize,blocksize);
                }
            }
        }
        return  static_cast<int>(min_ncc);
    }
    case MatchMethod_MSD:{
        for(int i=0;i<width-blocksize;i++){
            for(int j=0;j<height-blocksize;j++){
                Mat tmpmat=mat_range(Rect2i(i,j,blocksize,blocksize));
                //match by msd
                int tmpmad=static_cast<int>(calMSD(tmpmat,mat_block));
                if(minmad>tmpmad){
                    minmad=tmpmad;
                    rect_target=Rect2i(i+x,j+y,blocksize,blocksize);
                }



            }
        }
        return minmad;
    }
    case MatchMethod_MAD:{
        for(int i=0;i<width-blocksize;i++){
            for(int j=0;j<height-blocksize;j++){
                Mat tmpmat=mat_range(Rect2i(i,j,blocksize,blocksize));
                //            //match by msd
                int tmpmad=calMAD(tmpmat,mat_block);
                if(minmad>tmpmad){
                    minmad=tmpmad;
                    rect_target=Rect2i(i+x,j+y,blocksize,blocksize);
                }
            }
        }
        return minmad;
    }
    case MatchMethod_AMAD:{
        for(int i=0;i<width-blocksize;i++){
            for(int j=0;j<height-blocksize;j++){
                Mat tmpmat=mat_range(Rect2i(i,j,blocksize,blocksize));
                //            //match by msd
                int tmpmad=calAMAD(tmpmat,mat_block);
                if(minmad>tmpmad){
                    minmad=tmpmad;
                    rect_target=Rect2i(i+x,j+y,blocksize,blocksize);
                }

            }
        }
        return minmad;
    }
    }
    return -1;

}



int calMidWeightMAD(const Mat &mat1,const Mat &mat2){
    Size size1=mat1.size();
    Size size2=mat2.size();
    assert(size1 == size2);

    Point point_mid=Point(size1.width/2,size1.height/2);
    int count_number=0;
    int time_max=opencv_basic::getDistanceFromPoint(point_mid,Point(size1.width-1,size1.height-1));
    double sum=0;
    for(int r=0;r<size1.height;r++){
        for(int c=0;c<size1.width;c++){
            int num_tmp=opencv_basic::getDistanceFromPoint(point_mid,Point(c,r));
            int count_tmp=static_cast<int>(pow(2,time_max-num_tmp));
            count_number+=count_tmp;
            sum+=abs(int(mat1.at<uchar>(r,c))-int(mat2.at<uchar>(r,c)))*count_tmp;
        }
    }
    int mad=static_cast<int>(sum*1.0/count_number);
    return mad;

}


int calEdgeWeightMAD(const Mat &mat1,const Mat &mat2){
    Size size1=mat1.size();
    Size size2=mat2.size();
    assert(size1 == size2);

    Point point_mid=Point(size1.width/2,size1.height/2);
    int count_number=0;

    double sum=0;
    for(int r=0;r<size1.height;r++){
        for(int c=0;c<size1.width;c++){
            int num_tmp=opencv_basic::getDistanceFromPoint(point_mid,Point(c,r));
            int count_tmp=static_cast<int>(pow(2,num_tmp));
            count_number+=count_tmp;
            sum+=abs(int(mat1.at<uchar>(r,c))-int(mat2.at<uchar>(r,c)))*count_tmp;
        }
    }
    int mad=static_cast<int>(sum*1.0/count_number);
    return mad;
}






}
