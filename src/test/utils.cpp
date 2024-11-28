#include <vector>

#include <catch2/catch_test_macros.hpp>

#include "Utils.hpp"

TEST_CASE("test utility functions: range") {
    auto r1 = Util::range(-1000, 1000);
    std::vector<int> r2;
    for(auto i = -1000; i < 1000; i++) {
        r2.push_back(i);
    }
    REQUIRE(r1 == r2);
}
