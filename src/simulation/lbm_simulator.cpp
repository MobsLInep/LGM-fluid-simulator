#include "simulation/lbm_simulator.h"
#include <algorithm>
#include <cmath>
#include <iostream>
#include "utils/timer.h"

namespace lbm {

bool LBMSimulator::initialize(const SimulationConfig& cfg) {
    config = cfg;
    config.tau = (config.tau > 0.5)
        ? config.tau
        : 0.5 + 3.0 * config.nu * config.dt / (config.dx * config.dx);
    g = LBMGrid(cfg.width, cfg.height);
    g.initialize(1.0, Vector2D{0.0, 0.0});
    for (int x = 0; x < cfg.width; ++x) {
        g.setWall(x, 0, true);
        g.setWall(x, cfg.height - 1, true);
    }
    return true;
}

void LBMSimulator::setBodyForce(const Vector2D& f) { force = f; }

void LBMSimulator::collide() {
    double tau = config.tau;
    clampNegThisFrame = 0;
    clampNonFiniteThisFrame = 0;
    for (int y = 0; y < g.height(); ++y) {
        for (int x = 0; x < g.width(); ++x) {
            if (g.isWall(x,y)) {
                for (int k = 0; k < 9; ++k) {
                    std::size_t id = static_cast<std::size_t>(((y * g.width()) + x) * 9 + k);
                    g.fB[id] = g.fA[id];
                }
                continue;
            }
            double rho = 0.0;
            for (int k = 0; k < 9; ++k) {
                std::size_t idk = static_cast<std::size_t>(((y * g.width()) + x) * 9 + k);
                rho += g.fA[idk];
            }
            Vector2D u{0.0,0.0};
            for (int k = 0; k < 9; ++k) {
                std::size_t id = static_cast<std::size_t>(((y * g.width()) + x) * 9 + k);
                u.x += g.fA[id] * c[k].x;
                u.y += g.fA[id] * c[k].y;
            }
            u.x /= rho;
            u.y /= rho;
            double uu = u.dot(u);
            for (int k = 0; k < 9; ++k) {
                double cu = c[k].dot(u);
                double feq = w[k] * rho * (1.0 + 3.0 * cu / cs2 + 4.5 * (cu * cu) / (cs2 * cs2) - 1.5 * uu / cs2);
                std::size_t id = static_cast<std::size_t>(((y * g.width()) + x) * 9 + k);
                double fin = g.fA[id];
                double ci_dot_F = c[k].x * force.x + c[k].y * force.y;
                double forcing = w[k] * (3.0 / cs2) * ci_dot_F;
                double out = fin - (fin - feq) / tau + forcing;
                if (!std::isfinite(out)) { out = feq; ++clampCount; ++clampNonFiniteThisFrame; }
                else if (out < 0.0) { out = feq; ++clampCount; ++clampNegThisFrame; }
                if (x == diagX && y == diagY) {
                    diagRho = rho;
                    diagU = u;
                    diagFeq[k] = feq;
                    diagFout[k] = out;
                    diagFin[k] = fin;
                }
                g.fB[id] = out;
            }
        }
    }
}

void LBMSimulator::applyBoundary() {
    for (int y = 0; y < g.height(); ++y) {
        for (int x = 0; x < g.width(); ++x) {
            if (!g.isWall(x,y)) continue;
            for (int k = 0; k < 9; ++k) {
                std::size_t id = static_cast<std::size_t>(((y * g.width()) + x) * 9 + k);
                std::size_t idOpp = static_cast<std::size_t>(((y * g.width()) + x) * 9 + opposite[k]);
                if (id < g.fB.size() && idOpp < g.fB.size()) {
                    double t = g.fB[idOpp];
                    g.fB[id] = t;
                }
            }
        }
    }
}

void LBMSimulator::stream() {
    std::vector<double> next(g.fA.size());
    for (int y = 0; y < g.height(); ++y) {
        for (int x = 0; x < g.width(); ++x) {
            if (g.isWall(x,y)) {
                for (int k = 0; k < 9; ++k) {
                    std::size_t dst = static_cast<std::size_t>(((y * g.width()) + x) * 9 + k);
                    next[dst] = g.fB[dst];
                }
            } else {
                for (int k = 0; k < 9; ++k) {
                    int nx = x - static_cast<int>(c[k].x);
                    int ny = y - static_cast<int>(c[k].y);
                    if (nx < 0) nx += g.width();
                    if (nx >= g.width()) nx -= g.width();
                    std::size_t dst = static_cast<std::size_t>(((y * g.width()) + x) * 9 + k);
                    if (ny < 0 || ny >= g.height()) {
                        std::size_t idOpp = static_cast<std::size_t>(((y * g.width()) + x) * 9 + opposite[k]);
                        next[dst] = g.fB[idOpp];
                        continue;
                    }
                    if (g.isWall(nx, ny)) {
                        std::size_t idOpp = static_cast<std::size_t>(((y * g.width()) + x) * 9 + opposite[k]);
                        next[dst] = g.fB[idOpp];
                        continue;
                    }
                    std::size_t src = static_cast<std::size_t>(((ny * g.width()) + nx) * 9 + k);
                    next[dst] = g.fB[src];
                }
            }
        }
    }
    g.fA.swap(next);
}

void LBMSimulator::swap() { std::swap(g.fA, g.fB); }

void LBMSimulator::step() {
    for (int s = 0; s < config.stepsPerFrame; ++s) {
        lbm::utils::Timer t1; t1.start();
        collide();
        tC = t1.stopMs();
        lbm::utils::Timer t2; t2.start();
        applyBoundary();
        tB = t2.stopMs();
        lbm::utils::Timer t3; t3.start();
        stream();
        tS = t3.stopMs();
    }
}

void LBMSimulator::uploadToGPU(lbm::gpu::BufferManager& bm) {
    auto id = bm.createBuffer(g.fA.size() * sizeof(double));
    bm.uploadData(id, g.fA.data(), g.fA.size() * sizeof(double));
}

void LBMSimulator::addImpulse(int x, int y, const Vector2D& du) {
    if (x < 0 || y < 0 || x >= g.width() || y >= g.height()) return;
    double rho = g.density(x,y);
    Vector2D u = g.velocity(x,y);
    u += du;
    double uu = u.dot(u);
    for (int k = 0; k < 9; ++k) {
        double cu = c[k].dot(u);
        double feq = w[k] * rho * (1.0 + 3.0 * cu / cs2 + 4.5 * (cu * cu) / (cs2 * cs2) - 1.5 * uu / cs2);
        std::size_t id = static_cast<std::size_t>(((y * g.width()) + x) * 9 + k);
        g.fA[id] = feq;
        g.fB[id] = feq;
    }
}

void LBMSimulator::addObstacle(int cx, int cy, int r) {
    int r2 = r * r;
    for (int y = std::max(0, cy - r); y < std::min(g.height(), cy + r + 1); ++y) {
        for (int x = std::max(0, cx - r); x < std::min(g.width(), cx + r + 1); ++x) {
            int dx = x - cx;
            int dy = y - cy;
            if (dx*dx + dy*dy <= r2) g.setWall(x,y,true);
        }
    }
}

LBMGrid& LBMSimulator::grid() { return g; }

void LBMSimulator::getStageTimes(double& tc, double& tb, double& ts) const { tc = tC; tb = tB; ts = tS; }

std::size_t LBMSimulator::getClampCount() const { return clampCount; }
void LBMSimulator::resetClampCount() { clampCount = 0; }

void LBMSimulator::setDiagnosticCell(int x, int y) { diagX = x; diagY = y; }
void LBMSimulator::getDiagnostic(double& rho, Vector2D& u,
                                 std::array<double,9>& feq,
                                 std::array<double,9>& fout,
                                 std::array<double,9>& fin) const {
    rho = diagRho;
    u = diagU;
    feq = diagFeq;
    fout = diagFout;
    fin = diagFin;
}
void LBMSimulator::getClampBreakdown(std::size_t& neg, std::size_t& nonfinite) const { neg = clampNegThisFrame; nonfinite = clampNonFiniteThisFrame; }
void LBMSimulator::resetClampBreakdown() { clampNegThisFrame = 0; clampNonFiniteThisFrame = 0; }

}
