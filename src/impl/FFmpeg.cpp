#include <cstdio>

#include <opencv2/opencv.hpp>
#include <spdlog/spdlog.h>

#include "FFmpeg.hpp"

using namespace asck;

const void FFmpeg::open() {
    const auto [res_x, res_y] = resolution;
    const auto [x, y] = position;
    const auto [X, Y] = dimensions;
    std::stringstream ss;
    ss << "ffmpeg -re -y -f rawvideo -vcodec rawvideo -pix_fmt bgr24 -s "
        << res_x/X << "x" << res_y/Y
        << " -r " << framerate
        << " -i - -f mpegts -preset ultrafast -s "
        << res_x/X << "x" << res_y/Y
        << " -r " << framerate
        << " -f rtsp -b:v "
        << bitrate
        << " rtsp://" << rtsp_server << "/frame/" << x << "/" << y <<
        " 2> ./logs/stderr-" << x << "-" << y << ".log"
        << " > ./logs/stdout-" << x << "-" << y << ".log";

    
    buffer = popen(ss.str().c_str(), "w");
}

const void FFmpeg::write(const cv::Mat& mat) const {
    fwrite(mat.data, 1, mat.cols * mat.rows * 3, buffer);
    fflush(buffer);
}

