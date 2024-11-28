#pragma once

#include <string>

#include <opencv2/opencv.hpp>

#include "Settings.hpp"

namespace Hyperwall {

class FFmpeg {
    FILE* buffer;
public:
    const coordinate resolution;
    const coordinate position;
    const coordinate dimensions;
    const int framerate;
    const std::string input;
    const std::string bitrate;


    constexpr FFmpeg(Settings settings, coordinate position) :
        resolution(settings.resolution),
        dimensions(settings.dimensions),
        framerate(settings.framerate),
        bitrate(settings.bitrate),
        position(position) {

    }

    constexpr FFmpeg(Settings settings) :
        resolution(settings.resolution),
        dimensions(settings.dimensions),
        framerate(settings.framerate),
        bitrate(settings.bitrate),
        position({0, 0}) {
    }

    constexpr FFmpeg(coordinate position) :
        resolution(1920, 1080),
        dimensions(2, 2),
        framerate(60),
        bitrate("1G"),
        position(position) {
    }
    
    constexpr FFmpeg() :
        resolution(1920, 1080),
        dimensions(0, 0),
        framerate(60),
        bitrate("1G"),
        position(0, 0) {
    }
    constexpr ~FFmpeg() = default;

    constexpr std::string uri() const {
        const auto [x, y] = position;
        return std::format("rtsp://0.0.0.0:8554/{}/{}", x, y);
    }

    const void open();
    const void write(const cv::Mat&) const;
};

} // Hyperwall
