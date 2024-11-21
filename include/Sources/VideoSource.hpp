#pragma once

#include <exception>
#include <opencv2/opencv.hpp>

namespace Hyperwall {

class VideoSourceT {
public:
  virtual cv::Mat read() {
    throw std::exception();
  };
};

} // Hyperwall
