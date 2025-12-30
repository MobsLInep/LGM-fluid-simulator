#pragma once
#include <string>

namespace lbm::gpu {

class GPUContext {
public:
    bool initialize(int w, int h, const std::string& title);
    bool isRunning() const;
    void* getDevice() const;
    void* getQueue() const;
    void* getWindow() const;
    bool pump();

private:
    int width = 0;
    int height = 0;
    bool running = false;
    void* device = nullptr;
    void* queue = nullptr;
    void* window = nullptr;
};

}
