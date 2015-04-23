#ifndef MJPEGCAPTURE_H
#define MJPEGCAPTURE_H

#include <vector>
#include <string>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>


class MJPEGCapture
{
public:
  // Instantiate a Capture object.
  // The default size is 320 x 240.
  MJPEGCapture();

  // The destructor automatically closes the camera.
  virtual ~MJPEGCapture();

  // You can turn on verbose mode to which will cause the capture
  // object to spew debug messages to cout.
  void setVerbose(bool verboseOn);
  bool verbose() const;

  // When the capture object is closed you can set the size. At the
  // time the capture object is opened the hardware will be queried
  // for a supported size which may differ from the requested size,
  // so do not assume the images you retrieve from the capture object
  // are the requested size.
  void setDesiredSize(uint32_t width, uint32_t height);
  void setDesiredFrameRate(uint32_t frate);

  // Before capturing images you must open the capture object.
  // The open call returns true if it was successful.
  // Open to read from the camera.
  bool open();
  // Returns true if the capture object is open.
  bool isOpen() const;

  // After the capture object is opened you can query for the final
  // size that it negotiated with the camera.
  uint32_t width() const;
  uint32_t height() const;
  uint32_t frameRate() const;

  // Close the capture object. This releases the video device and
  // frees up driver-related memory. You can change the desired image
  // size while the object is closed.
  void close();

  // The capturing process is divided into two parts. In the first
  // step you call 'grab' to actually grab the (JPEG) image. Then
  // later you call 'mjpeg' to convert the grabbed image to
  // the desired color space.
  bool grab();
  bool mjpeg(cv::Mat& rgb);

private:
  int retry_ioctl(int request, void* argument);
  bool firstGrabSetup();
  void reportError(const char* error);
  void reportError(const char* error, int64_t value);

  void resizeMat(cv::Mat& mat, int matType);

private:
  // What the client wants...
  uint32_t    m_desired_width;
  uint32_t    m_desired_height;
  uint32_t    m_desired_frame_rate;
  bool      m_verbose;

  // Internal bookkeeping for the camera
  int       m_camera_handle;
  bool      m_first_grab;

  // The size we negotitated with the driver.
  uint32_t    m_final_width;
  uint32_t    m_final_height;
  uint32_t    m_final_frame_rate;

  // These are the memory mapped image buffers
  // provided by the camera driver.
  std::vector<void*>  m_mapped_buffer_ptrs;
  std::vector<size_t> m_mapped_buffer_lens;

  // A copy of the mostly recently grabbed YUV data.
  size_t      m_yuv_image_size;
  uint8_t*    m_yuv_image_data;
  uint8_t*    m_jpeg_data;
  size_t m_jpeg_data_len;
  uint32_t    m_yuv_bytes_per_line;

};

#endif

