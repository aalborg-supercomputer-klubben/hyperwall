#pragma once

#include <string>
#include <vector>
#include <cmath>

namespace asck {
typedef std::tuple<int, int> coordinate;

template<typename T = int>
constexpr std::vector<T> range(const int n) {
    std::vector<T> values;
    for(auto i = 0; i < n; i++)
        values.push_back(i);
    return values;
}

template<typename T = int>
constexpr std::vector<T> range(const int start, const int end) {
    std::vector<T> values;
    for(auto i = start; i < end; i++)
        values.push_back(i);
    return values;
}

constexpr std::tuple<int, int> splitResolution(const std::string res) {
    return {
        std::stoi(res.substr(0, res.find("x"))),
        std::stoi(res.substr(res.find("x")+1, res.size()))
    };
}

template<int number>
constexpr bool isPerfectSquare() {
    if (number < 0) {
        return false;
    } else {
        auto root = static_cast<int>(std::sqrt(number));
        return root * root == number;
    }
}

template<int count>
constexpr coordinate countToDimensions() {
    static_assert(isPerfectSquare<count>(), "Count must be a perfect square");
    int root = 1;
    while (root * root < count) ++root;
    return coordinate{root, root};
}


}
