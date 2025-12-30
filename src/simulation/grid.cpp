#include "simulation/grid.h"
#include <algorithm>

namespace lbm {

LBMGrid::LBMGrid(int w, int h) : W(w), H(h), fA(static_cast<std::size_t>(w*h*9), 0.0), fB(static_cast<std::size_t>(w*h*9), 0.0), is_wall(static_cast<std::size_t>(w*h), 0) {}

void LBMGrid::initialize(double rho0, const Vector2D& u0) {
    for (int y = 0; y < H; ++y) {
        for (int x = 0; x < W; ++x) {
            double uu = u0.dot(u0);
            for (int k = 0; k < 9; ++k) {
                double cu = c[k].dot(u0);
                double feq = w[k] * rho0 * (1.0 + 3.0 * cu / cs2 + 4.5 * (cu * cu) / (cs2 * cs2) - 1.5 * uu / cs2);
                fA[idx(x,y,k)] = feq;
                fB[idx(x,y,k)] = feq;
            }
        }
    }
}

void LBMGrid::setWall(int x, int y, bool wall) {
    if (x < 0 || y < 0 || x >= W || y >= H) return;
    is_wall[static_cast<std::size_t>(y*W + x)] = wall ? 1 : 0;
}

const std::vector<double>& LBMGrid::getDistributions() const { return fA; }

double LBMGrid::density(int x, int y) const {
    double rho = 0.0;
    for (int k = 0; k < 9; ++k) {
        std::size_t id = idx(x,y,k);
        if (id < fA.size()) rho += fA[id];
    }
    return rho;
}

Vector2D LBMGrid::velocity(int x, int y) const {
    double rho = density(x,y);
    Vector2D u{0.0, 0.0};
    if (rho <= 0.0) return u;
    for (int k = 0; k < 9; ++k) {
        std::size_t id = idx(x,y,k);
        if (id < fA.size()) {
            u.x += fA[id] * c[k].x;
            u.y += fA[id] * c[k].y;
        }
    }
    u.x /= rho;
    u.y /= rho;
    return u;
}

bool LBMGrid::isWall(int x, int y) const { return is_wall[static_cast<std::size_t>(y*W + x)] != 0; }
int LBMGrid::width() const { return W; }
int LBMGrid::height() const { return H; }

std::size_t LBMGrid::idx(int x, int y, int k) const { return static_cast<std::size_t>(((y * W) + x) * 9 + k); }

}
