#include <spdlog/spdlog.h>

#include "Hyperframe.hpp"

using namespace asck;

HyperFrame::HyperFrame(const coordinate& position, const Settings& settings, FFmpeg& ffmpeg) :
    position(position),
    settings(settings),
    ffmpeg(ffmpeg) {
    this->ffmpeg.open();
    const auto& [x, y] = position;
    spdlog::info("Built HyperFrame: [x: {}, y: {}, uri: {}]", x, y, ffmpeg.uri());
}

HyperFrame::HyperFrame(const HyperFrame& other) :
    position(other.position),
    settings(other.settings),
    ffmpeg(other.ffmpeg) {
    const auto& [x, y] = position;
    const auto& [X, Y] = settings.dimensions;
    spdlog::debug("Copied hyperframe object at: ({}) in {}", x,y,X,Y);
}

void HyperFrame::run(const cv::Mat& image) {
    const auto& [x, y] = position;
    const auto& [X, Y] = settings.dimensions;
    const auto& [res_x, res_y] = settings.resolution;
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
