#include "tiledetect.h"

int moveDetect(Mat frame, Mat previous_frame, Mat mask) {
    GaussianBlur(frame, frame, Size( 3, 3 ), -1);
    GaussianBlur(previous_frame, previous_frame, Size( 3, 3 ), -1);
    absdiff(frame, previous_frame, mask);
    //imshow("After absdiff:", mask);
    threshold( mask, mask, 100, 255, THRESH_BINARY );
    imshow("After threshold:", mask);
    if(somethingIsMoving(mask) == 1){
        if (paused == 0){
            paused++;
            imageCounter++;
            return 1;
        }
        else if (paused <33){ //важно! настроечный параметр, индивидуально для каждой камеры и участка
            paused++;
            return 0;
        }
        else {
            paused = 0;
            return 0;
        }
    }
}

int somethingIsMoving(Mat mask){
    int movingPoints = 0, limitValue = 10000; //важно! настроечный параметр, индивидуально для каждой камеры и участка
    for (int i = 0; i < mask.rows; i++){
        for (int j = 0; j < mask.cols; j++){
            if (mask.at<uchar>(i, j) == 255)
                movingPoints++;
        }
    }
    if (movingPoints > limitValue)
        return 1;
    else
        return 0;
}

float compareImages(Mat image, Mat temp, string filename){
    Mat t_image, t_temp, bg;
    bg = imread("background.jpg", CV_LOAD_IMAGE_GRAYSCALE); //check it!
    Mat res(image.rows-temp.rows+1, image.cols-temp.cols+1, CV_32FC1);
    cvtColor(image, t_image, CV_RGB2GRAY);
    cvtColor(temp, t_temp, CV_RGB2GRAY);
    matchTemplate(t_image, t_temp, res, CV_TM_CCORR_NORMED);
    threshold(res, res, 0.1, 1., CV_THRESH_TOZERO);
    while(true) {
        double minval, maxval, low_threshold = 0.90, high_threshold = 0.98; //важно! настроечный параметр, индивидуально для каждой камеры и участка
        cv::Point minloc, maxloc, resized_maxloc;
        cv::minMaxLoc(res, &minval, &maxval, &minloc, &maxloc);

        if(maxval >= low_threshold){
            tiles++;
            MaxVal = maxval;
            resized_maxloc.x = maxloc.x - image.cols/32;
            resized_maxloc.y = maxloc.y - image.rows/32;
//            cv::rectangle(image, resized_maxloc, cv::Point(maxloc.x + temp.cols + 5, maxloc.y + temp.rows + 5), CV_RGB(0,255,0), 2);
//            cv::floodFill(image, resized_maxloc, cv::Scalar(0), 0, cv::Scalar(.1), cv::Scalar(1.));
//            cv::Rect roi = cv::Rect(resized_maxloc.x, resized_maxloc.y, resized_maxloc.x + temp.cols, image.rows - resized_maxloc.y - 1);
            cv::Rect roi = cv::Rect(0, 0, image.cols/4 + temp.cols, image.rows);
            image = image(roi);
            filename = to_string(imageCounter) + ".jpg";
            imwrite(filename, image);
            if (maxval >= high_threshold) {
                cout << "Maxval is " << MaxVal << ". It's OK!" << endl;
                OKtiles++;
            }
            else {
                cout << "Maxval is " << MaxVal << ". Something's wrong..." << endl;
                bad++;
                if (checkGeometry(image, bg) != 0) {
                    cout << "Problem with geometry, lol" << endl;
                    broken++;
                }
                else {
                    cout << "Problem with surface" << endl;
                    badColored++;
                }
            }

            break;
        }
        else {
            break;
        }
    }
}
