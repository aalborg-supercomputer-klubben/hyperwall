#include "FFmpeg.hpp"
#include <cstdio>
#include <format>
#include <opencv2/core/mat.hpp>
#include <sstream>
#include <string>

Hyperwall::FFmpegBuilder& Hyperwall::FFmpegBuilder::add(const std::string option) {
  options.push_back(option);
  return *this;
}

Hyperwall::FFmpegBuilder& Hyperwall::FFmpegBuilder::add(const std::string key, const std::string value) {
  options.push_back(std::format("{} {}", key, value));
  return *this;
}

Hyperwall::FFmpegBuilder& Hyperwall::FFmpegBuilder::url(const std::string url) {
  this->_url = url;
  add(url);
  return *this;
}

const Hyperwall::FFmpeg Hyperwall::FFmpegBuilder::build() {
  std::stringstream ss;
  ss << "ffmpeg ";
  for(auto option : options) {
    ss << option << " ";
  }
  ss << ">> ./logs/ffmpeg.stdout 2> ./logs/ffmpeg.stderr";
  return {ss.str(), _url};
}

Hyperwall::FFmpeg::FFmpeg(const std::string command, const std::string url) : url(url) {
  //std::cout << command << std::endl;
  buffer = popen(command.c_str(), "w");
}

const void Hyperwall::FFmpeg::write(const cv::Mat& mat) const {
  //std::cout << url << std::endl;
  fwrite(mat.data, 1, mat.cols * mat.rows * 3, buffer);
  fflush(buffer);
}
