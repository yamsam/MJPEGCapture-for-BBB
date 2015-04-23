#include "MJPEGCapture.h"

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/objdetect/objdetect.hpp"

#include <unistd.h>
#include <iostream>
#include <iomanip>

#include <time.h>
#include <stdio.h>

using namespace cv;
using namespace std;

int cv_bench(int w, int h){
	cv::VideoCapture cap(0);

  if(!cap.isOpened())
    return -1;

  cap.set(CV_CAP_PROP_FRAME_WIDTH, w);
  cap.set(CV_CAP_PROP_FRAME_HEIGHT,h);
  cap.set(CV_CAP_PROP_FPS, 30);

  cv::Mat frame;

  unsigned int max_count = 100;
  unsigned int count = 0;

	double t = (double)cv::getTickCount();
  while (count < max_count){
		cap >> frame;
		count ++;
  }
	t = ((double)cv::getTickCount() - t)/cv::getTickFrequency();

	return 0;
}



void mjpeg_bench(double h, double w){
  MJPEGCapture capture;

  capture.setDesiredSize(h, w);
  capture.setDesiredFrameRate(30);
	//  capture.setVerbose(true);
  capture.open();

  if (!capture.isOpen()){
      cerr << "Failed to open camera" << endl;
	}

  cout << "Capture " << capture.width() << " x " << capture.height();
  cout << " pixels at " << capture.frameRate() << " fps" << endl;

  // The first several frames tend to come out black.
  for (int i = 0; i < 20; ++i)
		{
		capture.grab();
      usleep(1000);
    }

  Mat mjpeg;
  unsigned int max_count = 100;
  unsigned int count = 0;

	double t = (double)getTickCount();

  while (count < max_count)
		{
			if (capture.grab())
				{
					capture.mjpeg(mjpeg);
					count ++;
				}
		}

	t = ((double)getTickCount() - t)/getTickFrequency();

	std::cout << "mjpegcapture time=" << t << endl;
  std::cout << "fps=" << max_count / t << endl;
  capture.close();
}


int main(int argc, char** argv)
{
	mjpeg_bench(320, 240);
	mjpeg_bench(640, 480);

	//	cv_bench(320, 240);
	//	cv_bench(640, 480);

	return 0;
}

