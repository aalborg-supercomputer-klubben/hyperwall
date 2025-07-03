#pragma once

#include <filesystem>
#include <spdlog/common.h>
#include <spdlog/spdlog.h>
#include <tuple>
#include <string>

#include "HyperwallArguments.hpp"
#include "Utils.hpp"
#include "Mode.hpp"

namespace asck {


struct Settings {
protected:
public:
    const coordinate resolution;
    const coordinate dimensions;
    const std::string rtsp_server;
    const std::string bitrate;
    const unsigned int framerate;
    const std::string file;
    const Mode mode;
    const spdlog::level::level_enum loglevel;

    constexpr Settings(const coordinate resolution, const coordinate dimensions, const std::string rtsp_server, const std::string bitrate, const unsigned int framerate, const std::string file, Mode mode) :
        resolution(resolution),
        dimensions(dimensions),
        rtsp_server(rtsp_server),
        bitrate(bitrate),
        framerate(framerate),
        file(file),
        mode(mode),
        loglevel(spdlog::level::level_enum::info) {
    }

    constexpr Settings(const coordinate resolution, const coordinate dimensions, const std::string rtsp_server, const std::string bitrate, const unsigned int framerate, const std::string file) :
        Settings(
            resolution,
            dimensions,
            rtsp_server,
            bitrate,
            framerate,
            file,
            Mode::File) {
    }

    constexpr Settings(const coordinate resolution, const coordinate dimensions, const std::string rtsp_server, const std::string bitrate, const unsigned int framerate) :
        Settings(
            resolution,
            dimensions,
            rtsp_server,
            bitrate,
            framerate,
            "file.mp4"
        ) {
    }


    constexpr Settings(const coordinate resolution, const coordinate dimensions, const std::string rtsp_server, const std::string bitrate) :
        Settings(
            resolution,
            dimensions,
            rtsp_server,
            bitrate,
            60
        ) {
    }

    constexpr Settings(const coordinate resolution, const coordinate dimensions, const std::string rtsp_server) :
        Settings(
            resolution,
            dimensions,
            rtsp_server,
            "1G"
        ) {

        }


    constexpr Settings(const coordinate resolution, const coordinate dimensions) :
        Settings(
            resolution,
            dimensions,
            "0.0.0.0:8554"
        ) {
    }

    constexpr Settings(const coordinate resolution) :
        Settings(
            resolution,
            {2, 2}
        ) {
    }

    constexpr Settings() :
        Settings(
            {1920, 1080}
        ) {
    }

    constexpr Settings(const HyperwallArguments& arguments) :
        resolution(splitResolution(arguments.get("--resolution"))),
        dimensions(splitResolution(arguments.get("--dimensions"))),
        rtsp_server(arguments.get("--rtsp-server")),
        bitrate(arguments.get("--bitrate")),
        framerate(arguments.get<int>("--framerate")),
        loglevel(static_cast<spdlog::level::level_enum>(arguments.loglevel)),
        file(arguments.get("--file")),
        mode(toMode(arguments.get("mode"))) {
    }

    constexpr Settings(Settings& other) :
        resolution(other.resolution),
        dimensions(other.dimensions),
        rtsp_server(other.rtsp_server),
        bitrate(other.bitrate),
        framerate(other.framerate),
        loglevel(other.loglevel),
        file(other.file),
        mode(other.mode) {
    }

};

}
