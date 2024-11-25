#pragma once

#include "Sources/VideoSource.hpp"
#include "FFmpeg.hpp"

namespace Hyperwall {
  class TCPSource : public VideoSourceT {
  FFmpeg source;
  public:
    TCPSource();
    virtual cv::Mat read() override;
    virtual std::unique_ptr<VideoSourceT> clone() const override;
  };
}
