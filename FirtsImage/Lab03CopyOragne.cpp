#include <iostream>
#include <opencv2/core.hpp>    // osztalyok, strukturak, alapveto funkciok
#include <opencv2/highgui.hpp> // felulet
#include <opencv2/imgproc.hpp> // kepfeld. konyvtar, gyakran kell majd

using namespace std;
using namespace cv;



void copyOrangeRGB(const cv::Mat& rgb, cv::Mat& dest) {
    //creating a black image
    dest = Mat::zeros(rgb.size(), CV_8UC3);
    /* CV_8UC3 is an 8-bit unsigned integer matrix/image with 3 channels. 
    Although it is most common that this means an RGB (or actually BGR) image, 
    it does not mandate it. It simply means that there are three channel*/

    //nice
    cv::Vec3b c;
    for (int i = 0; i < rgb.rows; ++i) {
        for (int j = 0; j < rgb.cols; ++j) {
            c = rgb.at<cv::Vec3b>(i, j);
            // copy a pixel if red > green and red > blue
            if (c[2] > c[1] && c[2] > c[0])
                dest.at<cv::Vec3b>(i, j) = rgb.at<cv::Vec3b>(i, j);
        }
    }
}

void copyOrangeHSV(const cv::Mat& rgb, cv::Mat& dest) {
    //creating an image
    dest = Mat(rgb.size(), CV_8UC3);

    //painting the whole image with red color
    dest.setTo(Scalar(0, 0, 255));  //reason why background is red

    Mat hsv; // empty header
    // convert colors from BGR to HSV colorspace
    cvtColor(rgb, hsv, ColorConversionCodes::COLOR_BGR2HSV);

    cv::Vec3b c_rgb, c_hsv;
    for (int i = 0; i < rgb.rows; ++i) {
        for (int j = 0; j < rgb.cols; ++j) {
            c_rgb = rgb.at<cv::Vec3b>(i, j);
            c_hsv = hsv.at<cv::Vec3b>(i, j);
            // copy a pixel if hue < 30 (opencv range of red-orange pixels)
            if (c_hsv[0] < 30)  //原RGB图中<30 的(橘黄色)
                dest.at<cv::Vec3b>(i, j) = c_rgb;   
        }
    }
}

void copyOrangeHSV2(const cv::Mat& rgb, cv::Mat& dest) {
    //creating an image
    dest = Mat(rgb.size(), CV_8UC3);

    //painting the whole image with blue color
    dest.setTo(Scalar(255, 0, 0));

    Mat hsv; // empty header
    // convert colors from BGR to HSV colorspace
    cvtColor(rgb, hsv, ColorConversionCodes::COLOR_BGR2HSV);

    // creating a mask (black&white 1 channel image) where the pixels of the orange are white 
    Mat mask;
    inRange(hsv, Scalar(0, 0, 0), Scalar(30, 255, 255), mask);
    //在range里变成白的，反之为黑
    /*
Thresholding using cv2. inRange() function

'lowerb' and 'upperb' denotes the lower and upper boundary of the threshold region. 
A pixel is set to 255 if it lies within the boundaries specified otherwise set to 0. 
This way it returns the thresholded image.
                                                              */

    // copy all the pixel under the white part of the mask from the original image to the destination image
    rgb.copyTo(dest, mask);//前output 后input
    //how to copy the only white part and how to convert it back????

}

// one can also use template matrix
// if the type of matrix is defined, you can access the pixels easily
void copyOrangeHSV3(const cv::Mat_<cv::Vec3b>& rgb, cv::Mat_<cv::Vec3b>& dest) {
    Mat_<Vec3b> hsv;  //
    cvtColor(rgb, hsv, ColorConversionCodes::COLOR_BGR2HSV);

    //the type of the dest is already defined in the function header (cv::Vec3b --> CV_8UC3)
    dest.create(rgb.size());

    //this time we will paint the background to green
    dest.setTo(Scalar(0, 255, 0));

    int hue;
    for (int i = 0; i < rgb.rows; ++i) {
        for (int j = 0; j < rgb.cols; ++j) {
            // getting the hue value of the ith, jth pixel
            hue = hsv(i, j)[0];
            if (hue < 30) {
                dest(i, j) = rgb(i, j);
            }
        }
    }
}


int main() {

    Mat orig = imread("images//orange1.jpg");
    if (orig.empty())
    {
        cout << "A empty image" << endl;
        exit(-1);
    }

    Mat dest_rgb;
    copyOrangeRGB(orig, dest_rgb);

    Mat dest_hsv;
    copyOrangeHSV(orig, dest_hsv);

    Mat_<Vec3b> dest_hsv2;
    copyOrangeHSV2(orig, dest_hsv2);

    Mat_<Vec3b> dest_hsv3;
    copyOrangeHSV3(orig, dest_hsv3);


    imshow("original", orig);
    imshow("using_rgb", dest_rgb);
    imshow("using_hsv_v1", dest_hsv);
    imshow("using_hsv_v2", dest_hsv2);
    imshow("using_hsv_v3", dest_hsv3);
    waitKey(0);

    return 0;
}