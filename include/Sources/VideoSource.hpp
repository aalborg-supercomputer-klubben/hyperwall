#pragma once

#include <opencv2/opencv.hpp>

namespace Hyperwall {

class VideoSourceT {
public:
  virtual cv::Mat read() = 0;
  virtual ~VideoSourceT() = default;
  virtual std::unique_ptr<VideoSourceT> clone() const = 0;
};

} // Hyperwall
