#include <string>
#include <opencv2/opencv.hpp>

#include "Sources/FileSource.hpp"


Hyperwall::FileSource::FileSource(std::string filename) : capture(filename) {
}

cv::Mat Hyperwall::FileSource::read() {
  cv::Mat frame;
  capture.read(frame);
  return frame;
}
