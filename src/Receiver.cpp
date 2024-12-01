
#include <argparse/argparse.hpp>
#include <cstdlib>
#include <exception>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>

#include <opencv2/videoio.hpp>
#include <spdlog/spdlog.h>
#include <thread>

#include "Utils.hpp"

std::string split_res(std::string res, std::string direction) {
    if (direction == "x") {
        return res.substr(0, res.find("x"));
    }
    return res.substr(res.find("x")+1, res.size());
}

cv::VideoCapture await_capture(std::string path) {
    while(true) {
        cv::VideoCapture capture(path);
        if (capture.isOpened())
            return capture;
    }
}

int main(int argc, char* argv[]) {
    argparse::ArgumentParser parser;

    parser.add_argument("--address")
        .default_value("0.0.0.0");
    parser.add_argument("--test")
        .default_value(false)
        .implicit_value(true)
        .nargs(0);
    parser.add_argument("coordinate")
        .default_value("0x0");

    try {
        parser.parse_args(argc, argv);
    }
    catch(std::exception& e) {
        spdlog::error("Failed to parse args, exiting");
        exit(EXIT_FAILURE);
    }
    if(!parser.get<bool>("--test")) {
        cv::VideoCapture capture = await_capture(
            std::format("rtsp://0.0.0.0:8554/frame/{}/{}",
            split_res(parser.get("coordinate"), "x"),
            split_res(parser.get("coordinate"), "y")));
        while(true)  {
            cv::Mat frame;
            capture.read(frame);
            spdlog::debug("Read frame...");
            cv::imshow("frame", frame);

            if(cv::waitKey(30) == 27) {
                break;
            }
        }
        exit(EXIT_SUCCESS);
    }
    else {
        // not particularly good
        std::vector<std::thread> threads;
        for(const auto& x : Util::range(stoi(split_res(parser.get("coordinate"), "x")))) {
            for(const auto& y : Util::range(stoi(split_res(parser.get("coordinate"), "y")))) {
                threads.push_back(std::thread{[x, y](){
                    spdlog::info("Running thread: {} {}", x, y);
                    auto capture = await_capture(std::format("rtsp://0.0.0.0:8554/frame/{}/{}", x, y));
                    while(true) {
                        cv::Mat frame;
                        capture.read(frame);
                        cv::imshow(std::format("frame-{}-{}", x, y), frame);

                        if(cv::waitKey(30) == 27) {
                            break;
                        }
                    }
                }});
            }
        }
        for(auto& thread : threads)
            thread.join();
    }
}
