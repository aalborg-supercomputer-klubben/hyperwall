#pragma once

#include "FFmpeg.hpp"
#include "Sources/VideoSource.hpp"
#include <unordered_map>

namespace Hyperwall {

class HyperFrame {
  const int x;
  const int y;
  const int X;
  const int Y;
  const int RES_X;
  const int RES_Y;
  const FFmpeg ffmpeg;
public:
  HyperFrame(const HyperFrame&);
  HyperFrame(const int, const int, std::unordered_map<std::string, std::string>, const FFmpeg&);
  void run(const cv::Mat&);
};

class Hyperwall {
  std::unique_ptr<VideoSourceT> source;
  const int X;
  const int Y;
  std::unordered_map<int, std::unordered_map<int, HyperFrame>> frames;
public:
  Hyperwall(VideoSourceT&, std::unordered_map<std::string, std::string>);
  void run();
};

} // Hyperwall
