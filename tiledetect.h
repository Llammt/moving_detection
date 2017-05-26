#ifndef TILEDETECT_H
#define TILEDETECT_H

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <string>
#include <iostream>
#include "checkparameters.h"

using namespace cv;
using namespace std;

extern int paused, imageCounter;
extern int templateHeight;
extern int templateWidth;
extern string filename;
extern double MaxVal;
extern int tiles, OKtiles, broken, badColored, bad;

int moveDetect(Mat frame, Mat previous_frame, Mat mask);
int somethingIsMoving(Mat mask);
float compareImages(Mat image, Mat temp, string filename);

#endif // TILEDETECT_H
