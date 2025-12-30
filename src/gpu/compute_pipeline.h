#pragma once
#include <string>
#include <vector>
#include "gpu/buffer_manager.h"

namespace lbm::gpu {

class ComputePipeline {
public:
    bool initialize(void* device, void* queue, const std::string& shaderCode, const std::string& entryPoint);
    bool setupBindGroup(const std::vector<BufferManager::BufferId>& bufferIds);
    bool dispatch(unsigned int gx, unsigned int gy);

private:
    bool initialized = false;
    std::string shader;
    std::string entry;
    std::vector<BufferManager::BufferId> bound;
};

}

