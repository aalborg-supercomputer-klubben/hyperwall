#include <catch2/catch_test_macros.hpp>

#include "Settings.hpp"

using namespace asck;

TEST_CASE("Test settings constexpr") {
    if constexpr (Settings().framerate) {
        REQUIRE(true);
    }
    else {
        REQUIRE(false);
    }
}
