#include <opencv2/videoio.hpp>
#include <string>

#include <opencv2/opencv.hpp>
#include <spdlog/spdlog.h>

#include "Sources/FileSource.hpp"
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

WebcamSource::WebcamSource(const int index) : capture(index) {
    spdlog::info("Initialized webcam: {}", index);
}

cv::Mat WebcamSource::read() {
    cv::Mat frame;
    capture.read(frame);
    spdlog::debug("Read frame");
    return frame;
}

