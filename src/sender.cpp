#include "sender.hpp"

#include <cstdlib>
#include <opencv2/core/mat.hpp>
#include <opencv2/opencv.hpp>
#include <string>
#include <unordered_map>

// TODO: argument parsing
auto X = 1;
auto Y = 1;
auto RES_X = 1920;
auto RES_Y = 1080;
auto FRAMERATE = 60;
auto REMOTE = "localhost:8554";

std::string ffmpeg(int x, int y) {
    return std::string("ffmpeg -re -f rawvideo -video_size 1920x1080 -pixel_format bgr24 -i pipe: -f rtsp -b:v 2M rtsp://") + REMOTE + "/frame/" + std::to_string(x) + "/" + std::to_string(y);
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
