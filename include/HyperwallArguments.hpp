// Uses argparse to generate a settings object
// This way the settings object is just a generic struct-like object while the settingsfactory can essentially do the same but using argparse
#pragma once

#include <argparse/argparse.hpp>
#include <spdlog/spdlog.h>

namespace asck {
    class HyperwallArguments : public argparse::ArgumentParser {
    public:
        int loglevel = spdlog::level::info;

        HyperwallArguments(const int argc, const char* argv[]) : ArgumentParser(argv[0]) {
    
            add_argument("--resolution")
                .default_value("1920x1080");
            add_argument("--dimensions")
                .default_value("2x2");
            add_argument("--framerate")
                .scan<'i', int>()
                .default_value(60);
            add_argument("--file")
                .default_value("file.mp4");
            add_argument("--bitrate")
                .default_value("1G");
            add_argument("--rtsp-server")
                .default_value("0.0.0.0:8554");
            add_argument("mode")
                .default_value("file");
            add_argument("-v")
                .action([&](const auto &){loglevel--;})
                .append()
                .default_value(false)
                .implicit_value(true)
                .nargs(0);
            add_argument("-q")
                .action([&](const auto &){loglevel++;})
                .append()
                .default_value(false)
                .implicit_value(true)
                .nargs(0);
    
            try {
                parse_args(argc, argv);
            } catch(std::exception& e) {
                spdlog::error("Failed to parse arguments, exiting!");
                exit(EXIT_FAILURE);
            }
        }
    };
}
