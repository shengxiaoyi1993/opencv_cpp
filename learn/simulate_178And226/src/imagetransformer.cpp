#include "imagetransformer.h"
#include <iostream>
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>

using namespace std;
using namespace cv;


//------------------------------------------------------------------------------
ImageTransformer::ImageTransformer(int v_channels,
                                   int v_bit_channel,
                                   int v_bit_delivery):
    m_channels(v_channels),
    m_bit_channel(v_bit_channel),
    m_bit_delivery(v_bit_delivery)
{

}



//------------------------------------------------------------------------------
int ImageTransformer::transform(const cv::Mat & mat_src,
              const std::string & path_output){

    if(mat_src.empty()){
        cout<<"input image is empty"<<endl;
        return  -1;
    }


    Mat mat_clone;
    if(mat_src.channels() != 1){
        cvtColor(mat_src, mat_clone, COLOR_BGR2GRAY);
    }
    else{
        mat_clone=mat_src.clone();
    }

    //计算每一行的数据，将数据保存文件中
    for(int c_r=0;c_r<mat_clone.rows;c_r++){
        uchar* pdata_rows_tmp=mat_clone.ptr<uchar>(c_r);
        int size_output;
        void *psave=FrameData::transformToFrameData(m_channels,
                                                     m_bit_channel,
                                                     m_bit_delivery,
                                                     mat_clone.cols,
                                                     pdata_rows_tmp,
                                                     size_output
                                                     );
        cout<<"size_output: "<<size_output<<endl;


        //将
        if(psave!=nullptr && size_output!=0){
            int flag = saveBufferToFile(static_cast<uchar*>(psave),
                                        static_cast<uint>(modWithCeil(size_output,8)),
                                        path_output);
            free(psave);
            psave=nullptr;
        }
        else{
            cout<<">>Error: Fail to save"<<endl;
            return -1;
        }

    }
    return 0;



}


//------------------------------------------------------------------------------
int saveBufferToFile(const uchar* v_pdata,uint size,std::string path_file){

        FILE *fp = fopen(path_file.c_str(), "ab");
        if (fp==nullptr) {
        printf("can't open file\n");
        return -1;
        }
        else{
            fwrite(v_pdata, sizeof(char)*size, 1, fp);
            fclose(fp);
            return 0;
        }
}

//------------------------------------------------------------------------------
void generateInsertList(std::vector<int> & v_list,int v_min,int v_max){
    srand(static_cast<unsigned>(time(nullptr)));//用当前时间，设置种子
    for(uint c_l=0;c_l<v_list.size();c_l++){
        cout<<"rand():"<<rand()<<endl;
        v_list[c_l]=((v_max-v_min)*(rand()%100))/100+v_min;
    }



}




