#include "Hyperwall.hpp"
#include "Sources/FileSource.hpp"
#include "ffmpeg.hpp"
#include <unordered_map>

const Hyperwall::FFMPEG default_ffmpeg(const int x, const int y) {
    Hyperwall::FFMPEGBuilder builder;
    return builder.add("-re")
      .add("-y")
      .add("-f", "rawvideo")
      .add("-vcodec", "rawvideo")
      .add("-pix_fmt", "bgr24")
      .add("-s", "1920x1080")
      .add("-r", "60")
      .add("-i", "-")
      .add("-c:v", "libx264")
      .add("-preset", "ultrafast")
      .add("-f", "rtsp")
      .add("-rtsp_transport", "tcp")
      .add("-muxdelay", "0.1")
      .add("-bsf:v", "dump_extra")
      .add("-b:v", "20M")
      .url(std::format("rtsp://localhost:8554/frame/{}/{}", x, y))
      .build();
  }


Hyperwall::HyperFrame::HyperFrame(const int x, const int y, const int X, const int Y, const FFMPEG& ffmpeg) :
  x(x),
  y(y),
  X(X),
  Y(Y),
  ffmpeg(ffmpeg) {
  std::cout << "Built frame: [x: " << x << ", y: " << y << "]" << std::endl;
}

Hyperwall::HyperFrame::HyperFrame(const HyperFrame& other) :
  x(other.x),
  y(other.y),
  X(other.X),
  Y(other.Y),
  ffmpeg(other.ffmpeg){}

void Hyperwall::HyperFrame::run(const cv::Mat& image) {
  auto start_x = image.cols * ((0.0 + x)/X);
  auto end_x = image.cols * ((1.0+x)/X);
  auto start_y = image.rows * ((0.0 + y)/Y);
  auto end_y = image.rows * ((1.0+y)/Y);
  //std::cout << std::format("{}-{} {}-{}", start_x, end_x, start_y, end_y);

  auto final_image = image(cv::Range(start_y, end_y), cv::Range(start_x, end_x));
  ffmpeg.write(final_image);
}

Hyperwall::Hyperwall::Hyperwall(FileSource& source, int X, int Y, std::unordered_map<std::string, std::string> settings) : source(source), X(X), Y(Y) {
  for(auto x = 0; x < X; x++) {
    frames.insert({x, {}});
    for(auto y = 0; y < Y; y++) {
      FFMPEG ffmpeg = default_ffmpeg(x, y);
      frames[x].insert({y, HyperFrame(x, y, X, Y, ffmpeg)});
    }
  }
};

void Hyperwall::Hyperwall::run() {
  while(true) {
    auto image = source.read();
    for(auto [x, x_frames] : frames) {
      for(auto [y, frame] : x_frames) {
        frame.run(image);
      }
    }
  }
}
