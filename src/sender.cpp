#include <cstdlib>
#include <format>
#include <opencv2/core/mat.hpp>
#include <opencv2/opencv.hpp>
#include <string>
#include <unordered_map>

#include "ffmpeg.hpp"

// TODO: argument parsing
const auto X = 1;
const auto Y = 1;
const auto RES_X = 1920;
const auto RES_Y = 1080;
const auto FRAMERATE = 60;
const auto REMOTE = "localhost:8554";
const auto BITRATE = "20M";

const std::string ffmpeg(const int x, const int y) {
  Hyperwall::FFMPEG obj;
  return obj.add("-re")
    .add("-y")
    .add("-f", "rawvideo")
    .add("-vcodec", "rawvideo")
    .add("-pix_fmt", "bgr24")
    .add("-s", std::format("{}x{}", RES_X/X, RES_Y/Y))
    .add("-r", std::to_string(FRAMERATE))
    .add("-i", "-")
    .add("-c:v", "libx264")
    .add("-preset", "ultrafast")
    .add("-f", "rtsp")
    .add("-rtsp_transport", "tcp")
    .add("-muxdelay", "0.1")
    .add("-bsf:v", "dump_extra")
    .add("-b:v", BITRATE)
    .add(std::format("rtsp://{}/frame/{}/{}", REMOTE, x, y))
    .build();

}

int main() {
  std::unordered_map<int, std::unordered_map<int, FILE*>> pipes;
  for(auto x = 0; x < X; x++) {
    for(auto y = 0; y < Y; y++) {
      pipes[x][y] = popen(ffmpeg(x, y).c_str(), "w");
    }
  }
  cv::VideoCapture capture("file.mp4");
  while(true) {
    cv::Mat frame;
    capture.read(frame);
    for(auto x = 0; x < X; x++) {
      for(auto y = 0; y < Y; y++) {
        auto sx = frame.cols * (x/X);
        auto ex = frame.cols * ((1.0+x)/X);
        auto sy = frame.rows * (y/Y);
        auto ey = frame.rows * ((1.0+y)/Y);
        auto final_frame = frame(cv::Range(sy, ey), cv::Range(sx, ex));
        fwrite(final_frame.data, 1, (size_t)final_frame.cols * final_frame.rows * 3, pipes[x][y]);
      }
    }
  }
  for(auto [_, m] : pipes)
    for(auto [_, pipe] : m)
      pclose(pipe);

  exit(EXIT_SUCCESS);
}
