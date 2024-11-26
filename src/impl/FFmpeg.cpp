#include <cstdio>
#include <format>
#include <spdlog/spdlog.h>
#include <sstream>
#include <string>

#include <opencv2/opencv.hpp>

#include "FFmpeg.hpp"

Hyperwall::FFmpegBuilder& Hyperwall::FFmpegBuilder::add(const std::string option) {
    options.push_back(option);
    spdlog::debug("Adding option: {}", option);
    return *this;
}

Hyperwall::FFmpegBuilder& Hyperwall::FFmpegBuilder::add(const std::string key, const std::string value) {
    options.push_back(std::format("{} {}", key, value));
    spdlog::debug("Adding option: {} identified by: {}", value, key);
    return *this;
}

Hyperwall::FFmpegBuilder& Hyperwall::FFmpegBuilder::url(const std::string url) {
    this->_url = url;
    add(url);
    return *this;
}

const Hyperwall::FFmpeg Hyperwall::FFmpegBuilder::build(std::string logname) {
    std::stringstream ss;
    ss << "ffmpeg ";
    for(auto option : options)
        ss << option << " ";
    ss << std::format(">> ./logs/stdout-{0} 2> ./logs/stderr-{0}", logname);
    return {ss.str(), _url};
}

Hyperwall::FFmpeg::FFmpeg(const std::string command, const std::string url) : url(url) {
    buffer = popen(command.c_str(), "w");
}

const void Hyperwall::FFmpeg::write(const cv::Mat& mat) const {
    //std::cout << url << std::endl;
    fwrite(mat.data, 1, mat.cols * mat.rows * 3, buffer);
    fflush(buffer);
}

