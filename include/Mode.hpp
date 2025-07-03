#pragma once

#include <string>
#include <unordered_map>

namespace asck {
    enum Mode {
        Webcam,
        Screenshare,
        File
    };


    inline Mode toMode(std::string modeString) {
        std::unordered_map<std::string, Mode> modeMap{
            {"webcam", Webcam},
            {"screenshare", Screenshare},
            {"file", File}
        };
        if (modeMap.contains(modeString)) {
            return modeMap[modeString];
        } else {
            throw std::exception();
        }
    }
    
    inline std::string fromMode(Mode mode) {
        switch(mode) {
            case Mode::Webcam:
                return "webcam";
            case Mode::Screenshare:
                return "screenshare";
            case Mode::File:
                return "file";
            default:
                throw std::exception();
        }
    }
}
