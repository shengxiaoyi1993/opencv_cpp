#include <iostream>
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/core.hpp"
#include<vector>
#include<fstream>
#include <stdlib.h>
#include<stdlib.h>




//#define DEBUG
using namespace std;
using namespace cv;



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


int main()
{


    return 0;
}
