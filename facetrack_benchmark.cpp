//
// face tracking sample using MJPEGCapture
//

#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <unistd.h>
#include <iostream>
#include <iomanip>
#include <time.h>
#include <iostream>
#include <stdio.h>

#include "MJPEGCapture.h"

using namespace std;
using namespace cv;

void detectAndDisplay( Mat frame );

//String face_cascade_name = "haarcascade_frontalface_default.xml";
String face_cascade_name = "lbpcascade_frontalface.xml";

CascadeClassifier face_cascade;

string window_name = "Capture - Face detection";

int main( int argc, const char** argv ){

  Mat frame;
  if( !face_cascade.load( face_cascade_name ) ){
    printf("--(!)Error loading\n");
    return -1;
  }

  MJPEGCapture capture;

  capture.setDesiredSize(640, 480);
  capture.setDesiredFrameRate(30);
  capture.setVerbose(true);
  capture.open();

  if( !capture.isOpen() ){
    cerr << "Failed to open camera" << endl;
  }

  for (int i = 0; i < 20; ++i){
    capture.grab();
    usleep(1000);
  }

  Mat mjpeg;
  unsigned int max_count = 100;
  unsigned int count = 0;

  double t = (double)getTickCount();

  while (count < max_count){
    if (capture.grab()){
      capture.mjpeg(mjpeg);
      count ++;
      if( !mjpeg.empty() ){
        detectAndDisplay(mjpeg);
      }else{
        printf(" --(!) No captured frame -- Break!");
        break;
      }
    }
  }

  t = ((double)getTickCount() - t)/getTickFrequency();

  std::cout << "facetrack time=" << t << endl;
  std::cout << "fps=" << max_count / t << endl;
  capture.close();
  return 0;
}


void detectAndDisplay( Mat frame ){
  std::vector<Rect> faces;
  Mat frame_gray;

  cvtColor( frame, frame_gray, CV_BGR2GRAY );
  //  equalizeHist( frame_gray, frame_gray );
  face_cascade.detectMultiScale( frame_gray, faces,
                                 1.1, 2, 0,
                                 Size(30, 30) );

  for( size_t i = 0; i < faces.size(); i++ ){
    double x =  faces[i].x + faces[i].width*0.5;
    double y = faces[i].y + faces[i].height*0.5;
    cout <<  "face center = " << x << ", " << y << endl;
  }
}
