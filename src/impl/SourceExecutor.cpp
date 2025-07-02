#include <string>

#include <spdlog/spdlog.h>

#include "ModeExecutor.hpp"
#include "Hyperwall.hpp"
#include "Settings.hpp"
#include "Sources/WebcamSource.hpp"
#include "Sources/FileSource.hpp"

using namespace asck;

Hyperwall SourceExecutor::run(std::string mode, Settings settings) {
    spdlog::info("Chosen mode: {}", mode);
    if(mode == "webcam") {
        WebcamSource source(0);
        Hyperwall hyperwall(source, settings);
        return hyperwall;
    }
    else if(mode == "screenshare") {
        FileSource source("tcp://0.0.0.0:8600?listen");
        Hyperwall hyperwall(source, settings);
        return hyperwall;
    }
    else {
        auto filename = parser.get<std::string>("--file");
        if(!std::filesystem::exists(std::filesystem::path(filename))){
            spdlog::error("File: {} does not exist!", filename);
            exit(EXIT_FAILURE);
        }
        FileSource source(filename);
        Hyperwall hyperwall(source, settings);
        return hyperwall;
    }

}
