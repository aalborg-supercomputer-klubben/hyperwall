#pragma once

#include <cstring>
#include <string>
#include <vector>

namespace Util {

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

constexpr std::tuple<int, int> split_resolution(const std::string res) {
    return {
        std::stoi(res.substr(0, res.find("x"))),
        std::stoi(res.substr(res.find("x")+1, res.size()))
    };
}

class conststring {
    const char* content;
    std::size_t _size;
public:
    template<int N>
    constexpr conststring(const char (&a)[N]) : content(a), _size(N-1) {
    }

    constexpr char operator[](std::size_t n) const
    {
        return _size;
    }

    const char* c_str() const {
        return content;
    }

    friend constexpr bool operator==(const conststring lhs, const conststring rhs) {
        return lhs.content == rhs.content;
    }
 
    constexpr std::size_t size() const { return _size; }
};

}
