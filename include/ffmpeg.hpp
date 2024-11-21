#pragma once

#include <string>
#include <vector>

#include <opencv2/opencv.hpp>

namespace Hyperwall {

  class FFMPEG {
    FILE* buffer;
  public:
    const std::string url;

    FFMPEG(const std::string, const std::string);
    const void write(const cv::Mat&) const;
  };

  class FFMPEGBuilder {
    std::vector<std::string> options;
    std::string _url;

  public:
    FFMPEGBuilder& add(const std::string);
    FFMPEGBuilder& add(const std::string, const std::string);
    FFMPEGBuilder& url(const std::string);
    const FFMPEG build();
  };
} // Hyperwall
