#include "opencv_basic/opencv_transform.h"
#include "opencv_basic/opencv_basic.h"


using namespace   std;
using namespace   cv;


namespace transformation {
cv::Mat rotateAndCutImage(const cv::Mat& mat_src,double angle,Rect2i &rect_in){

    if(angle<0.001&&angle>-0.001){
        return mat_src;
    }
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

    if(w_tl>h_tl){
        rect_in=Rect2i(w_tr,h_tl,rot_image.cols-2*w_tr,rot_image.rows-2*h_tl);
    }
    else{
        rect_in=Rect2i(w_tl,h_tr,rot_image.cols-2*w_tl,rot_image.rows-2*h_tr);
    }

    Mat mat_in;
    if(rect_in.x>=0&&rect_in.y>=0&&rect_in.width>0&&rect_in.height>0){
        mat_in=rot_image(rect_in);
    }

    return mat_in;

}



cv::Mat cutImageByLine(const int startline,
                       const int endline,
                       const Mat& mat_src){

    Mat mat_res;
    if(startline<endline&&startline>=0&&endline<mat_src.rows){
        mat_res=mat_src(Rect2i(0,startline,mat_src.cols,endline-startline+1));
    }
    else{
        cout<<__func__<<": para of cut wrong"<<endl;
    }
    return mat_res;

}

cv::Mat cutImageByCol(const int startcol,
                      const int endcol,
                      const Mat& mat_src){
    Mat mat_res;
    if(startcol<endcol&&startcol>=0&&endcol<mat_src.cols){
        mat_res=mat_src(Rect2i(startcol,0,endcol-startcol+1,mat_src.rows));
    }
    else{
        cout<<__func__<<": para of cut wrong"<<endl;
    }
    return mat_res;

}


std::vector<cv::Mat>  cutMatIntoSeveralChunkCrosswise(const cv::Mat& mat_src,int num_chunk){
    std::vector<cv::Mat> list_matcut;
    int cols=mat_src.cols;
    int rows=mat_src.rows;
    if(cols==0||rows==0){
        cout<<__func__<<": image is empty"<<endl;
        return list_matcut;
    }

    std::vector<int> list_rows;
    int sum_help=0;
    for(int i=0;i<num_chunk-1;i++){
        sum_help+=rows/num_chunk;
        list_rows.push_back(sum_help-1);

    }
    list_rows.push_back(rows-1);

    //example:2048
    //->512 512 512 512
    //0~511 512~1023 1024~1535 1536~2047

    for(unsigned int i=0;i<list_rows.size();i++){
        Mat mat_chunk_tmp;
        if(i==0){
            mat_chunk_tmp=cutImageByLine(0,list_rows[i],mat_src);
        }
        else{
            mat_chunk_tmp=cutImageByLine(list_rows[i-1]+1,list_rows[i],mat_src);

        }
        list_matcut.push_back(mat_chunk_tmp);
    }
    return  list_matcut;
}



std::vector<cv::Mat>  cutMatIntoSeveralChunkLengthwise(const cv::Mat& mat_src,int num_chunk){
    std::vector<cv::Mat> list_matcut;
    int cols=mat_src.cols;
    int rows=mat_src.rows;
    if(cols==0||rows==0){
        cout<<__func__<<": image is empty"<<endl;
        return list_matcut;
    }

    std::vector<int> list_cols;
    int sum_help=0;
    for(int i=0;i<num_chunk-1;i++){
        sum_help+=cols/num_chunk;
        list_cols.push_back(sum_help-1);

    }
    list_cols.push_back(cols-1);

    //example:2048
    //->512 512 512 512
    //0~511 512~1023 1024~1535 1536~2047

    for(unsigned int i=0;i<list_cols.size();i++){
        Mat mat_chunk_tmp;
        if(i==0){
            mat_chunk_tmp=cutImageByCol(0,list_cols[i],mat_src);
        }
        else{
            mat_chunk_tmp=cutImageByCol(list_cols[i-1]+1,list_cols[i],mat_src);

        }
        list_matcut.push_back(mat_chunk_tmp);
    }
    return  list_matcut;
}




cv::Mat getImageCorrectCrosswise(const cv::Mat& mat_src,
                                 std::vector<Point2i> list_point_correct,
                                 int interval_lengthwise,
                                 int width_target,
                                 ImageReverse flag){
    Mat mat_result;
    if(flag == ImageReverse_right){
        for(uint i=0;i<list_point_correct.size()-1;i++){
            Point2f srcTri[4],dstTri[4];
            srcTri[0]=list_point_correct[i];
            srcTri[1]=Point(mat_src.cols-1,list_point_correct[i].y);
            int tmp_x=opencv_basic::getXFromStraightLineAtY(list_point_correct[i],
                                                     list_point_correct[i+1],
                    list_point_correct[i+1].y-1);
            srcTri[2]=Point(tmp_x,list_point_correct[i+1].y-1);
            srcTri[3]=Point(mat_src.cols-1,list_point_correct[i+1].y-1);

            dstTri[0]=Point(0,0);
            dstTri[1]=Point(width_target-1,0);
            dstTri[2]=Point(0,interval_lengthwise-1);
            dstTri[3]=Point(width_target-1,interval_lengthwise-1);
            Mat transform=Mat::zeros(3,3,CV_32FC1);
            transform=getPerspectiveTransform(srcTri,dstTri);
            Mat mat_correct_tmp;
            warpPerspective(mat_src,mat_correct_tmp,transform,
                            Size(width_target,interval_lengthwise));
            if(mat_result.rows==0){
                mat_result=mat_correct_tmp;
            }
            else{
                vconcat(mat_result,mat_correct_tmp,mat_result);
            }
        }
    }
    else if(flag == ImageReverse_left){
        for(uint i=0;i<list_point_correct.size()-1;i++){
            Point2f srcTri[4],dstTri[4];
            srcTri[0]=Point(0,list_point_correct[i].y);
            srcTri[1]=list_point_correct[i];
            srcTri[2]=Point(0,list_point_correct[i+1].y-1);
            int tmp_x=opencv_basic::getXFromStraightLineAtY(list_point_correct[i],
                                                     list_point_correct[i+1],
                    list_point_correct[i+1].y-1);
            srcTri[3]=Point(tmp_x,list_point_correct[i+1].y-1);

            dstTri[0]=Point(0,0);
            dstTri[1]=Point(width_target-1,0);
            dstTri[2]=Point(0,interval_lengthwise-1);
            dstTri[3]=Point(width_target-1,interval_lengthwise-1);
            Mat transform=Mat::zeros(3,3,CV_32FC1);
            transform=getPerspectiveTransform(srcTri,dstTri);
            Mat mat_correct_tmp;
            warpPerspective(mat_src,mat_correct_tmp,transform,
                            Size(width_target,interval_lengthwise));
            if(mat_result.rows==0){
                mat_result=mat_correct_tmp;
            }
            else{
                vconcat(mat_result,mat_correct_tmp,mat_result);
            }
        }
    }

    return mat_result;

}



int adjustGrayAroundLengthwiseLine(cv::Mat &mat_src,
                                   int interval_length,
                                   const std::vector<float> list_gray_offset,
                                   int line_x,
                                   int width_adjust,
                                   Direction direction
                                   ){

    if(interval_length*(static_cast<int>(list_gray_offset.size())-1)
            != mat_src.rows){
        cout<<"list_gray_offset not match"<<endl;

//        return -1;
        assert(0);
    }
    if(line_x<0||line_x>=mat_src.cols){
        cout<<__func__<<" error: line_x wrong"<<endl;
        assert(0);
    }






    int flag_direction;
    switch (direction) {
    case Direction_Left:{
        flag_direction=-1;
        break;
    }
    case Direction_Right:{
        flag_direction=1;
        break;
    }
    }

    for(int r=0;r<mat_src.rows;r++){
        float gray_offset_row=opencv_basic::calValueWithProportion(
                    list_gray_offset[r/interval_length],
                list_gray_offset[r/interval_length+1],
                interval_length,r%interval_length);
//        cout<<"gray_offset_row: "<<gray_offset_row<<endl;

        uchar* grayptr=static_cast<uchar*>(mat_src.ptr(r));
        for(int c_num=0;c_num<width_adjust;c_num++){
            int c=line_x+c_num*flag_direction;
            float offset_tmp=opencv_basic::calValueWithCurve(gray_offset_row,1.0,width_adjust,c_num);
            int gray_tmp=static_cast<int>(grayptr[c]*offset_tmp);
            gray_tmp=gray_tmp<=255?gray_tmp:255;
            grayptr[c]=static_cast<uchar>(gray_tmp);
        }
    }


    return 0;
}


int getImageDivide(const cv::Mat & mat_src,cv::Size v_size,
                   int v_num,const std::vector<std::string> v_list_path){
    if(mat_src.cols!=v_size.width || mat_src.rows!=v_size.height){
        cout<<"error0"<<endl;
        return -1;
    }
    if(v_num != static_cast<int>(v_list_path.size())){
        cout<<"error1"<<endl;

        return -1;
    }
    if(v_num!=2 && v_num!=4 ){
        cout<<"error2"<<endl;

        return -1;
    }

    if(v_num == 2){
        Mat mat0=mat_src(Rect(0,0,v_size.width/2,v_size.height));
        imwrite(v_list_path[0],mat0);

        Mat mat1=mat_src(Rect(v_size.width/2,0,v_size.width/2,v_size.height));
        imwrite(v_list_path[1],mat1);

    }
    else if(v_num == 4){
        Mat mat0=mat_src(Rect(0,0,v_size.width/2,v_size.height/2));
        imwrite(v_list_path[0],mat0);

        Mat mat1=mat_src(Rect(v_size.width/2,0,v_size.width/2,v_size.height/2));
        imwrite(v_list_path[1],mat1);

        Mat mat2=mat_src(Rect(0,v_size.height/2,v_size.width/2,v_size.height/2));
        imwrite(v_list_path[2],mat2);

        Mat mat3=mat_src(Rect(v_size.width/2,v_size.height/2,v_size.width/2,v_size.height/2));
        imwrite(v_list_path[3],mat3);
    }

    return 0;

}


int getMakeUp(cv::Size v_target_size,const std::vector<std::string> v_list_path){
    if(v_list_path.size()<=0){
        return -1;
    }
    if(v_target_size.height<=0&&v_target_size.width<=0){
        return -1;
    }
    Mat mat_tmp =Mat::zeros(v_target_size.height,v_target_size.width,CV_8UC1);

    for(uint c_i=0;c_i<v_list_path.size();c_i++){
        imwrite(v_list_path[c_i],mat_tmp);
    }
    return 0;
}





}
