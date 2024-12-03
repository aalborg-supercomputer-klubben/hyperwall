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

// TODO: fix range statement constexpr
//TEST_CASE("test utility functions: range constexpr") {
//    if constexpr (Util::range(10) == Util::range(10)) {
//        REQUIRE(true);
//    }
//    else {
//        REQUIRE(false);
//    }
//}

TEST_CASE("test conststring") {
    if constexpr(Util::conststring("test") == Util::conststring("test")) {

    }
}
