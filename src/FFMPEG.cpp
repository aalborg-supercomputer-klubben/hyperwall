#include "ffmpeg.hpp"
#include <format>
#include <sstream>
#include <string>

Hyperwall::FFMPEG& Hyperwall::FFMPEG::add(std::string option) {
  this->options.push_back(option);
  return *this;
}

Hyperwall::FFMPEG& Hyperwall::FFMPEG::add(std::string key, std::string value) {
  this->options.push_back(std::format("{0} {1}", key, value));
  return *this;
}

std::string Hyperwall::FFMPEG::build() {
  std::stringstream ss;
  ss << "ffmpeg ";
  for(auto option : options)
    ss << option << " ";
  return ss.str();
}
