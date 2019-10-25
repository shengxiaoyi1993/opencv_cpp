#include <iostream>
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/core.hpp"
#include<vector>
#include<fstream>
#include <stdlib.h>
#include<stdlib.h>
#include<opencv2/features2d/features2d.hpp>
#include"orbmatch.h"

//#define DEBUG
using namespace std;
using namespace cv;


int main()
{

    matchWithFlann("../../../resource/image_match/move.jpg"
                ,"../../../resource/image_match/source.jpg");

    return 0;
}

