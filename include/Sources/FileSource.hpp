#pragma once

#include "Sources/VideoSource.hpp"
#include <opencv2/videoio.hpp>

namespace Hyperwall {

class FileSource : public VideoSourceT {
  cv::VideoCapture capture;

public:
  FileSource(std::string);
  cv::Mat read() override;
};

} // Hyperwall
