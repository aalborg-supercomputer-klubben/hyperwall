#pragma once

#include "Sources/VideoSource.hpp"
#include "Settings.hpp"
#include "Hyperframe.hpp"

namespace asck {

    class Hyperwall {
        VideoSourceT& source;
        std::vector<HyperFrame> frames;
    public:
        Hyperwall(VideoSourceT&, const Settings&);
        void run();
    };

} // Hyperwall
