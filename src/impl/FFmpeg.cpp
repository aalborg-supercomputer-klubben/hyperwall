#include <cstdio>

#include <opencv2/opencv.hpp>
#include <spdlog/spdlog.h>

#include "FFmpeg.hpp"

const void Hyperwall::FFmpeg::open() {
    const auto [res_x, res_y] = resolution;
    const auto [x, y] = position;
    std::stringstream ss;
    ss << "ffmpeg -re -y -f rawvideo -vcodec rawvideo -pix_fmt bgr24 -s "
        << res_x << "x" << res_y
        << " -r " << framerate
        << " -i - -f mpegts -preset ultrafast -s "
        << res_x << "x" << res_y
        << " -r " << framerate
        << " -f rtsp -b:v "
        << bitrate
        << " rtsp://0.0.0.0:8554/frame/" << x << "/" << y <<
        " 2> ./logs/stderr-" << x << "-" << y << ".log"
        << " > ./logs/stdout-" << x << "-" << y << ".log";

    
    buffer = popen(ss.str().c_str(), "w");
}

const void Hyperwall::FFmpeg::write(const cv::Mat& mat) const {
    fwrite(mat.data, 1, mat.cols * mat.rows * 3, buffer);
    fflush(buffer);
}

