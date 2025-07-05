#include <vector>

#include <catch2/catch_test_macros.hpp>

#include "Utils.hpp"

using namespace asck;

TEST_CASE("test utility functions: range") {
    auto r1 = range(-1000, 1000);
    std::vector<int> r2;
    for(auto i = -1000; i < 1000; i++) {
        r2.push_back(i);
    }
    REQUIRE(r1 == r2);
}

TEST_CASE("test utility functions: range constexpr") {
    if constexpr (range(10) == range(10)) {
        REQUIRE(true);
    }
    else {
        REQUIRE(false);
    }
}
