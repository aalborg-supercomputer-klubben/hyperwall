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

int main(const int argc, const char* argv[]) {
    HyperwallArguments arguments(argc, argv);
    Settings settings(arguments);
    spdlog::set_level(settings.loglevel);

    std::cout << "Log level: " << settings.loglevel << std::endl;
    spdlog::debug("Generating settings");

    auto hyperwall = [](Settings settings) {
        spdlog::info("Chosen mode: {}", fromMode(settings.mode));
        switch (settings.mode) {
            case Mode::Webcam: {
                WebcamSource source(0);
                Hyperwall hyperwall(source, settings);
                return hyperwall;
            }
            case Mode::Screenshare: {
                FileSource source("tcp://0.0.0.0:8600?listen");
                Hyperwall hyperwall(source, settings);
                return hyperwall;
            }
            case Mode::File:
            default: {
                FileSource source(settings.file);
                Hyperwall hyperwall(source, settings);
                return hyperwall;
            }
        }
    }(settings);
    {
        hyperwall.run();
    }
    exit(EXIT_SUCCESS);
}
