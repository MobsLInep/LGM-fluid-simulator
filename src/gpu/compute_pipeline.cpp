#include "gpu/compute_pipeline.h"

namespace lbm::gpu {

bool ComputePipeline::initialize(void* device, void* queue, const std::string& shaderCode, const std::string& entryPoint) {
    shader = shaderCode;
    entry = entryPoint;
    initialized = true;
    return true;
}

bool ComputePipeline::setupBindGroup(const std::vector<BufferManager::BufferId>& bufferIds) {
    if (!initialized) return false;
    bound = bufferIds;
    return true;
}

bool ComputePipeline::dispatch(unsigned int gx, unsigned int gy) {
    if (!initialized) return false;
    return gx > 0 && gy > 0;
}

}

