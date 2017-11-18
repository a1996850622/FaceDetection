/** Used to take pictures **/
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

/** Gloabal variables **/
String face_cascade_name = "../Source/haarcascade_frontalface_default.xml";
String eyes_cascade_name = "../Source/haarcascade_eye_tree_eyeglasses.xml";
CascadeClassifier face_cascade; // Define the face classifier
CascadeClassifier eyes_cascade; // Define the eyes classifier

int main(void){
	VideoCapture capture = VideoCapture(0);
	std::vector<Rect> faces;
	Mat frame, frame_gray;
	int i = 1;

	if (!face_cascade.load(face_cascade_name)) 
		PANIC("Error loading face cascade");
	if (!eyes_cascade.load(eyes_cascade_name))
		PANIC("Error loading eyes cascade");

	cout << "Press p to take a picture" << endl;
	while(1){
		char key = waitKey(100);
		capture >> frame;

		// Convert to Gray Scale
		cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
		equalizeHist(frame_gray, frame_gray);

		// Detect faces of different sizes using cascade classifier 
    	face_cascade.detectMultiScale(frame_resize, faces, 1.1, 5, CV_HAAR_SCALE_IMAGE, Size(30, 30));

		imshow("photo", frame);
		String filename = format("picture%d.jpg", i);

		/** Press p to take pictures **/
		switch(key){
			case 'p':
				i++;
				imwrite(filename, frame);
				imshow("photo", frame);
				waitKey(500);
				destroyWindow("photo");
				break;
			default:
				break;
		}
	}
}
