#pragma once

#include "Sources/VideoSource.hpp"

namespace asck {

class FileSource : public VideoSourceT {
    cv::VideoCapture capture;

public:
    FileSource(const std::string);
    virtual cv::Mat read() override;
};

} // Hyperwall
