#include <cassert>
#include <string>
#include <cmath>
#include "math/config.h"
#include "simulation/lbm_simulator.h"

int main() {
    lbm::SimulationConfig cfg;
    cfg.width = 64;
    cfg.height = 32;
    cfg.tau = 0.56;
    cfg.stepsPerFrame = 1;
    std::string err;
    assert(cfg.validate(err));
    lbm::LBMSimulator sim;
    assert(sim.initialize(cfg));
    sim.setBodyForce(lbm::Vector2D{1e-8, 0.0});
    for (int i = 0; i < 3000; ++i) sim.step();
    double H = static_cast<double>(cfg.height - 2);
    double l2 = 0.0, l2ref = 0.0;
    double umax = 0.0;
    for (int y = 1; y < cfg.height - 1; ++y) {
        double u = 0.0;
        for (int x = 0; x < cfg.width; ++x) u += sim.grid().velocity(x,y).x;
        u /= static_cast<double>(cfg.width);
        if (u > umax) umax = u;
    }
    for (int y = 1; y < cfg.height - 1; ++y) {
        double yy = static_cast<double>(y - 1) + 0.5;
        double eta = (2.0 * yy / H) - 1.0;
        double uRef = 1.0 - (eta * eta);
        double u = 0.0;
        for (int x = 0; x < cfg.width; ++x) u += sim.grid().velocity(x,y).x;
        u /= static_cast<double>(cfg.width);
        double du = (u/umax) - uRef;
        l2 += du * du;
        l2ref += uRef * uRef;
    }
    double errRel = std::sqrt(l2 / l2ref);
    assert(errRel < 0.2);
    return 0;
}
