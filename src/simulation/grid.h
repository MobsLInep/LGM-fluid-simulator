#pragma once
#include <vector>
#include <cstddef>
#include <cstdint>
#include "math/vector.h"
#include "math/constants.h"

namespace lbm {

class LBMGrid {
public:
    LBMGrid() = default;
    LBMGrid(int w, int h);
    void initialize(double rho0, const Vector2D& u0);
    void setWall(int x, int y, bool wall);
    const std::vector<double>& getDistributions() const;
    double density(int x, int y) const;
    Vector2D velocity(int x, int y) const;
    bool isWall(int x, int y) const;
    int width() const;
    int height() const;

    std::vector<double> fA;
    std::vector<double> fB;
    std::vector<uint8_t> is_wall;

private:
    int W = 0;
    int H = 0;
    std::size_t idx(int x, int y, int k) const;
};

}
