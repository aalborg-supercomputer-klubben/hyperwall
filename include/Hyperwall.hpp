#pragma once

#include "Sources/VideoSource.hpp"
#include "Settings.hpp"
#include "Hyperframe.hpp"

namespace asck {

class Hyperwall {
    std::unique_ptr<VideoSourceT> source;
    std::vector<HyperFrame> frames;
    const coordinate dimensions;
public:
    Hyperwall(VideoSourceT&, Settings&);
    void run();
};

} // Hyperwall
