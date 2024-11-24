#include "Sources/VideoSource.hpp"
#include "Socket.hpp"

namespace Hyperwall {
  class TCPSource : public VideoSourceT {
    Socket::ServerSocket socket;
    Socket::Socket client;
  public:
    TCPSource();
    virtual cv::Mat read() override;
    virtual std::unique_ptr<VideoSourceT> clone() const override;
  };
}
