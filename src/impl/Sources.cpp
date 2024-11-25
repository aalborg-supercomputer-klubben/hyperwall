#include <memory>
#include <opencv2/core/hal/interface.h>
#include <string>
#include <opencv2/opencv.hpp>
#include <sys/socket.h>

#include "FFmpeg.hpp"
#include "Sources/FileSource.hpp"
#include "Sources/VideoSource.hpp"
#include "Sources/WebcamSource.hpp"
#include "Sources/TCPSource.hpp"

Hyperwall::FFmpeg ffmpeg() {
  Hyperwall::FFmpegBuilder builder;
  return builder.add("-f mpegts")
    .add("-i")
    .url("tcp://127.0.0.1:8600?listen")
    .add("-f", "rawvideo")
    .add("-vcodec", "rawvideo")
    .add("-pix_fmt", "bgr24")
    .add("pipe:1")
    .build("input");
}

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

Hyperwall::TCPSource::TCPSource() : source(ffmpeg()) {
  std::cout << "waiting for initial data..." << std::endl;
}

cv::Mat Hyperwall::TCPSource::read(){
  auto frame = source.read(1920, 1080); // TODO: make a better solution
  return frame;
}

std::unique_ptr<Hyperwall::VideoSourceT> Hyperwall::TCPSource::clone() const {
  return std::make_unique<TCPSource>(*this);
}
