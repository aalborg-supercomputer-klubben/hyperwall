#include <string>

#include <opencv2/opencv.hpp>
#include <spdlog/spdlog.h>

#include "Sources/FileSource.hpp"
#include "Sources/VideoSource.hpp"
#include "Sources/WebcamSource.hpp"

using namespace asck;

FileSource::FileSource(std::string filename) : capture(filename) {
    spdlog::info("Initialized filesource: {}", filename);
}

cv::Mat FileSource::read() {
    cv::Mat frame;
    capture.read(frame);
    spdlog::debug("Read frame");
    return frame;
}

std::unique_ptr<VideoSourceT> FileSource::clone() const {
    spdlog::debug("Cloned video source object");
    return std::make_unique<FileSource>(*this);
}

WebcamSource::WebcamSource(const int index) : capture(index) {
    spdlog::info("Initialized webcam: {}", index);
}

cv::Mat WebcamSource::read() {
    cv::Mat frame;
    capture.read(frame);
    spdlog::debug("Read frame");
    return frame;
}

std::unique_ptr<VideoSourceT> WebcamSource::clone() const {
    spdlog::debug("Cloned video source object");
    return std::make_unique<WebcamSource>(*this);
}
