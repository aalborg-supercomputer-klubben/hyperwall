#pragma once

#include "Sources/VideoSource.hpp"

namespace Hyperwall {

class FileSource : public VideoSourceT {
    cv::VideoCapture capture;

public:
    FileSource(std::string);
    virtual cv::Mat read() override;
    virtual std::unique_ptr<VideoSourceT> clone() const override;
};

} // Hyperwall
