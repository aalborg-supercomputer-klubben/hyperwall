#pragma once

#include <unordered_map>

#include "FFmpeg.hpp"
#include "Sources/VideoSource.hpp"

namespace Hyperwall {

class HyperFrame {
    const int x;
    const int y;
    const int X;
    const int Y;
    const int RES_X;
    const int RES_Y;
    const FFmpeg ffmpeg;
public:
    HyperFrame(const HyperFrame&);
    HyperFrame(const int, const int, std::unordered_map<std::string, std::string>, const FFmpeg&);
    void run(const cv::Mat&);
};

class Hyperwall {
    std::unique_ptr<VideoSourceT> source;
    std::unordered_map<int, std::unordered_map<int, HyperFrame>> frames;
    const int X;
    const int Y;
public:
    Hyperwall(VideoSourceT&, std::unordered_map<std::string, std::string>);
    void run();
};

} // Hyperwall
