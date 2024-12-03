#pragma once

#include <tuple>

#include "Utils.hpp"

using namespace Util;

namespace Hyperwall {

typedef std::tuple<int, int> coordinate;

struct Settings {
public:
    const coordinate resolution;
    const coordinate dimensions;
    const conststring rtsp_server;
    const conststring bitrate;
    const unsigned int framerate;

    constexpr Settings(const coordinate& resolution, const coordinate& dimensions, const conststring rtsp_server, const conststring bitrate, const unsigned int framerate) :
        resolution(resolution),
        dimensions(dimensions),
        rtsp_server(rtsp_server),
        bitrate(bitrate),
        framerate(framerate) {
    }

    constexpr Settings(const coordinate& resolution, const coordinate& dimensions, const conststring rtsp_server, const conststring bitrate) :
        resolution(resolution),
        dimensions(dimensions),
        rtsp_server(rtsp_server),
        bitrate(bitrate),
        framerate(60) {
    }

    constexpr Settings(const coordinate& resolution, const coordinate& dimensions, const conststring rtsp_server) :
        resolution(resolution),
        dimensions(dimensions),
        rtsp_server(rtsp_server),
        bitrate("1G"),
        framerate(60) {
    }

    constexpr Settings(const coordinate& resolution, const coordinate& dimensions) :
        resolution(resolution),
        dimensions(dimensions),
        rtsp_server("0.0.0.0:8554"),
        bitrate("1G"),
        framerate(60) {
    }
    
    constexpr Settings(const coordinate& resolution) :
        resolution(resolution),
        dimensions({2, 2}),
        rtsp_server("0.0.0.0:8554"),
        bitrate("1G"),
        framerate(60) {
    }

    constexpr Settings() :
        resolution({1920, 1080}),
        dimensions({2, 2}),
        rtsp_server("0.0.0.0:8554"),
        bitrate("1G"),
        framerate(60) {
    }

    constexpr Settings(Settings& other) :
        resolution(other.resolution),
        dimensions(other.dimensions),
        rtsp_server(other.rtsp_server),
        bitrate(other.bitrate),
        framerate(other.framerate) {
    }
    constexpr friend bool operator==(const Settings lhs, const Settings rhs) {
        return 
            lhs.resolution  == rhs.resolution &&
            lhs.dimensions  == rhs.dimensions &&
            lhs.rtsp_server == rhs.rtsp_server &&
            lhs.bitrate     == rhs.rtsp_server &&
            lhs.framerate   == rhs.framerate;
    }
};

}
