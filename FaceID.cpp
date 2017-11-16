/** g++ FaceID.cpp -o output `pkg-config --cflags --libs opencv` **/
//#include <opencv2/objdetect.hpp>
//#include <opencv2/highgui.hpp>
//#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdio.h>
 
using namespace std;
using namespace cv;

void PANIC(char *msg);
#define PANIC(msg){perror(msg); exit(-1);}

/** Function for face detection **/
void detectAndDraw(Mat frame);

/** Gloabal variables **/
String face_cascade_name = "Source/haarcascade_frontalface_default.xml";
String eyes_cascade_name = "Source/haarcascade_eye_tree_eyeglasses.xml";
CascadeClassifier face_cascade; // Define the face classifier
CascadeClassifier eyes_cascade; // Define the eyes classifier
String window_name = "Face detection";
 
int main(int argc, char *argv[]){
    // VideoCapture class for playing video for which faces to be detected
    VideoCapture capture = VideoCapture(0); 
    Mat frame, image;
 
 	if (!face_cascade.load(face_cascade_name)) 
 		PANIC("Error loading face cascade");
    if (!eyes_cascade.load(eyes_cascade_name))
    	PANIC("Error loading eyes cascade");

    // After the webcamera is opened
    if(capture.isOpened()){
        cout << "Face Detection Started...." << endl;

        while(1){
            capture >> frame; // Get photos from camera

            if(frame.empty())
            	PANIC("Error capture frame");

            detectAndDraw(frame); 

            // Press q to exit from window
            char ch = (char)waitKey(10);
            if(ch == 27 || ch == 'q' || ch == 'Q') 
                break;
        }
    }
    else
        PANIC("Error open camera");

    return 0;
}
 
void detectAndDraw(Mat frame){
    std::vector<Rect> faces;
    std::vector<Rect> eyes;
    Mat frame_gray, frame_resize;

    int radius;
 
 	// Convert to Gray Scale
    cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
 
    // Resize the Grayscale Image 
    resize(frame_gray, frame_resize, Size(), 1, 1, INTER_LINEAR);

    // Histogram equalization
    equalizeHist(frame_resize, frame_resize);
 
    // Detect faces of different sizes using cascade classifier 
    face_cascade.detectMultiScale(frame_resize, faces, 1.1, 5, 0|CASCADE_SCALE_IMAGE, Size(30, 30));
 
    // Draw circles around the faces
    for (size_t i = 0; i < faces.size(); i++)
    {
        Rect r = faces[i];
        //Mat smallImgROI;
        Point center;
 
        rectangle(frame, faces[i], Scalar(255, 0, 0), 2, 8, 0);

        Mat faceROI = frame_resize(faces[i]);

        // Detection of eyes int the input image
        eyes_cascade.detectMultiScale(faceROI, eyes, 1.1, 1,
                                        0|CASCADE_SCALE_IMAGE, Size(3, 3)); 
         
        // Draw circles around eyes
        for (size_t j = 0; j < eyes.size(); j++) 
        {
            Rect nr = eyes[j];
            center.x = cvRound((r.x + nr.x + nr.width*0.5));
            center.y = cvRound((r.y + nr.y + nr.height*0.5));
            radius = cvRound((nr.width + nr.height)*0.25);
            circle(frame, center, radius, Scalar(0, 255, 0), 2, 8, 0);
        }
    }
 
    // Show Processed Image with detected faces
    imshow( "Face Detection", frame); 
}