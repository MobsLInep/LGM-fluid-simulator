#pragma once
#include "simulation/grid.h"

namespace lbm::gpu {

class Renderer {
public:
    bool initialize(int w, int h);
    bool setWindow(void* hwnd);
    void renderFrame(const lbm::LBMGrid& g);
private:
    int W = 0;
    int H = 0;
    void* window = nullptr;
};

}
