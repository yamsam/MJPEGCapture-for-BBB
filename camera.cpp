// This sample program captures images from your web camera
// via MJPEG format.
#include <unistd.h>
#include <iostream>
#include <iomanip>

#include <time.h>
#include <stdio.h>

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/objdetect/objdetect.hpp"

#include "MJPEGCapture.h"

using namespace cv;
using namespace std;

int main(int argc, char** argv){
	 MJPEGCapture capture;

	 capture.setDesiredSize(640, 480);
	 capture.setDesiredFrameRate(30);
	 capture.setVerbose(true);
	 capture.open();

	 if (!capture.isOpen()){
			 cerr << "Failed to open camera" << endl;
			 return -1;
	 }

	 cout << "Capture " << capture.width() << " x " << capture.height();
	 cout << " pixels at " << capture.frameRate() << " fps" << endl;

	 // The first several frames tend to come out black.
	 for (int i = 0; i < 20; ++i){
			 capture.grab();
			 usleep(1000);
	 }

	 namedWindow("MJPEG", CV_WINDOW_AUTOSIZE);

	 Mat mjpeg, gray, canny;

	 bool loop = true;
	 cout << "to exit, press 'q'" << endl;

	 while (loop){
		 if (capture.grab()){
			 capture.mjpeg(mjpeg);
			 imshow("MJPEG", mjpeg);
			 int key = waitKey(10);
			 if (key == 113){
				 loop = false;
				 break;
			 }
		 }
	 }

	 capture.close();
	 return 0;
 }
