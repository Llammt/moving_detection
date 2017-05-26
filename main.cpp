#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <string>
#include "tiledetect.h"
using namespace cv;
using namespace std;

int paused = 0, imageCounter = 0;
int templateHeight = 0;
int templateWidth = 0;
string filename;
double MaxVal = 0;
int tiles = 0, OKtiles = 0, broken = 0, badColored = 0, bad = 0;

int main() {
   VideoCapture stream("tileVideo2.mp4");
//    VideoCapture stream(0);
    if (!stream.isOpened())
        cout << "Cannot open camera." << endl;
    Mat frame, resized_frame, previous_frame, resized_previous_frame, mask;
    Mat roiRegion, previous_roiRegion, templateImage, writingImage, bg;
    templateImage = imread("template.jpg");
    if (templateImage.data == NULL)
        return -1;
    templateHeight = templateImage.size().height;
    templateWidth = templateImage.size().width;
    stream.read(previous_frame);  
    resize(previous_frame, resized_previous_frame, cv::Size(), 0.25, 0.25);
    cvtColor(resized_previous_frame, resized_previous_frame, CV_RGB2GRAY);
    while(stream.read(frame)){
        resize(frame, resized_frame, cv::Size(), 0.25, 0.25); 
        imshow("Video Stream", resized_frame);
        cvtColor(resized_frame, resized_frame, CV_RGB2GRAY);

        cv::Rect roi = cv::Rect(0, 0, (resized_frame.cols)/4, resized_frame.rows);
        roiRegion = resized_frame(roi);
        cv::Rect prev_roi = cv::Rect(0, 0, (resized_previous_frame.cols)/4, resized_previous_frame.rows);
        previous_roiRegion = resized_previous_frame(prev_roi);

        if (moveDetect(roiRegion, previous_roiRegion, mask) == 1) {
            resize(frame, writingImage, cv::Size(), 0.25, 0.25);
            cv::Rect newImg = cv::Rect(0, 0, (writingImage.cols)/4 + templateWidth, writingImage.rows);
            writingImage = writingImage(newImg);
            compareImages(writingImage, templateImage, filename);
        }
        previous_frame = frame;
        MaxVal = 0;
        waitKey(10);
    }

    cout << endl << endl << "tiles = " << tiles << endl;
    cout << endl << endl << "OKtiles = " << OKtiles << endl;
    cout << "Bad = " << bad << endl;
    cout << "badColored = " << badColored << endl;
    cout << "Broken = " << broken << endl;

    stream.release();
    frame.release();
    resized_frame.release();
    previous_frame.release();
    resized_previous_frame.release();
    mask.release();
    roiRegion.release();
    previous_roiRegion.release();
    templateImage.release();
    writingImage.release();
    bg.release();

    return 0;
}
