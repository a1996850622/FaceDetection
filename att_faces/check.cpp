#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;

int main(int argc, char *argv[]){
	if(argc<2){
		printf("Please enter the filename of picture\n");
		exit(-1);
	}

	char *filename = argv[1];

	Mat img = imread(filename, IMREAD_COLOR);

	imshow(filename, img);
	
	waitKey(0);

	return 0;
}