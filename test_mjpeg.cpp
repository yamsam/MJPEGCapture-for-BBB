
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>


int main(int argc, const char* argv[])
{

  cv::VideoCapture cap(0);

  if(!cap.isOpened())
    return -1;

  cap.set(CV_CAP_PROP_FRAME_WIDTH, 640);
  cap.set(CV_CAP_PROP_FRAME_HEIGHT, 480);
  cap.set(CV_CAP_PROP_FPS, 30);

  cv::namedWindow("image", cv::WINDOW_AUTOSIZE);
  cv::Mat frame;

  unsigned int max_count = 100;
  unsigned int count = 0;

  double t = (double)cv::getTickCount();
  while (count < max_count){
    cap >> frame;
    count ++;
  }
  t = ((double)cv::getTickCount() - t)/cv::getTickFrequency();

  std::cout << "opencv time=" << t << std::endl;
  std::cout << "fps=" << max_count / t << std::endl;

  return 0;
}
