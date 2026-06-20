#pragma once
#include "../std.hpp"

namespace src::generic {

template <typename T>
size_t exponential_choice(const std::vector<T> &v, float exponent) {

  // leave these function-internal variables static to reuse them if v.size()
  // doesn't change between multiple executions
  static std::vector<size_t> probability_density(v.size());
  static std::mt19937 rng{std::random_device{}()};
  static std::uniform_real_distribution<float> dist(0.f, 1.0f);

  // refresh the probability density if v.size() does change
  if (v.size() != probability_density.size()) {
    probability_density = std::vector<size_t>(v.size());
    float sum = 0;
    for (size_t i = 0; i < v.size(); i++) {
      probability_density[i] = exp(-i * exponent);
      sum += probability_density[i];
    }

    for (size_t i = 0; i < v.size(); i++) {
      probability_density[i] /= sum;
    }
  }

  float r = dist(rng);
  float cumulative = 0;
  for (size_t i = 0; i < v.size(); i++) {
    if (cumulative + probability_density[i] >= r) {
      return i;
    } else {
      cumulative += probability_density[i];
    }
  }
  return v.size() - 1;
}

}; // namespace src::generic