#pragma once

#include "Sources/FileSource.hpp"
#include "ffmpeg.hpp"

namespace Hyperwall {

class HyperFrame {
  const int x;
  const int y;
  const int X;
  const int Y;
  const FFMPEG ffmpeg;
public:
  HyperFrame(const HyperFrame&);
  HyperFrame(const int, const int, const int, const int, const FFMPEG&);
  void run(const cv::Mat&);
};

class Hyperwall {
  FileSource source; //TODO: fix later
  const int X;
  const int Y;
  std::unordered_map<int, std::unordered_map<int, HyperFrame>> frames;
public:
  Hyperwall(FileSource&, int, int, std::unordered_map<std::string, std::string>);
  void run();
};

} // Hyperwall
