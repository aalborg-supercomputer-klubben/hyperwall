#include "Socket.hpp"

#include <opencv2/opencv.hpp>

#include <iostream>
#include <sys/socket.h>

int main() {
  Socket::ServerSocket s(AF_INET, SOCK_STREAM);
  s.bind("127.0.0.1", 8080);
  s.listen();
  while(true) {
    auto c = s.accept();
    std::cout << "received client" << std::endl;
    std::string buf;
    while(true) {
      auto input = c.read();
      if(input == EOF) {
        std::cout << "file over" << std::endl;
        cv::Mat mat(1080, 1920, CV_8UC3, (std::byte*)buf.c_str());
        std::cout << mat << std::endl;
        exit(0);
      }
      else {
        buf += input;
      }
    }
    
  }
}
