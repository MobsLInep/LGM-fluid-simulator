#pragma once
#include <array>
#include "math/vector.h"

namespace lbm {

inline constexpr double cs2 = 1.0 / 3.0;
inline constexpr std::array<double, 9> w = {4.0 / 9.0,
                                             1.0 / 9.0, 1.0 / 9.0, 1.0 / 9.0, 1.0 / 9.0,
                                             1.0 / 36.0, 1.0 / 36.0, 1.0 / 36.0, 1.0 / 36.0};

inline constexpr std::array<Vector2D, 9> c = {
    Vector2D{0.0, 0.0},
    Vector2D{1.0, 0.0}, Vector2D{0.0, 1.0}, Vector2D{-1.0, 0.0}, Vector2D{0.0, -1.0},
    Vector2D{1.0, 1.0}, Vector2D{-1.0, 1.0}, Vector2D{-1.0, -1.0}, Vector2D{1.0, -1.0}
};

inline constexpr std::array<int, 9> opposite = {0, 3, 4, 1, 2, 7, 8, 5, 6};

}

