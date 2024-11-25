#include <string>
#include <opencv2/opencv.hpp>

#include "Sources/FileSource.hpp"
#include "Sources/VideoSource.hpp"
#include "Sources/WebcamSource.hpp"


Hyperwall::FileSource::FileSource(std::string filename) : capture(filename) {
}

cv::Mat Hyperwall::FileSource::read() {
  cv::Mat frame;
  capture.read(frame);
  return frame;
}

std::unique_ptr<Hyperwall::VideoSourceT> Hyperwall::FileSource::clone() const {
  return std::make_unique<FileSource>(*this);
}

Hyperwall::WebcamSource::WebcamSource(const int index) : capture(index) {
}

cv::Mat Hyperwall::WebcamSource::read() {
  cv::Mat frame;
  capture.read(frame);
  return frame;
}

std::unique_ptr<Hyperwall::VideoSourceT> Hyperwall::WebcamSource::clone() const {
  return std::make_unique<WebcamSource>(*this);
}
