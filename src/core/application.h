#pragma once
#include "math/config.h"
#include "simulation/lbm_simulator.h"
#include "gpu/gpu_context.h"
#include "gpu/renderer.h"
#include "ui/input_handler.h"
#include "ui/visualization.h"
#include "utils/timer.h"
#include "utils/profiler.h"
#include "utils/logger.h"
#include "gpu/buffer_manager.h"

namespace lbm::core {

class Application {
public:
    bool initialize();
    void run();
    void shutdown();
private:
    lbm::SimulationConfig cfg;
    lbm::gpu::GPUContext ctx;
    lbm::LBMSimulator sim;
    lbm::gpu::Renderer renderer;
    lbm::ui::InputHandler input;
    lbm::ui::Visualization viz;
    lbm::utils::Profiler prof;
    lbm::utils::Logger log;
    lbm::gpu::BufferManager buffers;
};

}

