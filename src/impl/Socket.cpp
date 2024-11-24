#include "Socket.hpp"

#include <cstdlib>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>

#include <iostream>
#include <unistd.h>

Socket::Socket::Socket() {

}

Socket::Socket::Socket(int domain, int type) {
  if((fd = socket(domain, type, 0)) == -1) {
    std::cerr << "Error, failed to create socket" << std::endl;
  };
  saddr.sin_family = domain;
}

Socket::Socket::Socket(int fd, sockaddr_in addr) : fd(fd), saddr(addr) {

}

void Socket::Socket::connect(std::string addr, int port) {
  saddr.sin_port = htons(port);
  saddr.sin_addr.s_addr = inet_addr(addr.c_str());
  if (::connect(fd, (struct sockaddr*)&saddr, sizeof(sockaddr)) == -1) {
    std::cerr << "Error, failed to connect..." << std::endl;
    exit(EXIT_FAILURE);
  }
}

std::string Socket::Socket::read(int amount) {
  char* buffer = (char*) malloc(amount*sizeof(char));
  recv(fd, buffer, sizeof(buffer), 0);
  return std::string(buffer);
}

char Socket::Socket::read() {
  char buf[1];
  recv(fd, buf, sizeof(buf), 0);
  return buf[0];
}

void Socket::Socket::write(char* input) {
  ::send(fd, input, strlen(input), 0);
}

void Socket::Socket::close() {
  ::close(fd);
}

Socket::ServerSocket::ServerSocket(int domain, int type) {
  if((fd = socket(domain, type, 0)) == -1) {
    std::cerr << "Error, failed to create socket" << std::endl;
    exit(EXIT_FAILURE);
  }
  saddr.sin_family = domain;
}

void Socket::ServerSocket::bind(int port) {
  saddr.sin_port = htons(port);
  saddr.sin_addr.s_addr = INADDR_ANY;
  if (::bind(fd, (struct sockaddr*)&saddr, sizeof(saddr)) == -1) {
    std::cerr << "Error, failed to bind socket" << std::endl;
    exit(EXIT_FAILURE);
  }
}

void Socket::ServerSocket::bind(std::string addr, int port) {
  saddr.sin_port = htons(port);
  saddr.sin_addr.s_addr = inet_addr(addr.c_str());
  if(::bind(fd, (struct sockaddr*)&saddr, sizeof(saddr)) == -1) {
    std::cerr << "Error, failed to bind socket" << std::endl;
    exit(EXIT_FAILURE);
  }
}

void Socket::ServerSocket::listen() {
  if(::listen(fd, 10) == -1) {
    std::cerr << "Failed to start listening" << std::endl;
    exit(EXIT_FAILURE);
  }
}

Socket::Socket Socket::ServerSocket::accept() {
  sockaddr_in client_saddr;
  socklen_t socklen = sizeof(client_saddr);
  int c_fd = ::accept(fd, (struct sockaddr*)&client_saddr, &socklen);
  return {c_fd, client_saddr};
}
