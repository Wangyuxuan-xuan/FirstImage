#include "contour.h"
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace std;


void question0(Mat& img) {
	// we read the image in color => we can draw on it in different colors


	// we change the color space, because the threshold method requires grayscale image
	Mat gray, mask;
	cvtColor(img, gray, COLOR_BGR2GRAY);

	// find the mask of the cheese 
	// (cheese_mask is a black&white image, type: CV_8UC1)
	threshold(gray, mask, 250, 255, THRESH_BINARY_INV);

	// a little noise filtering 
	// (without this, the findContours will return with 3 contours: the contour of the cheese and noises)
	medianBlur(mask, mask, 5);

	// find the external contour(s) of the object(s)
	vector<vector<Point>> contours;
	findContours(mask, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);

	// see the number of the contours
	cout << "num of the contours:" << contours.size();

	// draw all the contours
	drawContours(img, contours, -1, Scalar(255, 0, 255), 2);

	for (int i = 0; i < contours.size(); i++)
	{
		//double area = contourArea(i);
		//cout << "area : " << area << endl;
	}
	imshow("gray", gray);
	imshow("mask", mask);
	imshow("img", img);
	waitKey(0);

}

void question1(Mat& img) {
	vector<vector<Point>> cont;
	findContours(img, cont, RETR_EXTERNAL, CHAIN_APPROX_NONE);
	double area;
	for (vector<Point> c : cont) {
		area = contourArea(c);
		cout << area << endl;
	}
	waitKey();
}

void question2(Mat& img) {
	vector<vector<Point>> cont;
	findContours(img, cont, RETR_EXTERNAL, CHAIN_APPROX_NONE);

	Rect r;

	for (int i = 0; i < cont.size(); i++)
	{
		r = boundingRect(cont[i]);
		imshow("result" + to_string(i), img(r));

		cout << countNonZero(img(r)) << endl;
		waitKey(300);

	}
	waitKey();
}

void question3(Mat& img) {

	Mat gray;
	cvtColor(img, gray, COLOR_BGR2GRAY);

	vector<vector<Point>> cont;
	findContours(gray, cont, RETR_EXTERNAL, CHAIN_APPROX_NONE);

	drawContours(img, cont, -1, Scalar(rand() & 255, rand() & 255, rand() & 255), 2);
	imshow("img", img);
	waitKey();
}

void question4(Mat& img){

	vector<vector<Point>> cont;
	findContours(img, cont, RETR_EXTERNAL, CHAIN_APPROX_NONE);

	Rect r;
	for (int i = 0; i < cont.size(); i++)
	{
		r = boundingRect(cont[i]);
		imshow("result" + to_string(i), img(r));
		waitKey(300);
	}

	waitKey(0);

}
void question5(Mat& img) {
	Mat gray;
	cvtColor(img, gray, COLOR_BGR2GRAY);
	
	vector<Vec3f> circles;
	HoughCircles(gray, circles, HOUGH_GRADIENT, 2, 10, 80, 60, 22, 30);
	for (Vec3f c : circles) {
		circle(img, Point(c[0], c[1]), c[2], Scalar(0, 255, 0), 2);
	}
	imshow("result", img);
	waitKey();
}
int main() {
	Mat q1 = imread("images//practice//ragott.png",IMREAD_GRAYSCALE);
	
	//question1(q1);

	//check();

	Mat q2 = imread("images//practice//ragott.png", IMREAD_GRAYSCALE);
	//question2(q2);


	Mat q3 = imread("images//practice//ragott.png");
	//question3(q3);

	Mat q4 = imread("images//practice//ragott.png",IMREAD_GRAYSCALE);
	//question4(q4);

	Mat q5 = imread("images//practice//coins.png");
	question5(q5);
}