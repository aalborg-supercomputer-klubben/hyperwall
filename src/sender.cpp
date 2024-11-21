#include "sender.hpp"

#include <cstdlib>
#include <opencv2/core/mat.hpp>
#include <opencv2/opencv.hpp>

// TODO: argument parsing
auto X = 2;
auto Y = 2;
auto RES_X = 1920;
auto RES_Y = 1080;
auto FFMPEG = "";

int main() {
  FILE* pipeout = popen(FFMPEG, "w");
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
        std::cout << "rows: " << frame.rows << " cols: " << frame.cols << std::endl;
        std::cout << "sx: " << sx << " ex: " << ex << " sy: " << sy << " ey: " << ey << std::endl;
        auto final_frame = frame(cv::Range(sx, ex), cv::Range(sy, ey));
        fwrite(frame.data, 1, (size_t)frame.cols * frame.rows, pipeout);
      }
    }
  }
}
