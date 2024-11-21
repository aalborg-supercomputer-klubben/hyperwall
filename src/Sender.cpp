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
const auto RES_X = 3840;
const auto RES_Y = 2160;
const auto FRAMERATE = 60;
const auto REMOTE = "localhost";

std::unordered_map<std::string, std::string> settings = {
  {"RES_X", std::to_string(RES_X)},
  {"RES_Y", std::to_string(RES_Y)},
  {"X", std::to_string(X)},
  {"Y", std::to_string(Y)},
  {"FRAMERATE", std::to_string(FRAMERATE)},
  {"REMOTE", REMOTE}
};

int main() {
  Hyperwall::FileSource source("file.mp4");
  Hyperwall::Hyperwall hyperwall(source, X, Y, settings);
  {
    hyperwall.run();
  }
  exit(EXIT_SUCCESS);
}
