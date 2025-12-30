#pragma once

namespace lbm::utils {

struct Profiler {
    double tCollisionMs = 0.0;
    double tBoundaryMs = 0.0;
    double tStreamingMs = 0.0;
    double tRenderMs = 0.0;
};

}

