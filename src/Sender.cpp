#include <cstdlib>
#include <opencv2/core/mat.hpp>
#include <opencv2/opencv.hpp>
#include <string>
#include <unordered_map>

#include <argparse/argparse.hpp>

#include "Hyperwall.hpp"
#include "Sources/FileSource.hpp"
#include "Sources/WebcamSource.hpp"
#include "Sources/TCPSource.hpp"

std::string split_res(std::string res, std::string direction) {
  if (direction == "x") {
    return res.substr(0, res.find("x"));
  }
  return res.substr(res.find("x")+1, res.size());
}

int main(int argc, char* argv[]) {
  argparse::ArgumentParser parser;
  parser.add_argument("--dimensions")
    .default_value("2x2");
  parser.add_argument("--resolution")
    .default_value("1920x1080");
  parser.add_argument("--framerate")
    .default_value("60");
  parser.add_argument("--file")
    .default_value("file.mp4");
  parser.add_argument("mode")
    .default_value("file");

  try {
    parser.parse_args(argc, argv);
  } catch(std::exception& e) {
    std::cerr << "fuck, exiting..." << std::endl;
    exit(EXIT_FAILURE);
  }

  std::unordered_map<std::string, std::string> settings({
    {"RES_X", split_res(parser.get<std::string>("--resolution"), "x")},
    {"RES_Y", split_res(parser.get<std::string>("--resolution"), "y")},
    {"X", split_res(parser.get<std::string>("--dimensions"), "x")},
    {"Y", split_res(parser.get<std::string>("--dimensions"), "y")},
    {"FRAMERATE", parser.get<std::string>("--framerate")}
  });
  Hyperwall::Hyperwall hyperwall = [&settings, &parser](std::string mode) {
    if(mode == "webcam") {
      Hyperwall::WebcamSource source(0);
      Hyperwall::Hyperwall hyperwall(source, settings);
      return hyperwall;
    }
    else if(mode == "tcp") {
      Hyperwall::TCPSource source;
      Hyperwall::Hyperwall hyperwall(source, settings);
      return hyperwall;
    }
    else {
      Hyperwall::FileSource source(parser.get<std::string>("--file"));
      Hyperwall::Hyperwall hyperwall(source, settings);
      return hyperwall;
    }
  }(parser.get<std::string>("mode"));
  {
    hyperwall.run();
  }
  exit(EXIT_SUCCESS);
}
