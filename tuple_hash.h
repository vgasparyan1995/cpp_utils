#pragma once

// A generic hash function for std::tuple.
//
// A template specialization of std::hash for std::tuple of any types that uses
// std::hash for each component and XOR to cobine them.

template <typename... Ts>
struct std::hash<std::tuple<Ts...>> {
  size_t operator()(const std::tuple<Ts...>& t) const noexcept {
    return std::apply(
        [](const Ts&... val) { return (std::hash<Ts>{}(val) ^ ...); }, t);
  }
};
