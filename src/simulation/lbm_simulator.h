#pragma once
#include "math/config.h"
#include "simulation/grid.h"
#include "gpu/buffer_manager.h"
#include "gpu/gpu_context.h"
#include "gpu/compute_pipeline.h"

namespace lbm {

class LBMSimulator {
public:
    bool initialize(const SimulationConfig& cfg);
    void step();
    void uploadToGPU(lbm::gpu::BufferManager& bm);
    void addImpulse(int x, int y, const Vector2D& du);
    void addObstacle(int cx, int cy, int r);
    LBMGrid& grid();
    void setBodyForce(const Vector2D& f);
    void getStageTimes(double& tc, double& tb, double& ts) const;
    std::size_t getClampCount() const;
    void resetClampCount();
    void setDiagnosticCell(int x, int y);
    void getDiagnostic(double& rho, Vector2D& u,
                       std::array<double,9>& feq,
                       std::array<double,9>& fout,
                       std::array<double,9>& fin) const;
    void getClampBreakdown(std::size_t& neg, std::size_t& nonfinite) const;
    void resetClampBreakdown();

private:
    SimulationConfig config;
    LBMGrid g;
    Vector2D force{0.0, 0.0};
    double tC = 0.0;
    double tB = 0.0;
    double tS = 0.0;
    std::size_t clampCount = 0;
    std::size_t clampNegThisFrame = 0;
    std::size_t clampNonFiniteThisFrame = 0;
    int diagX = -1;
    int diagY = -1;
    double diagRho = 0.0;
    Vector2D diagU{0.0,0.0};
    std::array<double,9> diagFeq{};
    std::array<double,9> diagFout{};
    std::array<double,9> diagFin{};

    void collide();
    void applyBoundary();
    void stream();
    void swap();
};

}
