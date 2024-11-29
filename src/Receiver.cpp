
#include <argparse/argparse.hpp>
#include <cstdlib>
#include <exception>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>

#include <spdlog/spdlog.h>

std::string split_res(std::string res, std::string direction) {
    if (direction == "x") {
        return res.substr(0, res.find("x"));
    }
    return res.substr(res.find("x")+1, res.size());
}

int main(int argc, char* argv[]) {
    argparse::ArgumentParser parser;

    parser.add_argument("coordinate")
        .default_value("0x0");

    try {
        parser.parse_args(argc, argv);
    }
    catch(std::exception& e) {
        spdlog::error("Failed to parse args, exiting");
        exit(EXIT_FAILURE);
    }

    cv::VideoCapture capture(
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
