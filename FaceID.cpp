/** g++ FaceID.cpp -o output `pkg-config --cflags --libs opencv` **/
#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

void PANIC(char *msg);
#define PANIC(msg){perror(msg); exit(-1);}

/** Function Headers **/
void detectAndDisplay(Mat frame);

/** Global variables **/
String face_cascade_name = "Source/haarcascade_frontalface_default.xml";
String eyes_cascade_name = "Source/haarcascade_eye_tree_eyeglasses.xml";
CascadeClassifier face_cascade; // Define the face classifier
CascadeClassifier eyes_cascade; // Define the eyes classifier
String window_name = "Capture - Face detection";

int main(int argc, char *argv[]){
	Mat frame = imread("Picture/test1.jpg", IMREAD_COLOR);

	imshow("original", frame);

	// Load the cascades
	if(!face_cascade.load(face_cascade_name))
		PANIC("Error loading face cascade");
	if(!eyes_cascade.load(eyes_cascade_name))
		PANIC("Error loading eyes cascade");

	// Apply the classifier to the frame
	detectAndDisplay(frame);

	int ch = waitKey(0);
	if((char)ch == 27) return 0; //Escape

	return 0;
}

void detectAndDisplay(Mat frame){
	std::vector<Rect> faces;
	Mat frame_gray;

	// Change BGR to grayscale
	cvtColor(frame, frame_gray, COLOR_BGR2GRAY);

	imshow("grayscale", frame_gray);

	// equalizeHist(frame_gray, frame_gray);
}