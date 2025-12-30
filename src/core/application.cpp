#include "core/application.h"
#include <thread>
#include <chrono>
#include <cassert>
#include <cmath>

namespace lbm::core {

bool Application::initialize() {
    cfg = lbm::SimulationConfig{};
    cfg.tau = 0.5 + 3.0 * cfg.nu * cfg.dt / (cfg.dx * cfg.dx);
    std::string e;
    if (!cfg.validate(e)) return false;
    ctx.initialize(cfg.width, cfg.height, "LBM");
    sim.initialize(cfg);
    renderer.initialize(cfg.width, cfg.height);
    renderer.setWindow(ctx.getWindow());
    viz.initialize(cfg.width, cfg.height);
    sim.setBodyForce(lbm::Vector2D{0.0, 0.0});
    return true;
}

void Application::run() {
    int frames = 200;
    const double cells = static_cast<double>(cfg.width * cfg.height);
    double stepsTotal = 0.0;
    lbm::utils::Timer simTimer;
    simTimer.start();
    for (int f = 0; f < frames; ++f) {
        lbm::utils::Timer t;
        t.start();
        if (f == 10) { sim.addImpulse(cfg.width/2, cfg.height/2, lbm::Vector2D{1e-6, 0.0}); }
        if (f == 0) { sim.setDiagnosticCell(cfg.width/2, cfg.height/2); }
        sim.step();
        
        stepsTotal += cfg.stepsPerFrame;
        double tc, tb, ts;
        sim.getStageTimes(tc, tb, ts);
        prof.tCollisionMs += tc;
        prof.tBoundaryMs += tb;
        prof.tStreamingMs += ts;
        double upd = t.stopMs();
        lbm::utils::Timer tr;
        tr.start();
        renderer.renderFrame(sim.grid());
        prof.tRenderMs += tr.stopMs();
        double minRho = std::numeric_limits<double>::infinity();
        double maxRho = -std::numeric_limits<double>::infinity();
        double sumRho = 0.0;
        double maxU = 0.0;
        for (int y = 0; y < cfg.height; ++y) {
            for (int x = 0; x < cfg.width; ++x) {
                double rho = sim.grid().density(x,y);
                auto u = sim.grid().velocity(x,y);
                double umag = u.magnitude();
                if (rho < minRho) minRho = rho;
                if (rho > maxRho) maxRho = rho;
                sumRho += rho;
                if (umag > maxU) maxU = umag;
            }
        }
        double avgRho = sumRho / static_cast<double>(cfg.width * cfg.height);
        if (!std::isfinite(avgRho) || !std::isfinite(maxU)) {
            log.info("nonfinite values detected");
        }
        if (f >= 100) {
            if (!(minRho >= 0.99 && maxRho <= 1.01)) {
                log.info("rho_out_of_bounds ", minRho, " ", maxRho);
            }
            if (!(maxU <= 0.1)) {
                log.info("uMax_out_of_bounds ", maxU);
            }
        }
        auto cc = sim.getClampCount();
        std::size_t cneg=0, cnan=0; sim.getClampBreakdown(cneg, cnan);
        if (cc > 0) log.info("clamp ", cc, " neg ", cneg, " nonfinite ", cnan);
        sim.resetClampCount();
        sim.resetClampBreakdown();
        double crho; lbm::Vector2D cu; std::array<double,9> feq, fout, fin;
        sim.getDiagnostic(crho, cu, feq, fout, fin);
        double mass = 0.0; double mux = 0.0; double muy = 0.0;
        for (int k = 0; k < 9; ++k) { mass += fout[k]; mux += fout[k] * c[k].x; muy += fout[k] * c[k].y; }
        log.info("cell ", cfg.width/2, ",", cfg.height/2, " rho ", crho, " ux ", cu.x, " uy ", cu.y);
        log.info("feq ", feq[0], ",", feq[1], ",", feq[2], ",", feq[3], ",", feq[4], ",", feq[5], ",", feq[6], ",", feq[7], ",", feq[8]);
        log.info("fout ", fout[0], ",", fout[1], ",", fout[2], ",", fout[3], ",", fout[4], ",", fout[5], ",", fout[6], ",", fout[7], ",", fout[8]);
        log.info("mass ", mass, " rho_target ", crho);
        log.info("mom ", mux, ",", muy, " target ", crho * cu.x, ",", crho * cu.y);
        log.info("frame ", f, " update ", upd, " c ", tc, " b ", tb, " s ", ts, " rho ", avgRho, " uMax ", maxU);
        ctx.pump();
    }
    double totalMs = simTimer.stopMs();
    double mlups = (cells * stepsTotal) / ( (totalMs/1000.0) * 1e6);
    log.info("MLUPS ", mlups);
}

void Application::shutdown() {}

}
