#pragma once

#include <string>

#include <opencv2/opencv.hpp>

namespace Hyperwall {

class FFmpeg {
    FILE* buffer;
public:
    const std::tuple<int, int> resolution;
    const std::tuple<int, int> position;
    const int framerate;
    const std::string input;
    const std::string bitrate;

    constexpr FFmpeg(const std::tuple<int, int>& resolution, const int& framerate, const std::string& bitrate, const std::tuple<int, int>& position) :
        resolution(resolution),
        framerate(framerate),
        bitrate(bitrate),
        position(position) {
    }

    constexpr FFmpeg(const int framerate, const std::string bitrate, const std::tuple<int, int> position) :
        resolution(1920, 1080),
        framerate(framerate),
        bitrate(bitrate),
        position(position) {

    }

    constexpr FFmpeg(const std::string bitrate, const std::tuple<int, int> position) :
        resolution(1920, 1080),
        framerate(60),
        bitrate(bitrate),
        position(position) {

    }

    constexpr FFmpeg(const std::tuple<int, int> position) :
        resolution(1920, 1080),
        framerate(60),
        bitrate("1G"),
        position(position) {

    }
    
    constexpr FFmpeg() :
        resolution({1920, 1080}),
        framerate(60),
        bitrate("1G"),
        position({0, 0}) {
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
