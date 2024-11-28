#include <spdlog/spdlog.h>

#include <spdlog/spdlog.h>

#include "Utils.hpp"
#include "FFmpeg.hpp"
#include "Hyperwall.hpp"

Hyperwall::HyperFrame::HyperFrame(const coordinate& position, Settings settings, FFmpeg& ffmpeg) :
    position(position),
    dimensions(settings.dimensions),
    ffmpeg(ffmpeg),
    resolution(settings.resolution) {
    this->ffmpeg.open();
    const auto& [x, y] = position;
    spdlog::info("Built HyperFrame: [x: {}, y: {}, uri: {}]", x, y, ffmpeg.uri());
}

Hyperwall::HyperFrame::HyperFrame(const HyperFrame& other) :
    position(other.position),
    dimensions(other.dimensions),
    resolution(other.resolution),
    ffmpeg(other.ffmpeg) {
    const auto& [x, y] = position;
    const auto& [X, Y] = dimensions;
    spdlog::debug("Copied hyperframe object at: ({}) in {}", x,y,X,Y);
}

void Hyperwall::HyperFrame::run(const cv::Mat& image) {
    const auto& [x, y] = position;
    const auto& [X, Y] = dimensions;
    const auto& [res_x, res_y] = resolution;
    spdlog::debug("Running Hyperframe: p: {}x{}, d: {}x{}, r: {}x{}", x, y, X, Y, res_x, res_y);
    auto start_x = (int)(image.cols * ((0.0 + x)/X));
    auto end_x = (int)(image.cols * ((1.0+x)/X));
    auto start_y = (int)(image.rows * ((0.0 + y)/Y));
    auto end_y = (int)(image.rows * ((1.0+y)/Y));

    auto sub_image = image(cv::Range(start_y, end_y), cv::Range(start_x, end_x));
    cv::Mat resized_image;
    cv::resize(sub_image, resized_image, cv::Size(res_x/X, res_y/Y));
    ffmpeg.write(resized_image);
}

Hyperwall::Hyperwall::Hyperwall(VideoSourceT& source, Settings settings) :
    source(source.clone()),
    dimensions(settings.dimensions) {
    spdlog::info("Generating hyperwall...");
    const auto& [res_x, res_y] = settings.resolution;
    const auto& [X, Y] = settings.dimensions;
    for(const auto x : Util::range(X)) {
        for(const auto y : Util::range(Y)) {
            FFmpeg ffmpeg(settings, {x, y});
            frames.push_back({{x, y}, settings, ffmpeg});
        }
    }
};

void Hyperwall::Hyperwall::run() {
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
