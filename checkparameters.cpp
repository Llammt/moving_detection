#include "checkparameters.h"

int checkGeometry(Mat image, Mat bg) {
    Mat mask;
    vector<vector<Point> > contours, appContours;
    vector<Vec4i> hierarchy;

    cvtColor(image, image, CV_RGB2GRAY);
    GaussianBlur(image, image, Size( 23, 23 ), -1);
    GaussianBlur(bg, bg, Size( 23, 23 ), -1);
    absdiff(image, bg, mask);
    threshold( mask, mask, 50, 255, THRESH_BINARY );
    Canny(mask, mask, 50, 255, 3 );
    findContours( mask, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );
    appContours.resize(contours.size());

    for( int i = 0; i< contours.size(); i++ ) {
        convexHull( Mat(contours[i]), contours[i], false );
        approxPolyDP(contours[i], appContours[i], 7, true);
        if(contourArea(appContours[i]) > mask.rows*mask.cols/4){
            if (appContours[i].size() != 4)
                return -1;
            else
                return 0;
        }
    }
}
