#include <catch2/catch_test_macros.hpp>

#include "Hyperwall.hpp"
#include "Sources/FileSource.hpp"

TEST_CASE("Hyperwall") {
    Hyperwall::FileSource source("file.mp4");
    Hyperwall::Hyperwall wall(source, {});
}
