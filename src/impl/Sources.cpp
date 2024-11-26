#include <spdlog/spdlog.h>
#include <string>

#include <opencv2/opencv.hpp>

#include "Sources/FileSource.hpp"
#include "Sources/VideoSource.hpp"
#include "Sources/WebcamSource.hpp"


Hyperwall::FileSource::FileSource(std::string filename) : capture(filename) {
    spdlog::info("Initialized filesource: {}", filename);
}

cv::Mat Hyperwall::FileSource::read() {
    cv::Mat frame;
    capture.read(frame);
    spdlog::debug("Read frame");
    return frame;
}

std::unique_ptr<Hyperwall::VideoSourceT> Hyperwall::FileSource::clone() const {
    spdlog::debug("Cloned video source object");
    return std::make_unique<FileSource>(*this);
}

Hyperwall::WebcamSource::WebcamSource(const int index) : capture(index) {
    spdlog::info("Initialized webcam: {}", index);
}

cv::Mat Hyperwall::WebcamSource::read() {
    cv::Mat frame;
    capture.read(frame);
    spdlog::debug("Read frame");
    return frame;
}

std::unique_ptr<Hyperwall::VideoSourceT> Hyperwall::WebcamSource::clone() const {
    spdlog::debug("Cloned video source object");
    return std::make_unique<WebcamSource>(*this);
}
