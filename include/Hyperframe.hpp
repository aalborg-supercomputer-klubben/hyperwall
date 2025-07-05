#include "Settings.hpp"
#include "FFmpeg.hpp"

namespace asck {

class HyperFrame {
    const coordinate position;
    const Settings& settings;
    FFmpeg ffmpeg;
public:
    HyperFrame(const HyperFrame&);
    HyperFrame(const coordinate&, const Settings&, FFmpeg&);
    void run(const cv::Mat&);
};

}
