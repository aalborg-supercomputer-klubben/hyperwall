#include <catch2/catch_test_macros.hpp>

#include "Settings.hpp"

TEST_CASE("Test settings constexpr") {
    if constexpr (Hyperwall::Settings().framerate) {
        REQUIRE(true);
    }
    else {
        REQUIRE(false);
    }
}