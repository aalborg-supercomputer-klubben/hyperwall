#include <spdlog/spdlog.h>
#include <string>
#include <unordered_map>

#include <spdlog/spdlog.h>

#include "Utils.hpp"
#include "FFmpeg.hpp"
#include "Hyperwall.hpp"

Hyperwall::HyperFrame::HyperFrame(const int x, const int y, std::unordered_map<std::string, std::string> settings, FFmpeg& ffmpeg) :
    x(x),
    y(y),
    X(stoi(settings["X"])),
    Y(stoi(settings["Y"])),
    ffmpeg(ffmpeg),
    RES_X(stoi(settings["RES_X"])),
    RES_Y(stoi(settings["RES_Y"])) {
    this->ffmpeg.open();
    spdlog::info("Built HyperFrame: [x: {}, y: {}, uri: {}]", x, y, ffmpeg.uri());
}

Hyperwall::HyperFrame::HyperFrame(const HyperFrame& other) :
    x(other.x),
    y(other.y),
    X(other.X),
    Y(other.Y),
    ffmpeg(other.ffmpeg),
    RES_X(other.RES_X),
    RES_Y(other.RES_Y) {
    spdlog::debug("Copied hyperframe object at: ({},{}) in {}x{}", x,y,X,Y);
}

void Hyperwall::HyperFrame::run(const cv::Mat& image) {
    spdlog::debug("Running Hyperframe");
    auto start_x = (int)(image.cols * ((0.0 + x)/X));
    auto end_x = (int)(image.cols * ((1.0+x)/X));
    auto start_y = (int)(image.rows * ((0.0 + y)/Y));
    auto end_y = (int)(image.rows * ((1.0+y)/Y));

    auto sub_image = image(cv::Range(start_y, end_y), cv::Range(start_x, end_x));
    cv::Mat resized_image;
    cv::resize(sub_image, resized_image, cv::Size(RES_X/X, RES_Y/Y));
    ffmpeg.write(resized_image);
}

Hyperwall::Hyperwall::Hyperwall(VideoSourceT& source, std::unordered_map<std::string, std::string> settings) : source(source.clone()), X(stoi(settings["X"])), Y(stoi(settings["Y"])) {
    spdlog::info("Generating hyperwall...");
    for(const auto x : Util::range(X)) {
        frames.insert({x, {}});
        for(const auto y : Util::range(Y)) {
            FFmpeg ffmpeg(
                {std::stoi(settings["RES_X"])/X, std::stoi(settings["RES_Y"])/Y},
                std::stoi(settings["FRAMERATE"]),
                settings["BITRATE"],
                {x, y}
            );
            frames[x].insert({y, HyperFrame(x, y, settings, ffmpeg)});
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
        for(auto& [x, x_frames] : frames) {
            for(auto& [y, frame] : x_frames) {
              frame.run(image);
            }
        }
    }
    spdlog::info("Finished hyperwall execution");
}
