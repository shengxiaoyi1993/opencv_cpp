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




}
