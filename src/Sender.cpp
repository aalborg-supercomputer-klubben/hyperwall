#include <cstdlib>
#include <opencv2/core/mat.hpp>
#include <opencv2/opencv.hpp>
#include <string>
#include <unordered_map>

#include "Hyperwall.hpp"
#include "Sources/FileSource.hpp"

// TODO: argument parsing
const auto X = 2;
const auto Y = 2;
const auto RES_X = 1920;
const auto RES_Y = 1080;
const auto FRAMERATE = 60;
const auto REMOTE = "localhost:8554";
const auto BITRATE = "2M";

std::unordered_map<std::string, std::string> settings = {};

int main() {
  Hyperwall::FileSource source("file.mp4");
  Hyperwall::Hyperwall hyperwall(source, X, Y, settings);
  {
    hyperwall.run();
  }
  exit(EXIT_SUCCESS);
}
