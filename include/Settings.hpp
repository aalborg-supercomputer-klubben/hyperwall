#pragma once

#include <tuple>
#include <string>

namespace asck {

typedef std::tuple<int, int> coordinate;

struct Settings {
public:
    const coordinate resolution;
    const coordinate dimensions;
    const std::string rtsp_server;
    const std::string bitrate;
    const unsigned int framerate;

    constexpr Settings(const coordinate& resolution, const coordinate& dimensions, const std::string rtsp_server, const std::string bitrate, const unsigned int framerate) :
        resolution(resolution),
        dimensions(dimensions),
        rtsp_server(rtsp_server),
        bitrate(bitrate),
        framerate(framerate) {
    }

    constexpr Settings(const coordinate& resolution, const coordinate& dimensions, const std::string rtsp_server, const std::string bitrate) :
        resolution(resolution),
        dimensions(dimensions),
        rtsp_server(rtsp_server),
        bitrate(bitrate),
        framerate(60) {
    }

    constexpr Settings(const coordinate& resolution, const coordinate& dimensions, const std::string rtsp_server) :
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
};

}
