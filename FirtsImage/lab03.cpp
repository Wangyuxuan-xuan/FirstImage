#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

void copyNonWhitePixels(const Mat fg, Mat& bg) {
	Vec3b c;
	resize(bg, bg, fg.size());
	for (int i = 0; i < fg.rows; ++i) {
		for (int j = 0; j < fg.cols; ++j) {
			c = fg.at<Vec3b>(i, j);
			// if the pixel is not pure white
			if (c[0] != 255 || c[1] != 255 || c[2] != 255) { //copyÇÒ¸²¸ÇµÄÌõ¼þ
				bg.at<Vec3b>(i, j) = c;//why there's white interval???
			}
		}
	}
}

void copyKurama(const Mat fg, Mat& bg) {
	Vec3b c;
	resize(bg, bg, fg.size());
	for (int i = 0; i < fg.rows; ++i) {
		for (int j = 0; j < fg.cols; ++j) {
			c = fg.at<Vec3b>(i, j);
			if (c[0] < 200 || c[1] < 200 || c[2] < 200) { //why difference??
				bg.at<Vec3b>(i, j) = c;
			}
		}
	}
}

//int main() {
//
//	Mat fg = imread("images//kurama.jpg");
//	Mat bg = imread("images//background.jpg");
//	Mat bg2 = bg.clone();
//
//	copyNonWhitePixels(fg, bg);
//	copyKurama(fg, bg2);
//
//	imshow("copyNonWhitePixels", bg);
//	imshow("copyKurama", bg2);
//
//	waitKey(0);
//
//	return 0;
//}
