#pragma once

#include <opencv2/opencv.hpp>

namespace asck {

    class VideoSourceT {
    public:
        virtual cv::Mat read() = 0;
    };

} // Hyperwall
