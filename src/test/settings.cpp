#include <catch2/catch_test_macros.hpp>

#include "Settings.hpp"

using namespace asck;

TEST_CASE("Test settings constexpr") {
    static constexpr Settings settings;
    if constexpr (settings.framerate) {
        REQUIRE(true);
    }
    else {
        REQUIRE(false);
    }
}
