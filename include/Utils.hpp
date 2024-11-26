
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

}
