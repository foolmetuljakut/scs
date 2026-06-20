#pragma once
#include "../std.hpp"

namespace src::generic {

template <typename T, typename Comparison>
T max_choice(const std::vector<T> &v, Comparison greater) {
  return *std::max_element(v.begin(), v.end(), greater);
}

} // namespace src::generic