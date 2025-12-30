#include <cassert>
#include <string>
#include <cmath>
#include "math/config.h"
#include "simulation/lbm_simulator.h"

int main() {
    lbm::SimulationConfig cfg;
    std::string err;
    assert(cfg.validate(err) && err.empty());

    cfg.tau = 0.5;
    assert(!cfg.validate(err));
    cfg.tau = 0.6;
    cfg.width = 513;
    assert(!cfg.validate(err));
    cfg.width = 512;
    cfg.workgroupX = 16;
    assert((512 % 16) == 0);
    assert(cfg.validate(err));
    cfg.tau = 0.56;
    cfg.stepsPerFrame = 0;
    assert(!cfg.validate(err));
    cfg.stepsPerFrame = 1;

    cfg.width = 64;
    cfg.height = 32;
    assert(cfg.validate(err));
    lbm::LBMSimulator sim;
    assert(sim.initialize(cfg));
    sim.setBodyForce(lbm::Vector2D{0.0, 0.0});
    sim.step();
    double avgRho = 0.0;
    for (int y = 0; y < cfg.height; ++y)
        for (int x = 0; x < cfg.width; ++x)
            avgRho += sim.grid().density(x,y);
    avgRho /= static_cast<double>(cfg.width * cfg.height);
    assert(std::isfinite(avgRho));
    auto v = sim.grid().velocity(cfg.width/2, cfg.height/2);
    assert(std::isfinite(v.x) && std::isfinite(v.y));
    return 0;
}
