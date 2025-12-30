#pragma once
#include "simulation/grid.h"
#include "math/vector.h"

namespace lbm::ui {

class Visualization {
public:
    void initialize(int w, int h);
    double averageDensity(const lbm::LBMGrid& g) const;
    double averageSpeed(const lbm::LBMGrid& g) const;
};

}

