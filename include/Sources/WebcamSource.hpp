#pragma once

#include "Sources/VideoSource.hpp"

namespace Hyperwall {

class WebcamSource : public VideoSourceT {
    cv::VideoCapture capture;
public:
    WebcamSource(const int);
    virtual cv::Mat read() override;
    virtual std::unique_ptr<VideoSourceT> clone() const override;
};

} // Hyperwall
