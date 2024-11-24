#include <memory>
#include <opencv2/core/hal/interface.h>
#include <string>
#include <opencv2/opencv.hpp>
#include <sys/socket.h>

#include "Sources/FileSource.hpp"
#include "Sources/VideoSource.hpp"
#include "Sources/WebcamSource.hpp"
#include "Sources/TCPSource.hpp"


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

Hyperwall::TCPSource::TCPSource() : socket(AF_INET, SOCK_STREAM) {
  socket.bind(8600);
  socket.listen();
  std::cout << "Waiting on a TCP stream..." << std::endl;
  client = socket.accept();
}

cv::Mat Hyperwall::TCPSource::read(){
  std::string buf;
  char recv = 0;
  while((recv = client.read()) != EOF)
    buf += recv;
  return cv::Mat(1920, 1080, CV_8UC3, (std::byte*)buf.c_str());
}

std::unique_ptr<Hyperwall::VideoSourceT> Hyperwall::TCPSource::clone() const {
  return std::make_unique<TCPSource>(*this);
}
