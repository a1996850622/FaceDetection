/** g++ FaceID.cpp -o output `pkg-config --cflags --libs opencv` **/
#include <opencv2/objdetect.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
//#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdio.h>
 
using namespace std;
using namespace cv;

void PANIC(char *msg);
#define PANIC(msg){perror(msg); exit(-1);}

/** Function for face detection **/
void detectAndDraw(Mat frame);

/** Gloabal variables **/
String face_cascade_name = "Source/haarcascade_frontalcatface.xml";
String eyes_cascade_name = "Source/haarcascade_eye_tree_eyeglasses.xml";
CascadeClassifier face_cascade; // Define the face classifier
CascadeClassifier eyes_cascade; // Define the eyes classifier
String window_name = "Face detection";
 
int main(int argc, char *argv[]){
    // VideoCapture class for playing video for which faces to be detected
    VideoCapture capture; 
    Mat frame, image;
 
 	if (!face_cascade.load(face_cascade_name)) 
 		PANIC("Error loading face cascade");
    if (!eyes_cascade.load(eyes_cascade_name))
    	PANIC("Error loading eyes cascade");

    // CascadeClassifier cascade, nestedCascade; 
    // nestedCascade.load( "Sorce/haarcascade_eye_tree_eyeglasses.xml" ) ;
    // cascade.load( "Source/haarcascade_frontalcatface.xml" ) ; 
 
    // Open the local webcamera
    capture.open(0);

    // After the webcamera is opened
    if(capture.isOpened()){
        cout << "Face Detection Started...." << endl;

        while(1){
            capture >> frame; // Get photos from camera
            detectAndDraw(frame); 

            // Press q to exit from window
            char ch = (char)waitKey(10);
            if(ch == 27 || ch == 'q' || ch == 'Q') 
                break;
        }
    }
    else
        cout<<"Could not Open Camera";

    return 0;
}
 
void detectAndDraw(Mat frame){
    vector<Rect> faces, faces2;
    Mat frame_gray, smallImg;
 
 	// Convert to Gray Scale
    cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
 
    // Resize the Grayscale Image 
    resize( frame_gray, smallImg, Size(), 1, 1, INTER_LINEAR ); 

    // Histogram equalization
    equalizeHist( smallImg, smallImg );
 
    // Detect faces of different sizes using cascade classifier 
    face_cascade.detectMultiScale( smallImg, faces, 1.1, 2, 0|CASCADE_SCALE_IMAGE, Size(30, 30) );
 
    // Draw circles around the faces
    for ( size_t i = 0; i < faces.size(); i++ )
    {
        Rect r = faces[i];
        Mat smallImgROI;
        vector<Rect> nestedObjects;
        Point center;
        Scalar color = Scalar(255, 0, 0); // Color for Drawing tool
        int radius;
 
        double aspect_ratio = (double)r.width/r.height;
        if( 0.75 < aspect_ratio && aspect_ratio < 1.3 )
        {
            center.x = cvRound((r.x + r.width*0.5));
            center.y = cvRound((r.y + r.height*0.5));
            radius = cvRound((r.width + r.height)*0.25);
            circle(frame, center, radius, color, 3, 8, 0);
        }
        else
            rectangle(frame, cvPoint(cvRound(r.x), cvRound(r.y)),
                    cvPoint(cvRound((r.x + r.width-1)), 
                    cvRound((r.y + r.height-1))), color, 3, 8, 0);
        if(eyes_cascade.empty())
            continue;
        smallImgROI = smallImg( r );
         
        // Detection of eyes int the input image
        eyes_cascade.detectMultiScale( smallImgROI, nestedObjects, 1.1, 2,
                                        0|CASCADE_SCALE_IMAGE, Size(30, 30) ); 
         
        // Draw circles around eyes
        for ( size_t j = 0; j < nestedObjects.size(); j++ ) 
        {
            Rect nr = nestedObjects[j];
            center.x = cvRound((r.x + nr.x + nr.width*0.5));
            center.y = cvRound((r.y + nr.y + nr.height*0.5));
            radius = cvRound((nr.width + nr.height)*0.25);
            circle(frame, center, radius, color, 3, 8, 0);
        }
    }
 
    // Show Processed Image with detected faces
    imshow( "Face Detection", frame); 
}