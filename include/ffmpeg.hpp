#include <string>
#include <vector>

namespace Hyperwall {

  class FFMPEG {
    std::vector<std::string> options;
    
    public:
      FFMPEG& add(std::string);
      FFMPEG& add(std::string, std::string);
      std::string build();
  };

} // Hyperwall
