#include "image.h"
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

//int main() {
//	Mat img = imread("images//background.jpg");
//	Mat resizeImg,imageCrop;
//	resize(img, resizeImg, Size(600,800));
//	//resize(img, resizeImg, Size(),0.5,0.5);
//	cout << img.size() << endl;
//	
//	Rect rect(100,100,300,250);
//	imageCrop = img(rect);//not crop from the middle , but according to the coordinate
//
//
//	imshow("my image", img);
//	imshow("resize", resizeImg);
//
//	imshow("crop", imageCrop);
//
//	waitKey(0);
//}
