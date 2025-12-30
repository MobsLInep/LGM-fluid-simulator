#pragma once
#include <string>

namespace lbm {

struct SimulationConfig {
    int width = 512;
    int height = 512;
    double tau = 0.6;
    double nu = 0.1; // kinematic viscosity
    double dt = 1.0;
    double dx = 1.0;
    int workgroupX = 8;
    int workgroupY = 8;
    int stepsPerFrame = 1;

    bool validate(std::string& error) const {
        if (width <= 0 || height <= 0) { error = "invalid grid size"; return false; }
        if (tau <= 0.5) { error = "tau must be > 0.5"; return false; }
        if (workgroupX <= 0 || workgroupY <= 0) { error = "invalid workgroup"; return false; }
        if (width % workgroupX != 0 || height % workgroupY != 0) { error = "grid not divisible by workgroup"; return false; }
        if (stepsPerFrame <= 0) { error = "stepsPerFrame must be > 0"; return false; }
        error.clear();
        return true;
    }
};

}
