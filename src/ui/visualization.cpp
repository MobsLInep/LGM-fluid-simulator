#include "ui/visualization.h"

namespace lbm::ui {

void Visualization::initialize(int, int) {}

double Visualization::averageDensity(const lbm::LBMGrid& g) const {
    double sum = 0.0;
    for (int y = 0; y < g.height(); ++y)
        for (int x = 0; x < g.width(); ++x)
            sum += g.density(x,y);
    return sum / static_cast<double>(g.width() * g.height());
}

double Visualization::averageSpeed(const lbm::LBMGrid& g) const {
    double sum = 0.0;
    for (int y = 0; y < g.height(); ++y)
        for (int x = 0; x < g.width(); ++x) {
            auto u = g.velocity(x,y);
            sum += u.magnitude();
        }
    return sum / static_cast<double>(g.width() * g.height());
}

}

