#include <catch2/catch_test_macros.hpp>

#include "Hyperwall.hpp"
#include "Settings.hpp"
#include "Sources/FileSource.hpp"

using namespace asck;

TEST_CASE("Hyperwall") {
    FileSource source("file.mp4");
    Settings settings;
    Hyperwall wall(source, settings);
}
