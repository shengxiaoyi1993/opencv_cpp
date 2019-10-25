#ifndef ORBMATCH_H
#define ORBMATCH_H

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

using namespace std;
using namespace cv;

int matchWithBF(string img1,string img2);

int matchWithFlann(string img1,string img2);


#endif // ORBMATCH_H
