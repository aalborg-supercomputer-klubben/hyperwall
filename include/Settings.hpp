#pragma once

#include <tuple>
#include <string>

namespace Hyperwall {

typedef std::tuple<int, int> coordinate;

struct Settings {
public:
    const coordinate resolution;
    const coordinate dimensions;
    const std::string bitrate;
    const unsigned int framerate;
    constexpr Settings(const coordinate& resolution, const coordinate& dimensions, const std::string bitrate, const unsigned int framerate) :
        resolution(resolution),
        dimensions(dimensions),
        bitrate(bitrate),
        framerate(framerate) {
    }

    constexpr Settings(const coordinate& resolution, const coordinate& dimensions, const std::string bitrate) :
        resolution(resolution),
        dimensions(dimensions),
        bitrate(bitrate),
        framerate(60) {

    }

    constexpr Settings(const coordinate& resolution, const coordinate& dimensions) :
        resolution(resolution),
        dimensions(dimensions),
        bitrate("1G"),
        framerate(60) {
    }
    
    constexpr Settings(const coordinate& resolution) :
        resolution(resolution),
        dimensions({2, 2}),
        bitrate("1G"),
        framerate(60) {
    }

    constexpr Settings() :
        resolution({1920, 1080}),
        dimensions({2, 2}),
        bitrate("1G"),
        framerate(60) {

    }
};

}
