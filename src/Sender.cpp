#include <cstdlib>
#include <string>

#include <argparse/argparse.hpp>
#include <opencv2/opencv.hpp>
#include <spdlog/spdlog.h>

#include "Hyperwall.hpp"
#include "Sources/FileSource.hpp"
#include "Sources/WebcamSource.hpp"
#include "Mode.hpp"

using namespace asck;

VideoSourceT& getVideoSource(const Settings& settings) {
    switch(settings.mode) {
        default:
        case Mode::File: {
            static FileSource source(settings.file);
            return source;
        }
        case Mode::Screenshare: {
            static FileSource source("tcp://0.0.0.0:8600?listen");
            return source;
        }
        case Mode::Webcam: {
            static WebcamSource source(0);
            return source;
        }
    }
}

int main(const int argc, const char* argv[]) {
    const HyperwallArguments arguments(argc, argv);
    const Settings settings(arguments);
    spdlog::set_level(settings.loglevel);

    std::cout << "Log level: " << settings.loglevel << std::endl;
    spdlog::debug("Generating settings");

    auto& source = getVideoSource(settings);
    Hyperwall hyperwall(source, settings);

    {
        hyperwall.run();
    }
    exit(EXIT_SUCCESS);
}
