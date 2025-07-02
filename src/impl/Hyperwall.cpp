#include <spdlog/spdlog.h>

#include "Utils.hpp"
#include "FFmpeg.hpp"
#include "Hyperwall.hpp"

using namespace asck;

Hyperwall::Hyperwall(VideoSourceT& source, Settings& settings) :
    source(source.clone()) {
    spdlog::info("Generating hyperwall...");
    const auto& [res_x, res_y] = settings.resolution;
    const auto& [X, Y] = settings.dimensions;
    for(const auto x : range(X)) {
        for(const auto y : range(Y)) {
            FFmpeg ffmpeg(settings, {x, y});
            frames.push_back({{x, y}, settings, ffmpeg});
        }
    }
};

void Hyperwall::run() {
    spdlog::info("Running Hyperwall");
    while(true) {
        auto image = source->read();
        if (image.rows == 0 || image.cols == 0) {
            break;
        }
        for(auto& frame : frames) {
            frame.run(image);
        }
    }
    spdlog::info("Finished hyperwall execution");
}
