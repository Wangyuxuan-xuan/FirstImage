#include "image.h"
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

//int main() {
//	Mat img = imread("images//background.jpg");
//	Mat imgGary, imgBlur, imgCanny, imgDila, imgErode;
//
//	cvtColor(img, imgGary, COLOR_BGR2GRAY);
//	GaussianBlur(img, imgBlur, Size(7, 7), 5, 0);//模糊化
//	Canny(imgBlur, imgCanny, 5, 15);//detect edges in an image
//
//	Mat kernel = getStructuringElement(MORPH_RECT, Size(5, 5));
//
//	dilate(imgCanny, imgDila, kernel);//可以扩张canny图像
//	erode(imgDila,imgErode,kernel); //侵蚀
//
//	imshow("my image", img);
//	imshow("Gray_image", imgGary);
//	imshow("Blur_image", imgBlur);
//	imshow("Canny_image", imgCanny);
//	imshow("Dilation_image", imgDila);
//	imshow("Erode_image", imgErode);
//	waitKey(0);
//}