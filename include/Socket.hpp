#include <sys/socket.h>
#include <netinet/in.h>


#include <string>

namespace Socket {
  class Socket {
    int fd;
    sockaddr_in saddr;
  public:
    Socket();
    Socket(int, int);
    Socket(int, sockaddr_in);
    void connect(std::string, int);
    char read();
    std::string read(int);
    void write(char*);
    void close();
  };

  class ServerSocket {
    int fd;
    sockaddr_in saddr;
  public:
    ServerSocket(int, int);
    void bind(int);
    void bind(std::string, int);
    void listen();
    Socket accept();
    void close();
    
  };
}
