#ifndef CHECKPARAMETERS_H
#define CHECKPARAMETERS_H

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <string>
#include <iostream>

using namespace cv;
using namespace std;

int checkGeometry(Mat image, Mat bg);

#endif // CHECKPARAMETERS_H
