#include <catch2/catch_test_macros.hpp>

#include "FFmpeg.hpp"

using namespace asck;

TEST_CASE("test ffmpeg constructors") {
    std::vector<FFmpeg> ffmpegs({
        {{{1920, 1080}, {2, 2}, "0.0.0.0:8554", "1G", 60}},
        {{{1920, 1080}, {2, 2}, "0.0.0.0:8554", "1G"}},
        {{{1920, 1080}, {2, 2}, "0.0.0.0:8554"}},
        {{{1920, 1080}, {2, 2}}},
        {{{1920, 1080}}},
        {}
    });
    for(auto i = 0; i < ffmpegs.size()-1; i++) {
        auto [rx1, ry1] = ffmpegs[i].resolution;
        auto [rx2, ry2] = ffmpegs[i].resolution;
        auto [x1, y1] = ffmpegs[i].position;
        auto [x2, y2] = ffmpegs[i].position;
        REQUIRE(rx1 == rx2);
        REQUIRE(ry1 == ry2);
        REQUIRE(ffmpegs[i].framerate == ffmpegs[i+1].framerate);
        REQUIRE(ffmpegs[i].bitrate == ffmpegs[i+1].bitrate);
        REQUIRE(x1 == x2);
        REQUIRE(y1 == y2);
    }
}
