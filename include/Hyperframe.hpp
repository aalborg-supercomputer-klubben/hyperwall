#include "Settings.hpp"
#include "FFmpeg.hpp"

namespace asck {

class HyperFrame {
    const coordinate position;
    const coordinate dimensions;
    const coordinate resolution;
    FFmpeg ffmpeg;
public:
    HyperFrame(const HyperFrame&);
    HyperFrame(const coordinate&, Settings&, FFmpeg&);
    void run(const cv::Mat&);
};

}
