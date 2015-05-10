//
// face tracking sample using MJPEGCapture
//

#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <stdio.h>

#include "MJPEGCapture.h"

using namespace std;
using namespace cv;

/** Function Headers */
void detectAndDisplay( Mat frame );

/** Global variables */
//String face_cascade_name = "haarcascade_frontalface_alt.xml";
String face_cascade_name = "lbpcascade_frontalface.xml";
CascadeClassifier face_cascade;

string window_name = "Capture - Face detection";


/** @function main */
int main( int argc, const char** argv )
{
  Mat frame;

  //-- 1. Load the cascades
  if( !face_cascade.load( face_cascade_name ) ){ printf("--(!)Error loading\n"); return -1; };

  MJPEGCapture capture;

  capture.setDesiredSize(640, 480);
  capture.setDesiredFrameRate(30);
  capture.setVerbose(true);
  capture.open();

  if( capture.isOpen() ){
    while(true){
      capture.grab();
      capture.mjpeg(frame);
      //-- 3. Apply the classifier to the frame
      if( !frame.empty() ){
        detectAndDisplay( frame );
      } else {
        printf(" --(!) No captured frame -- Break!"); break;
      }
      
      int c = waitKey(10);
      if( (char)c == 'q' ) { break; }
    }
  }
  return 0;
}


/** @function detectAndDisplay */
void detectAndDisplay( Mat frame )
{
  std::vector<Rect> faces;
  Mat frame_gray;

  cvtColor( frame, frame_gray, CV_BGR2GRAY );
  //equalizeHist( frame_gray, frame_gray );

  //-- Detect faces
  face_cascade.detectMultiScale(frame_gray, faces, 1.2, 2, 0 , Size(30, 30) );

  if (faces.size() != 0) {
    Point center( faces[0].x + faces[0].width*0.5,
                  faces[0].y + faces[0].height*0.5 );
    ellipse( frame, center, Size( faces[0].width*0.5,
                                  faces[0].height*0.5),
             0, 0, 360, Scalar( 255, 0, 255 ), 4, 8, 0 );
  }
  //-- Show what you got
  imshow( window_name, frame );
}
