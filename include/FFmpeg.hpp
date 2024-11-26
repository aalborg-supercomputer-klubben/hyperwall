#pragma once

#include <string>
#include <vector>

#include <opencv2/opencv.hpp>

namespace Hyperwall {

class FFmpeg{
    FILE* buffer;
public:
    const std::string url;

    FFmpeg(const std::string, const std::string);
    const void write(const cv::Mat&) const;
    const cv::Mat read(int, int) const;
};

class FFmpegBuilder {
    std::vector<std::string> options;
    std::string _url;

public:
    FFmpegBuilder& add(const std::string);
    FFmpegBuilder& add(const std::string, const std::string);
    FFmpegBuilder& url(const std::string);
    const FFmpeg build(std::string);
};
} // Hyperwall
