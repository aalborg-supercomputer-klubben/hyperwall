#pragma once

#include "FFmpeg.hpp"
#include "Sources/VideoSource.hpp"
#include "Settings.hpp"

namespace Hyperwall {

class HyperFrame {
    const coordinate position;
    const coordinate dimensions;
    const coordinate resolution;
    FFmpeg ffmpeg;
public:
    HyperFrame(const HyperFrame&);
    HyperFrame(const coordinate&, Settings&, FFmpeg&);
    void run(const cv::Mat&);
};

class Hyperwall {
    std::unique_ptr<VideoSourceT> source;
    std::vector<HyperFrame> frames;
    const coordinate dimensions;
public:
    Hyperwall(VideoSourceT&, Settings&);
    void run();
};

} // Hyperwall
