#include <cstdlib>
#include <filesystem>
#include <spdlog/common.h>
#include <string>

#include <argparse/argparse.hpp>
#include <opencv2/opencv.hpp>
#include <spdlog/spdlog.h>

#include "Hyperwall.hpp"
#include "Sources/FileSource.hpp"
#include "Sources/WebcamSource.hpp"
#include "Utils.hpp"

int main(int argc, char* argv[]) {
    auto loglevel = (int)spdlog::level::info;

    argparse::ArgumentParser parser;
    parser.add_argument("--dimensions")
        .default_value("2x2");
    parser.add_argument("--resolution")
        .default_value("1920x1080");
    parser.add_argument("--framerate")
        .scan<'i', int>()
        .default_value(60);
    parser.add_argument("--file")
        .default_value("file.mp4");
    parser.add_argument("--bitrate")
        .default_value("1G");
    parser.add_argument("--rtsp-server")
        .default_value("0.0.0.0:8554");
    parser.add_argument("mode")
        .default_value("file");
    parser.add_argument("-v")
        .action([&](const auto &){loglevel--;})
        .append()
        .default_value(false)
        .implicit_value(true)
        .nargs(0);
    parser.add_argument("-q")
        .action([&](const auto &){loglevel++;})
        .append()
        .default_value(false)
        .implicit_value(true)
        .nargs(0);

    try {
        parser.parse_args(argc, argv);
    } catch(std::exception& e) {
        spdlog::error("Failed to parse arguments, exiting!");
        exit(EXIT_FAILURE);
    }
    spdlog::set_level(static_cast<spdlog::level::level_enum>(loglevel));
    std::cout << "Log level: " << loglevel << std::endl;
    spdlog::debug("Generating settings");

    Hyperwall::Settings settings(
        Util::split_resolution(parser.get("--resolution")),
        Util::split_resolution(parser.get("--dimensions")),
        parser.get<Util::conststring>("--rtsp-server"),
        parser.get<Util::conststring>("--bitrate"),
        parser.get<int>("--framerate")
    );

    Hyperwall::Hyperwall hyperwall = [&settings, &parser](std::string mode) {
        spdlog::info("Chosen mode: {}", mode);
        if(mode == "webcam") {
            Hyperwall::WebcamSource source(0);
            Hyperwall::Hyperwall hyperwall(source, settings);
            return hyperwall;
        }
        else if(mode == "screenshare") {
            Hyperwall::FileSource source("tcp://0.0.0.0:8600?listen");
            Hyperwall::Hyperwall hyperwall(source, settings);
            return hyperwall;
        }
        else {
            auto filename = parser.get<std::string>("--file");
            if(!std::filesystem::exists(std::filesystem::path(filename))){
                spdlog::error("File: {} does not exist!", filename);
                exit(EXIT_FAILURE);
            }
            Hyperwall::FileSource source(filename);
            Hyperwall::Hyperwall hyperwall(source, settings);
            return hyperwall;
        }
    }(parser.get<std::string>("mode"));
    {
        hyperwall.run();
    }
    exit(EXIT_SUCCESS);
}
